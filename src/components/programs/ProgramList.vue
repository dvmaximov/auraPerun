<template>
  <div class="q-pa-md full-width">
    <h5 class="text-center text-bold">Программы</h5>
    <div class="q-my-md flex items-center">
      <q-btn color="primary" label="Добавить" @click="showAddDialog" />
      <q-input
        autofocus
        class="q-ml-md"
        debounce="300"
        outlined
        v-model="searchByName"
        label="Поиск по имени"
      >
        <template v-slot:append>
          <q-icon
            name="close"
            @click="searchByName = ''"
            class="cursor-pointer"
          />
        </template>
      </q-input>
      <q-btn
        class="q-ml-md"
        color="primary"
        label="Синхронизация"
        @click="synchronize"
      >
        <q-tooltip style="font-size: 14px">
          Синхронизация настроек программ при добавлении устройств подсветки
        </q-tooltip>
      </q-btn>
    </div>

    <div v-if="isEmpty" class="flex justify-center q-mt-xl">
      <h6>Список программ пустой</h6>
    </div>

    <q-virtual-scroll
      v-else
      :items="programList(searchByName)"
      v-slot="{ item }"
      class="scrool q-pt-md"
    >
      <q-item :key="item.id" dense class="items-center q-pl-md">
        <q-item-section>
          <div class="flex justify-start no-wrap q-pl-md">
            <q-expansion-item
              group="somegroup"
              icon="mdi-sitemap"
              :label="item.name"
              header-class="text-primary"
              class="item"
            >
              <q-card class="item-card">
                <q-card-section>
                  <ProgramContent :program="item" />
                </q-card-section>
              </q-card>
            </q-expansion-item>
            <div class="flex justify-center no-wrap q-pr-md items-center">
              <q-btn
                label="Удалить"
                color="accent"
                class="q-ml-md"
                @click="showDeleteDialog(item)"
              />
              <q-btn
                label="Терапия"
                class="q-ml-md"
                @click="showAddSessionDialog(item)"
              />
            </div>
          </div>
        </q-item-section>
      </q-item>
    </q-virtual-scroll>
  </div>

  <CommonDialog ref="newProgramDialog" @ok="addProgram">
    <template v-slot:title>
      <h6>Название новой программы</h6>
    </template>
    <q-separator />
    <template v-slot:content>
      <q-input autofocus outlined v-model="newProgramName" label="Название" />
    </template>
  </CommonDialog>

  <CommonDialog ref="newSessionDialog" @ok="toSession">
    <template v-slot:title>
      <h6>Продолжительность сессии</h6>
    </template>
    <q-separator />
    <template v-slot:content>
      <q-input
        autofocus
        outlined
        v-model="sessionDuring"
        label="Время в минутах"
        mask="###"
      />
    </template>
  </CommonDialog>

  <CommonDialog ref="deleteProgramDialog" @ok="removeProgram">
    <template v-slot:title>
      <h6>Удалить программу?</h6>
    </template>
  </CommonDialog>

  <CommonSpinner ref="spinner">
    <template v-slot:header>Синхронизация...</template>
    <template v-slot:content>{{ `${synchCount} из ${synchAmount}` }}</template>
  </CommonSpinner>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { storeToRefs } from 'pinia';
import { Program } from 'src/stores/entities/program.entity';
import { useProgramStore } from 'src/stores/program.store';
import { useSessionStore } from 'src/stores/session.store';
import CommonDialog from 'src/components/CommonDialog.vue';
import CommonSpinner from 'src/components/CommonSpinner.vue';
import ProgramContent from './ProgramContent.vue';

const programStore = useProgramStore();
const sessionStore = useSessionStore();
const { programList, isEmpty, programs } = storeToRefs(programStore);
const newProgramDialog = ref();
const deleteProgramDialog = ref();
const newSessionDialog = ref();
const spinner = ref();
const newProgramName = ref('');
const sessionDuring = ref(0);
const searchByName = ref('');
const synchCount = ref(1);
const synchAmount = ref(0);
let programToSessionAdd: Program;
let programToDelete: Program;

const showAddDialog = () => {
  newProgramName.value = '';
  newProgramDialog.value!.isShow = true;
};

const showDeleteDialog = (program: Program) => {
  programToDelete = program;
  deleteProgramDialog.value!.isShow = true;
};

const addProgram = async () => {
  const name = newProgramName.value.trim();
  if (name !== '') {
    await programStore.insert(name);
  }
  newProgramDialog.value!.isShow = false;
};

const removeProgram = async () => {
  await programStore.remove(programToDelete);
  deleteProgramDialog.value!.isShow = false;
};

const showAddSessionDialog = (program: Program) => {
  sessionDuring.value = 1;
  programToSessionAdd = program;
  newSessionDialog.value!.isShow = true;
};

const toSession = () => {
  let during = (sessionDuring.value =
    '' || +sessionDuring.value === 0 ? 1 : +sessionDuring.value);
  sessionStore.toSession(programToSessionAdd, during);
  newSessionDialog.value!.isShow = false;
};

const synchronize = async () => {
  function delay(ms: number) {
    return new Promise((resolve) => setTimeout(resolve, ms));
  }
  spinner.value.isShow = true;
  synchAmount.value = programs.value.length;
  await delay(800);
  for (const program of programs.value) {
    if (synchCount.value !== synchAmount.value) synchCount.value++;
    await programStore.synchronize(program);
  }
  spinner.value.isShow = false;
  synchCount.value = 1;
  programStore.synchronizeDone();
};
</script>

<style lang="scss" scoped>
.item {
  background-color: $bg-info;
  width: 80%;
}
.scrool {
  height: calc(100vh - 230px);
  border: 1px solid #cbcbcb;
}

.item-card {
  border: 1px solid #cbcbcb;
}
</style>
