<template>
  <section style="height: 1600px">
    <div class="q-my-md">
      <q-btn label="Сохранить" color="secondary" @click="update()" />
    </div>

    <!-- Центральный -->
    <q-card class="full-width q-pa-md card">
      <h6 class="q-mb-sm">Центральный светодиод</h6>
      <q-separator />

      <section class="row q-mt-lg q-mb-md justify-between items-center">
        <div
          class="column justify-between q-mr-xs picker"
          style="min-width: 150px"
        >
          <q-input filled v-model="programItem.color0" class="color-picker">
            <template v-slot:append>
              <q-icon ref="color0" name="colorize" class="cursor-pointer">
                <q-popup-proxy
                  cover
                  transition-show="scale"
                  transition-hide="scale"
                >
                  <q-color no-header no-footer v-model="programItem.color0" />
                </q-popup-proxy>
              </q-icon>
              <div
                style="height: 20px; width: 20px"
                :style="{ 'background-color': programItem.color0 }"
              ></div>
            </template>
          </q-input>
        </div>

        <!-- <section class="flex justify-evenly q-mb-md"> -->
        <div class="column justify-between picker"></div>
        <q-toggle
          v-model="programItem.enable0"
          :label="programItem.enable0 ? 'Включен' : 'Выключен'"
        />
        <q-input
          class="col-2 q-ml-md"
          outlined
          v-model="period0"
          label="Центральный, Гц (< 10 Гц)"
          mask="#.##"
        ></q-input>
      </section>
    </q-card>

    <div class="q-my-md">
      <q-btn label="Сохранить" color="secondary" @click="update()" />
    </div>

    <!-- Круг 1 -->
    <q-card class="full-width q-pa-md card">
      <h6 class="q-mb-sm">Круг 1</h6>
      <q-separator />

      <section class="row q-mt-lg q-mb-md justify-between items-center">
        <div
          class="column justify-between q-mr-xs picker"
          style="min-width: 150px"
        >
          <q-input filled v-model="programItem.color1" class="color-picker">
            <template v-slot:append>
              <q-icon ref="color1" name="colorize" class="cursor-pointer">
                <q-popup-proxy
                  cover
                  transition-show="scale"
                  transition-hide="scale"
                >
                  <q-color no-header no-footer v-model="programItem.color1" />
                </q-popup-proxy>
              </q-icon>
              <div
                style="height: 20px; width: 20px"
                :style="{ 'background-color': programItem.color1 }"
              ></div>
            </template>
          </q-input>
        </div>

        <!-- <section class="flex justify-evenly q-mb-md"> -->
        <div class="column justify-between picker"></div>
        <q-toggle
          v-model="programItem.enable1"
          :label="programItem.enable1 ? 'Включен' : 'Выключен'"
        />
        <q-select
          class="col-2 q-ml-md"
          outlined
          v-model="programItem.blockSize1"
          :options="blockOptions"
          label="Размер блока"
        />
        <q-input
          class="col-2 q-ml-md"
          outlined
          v-model="period1"
          label="Круг 1, Гц (< 10 Гц)"
          mask="#.#"
        ></q-input>
        <div class="column">
          <q-radio
            v-model="programItem.direction1"
            :val="0"
            label="по часовой"
          />
          <q-radio
            v-model="programItem.direction1"
            :val="1"
            label="против часовой"
          />
        </div>
      </section>
    </q-card>

    <div class="q-my-md">
      <q-btn label="Сохранить" color="secondary" @click="update()" />
    </div>

    <!-- Круг 2 -->
    <q-card class="full-width q-pa-md card">
      <h6 class="q-mb-sm">Круг 2</h6>
      <q-separator />

      <section class="row q-mt-lg q-mb-md justify-between items-center">
        <div
          class="column justify-between q-mr-xs picker"
          style="min-width: 150px"
        >
          <q-input filled v-model="programItem.color2" class="color-picker">
            <template v-slot:append>
              <q-icon ref="color2" name="colorize" class="cursor-pointer">
                <q-popup-proxy
                  cover
                  transition-show="scale"
                  transition-hide="scale"
                >
                  <q-color no-header no-footer v-model="programItem.color2" />
                </q-popup-proxy>
              </q-icon>
              <div
                style="height: 20px; width: 20px"
                :style="{ 'background-color': programItem.color2 }"
              ></div>
            </template>
          </q-input>
        </div>

        <!-- <section class="flex justify-evenly q-mb-md"> -->
        <div class="column justify-between picker"></div>
        <q-toggle
          v-model="programItem.enable2"
          :label="programItem.enable2 ? 'Включен' : 'Выключен'"
        />
        <q-select
          class="col-2 q-ml-md"
          outlined
          v-model="programItem.blockSize2"
          :options="blockOptions"
          label="Размер блока"
        />
        <q-input
          class="col-2 q-ml-md"
          outlined
          v-model="period2"
          label="Круг 1, Гц (< 10 Гц)"
          mask="#.#"
        ></q-input>
        <div class="column q-gutter-sm">
          <q-radio
            v-model="programItem.direction2"
            :val="0"
            label="по часовой"
          />
          <q-radio
            v-model="programItem.direction2"
            :val="1"
            label="против часовой"
          />
        </div>
      </section>
    </q-card>

    <div class="q-my-md">
      <q-btn label="Сохранить" color="secondary" @click="update()" />
    </div>

    <!-- Круг 3 -->
    <q-card class="full-width q-pa-md card">
      <h6 class="q-mb-sm">Круг 3</h6>
      <q-separator />

      <section class="row q-mt-lg q-mb-md justify-between items-center">
        <div
          class="column justify-between q-mr-xs picker"
          style="min-width: 150px"
        >
          <q-input filled v-model="programItem.color3" class="color-picker">
            <template v-slot:append>
              <q-icon ref="color3" name="colorize" class="cursor-pointer">
                <q-popup-proxy
                  cover
                  transition-show="scale"
                  transition-hide="scale"
                >
                  <q-color no-header no-footer v-model="programItem.color3" />
                </q-popup-proxy>
              </q-icon>
              <div
                style="height: 20px; width: 20px"
                :style="{ 'background-color': programItem.color3 }"
              ></div>
            </template>
          </q-input>
        </div>

        <!-- <section class="flex justify-evenly q-mb-md"> -->
        <div class="column justify-between picker"></div>
        <q-toggle
          v-model="programItem.enable3"
          :label="programItem.enable3 ? 'Включен' : 'Выключен'"
        />
        <q-select
          class="col-2 q-ml-md"
          outlined
          v-model="programItem.blockSize3"
          :options="blockOptions"
          label="Размер блока"
        />
        <q-input
          class="col-2 q-ml-md"
          outlined
          v-model="period3"
          label="Круг 1, Гц (< 10 Гц)"
          mask="#.#"
        ></q-input>
        <div class="column q-gutter-sm">
          <q-radio
            v-model="programItem.direction3"
            :val="0"
            label="по часовой"
          />
          <q-radio
            v-model="programItem.direction3"
            :val="1"
            label="против часовой"
          />
        </div>
      </section>
    </q-card>

    <div class="q-my-md">
      <q-btn label="Сохранить" color="secondary" @click="update()" />
    </div>

    <!-- Круг 4 -->
    <q-card class="full-width q-pa-md card">
      <h6 class="q-mb-sm">Круг 4</h6>
      <q-separator />

      <section class="row q-mt-lg q-mb-md justify-between items-center">
        <div
          class="column justify-between q-mr-xs picker"
          style="min-width: 150px"
        >
          <q-input filled v-model="programItem.color4" class="color-picker">
            <template v-slot:append>
              <q-icon ref="color4" name="colorize" class="cursor-pointer">
                <q-popup-proxy
                  cover
                  transition-show="scale"
                  transition-hide="scale"
                >
                  <q-color no-header no-footer v-model="programItem.color4" />
                </q-popup-proxy>
              </q-icon>
              <div
                style="height: 20px; width: 20px"
                :style="{ 'background-color': programItem.color4 }"
              ></div>
            </template>
          </q-input>
        </div>

        <!-- <section class="flex justify-evenly q-mb-md"> -->
        <div class="column justify-between picker"></div>
        <q-toggle
          v-model="programItem.enable4"
          :label="programItem.enable4 ? 'Включен' : 'Выключен'"
        />
        <q-select
          class="col-2 q-ml-md"
          outlined
          v-model="programItem.blockSize4"
          :options="blockOptions"
          label="Размер блока"
        />
        <q-input
          class="col-2 q-ml-md"
          outlined
          v-model="period4"
          label="Круг 1, Гц (< 10 Гц)"
          mask="#.#"
        ></q-input>
        <div class="column q-gutter-sm">
          <q-radio
            v-model="programItem.direction4"
            :val="0"
            label="по часовой"
          />
          <q-radio
            v-model="programItem.direction4"
            :val="1"
            label="против часовой"
          />
        </div>
      </section>
    </q-card>

    <div class="q-my-md">
      <q-btn label="Сохранить" color="secondary" @click="update()" />
    </div>

    <!-- Круг 5 -->
    <q-card class="full-width q-pa-md card">
      <h6 class="q-mb-sm">Круг 5</h6>
      <q-separator />

      <section class="row q-mt-lg q-mb-md justify-between items-center">
        <div
          class="column justify-between q-mr-xs picker"
          style="min-width: 150px"
        >
          <q-input filled v-model="programItem.color5" class="color-picker">
            <template v-slot:append>
              <q-icon ref="color5" name="colorize" class="cursor-pointer">
                <q-popup-proxy
                  cover
                  transition-show="scale"
                  transition-hide="scale"
                >
                  <q-color no-header no-footer v-model="programItem.color5" />
                </q-popup-proxy>
              </q-icon>
              <div
                style="height: 20px; width: 20px"
                :style="{ 'background-color': programItem.color5 }"
              ></div>
            </template>
          </q-input>
        </div>

        <!-- <section class="flex justify-evenly q-mb-md"> -->
        <div class="column justify-between picker"></div>
        <q-toggle
          v-model="programItem.enable5"
          :label="programItem.enable5 ? 'Включен' : 'Выключен'"
        />
        <q-select
          class="col-2 q-ml-md"
          outlined
          v-model="programItem.blockSize5"
          :options="blockOptions"
          label="Размер блока"
        />
        <q-input
          class="col-2 q-ml-md"
          outlined
          v-model="period5"
          label="Круг 1, Гц (< 10 Гц)"
          mask="#.#"
        ></q-input>
        <div class="column q-gutter-sm">
          <q-radio
            v-model="programItem.direction5"
            :val="0"
            label="по часовой"
          />
          <q-radio
            v-model="programItem.direction5"
            :val="1"
            label="против часовой"
          />
        </div>
      </section>
    </q-card>
  </section>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import {
  ProgramItem,
  ITEMColors,
} from 'src/stores/entities/program-item.entity';

interface Props {
  item: ProgramItem;
}
const props = withDefaults(defineProps<Props>(), {});
const emit = defineEmits(['update']);

const programItem = ref<ProgramItem>({ ...props.item });
const blockOptions = [1, 2, 3, 4, 5];
const period0 = ref(Math.trunc(10 * (1000 / programItem.value.period0!)) / 10);
const period1 = ref(Math.trunc(10 * (1000 / programItem.value.period1!)) / 10);
const period2 = ref(Math.trunc(10 * (1000 / programItem.value.period2!)) / 10);
const period3 = ref(Math.trunc(10 * (1000 / programItem.value.period3!)) / 10);
const period4 = ref(Math.trunc(10 * (1000 / programItem.value.period4!)) / 10);
const period5 = ref(Math.trunc(10 * (1000 / programItem.value.period5!)) / 10);

const update = () => {
  programItem.value.period0 = Math.trunc(1000 * (1 / +period0.value));
  programItem.value.period1 = Math.trunc(1000 * (1 / +period1.value));
  programItem.value.period2 = Math.trunc(1000 * (1 / +period2.value));
  programItem.value.period3 = Math.trunc(1000 * (1 / +period3.value));
  programItem.value.period4 = Math.trunc(1000 * (1 / +period4.value));
  programItem.value.period5 = Math.trunc(1000 * (1 / +period5.value));

  emit('update', programItem.value);
};
</script>

<style scoped lang="scss">
.card,
.color-label {
  border: 1px solid #cbcbcb;
}
.picker {
  width: 15%;
  height: 40px;
  // margin-left: 30px;
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
