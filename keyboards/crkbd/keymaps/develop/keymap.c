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
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  NG_A,
  NG_I,
  NG_U,
  NG_E,
  NG_O,
  NG_GA
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

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

const char str[26][1] PROGMEM = {
  "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","w","x","y","z"
};

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



const char PROGMEM N_GETA_1[5][1] = {
  "a","i","u","e","o"
};

const char PROGMEM N_GETA_2[91][2] = {
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
"ja", "ji", "ju", "je", "jo",
"qa", "qi", "qe", "qo",
"ya", "yu", "ye", "yo",
"wa", "wi", "we", "wo",
"fa", "fi", "fe", "fo"
};

const char PROGMEM N_GETA_3[58][3] = {
"kya", "kyi", "kyu", "kye", "kyo",
"gya", "gyi", "gyu", "gye", "gyo",
"sya", "syi", "syu", "sye", "syo",
"zya", "zyi", "zyu", "zye", "zyo",
"tya", "tyi", "tyu", "tye", "tyo",
"nya", "nyi", "nyu", "nye", "nyo",
"hya", "hyi", "hyu", "hye", "hyo",
"bya", "byi", "byu", "bye", "byo",
"pya", "pyi", "pyu", "pye", "pyo",
"mya", "myi", "myu", "mye", "myo",
"rya", "ryi", "ryu", "rye", "ryo",
"xya", "xyu", "xyo"
};

bool is_new_gata = true;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      KC_ESC,    NG_GA,    KC_W,     KC_MS_ACCEL0,     KC_R,     KC_T, KC_Y,     KC_MS_BTN1,     KC_MS_UP,     KC_MS_BTN2,     KC_MS_WH_UP,  KC_BSPC,\
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
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
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

bool send_new_gata_string(uint16_t keycode, keyrecord_t *record){
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  if(is_new_gata && send_new_gata_string(keycode, record)){
    return true;
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
        send_string_P(&N_GETA_1[0][0]);
      }
      return true;
      case NG_A:
      if(record->event.pressed) {
        // send_string_P(str[1]);
        send_string_P(&N_GETA_2[2][0]);
      }
      return true;
      case NG_O:
      if(record->event.pressed) {
        // send_string_P(str[1]);
        send_string_P(&*&N_GETA_3[4][0]);
        send_string_P(N_GETA_1[0]);
      }
      return true;
  }
  return true;
}

