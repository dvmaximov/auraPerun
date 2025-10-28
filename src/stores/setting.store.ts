import { defineStore } from 'pinia';
import { ref } from 'vue';
import { Setting } from 'src/stores/entities/setting.entity';

export const useSettingStore = defineStore('setting', {
  state: () => {
    const settings = ref<Setting[]>([]);
    const portableDir = ref('');
    const musikDir = ref('');

    window['auraDevice'].findAllSettings().then((data: any) => {
      settings.value = data;
    });

    window['auraDevice'].getProps().then((data: any) => {
      portableDir.value = process.env.DEBUGGING ? '' : data.portableDir;
      musikDir.value = data.musikDir;
    });

    return {
      settings,
      portableDir,
      musikDir,
    };
  },
  getters: {},
  actions: {
    // async save(device: Device) {
    //   const newDevice: Device = {
    //     id: device.id,
    //     ip: device.ip,
    //     isActive: true,
    //   };
    //   await window['auraDevice'].saveDevice(newDevice);
    // },
  },
});
