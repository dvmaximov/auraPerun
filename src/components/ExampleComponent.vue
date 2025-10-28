<template></template>

<script setup lang="ts">
import { computed, ref } from 'vue';

interface Props {
  title: string;
  active: boolean;
}
const props = withDefaults(defineProps<Props>(), {});
</script>
