export class ProgramItem {
  id?: number;
  device_id?: number;
  color0?: string;
  color1?: string;
  color2?: string;
  color3?: string;
  color4?: string;
  color5?: string;
  // externalColor1?: string;
  // internalColor1?: string;
  // centerColor1?: string;
  period0?: number;
  period1?: number;
  period2?: number;
  period3?: number;
  period4?: number;
  period5?: number;
  // externalPeriod1?: number;
  // internalPeriod1?: number;
  // centerPeriod1?: number;
  enable0?: boolean;
  enable1?: boolean;
  enable2?: boolean;
  enable3?: boolean;
  enable4?: boolean;
  enable5?: boolean;
  direction1?: ItemDirection;
  direction2?: ItemDirection;
  direction3?: ItemDirection;
  direction4?: ItemDirection;
  direction5?: ItemDirection;
  // externalDirection1?: ItemDirection;
  // internalDirection1?: ItemDirection;
  blockSize1?: number;
  blockSize2?: number;
  blockSize3?: number;
  blockSize4?: number;
  blockSize5?: number;
}

export type ProgramItems = ProgramItem[];

export enum ItemDirection {
  CLOCKWISE,
  COUNTERCLOCKWISE,
}

export const ItemDirectionName = {
  [ItemDirection.CLOCKWISE]: '',
  [ItemDirection.COUNTERCLOCKWISE]: '',
};

export const ITEMColors = ['#ffffff', '#0000ff', '#ff0000'];

export const getDefaultItem = (device_id: number): ProgramItem => {
  const defaultItem = new ProgramItem();
  defaultItem.device_id = device_id;
  defaultItem.color0 = ITEMColors[0];
  defaultItem.color1 = ITEMColors[1];
  defaultItem.color2 = ITEMColors[2];
  defaultItem.color3 = ITEMColors[1];
  defaultItem.color4 = ITEMColors[2];
  defaultItem.color5 = ITEMColors[1];
  // defaultItem.externalColor1 = ITEMColors[1];
  // defaultItem.internalColor1 = ITEMColors[2];
  // defaultItem.centerColor1 = ITEMColors[0];
  defaultItem.period0 = 1000;
  defaultItem.period1 = 1000;
  defaultItem.period2 = 1000;
  defaultItem.period3 = 1000;
  defaultItem.period4 = 1000;
  defaultItem.period5 = 1000;
  // defaultItem.externalPeriod1 = 1000;
  // defaultItem.internalPeriod1 = 1000;
  // defaultItem.centerPeriod1 = 1000;
  defaultItem.enable0 = true;
  defaultItem.enable1 = true;
  defaultItem.enable2 = true;
  defaultItem.enable3 = true;
  defaultItem.enable4 = true;
  defaultItem.enable5 = true;
  defaultItem.direction1 = ItemDirection.CLOCKWISE;
  defaultItem.direction2 = ItemDirection.COUNTERCLOCKWISE;
  defaultItem.direction3 = ItemDirection.CLOCKWISE;
  defaultItem.direction4 = ItemDirection.COUNTERCLOCKWISE;
  defaultItem.direction5 = ItemDirection.CLOCKWISE;
  // defaultItem.externalDirection1 = ItemDirection.CLOCKWISE;
  // defaultItem.internalDirection1 = ItemDirection.COUNTERCLOCKWISE;
  defaultItem.blockSize1 = 5;
  defaultItem.blockSize2 = 5;
  defaultItem.blockSize3 = 5;
  defaultItem.blockSize4 = 5;
  defaultItem.blockSize5 = 5;

  return defaultItem;
};
