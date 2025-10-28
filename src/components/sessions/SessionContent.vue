<template>
  <div class="q-pa-md">
    <div class="q-gutter-y-md">
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
            v-for="item of session.items"
            :key="item.id"
            :name="item.device_id"
            :label="`id ${item.device_id}`"
          />
          <q-tab name="Musik" label="Музыка" />
        </q-tabs>

        <q-separator />

        <q-tab-panels v-model="tab" animated>
          <q-tab-panel
            v-for="item of session.items"
            :key="item.id"
            :name="item.device_id"
          >
            <SessionItem :item="item" />
          </q-tab-panel>
          <q-tab-panel name="Musik">
            <ProgramMusik :program="session" :controls="false" />
          </q-tab-panel>
        </q-tab-panels>
      </q-card>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { Session } from 'src/stores/entities/session.entity';
import SessionItem from './SessionItem.vue';
import ProgramMusik from 'src/components/programs/ProgramMusik.vue';

interface Props {
  session: Session;
}
const props = withDefaults(defineProps<Props>(), {});

const tab = ref();
tab.value =
  props.session.items?.length !== 0 ? props.session.items![0].device_id : '';
</script>
