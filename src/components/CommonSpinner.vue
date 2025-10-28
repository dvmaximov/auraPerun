<template>
  <div v-show="isShow" class="wrapper" @click.prevent.stop="">
    <div class="loader-container">
      <div class="loader"></div>
      <div class="loader-text">
        <slot name="header"></slot>
      </div>
      <div class="loader-text__content">
        <slot name="content"></slot>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';

const isShow = ref(false);

defineExpose({
  isShow,
});
</script>

<style lang="scss" scoped>
.wrapper {
  background-color: #060606c0;
  position: absolute;
  left: 0;
  right: 0;
  top: 0;
  bottom: 0;
}
.loader-container {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  height: 100vh;
}

.loader {
  width: 70px;
  height: 70px;
  position: relative;
}

.loader:before {
  content: '';
  width: 70px;
  height: 70px;
  border-radius: 50%;
  border: 6px solid #007bff;
  position: absolute;
  top: 0;
  left: 0;
  animation: pulse 1s ease-in-out infinite;
}

.loader:after {
  content: '';
  width: 70px;
  height: 70px;
  border-radius: 50%;
  border: 6px solid transparent;
  border-top-color: #007bff;
  position: absolute;
  top: 0;
  left: 0;
  animation: spin 2s linear infinite;
}

.loader-text,
.loader-text__content {
  font-size: 24px;
  margin-top: 20px;
  color: #007bff;
  font-family: Arial, sans-serif;
  text-align: center;
  text-transform: uppercase;
}
.loader-text__content {
  text-transform: none;
}
@keyframes pulse {
  0% {
    transform: scale(0.6);
    opacity: 1;
  }
  50% {
    transform: scale(1.2);
    opacity: 0;
  }
  100% {
    transform: scale(0.6);
    opacity: 1;
  }
}

@keyframes spin {
  0% {
    transform: rotate(0deg);
  }
  100% {
    transform: rotate(360deg);
  }
}

.content {
  display: none;
}

.loaded .loader-container {
  display: none;
}

.loaded .content {
  display: block;
}
</style>
