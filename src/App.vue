<template>
  <router-view />
</template>

<script setup lang="ts">
import { useSettingStore } from 'src/stores/setting.store';
import { useDeviceStore } from 'src/stores/device.store';
import { useMessageStore } from 'src/stores/message.store';

const settingStore = useSettingStore();
const deviceStore = useDeviceStore();
const messageStore = useMessageStore();
</script>
