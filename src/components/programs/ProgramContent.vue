<template>
  <div class="q-pa-md">
    <div class="q-gutter-y-md">
      <q-input outlined v-model="name" label="Название программы"></q-input>
      <q-card>
        <q-tabs
          v-model="tab"
          dense
          class="text-grey"
          active-color="primary"
          indicator-color="primary"
          align="justify"
          narrow-indicator
        >
          <q-tab
            v-for="item of program.pureItems"
            :key="item.id"
            :name="item.device_id"
            :label="`id ${item.device_id}`"
          />
          <q-tab name="Musik" label="Музыка" />
        </q-tabs>

        <q-separator />

        <q-tab-panels v-model="tab" animated>
          <q-tab-panel
            v-for="item of program.pureItems"
            :key="item.id"
            :name="item.device_id"
          >
            <ProgramItem :item="item" @update="update" />
          </q-tab-panel>
          <q-tab-panel name="Musik">
            <ProgramMusik :program="program" controls @update="updateMusik" />
          </q-tab-panel>
        </q-tab-panels>
      </q-card>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { Program } from 'src/stores/entities/program.entity';
import { ProgramItem as Item } from 'src/stores/entities/program-item.entity';
import { useProgramStore } from 'src/stores/program.store';
import { useSessionStore } from 'src/stores/session.store';
import ProgramItem from './ProgramItem.vue';
import ProgramMusik from './ProgramMusik.vue';

interface Props {
  program: Program;
}
const props = withDefaults(defineProps<Props>(), {});

const tab = ref();
const name = ref('');
name.value = props.program.name!;
tab.value =
  props.program.pureItems?.length !== 0
    ? props.program.pureItems![0].device_id
    : '';
const programStore = useProgramStore();
const sessionStore = useSessionStore();

const update = async (item: Item) => {
  const program: Program = { ...props.program };
  program.pureItems = program.pureItems?.map((value) => {
    if (value.device_id === item.device_id) return item;
    else return value;
  });
  program.name = name.value;
  await programStore.update(program);
  sessionStore.synchronize(program);
};

const updateMusik = async (musik: string) => {
  const program: Program = { ...props.program };
  program.musik = musik;
  await programStore.update(program);
  sessionStore.synchronize(program);
};
</script>
