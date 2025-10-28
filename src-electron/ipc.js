import { ipcMain } from 'electron';
import path from 'path';
import {
  deviceRepository,
  settingRepository,
  programRepository,
} from './database/data.source';
import { Program } from 'src/stores/entities/program.entity';
import { Device } from 'src/stores/entities/device.entity';
import { copyFile } from 'node:fs/promises';
import { dialog } from 'electron';
import { MusikWatcher } from './musik-watcher';

const portableDir = `${process.env.PORTABLE_EXECUTABLE_DIR}${path.sep}`;
const musikDir = process.env.DEBUGGING
  ? `musik${path.sep}`
  : `${portableDir}musik${path.sep}`;

const cbForWatcher = async (file) => {
  const programs = await programRepository.find();
  for (const program of programs) {
    if (file.includes(program.musik)) {
      program.musik = '';
      await programRepository.save(program);
    }
  }
};

const watcher = new MusikWatcher(musikDir, cbForWatcher);

export const prepareIpc = async () => {
  ipcMain.handle('auraDevice:getProps', async (event, arg) => {
    return {
      dirName: __dirname,
      platform: process.platform || os.platform(),
      dir: process.env.PORTABLE_EXECUTABLE_DIR || '',
      debug: process.env.DEBUGGING,
      portableDir,
      musikDir,
    };
  });

  ipcMain.handle('auraDevice:getFileName', async (event, arg) => {
    const file = await dialog.showOpenDialog({
      properties: ['openFile', 'dontAddToRecent'],
      filters: [{ name: 'Музыка', extensions: ['mp3'] }],
    });
    if (file.canceled) return '';
    return file.filePaths[0];
  });

  ipcMain.handle('auraDevice:copyFile', async (event, arg) => {
    let fileName = arg.split('\\');

    try {
      fileName = fileName.length === 0 ? '' : fileName[fileName.length - 1];
      if (fileName === '') return false;
      await copyFile(arg, `${musikDir}${fileName}`);
      return fileName;
    } catch (e) {
      return false;
    }
  });

  ipcMain.handle('auraDevice:findAllPrograms', async (event, arg) => {
    return await programRepository.find();
  });

  ipcMain.handle('auraDevice:saveProgram', async (event, program) => {
    let res = null;
    if (program.id == 'undefined') {
      const updateProgram = new Program();
      updateProgram.items = program.items;
      updateProgram.name = program.name;
      updateProgram.musik = program.musik;
      res = await programRepository.save(updateProgram);
      return;
    } else {
      res = await programRepository.save(program);
    }
    return res;
  });

  ipcMain.handle('auraDevice:removeProgram', async (event, id) => {
    try {
      await programRepository.delete({ id });
      return true;
    } catch (e) {
      return false;
    }
  });

  ipcMain.handle('auraDevice:findAllSettings', async (event, arg) => {
    return await settingRepository.find();
  });

  ipcMain.handle('auraDevice:saveSetting', async (event, setting) => {
    return await settingRepository.save(setting);
  });

  ipcMain.handle('auraDevice:findAllDevices', async (event, arg) => {
    return await deviceRepository.find();
  });

  ipcMain.handle('auraDevice:saveDevice', async (event, device) => {
    delete device.isActive;
    let res = null;
    const updateDevice = await deviceRepository.findOneBy({ id: device.id });
    if (updateDevice) {
      updateDevice.ip = device.ip;
      res = await deviceRepository.save(updateDevice);
      return;
    } else {
      res = await deviceRepository.save(device);
    }
    return res;
  });

  ipcMain.handle('auraDevice:clearDevices', async (event, _) => {
    let devices = await deviceRepository.find();
    for (const device of devices) {
      await deviceRepository.remove(device);
    }
  });
};
