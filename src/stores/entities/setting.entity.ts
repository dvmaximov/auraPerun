import { Entity, Column, PrimaryColumn } from 'typeorm';

export enum SettingType {
  SETTING_EMPTY,
  SETTING_NAME,
  SETTING_HAVE_MUSIK,
}
export const SettingIDs = [
  SettingType.SETTING_EMPTY,
  SettingType.SETTING_NAME,
  SettingType.SETTING_HAVE_MUSIK,
];
export const SettingNames = ['empty', 'Имя устройства', 'Наличие музыки'];
export const SettingFieldTypes = ['string', 'string', 'boolean'];
export const SettingDefaulValues = ['', 'aura008', 'false'];

@Entity({ name: 'setting' })
export class Setting {
  @PrimaryColumn({ name: 'id', type: 'int', unique: true })
  id?: number;

  @Column({ name: 'name', type: 'text', length: 20, default: '', unique: true })
  name?: string;

  @Column({ name: 'settingFieldType', type: 'text', length: 20, default: '' })
  settingFieldType?: string;

  @Column({ name: 'value', type: 'text', length: 20, default: '' })
  value?: string;
}
