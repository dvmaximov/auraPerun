<template>
  <q-dialog
    v-model="isShow"
    persistent
    :backdrop-filter="`blur(4px) grayscale(100%)`"
  >
    <q-card>
      <q-card-section class="row items-center">
        <!-- <q-avatar icon="delete" color="primary" text-color="white" /> -->
        <div class="full-width q-mx-md q-mt-md">
          <slot name="title"></slot>
        </div>
        <div class="full-width q-mx-md q-mt-lg">
          <slot name="content"></slot>
        </div>
      </q-card-section>

      <q-card-actions align="right">
        <q-btn flat label="отмена" color="primary" @click="cancel" />
        <q-btn flat label="ok" color="primary" @click="sendOk" />
      </q-card-actions>
    </q-card>
  </q-dialog>
</template>

<script setup lang="ts">
import { ref } from 'vue';

const emit = defineEmits(['ok']);

const isShow = ref(false);

const sendOk = () => {
  emit('ok');
};

const cancel = () => {
  isShow.value = false;
};

defineExpose({
  isShow,
});
</script>
