import { defineStore } from 'pinia';
import { useQuasar } from 'quasar';
import eventBus, { EventType, EventData } from 'src/service/event.bus';

export const useMessageStore = defineStore('message', {
  state: () => {
    const q = useQuasar();

    eventBus.getData().subscribe((event: EventData) => {
      if (!event.data!['message'] && event.data!['message'] == '') return;
      if (event.type == EventType.EVENT_MESSAGE_ERROR) {
        q.notify({
          type: 'negative',
          message: event.data!['message'],
          timeout: event.data!['timeout'] || 2000,
        });
      }
      if (event.type == EventType.EVENT_MESSAGE_SUCCESS) {
        q.notify({
          type: 'positive',
          message: event.data!['message'],
          timeout: event.data!['timeout'] || 2000,
        });
      }
    });
    return {
      q,
    };
  },
  actions: {
    error(message: string, timeout = 2000) {
      this.q.notify({
        type: 'negative',
        message: message,
        timeout,
      });
    },
    success(message: string, timeout = 2000) {
      this.q.notify({
        type: 'positive',
        message: message,
        timeout,
      });
    },
  },
});
