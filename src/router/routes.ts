import { RouteRecordRaw } from 'vue-router';

const routes: RouteRecordRaw[] = [
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    children: [
      { path: '', component: () => import('pages/SessionPage.vue') },
      {
        path: '/programs',
        component: () => import('pages/ProgramsPage.vue'),
        // meta: { transition: 'slide-left' },
      },
      { path: '/devices', component: () => import('pages/DevicesPage.vue') },
    ],
  },
  {
    path: '/:catchAll(.*)*',
    component: () => import('pages/ErrorNotFound.vue'),
  },
];

export default routes;
