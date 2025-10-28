import { defineStore, storeToRefs } from 'pinia';
import { ref } from 'vue';
import { Program } from 'src/stores/entities/program.entity';
import {
  ProgramItems,
  ProgramItem,
  getDefaultItem,
} from './entities/program-item.entity';
import eventBus, { EventType } from 'src/service/event.bus';
import { SUCCESS_CODES } from 'src/service/success.codes';
import { useDeviceStore } from './device.store';
import { ERROR_CODES } from 'src/service/error.codes';

function compare(a: ProgramItem, b: ProgramItem) {
  if (!a || !b) return 0;
  if (!a.device_id || !b.device_id) return 0;
  if (a.device_id < b.device_id) {
    return -1;
  }
  if (a.device_id > b.device_id) {
    return 1;
  }
  return 0;
}

export const useProgramStore = defineStore('program', {
  state: () => {
    const programs = ref<Program[]>([]);

    const deviceStore = useDeviceStore();
    const { devices } = storeToRefs(deviceStore);
    window['auraDevice'].findAllPrograms().then((data: any) => {
      programs.value = data;
      for (let i = 0; i < programs.value.length; i++) {
        programs.value[i].pureItems = JSON.parse(programs.value[i].items!);
      }
    });
    return {
      programs,
      devices,
    };
  },
  getters: {
    isEmpty: (state) => state.programs.length === 0,
    programList:
      (state) =>
      (searchByName: string): Program[] => {
        if (searchByName === '') return state.programs;
        return state.programs.filter((program: Program) =>
          program.name?.includes(searchByName)
        );
      },
  },
  actions: {
    async insert(newName: string) {
      if (this.devices.length === 0) {
        eventBus.sendData({
          type: EventType.EVENT_MESSAGE_ERROR,
          data: { message: SUCCESS_CODES.DEVICES_EMPTY },
        });
        return;
      }
      const items: ProgramItems = [];
      const newProgram = new Program();
      for (const device of this.devices) {
        const item = getDefaultItem(device.id!);
        items.push(item);
      }

      newProgram.name = newName;
      newProgram.musik = '';
      newProgram.items = JSON.stringify(items);
      newProgram.pureItems = items;
      try {
        const resp = await window['auraDevice'].saveProgram(newProgram);
        if (resp !== 'undefined') this.programs.push(resp);
      } catch (_) {
        eventBus.sendData({
          type: EventType.EVENT_MESSAGE_ERROR,
          data: { message: ERROR_CODES.PROGRAM_EXISTS },
        });
      }
    },
    async synchronize(program: Program) {
      const items = [...program.pureItems!];
      const itemDeviceIDS = items.map((item) => item.device_id);
      for (const device of this.devices) {
        if (!itemDeviceIDS.includes(device.id)) {
          const item = getDefaultItem(device.id!);
          items.push(item);
          items.sort(compare);
          await window['auraDevice'].saveProgram({
            ...program,
            items: JSON.stringify(items),
            pureItems: null,
          });
          this.programs = this.programs.map((value) => {
            if (value.id === program.id) {
              return {
                ...value,
                pureItems: items,
                items: JSON.stringify(items),
              };
            } else return value;
          });
        }
      }
    },
    synchronizeDone() {
      eventBus.sendData({
        type: EventType.EVENT_MESSAGE_SUCCESS,
        data: { message: SUCCESS_CODES.PROGRAM_SYNCHRONIZE_DONE },
      });
    },
    async update(program: Program) {
      if (program.name === '') {
        eventBus.sendData({
          type: EventType.EVENT_MESSAGE_ERROR,
          data: { message: ERROR_CODES.PROGRAM_NULLNAME },
        });
        return;
      }
      const newProgram: Program = {
        id: program.id,
        items: JSON.stringify(program.pureItems),
        musik: program.musik,
        name: program.name,
      };
      const resp = await window['auraDevice'].saveProgram(newProgram);
      if (resp !== 'undefined') {
        resp.pureItems = program.pureItems;
        this.programs = this.programs.map((value) => {
          return value.id === resp.id ? resp : value;
        });
      }
      eventBus.sendData({
        type: EventType.EVENT_MESSAGE_SUCCESS,
        data: { message: SUCCESS_CODES.PROGRAM_UPDATED },
      });
    },
    async remove(program: Program) {
      if (await window['auraDevice'].removeProgram(program.id)) {
        this.programs = this.programs.filter(
          (value) => value.id !== program.id
        );
        eventBus.sendData({
          type: EventType.EVENT_MESSAGE_SUCCESS,
          data: { message: SUCCESS_CODES.PROGRAM_DELETED },
        });
      }
    },
  },
});
