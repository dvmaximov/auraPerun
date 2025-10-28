import { ProgramItems } from './program-item.entity';

export class Session {
  id?: string;
  program_id?: number;
  name?: string;
  items?: ProgramItems;
  during?: number;
  musik?: string;
}

export type Sessions = Session[];
