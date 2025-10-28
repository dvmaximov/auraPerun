<template>
  <!-- Центральный -->
  <q-card class="full-width q-pa-md card items-center">
    <h6 class="q-mb-sm">Центральный светодиод</h6>
    <q-separator />

    <section class="flex justify-between q-mb-md q-mt-lg">
      <div class="text-h6 q-pl-lg">
        {{ sessionItem.enable0 ? 'Включен' : 'Выключен' }}
      </div>

      <div class="column justify-between picker">
        <div class="flex">
          <div class="color-label text-center">
            {{ sessionItem.color0 }}
          </div>
          <div
            class="color-label"
            :style="{ 'background-color': sessionItem.color0 }"
          ></div>
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-6 q-mb-md text-h6">
          {{ `частота: ${period0}` }}
        </div>
      </div>
    </section>
  </q-card>

  <!-- Круг 1 -->
  <q-card class="full-width q-pa-md card">
    <h6 class="q-mb-sm">Круг 1</h6>
    <q-separator />

    <section class="flex justify-between q-mb-md q-mt-lg no-wrap items-center">
      <div class="text-h6 picker">
        {{ sessionItem.enable1 ? 'Включен' : 'Выключен' }}
      </div>

      <div class="column justify-between picker q-pt-xs">
        <div class="flex">
          <div class="color-label text-center">
            {{ sessionItem.color1 }}
          </div>
          <div
            class="color-label"
            :style="{ 'background-color': sessionItem.color1 }"
          ></div>
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `частота: ${period1}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `блок: ${sessionItem.blockSize1}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="q-px-sm text-h6">
          {{
            `${sessionItem.direction1 === 0 ? 'по часовой' : 'против часовой'}`
          }}
        </div>
      </div>
    </section>
  </q-card>

  <!-- Круг 2 -->
  <q-card class="full-width q-pa-md card">
    <h6 class="q-mb-sm">Круг 2</h6>
    <q-separator />

    <section class="flex justify-between q-mb-md q-mt-lg no-wrap items-center">
      <div class="text-h6 picker">
        {{ sessionItem.enable2 ? 'Включен' : 'Выключен' }}
      </div>

      <div class="column justify-between picker q-pt-xs">
        <div class="flex">
          <div class="color-label text-center">
            {{ sessionItem.color2 }}
          </div>
          <div
            class="color-label"
            :style="{ 'background-color': sessionItem.color2 }"
          ></div>
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `частота: ${period2}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `блок: ${sessionItem.blockSize2}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="q-px-sm text-h6">
          {{
            `${sessionItem.direction2 === 0 ? 'по часовой' : 'против часовой'}`
          }}
        </div>
      </div>
    </section>
  </q-card>

  <!-- Круг 3 -->
  <q-card class="full-width q-pa-md card">
    <h6 class="q-mb-sm">Круг 3</h6>
    <q-separator />

    <section class="flex justify-between q-mb-md q-mt-lg no-wrap items-center">
      <div class="text-h6 picker">
        {{ sessionItem.enable3 ? 'Включен' : 'Выключен' }}
      </div>

      <div class="column justify-between picker q-pt-xs">
        <div class="flex">
          <div class="color-label text-center">
            {{ sessionItem.color3 }}
          </div>
          <div
            class="color-label"
            :style="{ 'background-color': sessionItem.color3 }"
          ></div>
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `частота: ${period3}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `блок: ${sessionItem.blockSize3}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="q-px-sm text-h6">
          {{
            `${sessionItem.direction3 === 0 ? 'по часовой' : 'против часовой'}`
          }}
        </div>
      </div>
    </section>
  </q-card>

  <!-- Круг 4 -->
  <q-card class="full-width q-pa-md card">
    <h6 class="q-mb-sm">Круг 4</h6>
    <q-separator />

    <section class="flex justify-between q-mb-md q-mt-lg no-wrap items-center">
      <div class="text-h6 picker">
        {{ sessionItem.enable4 ? 'Включен' : 'Выключен' }}
      </div>

      <div class="column justify-between picker q-pt-xs">
        <div class="flex">
          <div class="color-label text-center">
            {{ sessionItem.color4 }}
          </div>
          <div
            class="color-label"
            :style="{ 'background-color': sessionItem.color4 }"
          ></div>
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `частота: ${period4}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `блок: ${sessionItem.blockSize4}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="q-px-sm text-h6">
          {{
            `${sessionItem.direction4 === 0 ? 'по часовой' : 'против часовой'}`
          }}
        </div>
      </div>
    </section>
  </q-card>

  <!-- Круг 5 -->
  <q-card class="full-width q-pa-md card">
    <h6 class="q-mb-sm">Круг 5</h6>
    <q-separator />

    <section class="flex justify-between q-mb-md q-mt-lg no-wrap items-center">
      <div class="text-h6 picker">
        {{ sessionItem.enable5 ? 'Включен' : 'Выключен' }}
      </div>

      <div class="column justify-between picker q-pt-xs">
        <div class="flex">
          <div class="color-label text-center">
            {{ sessionItem.color5 }}
          </div>
          <div
            class="color-label"
            :style="{ 'background-color': sessionItem.color5 }"
          ></div>
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `частота: ${period5}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="col-2 q-mb-md text-h6">
          {{ `блок: ${sessionItem.blockSize5}` }}
        </div>
      </div>

      <div class="column justify-between picker">
        <div class="q-px-sm text-h6">
          {{
            `${sessionItem.direction5 === 0 ? 'по часовой' : 'против часовой'}`
          }}
        </div>
      </div>
    </section>
  </q-card>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { ProgramItem } from 'src/stores/entities/program-item.entity';

interface Props {
  item: ProgramItem;
}
const props = withDefaults(defineProps<Props>(), {});
const sessionItem = ref<ProgramItem>(props.item);

const period0 = ref(Math.trunc(10 * (1000 / sessionItem.value.period0!)) / 10);
const period1 = ref(Math.trunc(10 * (1000 / sessionItem.value.period1!)) / 10);
const period2 = ref(Math.trunc(10 * (1000 / sessionItem.value.period2!)) / 10);
const period3 = ref(Math.trunc(10 * (1000 / sessionItem.value.period3!)) / 10);
const period4 = ref(Math.trunc(10 * (1000 / sessionItem.value.period4!)) / 10);
const period5 = ref(Math.trunc(10 * (1000 / sessionItem.value.period5!)) / 10);
</script>

<style scoped lang="scss">
.card,
.color-label {
  border: 1px solid #cbcbcb;
}
.picker {
  width: 20%;
  height: 40px;
  margin-left: 30px;
}
.color-label {
  width: 50%;
}
.color-picker {
  min-width: 80px;
  width: 100%;
  margin-bottom: 5px;
}
</style>
