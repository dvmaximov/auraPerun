<template>
  <q-btn
    color="primary"
    :label="isScannerShow ? 'Скрыть сканер' : 'Показать сканер'"
    @click="toggle"
  />
  <div class="flex justify-start items-center q-mt-md" v-if="isScannerShow">
    <q-input
      filled
      v-model="startIP"
      label="Стартовый IP"
      mask="###.###.#.###"
      autofocus
      class="ip q-mr-md q-mb-md"
    />
    <q-input
      filled
      v-model="endIP"
      label="Конечный IP"
      mask="###.###.#.###"
      class="ip q-mr-md q-mb-md"
    />
    <q-btn
      color="primary"
      :label="isScanStarted ? 'Стоп' : 'Старт'"
      @click="scan"
      class="q-mb-md"
    />
    <div
      class="flex justify-center items-center ip--scan q-mx-md q-mb-md q-px-md"
      v-if="isScanStarted"
    >
      {{ ipForScanner }}
    </div>
  </div>
  <h6 class="q-mb-md text-center" v-if="devices.length === 0">
    Список устройств пуст
  </h6>
  <div v-else>
    <h6 class="full-width q-mb-md text-center">Найденные устройства</h6>
    <div class="flex justify-center full-width">
      <q-virtual-scroll
        :items="devices"
        v-slot="{ item }"
        class="q-pt-md scrool"
      >
        <q-item :key="item.id" dense class="q-mb-sm item">
          <q-item-section class="q-pa-sm">
            <div class="flex justify-between items-center no-wrap q-pl-md">
              <q-avatar
                icon="mdi-developer-board"
                color="primary"
                text-color="white"
              />
              <section class="flex justify-between items-center id">
                <div>id - {{ item.id }}</div>
                <div>ip - {{ item.ip }}</div>
              </section>
              <div
                class="text-bold"
                :class="{ active: item.isActive, 'no-active': !item.isActive }"
              >
                {{ item.isActive ? 'активный' : 'неактивный' }}
              </div>
            </div>
          </q-item-section>
        </q-item>
      </q-virtual-scroll>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { storeToRefs } from 'pinia';
import { useDeviceStore } from 'src/stores/device.store';

const store = useDeviceStore();
const { isScanStarted, devices, ipForScanner } = storeToRefs(store);
const startIP = ref('192.168.1.2');
const endIP = ref('192.168.1.254');
const isScannerShow = ref(false);

const toggle = () => {
  isScannerShow.value = !isScannerShow.value;
};
const scan = async () => {
  if (isScanStarted.value) {
    store.stopScanner();
    return;
  }
  if (startIP.value === '' || endIP.value === '') return;
  await store.runScanner(startIP.value.trim(), endIP.value.trim());
};
</script>

<style lang="scss" scoped>
.ip {
  width: 300px;
}
.item {
  background-color: $bg-info;
  margin-left: 10vw;
  margin-right: 10vw;
}
.scrool {
  height: calc(100vh - 250px);
  border: 1px solid #cbcbcb;
  width: 100%;
}
.ip--scan {
  background-color: $active;
  color: white;
  height: 56px;
}
.id {
  width: 30%;
}
.active,
.no-active {
  width: 15%;
}
.active {
  color: $active;
}
.no-active {
  color: $negative;
}
</style>
