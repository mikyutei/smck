#pragma once

#include "keymap.h"

#ifdef LANG_JP
  // Row 1
  #define ICH_ZKHK KC_GRV  // Zenkaku ↔︎ Hankaku ↔ Kanji (半角 ↔ 全角 ↔ 漢字)
  #define ICH_CIRC KC_EQL  // ^
  #define ICH_YEN  KC_INT3 // ¥
  // Row 2
  #define ICH_AT   KC_LBRC // @
  #define ICH_LBRC KC_RBRC // [
  // Row 3
  #define ICH_EISU KC_CAPS // Eisū (英数)
  #define ICH_COLN KC_QUOT // :
  #define ICH_RBRC KC_NUHS // ]
  // Row 4
  #define ICH_BSLS KC_INT1 // (backslash)
  // Row 5
  #define ICH_MHEN KC_INT5 // Muhenkan (無変換)
  #define ICH_HENK KC_INT4 // Henkan (変換)
  #define ICH_KANA KC_INT2 // Katakana ↔ Hiragana ↔ Rōmaji (カタカナ ↔ ひらがな ↔ ローマ字)

  /* Shifted symbols
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
  * │   │ ! │ " │ # │ $ │ % │ & │ ' │ ( │ ) │   │ = │ ~ │ | │   │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
  * │     │   │   │   │   │   │   │   │   │   │   │ ` │ { │     │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
  * │ Caps │   │   │   │   │   │   │   │   │   │ + │ * │ } │    │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
  * │        │   │   │   │   │   │   │   │ < │ > │ ? │ _ │      │
  * ├─────┬──┴┬──┴──┬┴───┴┬──┴───┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬─────┤
  * │     │   │     │     │         │     │   │   │   │   │     │
  * └─────┴───┴─────┴─────┴─────────┴─────┴───┴───┴───┴───┴─────┘
  */
  // Row 1
  #define ICH_EXLM S(KC_1)    // !
  #define ICH_DQUO S(KC_2)    // "
  #define ICH_HASH S(KC_3)    // #
  #define ICH_DLR  S(KC_4)    // $
  #define ICH_PERC S(KC_5)    // %
  #define ICH_AMPR S(KC_6)    // &
  #define ICH_QUOT S(KC_7)    // '
  #define ICH_LPRN S(KC_8)    // (
  #define ICH_RPRN S(KC_9)    // )
  #define ICH_EQL  S(KC_MINS) // =
  #define ICH_TILD S(KC_CIRC) // ~
  #define ICH_PIPE S(KC_YEN)  // |
  // Row 2
  #define ICH_GRV  S(KC_AT)   // `
  #define ICH_LCBR S(KC_LBRC) // {
  // Row 3
  #define ICH_CAPS S(KC_EISU) // Caps Lock
  #define ICH_PLUS S(KC_SCLN) // +
  #define ICH_ASTR S(KC_COLN) // *
  #define ICH_RCBR S(KC_RBRC) // }
  // Row 4
  #define ICH_LABK S(KC_COMM) // <
  #define ICH_RABK S(KC_DOT)  // >
  #define ICH_QUES S(KC_SLSH) // ?
  #define ICH_UNDS S(KC_BSLS) // _

  #define ICH_MEISU KC_LANG2 // Eisū (英数) on macOS
  #define ICH_MKANA KC_LANG1 // Kana (かな) on macOS
#endif

#ifdef LANG_US
  // Row 1
  #define ICH_ZKHK RALT(KC_GRV)  // Zenkaku ↔︎ Hankaku ↔ Kanji (半角 ↔ 全角 ↔ 漢字)
  #define ICH_CIRC KC_CIRC  // ^
  #define ICH_YEN  KC_SLSH // ¥
  // Row 2
  #define ICH_AT   KC_AT // @
  #define ICH_LBRC KC_LBRC // [

  // Row 3
  #define ICH_EISU KC_CAPS // Eisū (英数)
  #define ICH_COLN KC_COLN // :
  #define ICH_RBRC KC_RBRC // ]
  // Row 4
  #define ICH_BSLS KC_BSLS // (backslash)
  // Row 5
  #define ICH_MHEN KC_INT5 // Muhenkan (無変換)
  #define ICH_HENK KC_INT4 // Henkan (変換)
  #define ICH_KANA KC_INT2 // Katakana ↔ Hiragana ↔ Rōmaji (カタカナ ↔ ひらがな ↔ ローマ字)

  /* Shifted symbols
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
  * │   │ ! │ " │ # │ $ │ % │ & │ ' │ ( │ ) │   │ = │ ~ │ | │   │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
  * │     │   │   │   │   │   │   │   │   │   │   │ ` │ { │     │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
  * │ Caps │   │   │   │   │   │   │   │   │   │ + │ * │ } │    │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
  * │        │   │   │   │   │   │   │   │ < │ > │ ? │ _ │      │
  * ├─────┬──┴┬──┴──┬┴───┴┬──┴───┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬─────┤
  * │     │   │     │     │         │     │   │   │   │   │     │
  * └─────┴───┴─────┴─────┴─────────┴─────┴───┴───┴───┴───┴─────┘
  */
  // Row 1
  #define ICH_EXLM KC_EXLM    // !
  #define ICH_DQUO KC_DQUO    // "
  #define ICH_HASH KC_HASH    // #
  #define ICH_DLR  KC_DLR    // $
  #define ICH_PERC KC_PERC    // %
  #define ICH_AMPR KC_AMPR    // &
  #define ICH_QUOT KC_QUOT    // '
  #define ICH_LPRN KC_LPRN    // (
  #define ICH_RPRN ICH_RPRN    // )
  #define ICH_EQL  KC_EQL // =
  #define ICH_TILD KC_TILD // ~
  #define ICH_PIPE KC_PIPE  // |
  // Row 2
  #define ICH_GRV  KC_GRV   // `
  #define ICH_LCBR KC_LCBR // {
  // Row 3
  #define ICH_CAPS KC_CAPS // Caps Lock
  #define ICH_PLUS KC_PLUS // +
  #define ICH_ASTR KC_ASTR // *
  #define ICH_RCBR KC_RCBR // }
  // Row 4
  #define ICH_LABK KC_LABK // <
  #define ICH_RABK KC_RABK  // >
  #define ICH_QUES KC_QUES // ?
  #define ICH_UNDS KC_UNDS // _

  #define ICH_MEISU KC_LANG2 // Eisū (英数) on macOS
  #define ICH_MKANA KC_LANG1 // Kana (かな) on macOS
#endif
