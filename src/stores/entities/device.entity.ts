import { Entity, Column, PrimaryColumn } from 'typeorm';

@Entity({ name: 'device' })
export class Device {
  @PrimaryColumn({ name: 'id', type: 'int', unique: true })
  id?: number;

  @Column({ name: 'ip', type: 'text', length: 20, default: '', unique: true })
  ip?: string;

  isActive?: boolean = false;
}
