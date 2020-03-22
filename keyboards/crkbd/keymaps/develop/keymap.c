#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;


extern uint8_t is_master;

#include "keymap_ichikawa.h"
#include "keymap_os.h"

bool _qwerty = false;
bool _shift = false;
bool _ctrl = false;
bool _alt = false;
bool _gui = false;

bool _mtgap_shift = false;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _MTGAP 0
#define _MTGAP_SHIFT 8
#define _N_GETA 1
#define _N_GETA_MIDDLE 2 //いか
#define _N_GETA_RING 3 //しと
#define _N_GETA_MIDDLE_TOP 4 //こは
#define _N_GETA_RING_TOP 5 //がに
#define _N_GETA_LITTLE_L 6 //の
#define _N_GETA_LITTLE_R 7 //な
#define _QWERTY 9
#define _NUM_LAYER 10
#define _SYMBOL_LAYER 11
#define _ICHIKAWA_LCRC 12
#define _ICHIKAWA_LLRC 13
#define _ICHIKAWA_RCLC 14
#define _ICHIKAWA_RCLL 15
#define _ICHIKAWA_LLLC 16 //隣り合ったkey 使用予定はなし
#define _ICHIKAWA_LCLL 17 //隣り合ったkey 使用予定はなし
#define _NO_KEY_LAYOUT_9 18
#define _NO_KEY_LAYOUT_A 19
#define _NO_KEY_LAYOUT_B 20
#define _NO_KEY_LAYOUT_C 21
#define _NO_KEY_LAYOUT_D 22
#define _NO_KEY_LAYOUT_E 23
#define _NO_KEY_LAYOUT_F 24
#define _NO_KEY_LAYOUT_G 25
#define _NO_KEY_LAYOUT_I 26
#define _MOUSE 30 //(_ICHIKAWA_LL)

//macro setting
char macro_buf[30];


enum custom_keycodes {
  THUMB_LL = SAFE_RANGE,
  THUMB_LC,
  THUMB_LR,
  THUMB_RL,
  THUMB_RC,
  THUMB_RR,
  ICH_LCTRL,
  ICH_RCTRL,
  ICH_LALT,
  ICH_RALT,
  ICH_LGUI,
  ICH_RGUI,
#ifdef WINDOWS
  WINDOW_OP_1, //maximize
  WINDOW_OP_2, //minimize
  WINDOW_OP_3, //nomalize
#endif
  NG_FIRST
};


enum new_geta {
  NG_A = NG_FIRST,
  NG_I,
  NG_U,
  NG_E,
  NG_O,
  NG_KYA,
  NG_KYI,
  NG_KYU,
  NG_KYE,
  NG_KYO,
  NG_GYA,
  NG_GYI,
  NG_GYU,
  NG_GYE,
  NG_GYO,
  NG_SYA,
  NG_SYI,
  NG_SYU,
  NG_SYE,
  NG_SYO,
  NG_ZYA,
  NG_ZYI,
  NG_ZYU,
  NG_ZYE,
  NG_ZYO,
  NG_TYA,
  NG_TYI,
  NG_TYU,
  NG_TYE,
  NG_TYO,
  NG_DYA,
  NG_DYI,
  NG_DYU,
  NG_DYE,
  NG_DYO,
  NG_THA,
  NG_THI,
  NG_THU,
  NG_THE,
  NG_THO,
  NG_DHA,
  NG_DHI,
  NG_DHU,
  NG_DHE,
  NG_DHO,
  NG_NYA,
  NG_NYI,
  NG_NYU,
  NG_NYE,
  NG_NYO,
  NG_HYA,
  NG_HYI,
  NG_HYU,
  NG_HYE,
  NG_HYO,
  NG_BYA,
  NG_BYI,
  NG_BYU,
  NG_BYE,
  NG_BYO,
  NG_PYA,
  NG_PYI,
  NG_PYU,
  NG_PYE,
  NG_PYO,
  NG_MYA,
  NG_MYI,
  NG_MYU,
  NG_MYE,
  NG_MYO,
  NG_RYA,
  NG_RYI,
  NG_RYU,
  NG_RYE,
  NG_RYO,
  NG_XYA,
  NG_XYU,
  NG_XYO,
  NG_XTU,
  NG_XWA,
  NG_UXO,
  NG_KA,
  NG_KI,
  NG_KU,
  NG_KE,
  NG_KO,
  NG_SA,
  NG_SI,
  NG_SU,
  NG_SE,
  NG_SO,
  NG_TA,
  NG_TI,
  NG_TU,
  NG_TE,
  NG_TO,
  NG_NA,
  NG_NI,
  NG_NU,
  NG_NE,
  NG_NO,
  NG_HA,
  NG_HI,
  NG_HU,
  NG_HE,
  NG_HO,
  NG_MA,
  NG_MI,
  NG_MU,
  NG_ME,
  NG_MO,
  NG_RA,
  NG_RI,
  NG_RU,
  NG_RE,
  NG_RO,
  NG_GA,
  NG_GI,
  NG_GU,
  NG_GE,
  NG_GO,
  NG_ZA,
  NG_ZI,
  NG_ZU,
  NG_ZE,
  NG_ZO,
  NG_DA,
  NG_DI,
  NG_DU,
  NG_DE,
  NG_DO,
  NG_BA,
  NG_BI,
  NG_BU,
  NG_BE,
  NG_BO,
  NG_PA,
  NG_PI,
  NG_PU,
  NG_PE,
  NG_PO,
  NG_XA,
  NG_XI,
  NG_XU,
  NG_XE,
  NG_XO,
  NG_VA,
  NG_VI,
  NG_VU,
  NG_VE,
  NG_VO,
  NG_QA,
  NG_QI,
  NG_QE,
  NG_QO,
  NG_YA,
  NG_YU,
  NG_YE,
  NG_YO,
  NG_WA,
  NG_WI,
  NG_WE,
  NG_WO,
  NG_FA,
  NG_FI,
  NG_FE,
  NG_FO,
  NG_JA,
  NG_JU,
  NG_JE,
  NG_JO,
  NG_NN,
  NG_LATEST
};

//uint32_t AAAAA = millis();

uint16_t b = NG_A;
// const char N_GETA_V[5][1] PROGMEM = {
//   "a","i","u","e","o"
// };

// const char N_GETA_C[19][1] PROGMEM = {
//   "k","s","t","n","h",
//   "m","y","r","w","g",
//   "z","d","b","p","q",
//   "x","f","v","j"
// };

// const char N_GETA_3[12][2] PROGMEM = {
//   "ky","gy","sy","zy","ty",
//   "ny","hy","by","py","my",
//   "ry","xy"
// };



const char PROGMEM N_GETA_1[5][2] = {
  "a","i","u","e","o"
};

const char PROGMEM N_GETA_2[91][3] = {
"ka", "ki", "ku", "ke", "ko",
"sa", "si", "su", "se", "so",
"ta", "ti", "tu", "te", "to",
"na", "ni", "nu", "ne", "no",
"ha", "hi", "hu", "he", "ho",
"ma", "mi", "mu", "me", "mo",
"ra", "ri", "ru", "re", "ro",
"ga", "gi", "gu", "ge", "go",
"za", "zi", "zu", "ze", "zo",
"da", "di", "du", "de", "do",
"ba", "bi", "bu", "be", "bo",
"pa", "pi", "pu", "pe", "po",
"xa", "xi", "xu", "xe", "xo",
"va", "vi", "vu", "ve", "vo",
"qa", "qi", "qe", "qo",
"ya", "yu", "ye", "yo",
"wa", "wi", "we", "wo",
"fa", "fi", "fe", "fo",
"ja", "ju", "je", "jo",
"nn"
};

const char PROGMEM N_GETA_3[76][4] = {
"kya", "kyi", "kyu", "kye", "kyo",
"gya", "gyi", "gyu", "gye", "gyo",
"sya", "syi", "syu", "sye", "syo",
"zya", "zyi", "zyu", "zye", "zyo",
"tya", "tyi", "tyu", "tye", "tyo",
"dya", "dyi", "dyu", "dye", "dyo",
"tha", "thi", "thu", "the", "tho",
"dha", "dhi", "dhu", "dhe", "dho",
"nya", "nyi", "nyu", "nye", "nyo",
"hya", "hyi", "hyu", "hye", "hyo",
"bya", "byi", "byu", "bye", "byo",
"pya", "pyi", "pyu", "pye", "pyo",
"mya", "myi", "myu", "mye", "myo",
"rya", "ryi", "ryu", "rye", "ryo",
"xya", "xyu", "xyo", "xtu", "xwa",
"uxo"
};

//japanese or english IME status on keyboard
bool is_new_gata = false;

// 文字送信間隔のためのtimer
uint16_t key_repeat_timer = 0;

//同じ文字列か判定用
uint16_t previous_keycode = 0;
uint16_t current_keycode = 0;

// macro_buf set only new geta layout char
void set_new_geta_string(const char * src) {
  strcpy_P(macro_buf,src);
}

// 入力可能時間か確認
bool is_input_time(uint16_t keycode) {

  if(keycode != previous_keycode) {
    previous_keycode = keycode;
    key_repeat_timer = timer_read();
    return true;
  } else if(KEY_REPEAT_DERAY < timer_elapsed(key_repeat_timer)) {
    key_repeat_timer = timer_read();
    return true;
  }
  return false;
}

bool process_record_new_gata(uint16_t keycode, keyrecord_t *record){

  if (!record->event.pressed && keycode >= NG_A && NG_NN >= keycode) {
    if(NG_KA <= keycode) {
      set_new_geta_string(&N_GETA_2[(uint8_t)(keycode - NG_KA)][0]);
    }else if (NG_KYA <= keycode) {
      set_new_geta_string(&N_GETA_3[(uint8_t)(keycode - NG_KYA)][0]);
    }else {
      set_new_geta_string(&N_GETA_1[(uint8_t)( keycode - NG_A) ][0]);
    }

    send_string(macro_buf);

    return false;
  }
  return true;
}

bool IS_INPUT = false;

//inputed_layer[_THUMB_LL]
//inputed_layer[_THUMB_LC]
//inputed_layer[_THUMB_RC]
#define _THUMB_LL 0
#define _THUMB_LC 1
#define _THUMB_LR 2
#define _THUMB_RL 3
#define _THUMB_RC 4
#define _THUMB_RR 5
#define _LAYER_NUM 6
uint8_t pressed_num = 0;
uint8_t inputed_layer[_LAYER_NUM] = {
  0,0,0,0,0,0
};

void release_custom_layer(uint8_t index) {
  for (int i = 0; i< _LAYER_NUM;i++){
    if (inputed_layer[i] > inputed_layer[index]) {
      inputed_layer[i]--;
    }
  }
  inputed_layer[index] = 0;
  pressed_num--;
}

void pressed_custom_layer(uint8_t index) {
  pressed_num++;
  inputed_layer[index] = pressed_num;
}

uint16_t key_tapping_timer = 0;
void set_tapping_timer(void){
  key_tapping_timer = timer_read();
}
// tapかどうか
bool is_tapped(void) {
  if(KEY_TAPPING_TERM >= timer_elapsed(key_tapping_timer)) {
    set_tapping_timer();
    return true;
  }
  return false;
}

#define SHIFT_ON register_code(KC_LSHIFT);\
                _shift = true;
#define SHIFT_OFF unregister_code(KC_LSHIFT);\
                  _shift = false;
#define QWERTY_ON layer_on(_QWERTY);\
                  _qwerty = true;
#define QWERTY_OFF layer_off(_QWERTY);\
                  _qwerty = false;

bool is_custom_layer_button_on(uint16_t exclude){
  for (int i = 0; i< _LAYER_NUM;i++){
    if (i == exclude) {
      continue;
    }
    if (inputed_layer[i] > 0) {
      return true;
    }
  }
  return false;
}

//return true -> 後続処理する
//return false -> 後続処理しない
bool process_record_custom_layer(bool pressed, bool is_inputted){

  if(inputed_layer[_THUMB_LL] == 1) {
    if(inputed_layer[_THUMB_LC] == 2) {
        if(pressed) {
          layer_on(_ICHIKAWA_LLLC);
        }else {
          layer_off(_ICHIKAWA_LLLC);
        }
    }
    else if(inputed_layer[_THUMB_RC] == 2) {
        if(pressed) {
          layer_on(_ICHIKAWA_LLRC);
        }else {
          layer_off(_ICHIKAWA_LLRC);
        }
    }
    if(pressed) {
      layer_on(_MOUSE);
    }else {
      layer_off(_MOUSE);
    }
  }

  if(inputed_layer[_THUMB_LC] == 1) {
    if(inputed_layer[_THUMB_LL] == 2) {
        if(pressed) {
          layer_on(_ICHIKAWA_LCLL);
        }else {
          layer_off(_ICHIKAWA_LCLL);
        }
    }
    else if(inputed_layer[_THUMB_RC] == 2) {
        if(pressed) {
          layer_on(_ICHIKAWA_LCRC);
        }else {
          layer_off(_ICHIKAWA_LCRC);
        }
    }
    if(pressed) {
      layer_on(_SYMBOL_LAYER);
    }else {
      layer_off(_SYMBOL_LAYER);
    }
  }

  if(inputed_layer[_THUMB_LR] == 1) {
    if(pressed) {
      QWERTY_ON
      register_code(KC_LCTRL);
      _ctrl = true;
    }else {
      QWERTY_OFF
      _ctrl = false;
      unregister_code(KC_LCTRL);
    }
  }

  if(inputed_layer[_THUMB_RL] == 1) {
    if(pressed) {
      layer_on(_MTGAP_SHIFT);
      _mtgap_shift = true;
    } else {
      layer_off(_MTGAP_SHIFT);
      _mtgap_shift = false;
    }
    if(is_custom_layer_button_on(_THUMB_RL)){
      if(pressed) {
        SHIFT_ON
      } else {
        SHIFT_OFF
      }
    }
  }
  else if(inputed_layer[_THUMB_RL] > 1) {
    if(pressed) {
      _mtgap_shift = true;
      SHIFT_ON
    } else {
      _mtgap_shift = false;
      SHIFT_OFF
    }
  }

  if(inputed_layer[_THUMB_RC] == 1) {
    if(inputed_layer[_THUMB_LL] == 2) {
        if(pressed) {
          layer_on(_ICHIKAWA_RCLL);
        }else {
          layer_off(_ICHIKAWA_RCLL);
        }
    }
    else if(inputed_layer[_THUMB_LC] == 2) {
        if(pressed) {
          layer_on(_ICHIKAWA_RCLC);
        }else {
          layer_off(_ICHIKAWA_RCLC);
        }
    }
    if(pressed) {
      layer_on(_NUM_LAYER);
    }
    else {
      layer_off(_NUM_LAYER);
    }
  }

  if(inputed_layer[_THUMB_RR] == 1) {
    if(pressed) {
      set_tapping_timer();
      QWERTY_ON
      register_code(ICH_MOD_L_KEY);
      _gui = true;
    }else {
      QWERTY_OFF
      _gui = false;
      //
      if(!_ctrl){
        register_code(KC_LCTRL);
        unregister_code(KC_LCTRL);
        unregister_code(ICH_MOD_L_KEY);
      }
      else if(!_shift){
        register_code(KC_LSHIFT);
        unregister_code(KC_LSHIFT);
        unregister_code(ICH_MOD_L_KEY);
      }
      else if(!_alt){
        register_code(KC_LALT);
        unregister_code(KC_LALT);
        unregister_code(ICH_MOD_L_KEY);
      }
      else {
        unregister_code(ICH_MOD_L_KEY);
      }
    }
  }

// 以下は一回押す系の処理
// 3キー以上押すことは定義してないので3以上でreturn
  if (pressed_num >= 3) return false;

  if(inputed_layer[_THUMB_LL] == 1) {
    if(inputed_layer[_THUMB_LC] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(TASK_MANAGER);
            unregister_code16(TASK_MANAGER);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_LR] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(LOGOUT);
            unregister_code16(LOGOUT);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_RL] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(LSFT(KC_ENTER));
            unregister_code16(LSFT(KC_ENTER));
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_RC] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(WINDOW_OP_2);
            unregister_code16(WINDOW_OP_2);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_RR] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(LSFT(LCTL(KC_ENTER)));
            unregister_code16(LSFT(LCTL(KC_ENTER)));
          }
          return false;
        }
    }
    if(pressed) {
      set_tapping_timer();
      return false;
    }else {
      if(!is_inputted && is_tapped()) {
        register_code(KC_BSPACE);
        unregister_code(KC_BSPACE);
      }
      return false;
    }
  }

  if(inputed_layer[_THUMB_LC] == 1) {
    if(inputed_layer[_THUMB_LL] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code(KC_PSCREEN);
            unregister_code(KC_PSCREEN);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_LR] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code(KC_APPLICATION);
            unregister_code(KC_APPLICATION);
          }
          return false;
        }
    }
    if(inputed_layer[_THUMB_RL] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(CLIPBOARD);
            unregister_code16(CLIPBOARD);
          }
          return false;
        }
    }
    if(inputed_layer[_THUMB_RC] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code(KC_TAB);
            unregister_code(KC_TAB);
          }
          return false;
        }
    }
    if(inputed_layer[_THUMB_RR] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(KILL_WINDOW);
            unregister_code16(KILL_WINDOW);
          }
          return false;
        }
    }
    if(pressed) {
      set_tapping_timer();
      return false;
    }else {
      if(!is_inputted && is_tapped()) {
        register_code(KC_MHEN);
        unregister_code(KC_MHEN);
        is_new_gata = false;
        layer_off(_N_GETA);
      }
      return false;
    }
  }

  if(inputed_layer[_THUMB_LR] == 1) {
    if(pressed) {
      set_tapping_timer();
      return false;
    }else {
      if(!is_inputted && is_tapped()) {
        register_code(KC_ENTER);
        unregister_code(KC_ENTER);
      }
      return false;
    }
  }

  if(inputed_layer[_THUMB_RL] == 1) {
    if(pressed) {
      set_tapping_timer();
      return false;
    }else {
      if(!is_inputted && is_tapped()) {
        register_code(KC_SPACE);
        unregister_code(KC_SPACE);
      }
      return false;
    }
  }

  if(inputed_layer[_THUMB_RC] == 1) {
    if(inputed_layer[_THUMB_LL] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(WINDOW_OP_1);
            unregister_code16(WINDOW_OP_1);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_LC] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(LSFT(KC_TAB));
            unregister_code16(LSFT(KC_TAB));
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_LR] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(WINDOW_OP_3);
            unregister_code16(WINDOW_OP_3);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_RL] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code16(WINDOW_OP_4);
            unregister_code16(WINDOW_OP_4);
          }
          return false;
        }
    }
    else if(inputed_layer[_THUMB_RR] == 2) {
        if(pressed) {
          set_tapping_timer();
          return false;
        }else {
          if(!is_inputted && is_tapped()) {
            register_code(KC_PAUSE);
            unregister_code(KC_PAUSE);
          }
          return false;
        }
    }
    if(pressed) {
      set_tapping_timer();
      return false;
    }else {
      if(!is_inputted && is_tapped()) {
        register_code(KC_HENK);
        unregister_code(KC_HENK);
        is_new_gata = true;
        layer_on(_N_GETA);
      }
      return false;
    }
  }

  if(inputed_layer[_THUMB_RR] == 1) {
    if(pressed) {
      set_tapping_timer();
      return false;
    }else {
      if(!is_inputted && is_tapped()) {
        if(_alt){
          unregister_code(KC_LALT);
          _alt = false;
        }
        else {
          register_code(KC_LALT);
          _alt = true;
        }
      }
      return false;
    }
  }

  return true;
}

// char itoa(uint16_t value) {
//   char a[255];
//   itoa(value,a,10);
//   return a;
// }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NO_KEY_LAYOUT_I] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_MTGAP] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_ENTER,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPACE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ICH_RALT,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSHIFT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ICH_RGUI,KC_NO,KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO ,KC_NO, ICH_RCTRL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                THUMB_LL,THUMB_LC,THUMB_LR,THUMB_RL,THUMB_RC,THUMB_RR \
                              //`--------------------'  `--------------------'
  ),

  [_MTGAP_SHIFT] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_N_GETA] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, NG_GE, NG_NI, NG_HA, KC_COMM, NG_TI,                NG_GU, NG_BA, NG_KO, NG_GA, NG_HI, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_NO, NG_TO, NG_KA, NG_NN, NG_XTU,                 NG_KU, NG_U, NG_I, NG_SI, NG_NA, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_SU, NG_MA, NG_KI, NG_RU, NG_TU,                  NG_TE, NG_TA, NG_DE, KC_DOT, NG_BU, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA_MIDDLE] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, NG_FA, NG_GO, NG_HU, NG_FI, NG_FE,                NG_WI, NG_PA, NG_YO, NG_MI, NG_WE, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_HO, NG_ZI, NG_RE, NG_MO, NG_YU,                 NG_HE, NG_A, NG_XYA, NG_XYU, NG_E, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_ZU, NG_ZO, NG_BO, NG_MU, NG_FO,                  NG_SE, NG_NE, NG_BE, NG_PU, NG_VU, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA_RING] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, NG_DI, NG_ME, NG_KE, NG_THI, NG_DHI,                NG_SYE, NG_PE, NG_DO, NG_YA, NG_JE, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_WO, NG_SA, NG_O, NG_RI, NG_ZU,                    NG_BI, NG_RA, NG_XYO,  NG_XWA,  NG_SO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_ZE, NG_ZA, NG_GI, NG_RO, NG_NU,                  NG_WA, NG_DA, NG_PI, NG_PO, NG_TYE, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA_MIDDLE_TOP] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, NG_HYU, NG_SYU, NG_SYO, NG_KYU, NG_TYU,            NG_MYA, NG_BYA,NG_PYA, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_HYO, NG_XA, NG_XI, NG_KYO, NG_TYO,              NG_MYU, NG_BYU,NG_PYU, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_HYA, NG_XU, NG_SYA, NG_KYA, NG_TYA,             NG_MYO, NG_BYO,NG_PYO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA_RING_TOP] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, NG_RYU, NG_JU, NG_JO, NG_GYU, NG_NYU,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_RYO, NG_XE, NG_XO, NG_GYO, NG_NYO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, NG_RYA, NG_UXO, NG_JA, NG_GYA, NG_NYA,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA_LITTLE_R] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA_LITTLE_L] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L,KC_SCLN,KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_NUM_LAYER] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_SYMBOL_LAYER] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ICHIKAWA_LCRC] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ICHIKAWA_LLRC] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ICHIKAWA_RCLC] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ICHIKAWA_RCLL] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ICHIKAWA_LLLC] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_ICHIKAWA_LCLL] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  ),

  [_MOUSE] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                               KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS \
                              //`--------------------'  `--------------------'
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(current_keycode == keycode){
    IS_INPUT = false;
  } else {
    IS_INPUT = true;
  }
  previous_keycode = current_keycode;
  current_keycode = keycode;

  switch (keycode) {
    case NG_I:
      if(record->event.pressed) {
        layer_on(_N_GETA_MIDDLE);
        return false;
      } else{
        layer_off(_N_GETA_MIDDLE);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_KA:
      if(record->event.pressed) {
        layer_on(_N_GETA_MIDDLE);
        return false;
      } else{
        layer_off(_N_GETA_MIDDLE);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_SI:
      if(record->event.pressed) {
        layer_on(_N_GETA_RING);
        return false;
      } else{
        layer_off(_N_GETA_RING);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_TO:
      if(record->event.pressed) {
        layer_on(_N_GETA_RING);
        return false;
      } else{
        layer_off(_N_GETA_RING);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_KO:
      if(record->event.pressed) {
        layer_on(_N_GETA_MIDDLE_TOP);
        return false;
      } else{
        layer_off(_N_GETA_MIDDLE_TOP);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_HA:
      if(record->event.pressed) {
        layer_on(_N_GETA_MIDDLE_TOP);
        return false;
      } else{
        layer_off(_N_GETA_MIDDLE_TOP);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_GA:
      if(record->event.pressed) {
        layer_on(_N_GETA_RING_TOP);
        return false;
      } else{
        layer_off(_N_GETA_RING_TOP);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_NI:
      if(record->event.pressed) {
        layer_on(_N_GETA_RING_TOP);
        return false;
      } else{
        layer_off(_N_GETA_RING_TOP);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_NO:
      if(record->event.pressed) {
        layer_on(_N_GETA_LITTLE_L);
        return false;
      } else{
        layer_off(_N_GETA_LITTLE_L);
        if(IS_INPUT){
          return false;
        }
      }
      break;
    case NG_NA:
      if(record->event.pressed) {
        layer_on(_N_GETA_LITTLE_R);
        return false;
      } else{
        layer_off(_N_GETA_LITTLE_R);
        if(IS_INPUT){
          return false;
        }
      }
      break;

    case THUMB_LL:
      if(record->event.pressed) {
        pressed_custom_layer(_THUMB_LL);
        if(!process_record_custom_layer(record->event.pressed,IS_INPUT)){
          return false;
        }
      }else {
        process_record_custom_layer(record->event.pressed,IS_INPUT);
        release_custom_layer(_THUMB_LL);
        if(!process_record_custom_layer(true,true)){
          return false;
        }
      }
      break;
    case THUMB_LC:
      if(record->event.pressed) {
        pressed_custom_layer(_THUMB_LC);
        if(!process_record_custom_layer(record->event.pressed,IS_INPUT)){
          return false;
        }
      }else {
        process_record_custom_layer(record->event.pressed,IS_INPUT);
        release_custom_layer(_THUMB_LC);
        if(!process_record_custom_layer(true,true)){
          return false;
        }
      }
      break;
    case THUMB_LR:
      if(record->event.pressed) {
        pressed_custom_layer(_THUMB_LR);
        if(!process_record_custom_layer(record->event.pressed,IS_INPUT)){
          return false;
        }
      }else {
        process_record_custom_layer(record->event.pressed,IS_INPUT);
        release_custom_layer(_THUMB_LR);
        if(!process_record_custom_layer(true,true)){
          return false;
        }
      }
      break;
    case THUMB_RL:
      if(record->event.pressed) {
        pressed_custom_layer(_THUMB_RL);
        if(!process_record_custom_layer(record->event.pressed,IS_INPUT)){
          return false;
        }
      }else {
        process_record_custom_layer(record->event.pressed,IS_INPUT);
        release_custom_layer(_THUMB_RL);
        if(!process_record_custom_layer(true,true)){
          return false;
        }
      }
      break;
    case THUMB_RC:
      if(record->event.pressed) {
        pressed_custom_layer(_THUMB_RC);
        if(!process_record_custom_layer(record->event.pressed,IS_INPUT)){
          return false;
        }
      }else {
        process_record_custom_layer(record->event.pressed,IS_INPUT);
        release_custom_layer(_THUMB_RC);
        if(!process_record_custom_layer(true,true)){
          return false;
        }
      }
      break;
    case THUMB_RR:
      if(record->event.pressed) {
        pressed_custom_layer(_THUMB_RR);
        if(!process_record_custom_layer(record->event.pressed,IS_INPUT)){
          return false;
        }
      }else {
        process_record_custom_layer(record->event.pressed,IS_INPUT);
        release_custom_layer(_THUMB_RR);
        if(!process_record_custom_layer(true,true)){
          return false;
        }
      }
      break;
      return false;
  }

  if(is_new_gata && !process_record_new_gata(keycode, record)){
    //IS_INPUT = true;
    return false;
  }

  return true;
}

