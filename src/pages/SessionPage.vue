<template>
  <q-page class="q-mx-xl q-pt-md items-center justify-evenly">
    <SessionList />
  </q-page>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import SessionList from 'src/components/sessions/SessionList.vue';
</script>
