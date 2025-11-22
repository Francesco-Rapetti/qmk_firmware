#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer 1 Mac
#if(WORK_MODE == THREE_MODE)
[0] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_F13, 	KC_DEL, 	MAC_PRTA,	TG(2),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	LNK_BLE1,	LNK_BLE2,	LNK_BLE3,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 				KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LOPT,	KC_LCMD,										KC_SPC, 							KC_RCMD,	KC_ROPT,	MO(1),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#else
[0] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_F13, 	KC_DEL, 	MAC_PRTA,	TG(2),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_NO,	    KC_NO,	    KC_NO,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 				KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LOPT,	KC_LCMD,										KC_SPC, 							KC_RCMD,	KC_ROPT,	MO(1),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#endif
// layer 1 Mac Fn
#if(WORK_MODE == THREE_MODE)
[1] = LAYOUT(
	_______, 	KC_SCRL,  	KC_PAUSE,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_PAUSE,   _______,	MAC_PRT,	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,    _______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(1),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#else
[1] = LAYOUT(
	_______, 	KC_SCRL,  	KC_PAUSE,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_PAUSE,   _______,	MAC_PRT,	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	_______,    _______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,    _______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(1),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#endif
// layer 2 Mac
#if(WORK_MODE == THREE_MODE)
[2] = LAYOUT(
	KC_ESC, 	KC_SCRL,  	KC_PAUSE,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_PAUSE, 	KC_DEL, 	MAC_PRTA,	TG(2),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	LNK_BLE1,	LNK_BLE2,	LNK_BLE3,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 				KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LOPT,	KC_LCMD,										KC_SPC, 							KC_RCMD,	KC_ROPT,	MO(3),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#else
[2] = LAYOUT(
	KC_ESC, 	KC_SCRL,  	KC_PAUSE,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_PAUSE, 	KC_DEL, 	MAC_PRTA,	TG(2),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_NO,	    KC_NO,	    KC_NO,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 				KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LOPT,	KC_LCMD,										KC_SPC, 							KC_RCMD,	KC_ROPT,	MO(3),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#endif
// layer 2 Mac Fn
#if(WORK_MODE == THREE_MODE)
[3] = LAYOUT(
	_______, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_F13,     _______,	MAC_PRT,	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,    _______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(3),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#else
[3] = LAYOUT(
	_______, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_F13,     _______,	MAC_PRT,	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	_______,    _______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,    _______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(3),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#endif
// layer 1 win
#if(WORK_MODE == THREE_MODE)
[4] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PAUSE, 	KC_SCRL,	WIN_PRTA,	TG(6),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	LNK_BLE1,	LNK_BLE2,	LNK_BLE3,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LWIN,	KC_LALT,										KC_SPC, 							KC_RALT,	KC_RWIN,	MO(5),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#else
[4] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PAUSE, 	KC_SCRL,	WIN_PRTA,	TG(6),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_NO,  	KC_NO,  	KC_NO,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LWIN,	KC_LALT,										KC_SPC, 							KC_RALT,	KC_RWIN,	MO(5),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#endif
// layer 1 win Fn
#if(WORK_MODE == THREE_MODE)
[5] = LAYOUT(
	_______, 	KC_BRID,  	KC_BRIU,  	_______, 	_______,  	_______,  	_______,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_NO,	    _______,	KC_PSCR,	TG(6),
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(5),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#else
[5] = LAYOUT(
	_______, 	KC_BRID,  	KC_BRIU,  	_______, 	_______,  	_______,  	_______,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_NO,	    _______,	KC_PSCR,	TG(6),
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	_______,    _______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(5),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#endif
// layer 2 win
#if(WORK_MODE == THREE_MODE)
[6] = LAYOUT(
	_______, 	KC_BRID,  	KC_BRIU,  	_______, 	_______,  	_______,  	_______,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_NO,	    _______,	KC_PSCR,	TG(6),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	LNK_BLE1,	LNK_BLE2,	LNK_BLE3,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LWIN,	KC_LALT,										KC_SPC, 							KC_RALT,	KC_RWIN,	MO(7),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#else
[6] = LAYOUT(
	_______, 	KC_BRID,  	KC_BRIU,  	_______, 	_______,  	_______,  	_______,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_NO,	    _______,	KC_PSCR,	TG(6),
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_VOLD,	KC_MPLY,	KC_VOLU,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_NO,  	KC_NO,  	KC_NO,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LWIN,	KC_LALT,										KC_SPC, 							KC_RALT,	KC_RWIN,	MO(7),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
#endif
// layer 2 win Fn
#if(WORK_MODE == THREE_MODE)
[7] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PAUSE, 	KC_SCRL,	WIN_PRTA,	TG(6),
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(5),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#else
[7] = LAYOUT(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PAUSE, 	KC_SCRL,	WIN_PRTA,	TG(6),
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	_______,    _______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	MO(9),		MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(3),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#endif
// layer 8
[8] = LAYOUT(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	RGB_TEST,  	_______,   	_______,   	_______,	_______, 	SIDE_SPD,	SIDE_SPI,	_______,				_______,				SIDE_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(4),		_______,				SIDE_MOD,   SIDE_VAD,	SIDE_HUI),
// layer 9
[9] = LAYOUT(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______, 	LOGO_SPD,	LOGO_SPI,	_______,				_______,				LOGO_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(5),		_______,				LOGO_MOD,   LOGO_VAD,	LOGO_HUI),
};
