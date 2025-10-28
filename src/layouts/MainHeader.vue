<template>
  <q-header elevated>
    <q-toolbar class="flex justify-between items-center">
      <q-toolbar-title v-if="$q.screen.gt.xs">
        <div class="flex justify-between logo">
          <div class="q-mr-md">
            {{ productName }}
          </div>
          <div>
            {{ version }}
          </div>
        </div>
      </q-toolbar-title>
      <div class="flex items-center q-mr-xl">
        <div
          v-for="device in devices"
          :key="device.id"
          class="device items-center justify-center q-ml-xs"
          :class="{ device__active: device.isActive }"
        >
          {{ device.id }}
        </div>
      </div>
      <nav>
        <q-btn
          outline
          rounded
          class="link q-ml-xs"
          label="Терапия"
          @click="router.push('/')"
        />
        <q-btn
          outline
          rounded
          class="link q-ml-xs"
          label="Программы"
          @click="router.push('/programs')"
        />
        <q-btn
          outline
          rounded
          class="link q-ml-xs"
          label="Устройства"
          @click="router.push('/devices')"
        />
      </nav>
    </q-toolbar>
  </q-header>
</template>

<script setup lang="ts">
import { onMounted, onUnmounted } from 'vue';
import { storeToRefs } from 'pinia';
import { useQuasar } from 'quasar';
import { useRouter } from 'vue-router';
import { useDeviceStore } from 'src/stores/device.store';
import { productName, version } from '../../package.json';

const $q = useQuasar();
const store = useDeviceStore();
const router = useRouter();
const { devices } = storeToRefs(store);

let timer: ReturnType<typeof setInterval> = setInterval(async () => {
  await store.checkAllIP();
}, 5000);

onMounted(async () => {
  await store.findAll();
  await store.checkAllIP();
});

onUnmounted(() => {
  clearInterval(timer);
});
</script>

<style lang="scss" scoped>
.device {
  display: inline-flex;
  border-radius: 50%;
  width: 20px;
  height: 20px;
  background-color: $no-active;
}
.device__active {
  background-color: $active;
}
.link {
  color: $link;
  background-color: $link;
}
.logo {
  width: 15%;
  flex-wrap: nowrap;
}
</style>
