<template>
  <q-page class="q-mx-xl q-pt-md items-center justify-evenly">
    <DeviceList />
  </q-page>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import DeviceList from 'src/components/devices/DeviceList.vue';
</script>
