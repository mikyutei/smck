#pragma once

#include "keymap.h"

#ifdef WINDOWS
  #define ICH_MOD_L KC_LGUI
  #define ICH_MOD_R KC_RGUI
#endif

#ifdef I3WM
#define ICH_MOD_L KC_LGUI
#define ICH_MOD_R KC_RGUI
#endif
