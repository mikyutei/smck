#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 16
#define _RAISE 17
#define _ADJUST 18

#define _N_GETA 2
#define _N_GETA_L 3
#define _N_GETA_R 4
#define _N_GETA_TL 5
#define _N_GETA_TR 6
#define _N_GETA_CR 7
#define _N_GETA_CL 8


//macro setting
char macro_buf[30];


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
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

const char PROGMEM N_GETA_2[87][3] = {
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
"nn"
};

const char PROGMEM N_GETA_3[74][4] = {
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
"xya", "xyu", "xyo",
"xtu"
};

//japanese or english IME status on keyboard
bool is_new_gata = true;

//input or not input use sendString
bool is_input = false;

// 文字送信間隔のためのtimer
uint16_t key_repeat_timer = 0;

//同じ文字列か判定用
uint16_t previous_keycode = 0;
uint16_t current_keycode = 0;

#define KEY_REPEAT_DERAY 10

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

if (!record->event.pressed) {
  is_input = false;
}

if (keycode >= NG_A && NG_NN >= keycode) {
  if(NG_KA <= keycode) {
    set_new_geta_string(&N_GETA_2[(uint8_t)(keycode - NG_KA)][0]);
  }else if (NG_KYA <= keycode) {
    set_new_geta_string(&N_GETA_3[(uint8_t)(keycode - NG_KYA)][0]);
  }else {
    set_new_geta_string(&N_GETA_1[(uint8_t)( keycode - NG_A) ][0]);
  }

  if (record->event.pressed) {
    is_input = true;
  }
  return false;
}

return true;
}


#define KC_TO TO
#define KC_MO MO
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      TO(_N_GETA),    NG_GA,    KC_W,     KC_MS_ACCEL0,     KC_R,     KC_T, KC_Y,     KC_MS_BTN1,     KC_MS_UP,     KC_MS_BTN2,     KC_MS_WH_UP,  KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TO(_LOWER),NG_A,    KC_S,     KC_MS_ACCEL1,     KC_F,     KC_G, KC_H,     KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,  KC_MS_WH_DOWN,  KC_QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_LSFT, NG_O,      KC_X,     KC_MS_ACCEL2,     KC_V,     KC_B, KC_N,     KC_M,  KC_COMM,   KC_DOT ,  KC_SLSH,  KC_RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_ALTKN, KC_MHEN,   KC_ENT,      KC_SPC, KC_HENK, KC_GUIEI \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        BSPC,     Y,     P,     O,     U,     J,                      K,     D,     L,     C,     W,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      TO(_QWERTY),     I,     N,     E,     A,     COMM,                      M,     H,     T,     S,  R,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Q,     Z,     SLSH,     DOT,     QUOT,                      B,     F,  G,   V,  X,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, MO(_RAISE),   SPC,      LSFT, MO(_RAISE), ALTKN \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  Y, P, O, U, J,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  I,  N,  E, A, SCLN,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  Q,  Z,  LT, GT, QUES,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER,   SPC,      ENT, RAISE, ALTKN \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  GUIEI, LOWER,   SPC,      ENT, RAISE, ALTKN \
                              //`--------------------'  `--------------------'
  ),
  [_N_GETA] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      KC_NO, NG_GE, NG_NI, NG_HA, KC_COMM, NG_TI,                NG_GU, NG_BA, NG_KO, NG_GA, NG_HI, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO, NG_NO, NG_TO, NG_KA, NG_NN, NG_XTU,                 NG_KU, NG_U, NG_I, NG_SI, NG_NA, KC_NO,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO, NG_SU, NG_MA, NG_KI, NG_RU, NG_TU,                  NG_TE, NG_TA, NG_DE, KC_DOT, NG_BU, KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  KC_NO, KC_NO,   KC_NO,      KC_NO, KC_NO, KC_NO \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  //eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }

  if(is_input && is_input_time(current_keycode) && is_new_gata) {
    send_string(macro_buf);
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

   current_keycode = keycode;

   if(is_new_gata && !process_record_new_gata(keycode, record)){
     return false;
   }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
      case NG_GA:
      if(record->event.pressed) {
        // send_string_P(str[0]);
        send_string(N_GETA_1[0]);
      }
      return false;
      case NG_A:
      if(record->event.pressed) {
        // send_string_P(str[1]);
        //send_string(N_GETA_2[2]);
        b = NG_A;
      }
      return false;
      case NG_O:
      if(record->event.pressed) {
        if (b >= NG_A && NG_NN >= b) {
          if(NG_KA <= b) {
            set_new_geta_string(&N_GETA_2[(uint8_t)(b - NG_KA)][0]);
            //sprintf(macro_buf,"%d",((uint8_t)(b - NG_KA)));
          }else if (NG_KYA <= b) {
            set_new_geta_string(&N_GETA_3[(uint8_t)(b - NG_KYA)][0]);
            //sprintf(macro_buf,"%d",((uint8_t)(b - NG_KYA)));
          }else {
            set_new_geta_string(&N_GETA_1[(uint8_t)( b - NG_A) ][0]);
            //sprintf(macro_buf,"%d",((uint8_t)(b - NG_A)));
          }
        }

        sprintf(macro_buf,"%d", is_input_time(keycode));
        //send_string(macro_buf);
        tap_code(KC_A);
        b++;
        // send_string_P(str[1]);
        // char a[10];
        // strcpy_P(a,N_GETA_3[7]);
        // send_string(a);
        // send_string(&N_GETA_1[0]);
      }
      return false;
  }
  return true;
}

