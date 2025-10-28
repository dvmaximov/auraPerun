import { AppDataSource } from 'src/service/database/data.source';
import { Device } from 'src/stores/entities/device.entity';

export const save = (record: Device) => {
  console.log(typeof record);
};
