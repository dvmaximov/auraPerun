import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';
import { ProgramItems } from './program-item.entity';

@Entity({ name: 'program' })
export class Program {
  @PrimaryGeneratedColumn()
  id?: number;

  @Column({
    name: 'name',
    type: 'text',
    length: 100,
    default: 'не задано',
    unique: true,
  })
  name?: string;

  @Column({ name: 'musik', type: 'text', default: '' })
  musik?: string;

  @Column({ name: 'items', type: 'text', nullable: false })
  items?: string;

  pureItems?: ProgramItems;
}
