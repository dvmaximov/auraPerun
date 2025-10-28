import { mkdir } from 'node:fs/promises';
import hound from 'hound';

export class MusikWatcher {
  watcher;
  cd;

  constructor(dir, cb) {
    this.musikDir = dir;
    this.cb = cb;
    this.init();
  }

  async init() {
    await mkdir(this.musikDir, { recursive: true });
    this.watcher = hound.watch(this.musikDir);

    this.watcher.on('delete', this.cb);
  }
}
