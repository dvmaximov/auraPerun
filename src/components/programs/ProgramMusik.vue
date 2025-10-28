<template>
  <div v-if="props.controls" class="flex q-mb-md">
    <q-btn
      :disable="choising"
      color="primary"
      label="Выбрать"
      @click="choiseFile"
    />
    <q-btn
      v-if="props.program.musik !== ''"
      :disable="choising"
      color="primary"
      label="Удалить"
      @click="clear"
      class="q-ml-md"
    />
  </div>
  <figure class="row q-mt-lg" v-if="props.program.musik !== ''">
    <figcaption class="q-ma-sm text-primary text-bold q-mb-xs">
      {{ props.program.musik }}
    </figcaption>
    <audio controls :src="musik" class="full-width"></audio>
  </figure>
  <div v-else>Музыка не выбрана</div>
</template>

<script setup lang="ts">
import { Program } from 'src/stores/entities/program.entity';
import { Session } from 'src/stores/entities/session.entity';
import { ref, watch } from 'vue';
import { storeToRefs } from 'pinia';
import { useSettingStore } from 'src/stores/setting.store';

interface Props {
  program: Program | Session;
  controls: boolean;
}
const props = withDefaults(defineProps<Props>(), {});

const emit = defineEmits(['update']);

const choising = ref(false);
const settings = useSettingStore();
const { musikDir } = storeToRefs(settings);
const musik = ref('');
musik.value = `${musikDir.value}${props.program.musik}`;

watch(
  () => props.program,
  (value) => {
    musik.value = `${musikDir.value}${props.program.musik}`;
  }
);

const choiseFile = async () => {
  choising.value = true;
  const file = await window['auraDevice'].getFileName();
  if (file !== '') {
    const res = await window['auraDevice'].copyFile(file);
    if (res) emit('update', res);
  }
  choising.value = false;
};

const clear = async () => {
  choising.value = true;
  emit('update', '');
  choising.value = false;
};
</script>
