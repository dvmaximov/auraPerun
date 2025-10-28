import { contextBridge, ipcRenderer } from 'electron';

contextBridge.exposeInMainWorld('auraDevice', {
  getProps: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:getProps`, arg);
  },

  getFileName: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:getFileName`, arg);
  },

  copyFile: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:copyFile`, arg);
  },

  saveDevice: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:saveDevice`, arg);
  },

  findAllDevices: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:findAllDevices`, arg);
  },

  clearDevices: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:clearDevices`, arg);
  },

  saveSetting: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:saveSetting`, arg);
  },

  findAllSettings: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:findAllSettings`, arg);
  },

  saveProgram: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:saveProgram`, arg);
  },

  removeProgram: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:removeProgram`, arg);
  },

  findAllPrograms: async (arg: any) => {
    return await ipcRenderer.invoke(`auraDevice:findAllPrograms`, arg);
  },
});
