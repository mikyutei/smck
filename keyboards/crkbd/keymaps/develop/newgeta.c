#include "newgeta.h"

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

void enable_new_geta(void){
  is_new_gata = true;
}
void disable_new_geta(void){
  is_new_gata = false;
}

//macro setting
char macro_buf[30];


// macro_buf set only new geta layout char
void set_new_geta_string(const char * src) {
  strcpy_P(macro_buf,src);
}

// 入力可能時間か確認
// bool is_input_time(uint16_t keycode) {

//   if(keycode != previous_keycode) {
//     previous_keycode = keycode;
//     key_repeat_timer = timer_read();
//     return true;
//   } else if(KEY_REPEAT_DERAY < timer_elapsed(key_repeat_timer)) {
//     key_repeat_timer = timer_read();
//     return true;
//   }
//   return false;
// }

bool process_record_new_gata(uint16_t keycode, keyrecord_t *record){
  if(!is_new_gata) return true;

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

