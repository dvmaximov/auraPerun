import { defineStore } from 'pinia';
import { ref } from 'vue';
import axios, { AxiosError } from 'axios';
import { productName } from '../../package.json';
import { ERROR_CODES } from 'src/service/error.codes';
import { SUCCESS_CODES } from 'src/service/success.codes';
import eventBus, { EventType } from 'src/service/event.bus';
import { Device } from 'src/stores/entities/device.entity';
import { ProgramItem } from './entities/program-item.entity';

function compare(a: Device, b: Device) {
  if (!a || !b) return 0;
  if (!a.id || !b.id) return 0;
  if (a.id < b.id) {
    return -1;
  }
  if (a.id > b.id) {
    return 1;
  }
  return 0;
}

function checkIpRange(fromIp: string, toIp: string): boolean {
  const from = fromIp.split('.');
  const to = toIp.split('.');
  if (from.length != 4 || to.length != 4) {
    eventBus.sendData({
      type: EventType.EVENT_MESSAGE_ERROR,
      data: { message: ERROR_CODES.WRONGE_IP },
    });
    return false;
  }
  for (let i = 0; i <= 2; i++) {
    if (from[i] != to[i]) {
      eventBus.sendData({
        type: EventType.EVENT_MESSAGE_ERROR,
        data: { message: ERROR_CODES.WRONGE_MASK_IP },
      });
      return false;
    }
  }
  if (parseInt(to[3]) - parseInt(from[3]) < 0) {
    eventBus.sendData({
      type: EventType.EVENT_MESSAGE_ERROR,
      data: { message: ERROR_CODES.WRONGE_RANGE_IP },
    });
    return false;
  }
  return true;
}

function getIpRange(fromIp: string, toIp: string): string[] {
  const result: string[] = [];
  const from = fromIp.split('.');
  const to = toIp.split('.');
  const start = parseInt(from[3]);
  const end = parseInt(to[3]);
  from.pop();
  const subnet = from.join('.');
  for (let i = start; i <= end; i++) {
    result.push(subnet + '.' + i);
  }
  return result;
}

export const useDeviceStore = defineStore('device', {
  state: () => {
    const devices = ref<Device[]>([]);
    const ipForScanner = ref('');
    const isScanStarted = ref(false);

    window['auraDevice'].findAllDevices().then((data: any) => {
      devices.value = data;
    });

    return {
      devices,
      ipForScanner,
      isScanStarted,
    };
  },
  getters: {},
  actions: {
    getIpById(id: number): string {
      for (const device of this.devices) {
        if (device.id === id) {
          return device.ip!;
        }
      }
      return '';
    },
    async start() {
      try {
        for (const device of this.devices) {
          const resp = await axios({
            method: 'get',
            url: `http://${device.ip}/start`,
            signal: AbortSignal.timeout(1000),
          });
          if (resp.status === 200) {
          }
        }
      } catch (e) {}
    },
    async stop() {
      try {
        for (const device of this.devices) {
          const resp = await axios({
            method: 'get',
            url: `http://${device.ip}/stop`,
            signal: AbortSignal.timeout(1000),
          });
          if (resp.status === 200) {
          }
        }
      } catch (e) {}
    },
    async sendSessionItem(item: ProgramItem) {
      const deviceIp = this.getIpById(item.device_id!);
      try {
        const resp = await axios({
          method: 'post',
          url: `http://${deviceIp}/setProgram`,
          data: JSON.stringify(item),
          signal: AbortSignal.timeout(1000),
        });
        if (resp.status === 200) {
        }
      } catch (e) {}
    },
    async checkIP(ip: string): Promise<{ found: boolean; isStarted: boolean }> {
      const result = { found: false, isStarted: false };
      try {
        const resp = await axios({
          method: 'get',
          url: `http://${ip}/check`,
          signal: AbortSignal.timeout(1000),
        });
        if (resp.status === 200) {
          result.found = true;
          result.isStarted = resp.data.started;
        }
      } catch (e) {}
      return result;
    },
    async checkAllIP() {
      for (const [index, device] of this.devices.entries()) {
        if (device.ip) {
          const resp = await this.checkIP(device.ip);
          this.devices[index].isActive = resp.found;
          const isDeviseStarted = resp.isStarted;
          if (!isDeviseStarted && this.devices[index].isActive) {
            eventBus.sendData({
              type: EventType.EVENT_DEVICE_FOUND,
              data: {
                id: this.devices[index].id,
              },
            });
          }
          if (!this.devices[index].isActive) {
            eventBus.sendData({
              type: EventType.EVENT_DEVICE_LOSS,
              data: {
                id: this.devices[index].id,
              },
            });
          }
        }
      }
    },
    async findAll() {
      try {
        this.devices = await window['auraDevice'].findAllDevices();
      } catch (e) {}
    },
    async save(device: Device) {
      const newDevice: Device = {
        id: device.id,
        ip: device.ip,
        isActive: true,
      };
      await window['auraDevice'].saveDevice(newDevice);
    },
    async saveAll() {
      for (const device of this.devices) {
        await this.save(device);
      }
    },
    stopScanner() {
      this.ipForScanner = '';
      this.isScanStarted = false;
    },
    async runScanner(fromIp: string, toIp: string) {
      const isCorrect = checkIpRange(fromIp, toIp);
      if (!isCorrect) return;
      const ipRange = getIpRange(fromIp, toIp);
      if (ipRange.length == 0) return;

      // await window['auraDevice'].clearDevices();
      this.devices = [];
      this.isScanStarted = true;

      for (const ip of ipRange) {
        if (!this.isScanStarted) break;
        this.ipForScanner = ip;
        try {
          const resp = await axios({
            method: 'get',
            url: `http://${ip}/check`,
            signal: AbortSignal.timeout(1500),
          });
          if (resp.status === 200 && resp.data.espName === productName) {
            const device: Device = {
              id: resp.data.espID,
              ip: resp.data.ip,
              isActive: true,
            };
            this.devices.push(device);
          }
        } catch (e) {}
      }
      this.devices.sort(compare);
      await this.saveAll();
      await this.findAll();
      this.stopScanner();
      eventBus.sendData({
        type: EventType.EVENT_MESSAGE_SUCCESS,
        data: { message: SUCCESS_CODES.IP_SCANNER_DONE },
      });
    },
  },
});
