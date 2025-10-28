<template>
  <div class="q-pa-md full-width">
    <h5 class="text-center text-bold">Терапия</h5>
    <div v-if="!isEmpty" class="q-my-md">
      <q-btn
        :label="isStarted ? 'Стоп' : 'Старт'"
        color="secondary"
        @click="run()"
      />
      <q-btn
        label="Очистить"
        color="primary q-ml-md"
        @click="showClearDialog"
      />
      <q-btn
        label="Рестарт"
        :disabled="!isStarted"
        color="primary q-ml-md"
        @click="restart"
      />
    </div>
    <div v-if="isEmpty" class="flex justify-center q-mt-xl">
      <h6>Список пустой</h6>
    </div>
    <q-virtual-scroll
      v-else
      class="scrool q-pt-md"
      :items="sessions"
      v-slot="{ item, index }"
    >
      <q-item :key="item.id" dense class="items-center q-pl-md">
        <q-item-section>
          <div class="flex justify-between items-center no-wrap q-pl-md">
            <q-expansion-item
              group="somegroup"
              header-class="text-primary"
              class="item"
              :class="{ active: item.id === active }"
            >
              <template v-slot:header>
                <q-item-section avatar>
                  <q-avatar
                    icon="mdi-medical-bag"
                    color="primary"
                    text-color="white"
                  />
                </q-item-section>

                <q-item-section>
                  {{ item.name }}
                </q-item-section>

                <q-item-section
                  side
                  v-if="counter === index"
                  class="flext text-h6 text-bold watch"
                >
                  {{ stopwatch }}
                </q-item-section>

                <q-item-section side class="text-bold">
                  {{ item.during }} мин.
                </q-item-section>
              </template>

              <q-card class="item-card">
                <q-card-section>
                  <SessionContent :session="item" />
                </q-card-section>
              </q-card>
            </q-expansion-item>
            <div class="flex justify-center no-wrap q-pr-md">
              <q-btn
                label="Удалить"
                color="accent"
                @click="showDeleteDialog(item.id)"
                class="q-ml-md"
              />
              <q-btn
                label="Изменить"
                class="q-ml-md"
                @click="showUpdateDialog(item)"
              />
            </div>
          </div>
        </q-item-section>
      </q-item>
    </q-virtual-scroll>
  </div>

  <audio ref="audio" loop :src="musik" class="full-width"></audio>

  <CommonDialog ref="deleteSessionDialog" @ok="deleteSession">
    <template v-slot:title>
      <h6>Удалить сессию?</h6>
    </template>
  </CommonDialog>

  <CommonDialog ref="clearSessionDialog" @ok="clear">
    <template v-slot:title>
      <h6>Удалить все сессии?</h6>
    </template>
  </CommonDialog>

  <CommonDialog ref="updateSessionDialog" @ok="updateSession">
    <template v-slot:title>
      <h6>Продолжительность сессии</h6>
    </template>
    <q-separator />
    <template v-slot:content>
      <q-input
        autofocus
        outlined
        v-model="during"
        label="Время в минутах"
        mask="###"
      />
    </template>
  </CommonDialog>
</template>

<script setup lang="ts">
import { ref, onUnmounted } from 'vue';
import { storeToRefs } from 'pinia';
import { useSessionStore } from 'src/stores/session.store';
import { useDeviceStore } from 'src/stores/device.store';
import SessionContent from './SessionContent.vue';
import CommonDialog from 'src/components/CommonDialog.vue';
import { Session } from 'src/stores/entities/session.entity';
import { useSettingStore } from 'src/stores/setting.store';
import eventBus, { EventType, EventData } from 'src/service/event.bus';

const deviceStore = useDeviceStore();
const sessionStore = useSessionStore();
const { sessions, isEmpty, isStarted } = storeToRefs(sessionStore);
const active = ref('');
let timer: ReturnType<typeof setTimeout>;
let counter = 0;
const deleteSessionDialog = ref();
const clearSessionDialog = ref();
const updateSessionDialog = ref();
const during = ref<number>();
const settings = useSettingStore();
const { musikDir } = storeToRefs(settings);
const musik = ref('');
const audio = ref();
let sessionIdToDelete: string;
let sessionToUpdate: Session;

const restart = async () => {
  if (isStarted.value) {
    await sendItems(sessions.value[counter]);
    await deviceStore.start();
  } else {
    await deviceStore.stop();
  }
};

const bus = eventBus.getData().subscribe(async (event: EventData) => {
  if (event.type == EventType.EVENT_DEVICE_FOUND && isStarted.value) {
    await restart();
  }
});

sessionStore.setIsStarted(false);

onUnmounted(async () => {
  bus.unsubscribe();
  if (isStarted.value) {
    await run();
  }
});

const stopwatch = ref('');
let seconds = 0;
let minutes = 0;
let hours = 0;
let interval: NodeJS.Timeout;

const updateStopWatch = () => {
  seconds++;
  if (seconds === 60) {
    minutes++;
    seconds = 0;
  }
  if (minutes === 60) {
    hours++;
    minutes = 0;
  }
  stopwatch.value = `${hours.toString().padStart(2, '0')}:${minutes
    .toString()
    .padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
};

const startStopwatch = () => {
  seconds = 0;
  minutes = 0;
  hours = 0;
  interval = setInterval(updateStopWatch, 1000);
};

const stopStopwatch = () => {
  clearInterval(interval);
  stopwatch.value = '';
  seconds = 0;
  minutes = 0;
  hours = 0;
};

const showClearDialog = () => {
  clearSessionDialog.value!.isShow = true;
};

const showDeleteDialog = (id: string) => {
  sessionIdToDelete = id;
  deleteSessionDialog.value!.isShow = true;
};

const showUpdateDialog = (session: Session) => {
  sessionToUpdate = session;
  during.value = session.during;
  updateSessionDialog.value!.isShow = true;
};

const clear = () => {
  sessionStore.clear();
  clearSessionDialog.value!.isShow = false;
};

const deleteSession = () => {
  sessionStore.delete(sessionIdToDelete);
  deleteSessionDialog.value!.isShow = false;
};

const updateSession = () => {
  sessionToUpdate.during = during.value =
    '' || +during.value! === 0 ? sessionToUpdate.during : +during.value!;
  sessionStore.update(sessionToUpdate);
  updateSessionDialog.value!.isShow = false;
};

const getMusik = (musikName: string) => {
  return `${musikDir.value}${musikName}`;
};

const sendItems = async (session: Session) => {
  for (const item of session.items!) {
    await deviceStore.sendSessionItem(item);
  }
};

const run = async () => {
  const setTimer = () => {
    timer = setTimeout(async () => {
      await deviceStore.stop();
      audio.value.pause();
      stopStopwatch();
      counter++;
      clearTimeout(timer);
      if (counter < sessions.value.length) {
        await sendItems(sessions.value[counter]);
        active.value = sessions.value[counter].id!;
        musik.value = getMusik(sessions.value[counter].musik!);
        startStopwatch();
        setTimer();
        await deviceStore.start();
        audio.value.load();
        audio.value.play();
      } else {
        stopStopwatch();
        isStarted.value = false;
        active.value = '';
        musik.value = '';
      }
    }, sessions.value[counter].during! * 60 * 1000);
  };

  if (sessions.value.length === 0) return;

  if (isStarted.value) {
    clearTimeout(timer);
    stopStopwatch();
    await deviceStore.stop();
    audio.value.pause();
    musik.value = '';
    active.value = '';
    isStarted.value = false;
  } else {
    isStarted.value = true;
    counter = 0;
    active.value = sessions.value[counter].id!;
    musik.value = getMusik(sessions.value[counter].musik!);
    await sendItems(sessions.value[counter]);
    setTimer();
    startStopwatch();
    await deviceStore.start();
    audio.value.load();
    audio.value.play();
  }
};
</script>

<style lang="scss" scoped>
.item {
  background-color: $bg-info;
  width: 70%;
}
.active {
  background-color: $bg-active;
}
.scrool {
  height: calc(100vh - 210px);
  border: 1px solid #cbcbcb;
}
.item-card {
  border: 1px solid #cbcbcb;
}
.watch {
  color: $primary;
  width: 20%;
  align-items: center;
}
</style>
