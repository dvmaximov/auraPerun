import { defineStore, storeToRefs } from 'pinia';
import { v4 as uuidv4 } from 'uuid';
import eventBus, { EventType, EventData } from 'src/service/event.bus';
import { SUCCESS_CODES } from 'src/service/success.codes';
import { Session, Sessions } from './entities/session.entity';
import { Program } from './entities/program.entity';
import { ref } from 'vue';

export const useSessionStore = defineStore('session', {
  state: () => {
    const sessions = [] as Sessions;
    const isStarted = ref(false);
    return { sessions, isStarted };
  },
  getters: {
    isEmpty: (state) => state.sessions.length === 0,
  },
  actions: {
    setIsStarted(value: boolean) {
      this.isStarted = value;
    },
    toSession(program: Program, during: number) {
      try {
        const newSession = new Session();
        newSession.id = uuidv4();
        newSession.program_id = program.id;
        newSession.name = program.name;
        newSession.musik = program.musik;
        newSession.items = program.pureItems;
        newSession.during = during;
        this.sessions.push(newSession);
        eventBus.sendData({
          type: EventType.EVENT_MESSAGE_SUCCESS,
          data: { message: SUCCESS_CODES.SESSION_ADDED },
        });
      } catch (e) {}
    },
    clear() {
      this.sessions = [];
    },
    update(session: Session) {
      this.sessions = this.sessions.map((item) => {
        if (item.id === session.id) return session;
        else return item;
      });
    },
    synchronize(program: Program) {
      this.sessions = this.sessions.map((session) => {
        if (session.program_id === program.id) {
          session.items = program.pureItems;
          session.musik = program.musik;
          session.name = program.name;
        }
        return session;
      });
    },
    delete(id: string) {
      this.sessions = this.sessions.filter((session) => session.id !== id);
      eventBus.sendData({
        type: EventType.EVENT_MESSAGE_SUCCESS,
        data: { message: SUCCESS_CODES.SESSION_DELETED },
      });
    },
  },
});
