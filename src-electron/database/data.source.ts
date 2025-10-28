import path from 'path';
import { DataSource } from 'typeorm';
import { productName } from '../../package.json';
import { Device } from '../../src/stores/entities/device.entity';
import { Program } from '../../src/stores/entities/program.entity';
import { ProgramItem } from '../../src/stores/entities/program-item.entity';
import {
  Setting,
  SettingNames,
  SettingFieldTypes,
  SettingDefaulValues,
  SettingIDs,
} from '../../src/stores/entities/setting.entity';

const dbName = process.env.DEBUGGING
  ? `${productName}.sqlite`
  : path.resolve(process.env.PORTABLE_EXECUTABLE_DIR!, `${productName}.sqlite`);

export const AppDataSource = new DataSource({
  type: 'sqlite',
  database: dbName,
  synchronize: true,
  logging: false,
  entities: [Setting, Device, Program],
  migrations: [],
  subscribers: [],
});

export const deviceRepository = AppDataSource.getRepository(Device);
export const settingRepository = AppDataSource.getRepository(Setting);
export const programRepository = AppDataSource.getRepository(Program);

export type DataType = Setting | Device | Program;

export const prepareDB = async () => {
  const setDefaultSettings = async () => {
    const newSetting = new Setting();
    for (let i = 1; i <= SettingIDs.length - 1; i++) {
      const setting = await settingRepository.findOneBy({
        id: SettingIDs[i],
      });
      if (!setting) {
        newSetting.id = SettingIDs[i];
        newSetting.name = SettingNames[SettingIDs[i]];
        newSetting.settingFieldType = SettingFieldTypes[SettingIDs[i]];
        newSetting.value = SettingDefaulValues[SettingIDs[i]];
        await settingRepository.save(newSetting);
      }
    }
    const settingDeviceName = await settingRepository.findOneBy({
      id: 1, //Имя устройства (aura008, aura...)
    });

    if (settingDeviceName) {
      settingDeviceName.value = productName;
      await settingRepository.save(settingDeviceName);
    }
  };

  await AppDataSource.initialize();
  const empty = (await settingRepository.find()).length === 0;
  if (empty) {
    await setDefaultSettings();
  }
};
