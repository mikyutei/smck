#pragma once

#include "keymap.h"

#ifdef WINDOWS
  #define ICH_MOD_L_KEY KC_LGUI
  #define ICH_MOD_R_KEY KC_RGUI
  #define ICH_L_MOD(kc) (LGUI(kc))
  #define ICH_R_MOD(kc) (RGUI(kc))
  #define KILL_WINDOW A(KC_F4)
  #define CLIPBOARD ICH_L_MOD(KC_V)
  #define TASK_MANAGER LSFT(LCTL(KC_ESC))
  //SEND_STRING("aaa");
  #define LOGOUT ICH_R_MOD(KC_L)
  #define WINDOW_OP_4 KC_NO
#endif

#ifdef I3WM
  #define ICH_MOD_L_KEY KC_LGUI
  #define ICH_MOD_R_KEY KC_RGUI
  #define ICH_L_MOD(kc) (LGUI(kc))
  #define ICH_R_MOD(kc) (RGUI(kc))
  #define KILL_WINDOW LSFT(ICH_L_MOD(KC_Q))
  #define CLIPBOARD KC_NO
  #define TASK_MANAGER KC_NO
  #define LOGOUT KC_NO
  #define WINDOW_OP_1 KC_NO //そのうち決める
  #define WINDOW_OP_2 KC_NO //そのうち決める
  #define WINDOW_OP_3 ICH_L_MOD(KC_F)//トグル
  #define WINDOW_OP_4 KC_NO
#endif

