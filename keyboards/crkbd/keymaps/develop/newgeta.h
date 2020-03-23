#pragma once
#include QMK_KEYBOARD_H

enum new_geta {
  NG_A = SAFE_RANGE,
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


void enable_new_geta(void);
void disable_new_geta(void);

bool process_record_new_gata(uint16_t keycode, keyrecord_t *record);
