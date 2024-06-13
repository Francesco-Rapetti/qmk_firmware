/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//     case LAYER_THREE:
//         if (record->event.pressed) {
//             // when keycode LAYER_THREE is pressed
//             rgb_matrix_set_color(0, RGB_RED);
//             rgb_matrix_set_color(73, RGB_RED);
//             SEND_STRING("Switched to Layer 3");
//         } else {
//             // when keycode LAYER_THREE is released
//         }
//         break;
//     }
//     return true;
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// layer 1 Mac
[0] = LAYOUT_ansi_84(
	KC_ESC, 	KC_BRID,  	KC_BRIU,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	MAC_PRTA,	KC_INS,		KC_DEL,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 				KC_BSPC,	LNK_BLE1,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 				KC_BSLS,	LNK_BLE2,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 						KC_ENT,		LNK_BLE3,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,	KC_UP,		TG(2),
	KC_LCTL,	KC_LALT,	KC_LGUI,										KC_SPC, 							KC_RGUI,	MO(1),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 1 Mac Fn
[1] = LAYOUT_ansi_84(
	_______, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	MAC_PRT,	_______,	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 				_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, 			BAT_SHOW,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 						_______,	_______,
	_______,				_______,   	_______,   	RGB_TEST,  	_______,   	BAT_NUM,   	_______,	MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,	RGB_VAI,	TG(2),
	_______,	_______,	_______,										_______, 							_______,	MO(1),   	_______,				RGB_MOD,	RGB_VAD,    RGB_HUI),

// layer 2 Mac
[2] = LAYOUT_ansi_84(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	MAC_PRT,	KC_INS,	    KC_DEL,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 				KC_BSPC,	LNK_BLE1,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 				KC_BSLS,	LNK_BLE2,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 						KC_ENT,		LNK_BLE3,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,	KC_UP,		TG(2),
	KC_LCTL,	KC_LALT,	KC_LGUI,										KC_SPC, 							KC_RGUI,	MO(3),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 2 Mac Fn
[3] = LAYOUT_ansi_84(
	_______, 	KC_BRID,  	KC_BRIU,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	MAC_PRTA,	_______,	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 				_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, 			BAT_SHOW,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 						_______,	_______,
	_______,				_______,   	_______,   	RGB_TEST,  	_______,   	BAT_NUM,   	_______,	MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,	RGB_VAI,	TG(2),
	_______,	_______,	_______,										_______, 							_______,	MO(3),   	_______,				RGB_MOD,	RGB_VAD,    RGB_HUI),

// layer 1 Win
[4] = LAYOUT_ansi_84(
    //KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PSCR,	KC_INS,		KC_DEL,
	KC_ESC, 	KC_BRID,   	KC_BRIU,    WIN_TASK,  	WIN_SEARCH, WIN_VOICE,  WIN_DND,   	KC_MPRV,   	KC_MPLY,   	KC_MNXT,  	KC_MUTE, 	KC_VOLD, 	KC_VOLU,	KC_PSCR,	WIN_CONSOLE,KC_DEL,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 				KC_BSPC,	LNK_BLE1,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 				KC_BSLS,	LNK_BLE2,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 						KC_ENT,		LNK_BLE3,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,	KC_UP,		TG(6),
	KC_LCTL,	KC_LGUI,	KC_LALT,										KC_SPC, 							KC_RALT,	MO(5),   	KC_RCTL,			    KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 1 Win Fn
[5] = LAYOUT_ansi_84(
	_______, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	_______,	_______,	_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 				_______,	_______,
	_______, 	KC_BTN2,    KC_MS_U,    KC_BTN1,    KC_WH_U,    KC_BTN3,	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, 			BAT_SHOW,	_______,
	_______,	KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_WH_D,    _______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 						KC_BTN1,	_______,
	KC_ACL2,				_______,   	_______,   	RGB_TEST,  	_______,   	BAT_NUM,   	_______,	MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,	RGB_VAI,	TG(6),
	KC_ACL1,	_______,	_______,										_______, 							_______,	MO(5),   	_______,			    RGB_MOD,	RGB_VAD,    RGB_HUI),

    // layer 2 Win
[6] = LAYOUT_ansi_84(
    //KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PSCR,	KC_INS,		KC_DEL,
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_PSCR,	WIN_CONSOLE,KC_DEL,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 				KC_BSPC,	LNK_BLE1,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC, 				KC_BSLS,	LNK_BLE2,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 						KC_ENT,		LNK_BLE3,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,	KC_UP,		TG(6),
	KC_LCTL,	KC_LGUI,	KC_LALT,										KC_SPC, 							KC_RALT,	MO(7),   	KC_RCTL,			    KC_LEFT,	KC_DOWN,    KC_RGHT),

// layer 2 Win Fn
[7] = LAYOUT_ansi_84(
	_______, 	KC_BRID,   	KC_BRIU,    WIN_TASK,  	WIN_SEARCH, WIN_VOICE,  WIN_DND,   	KC_MPRV,   	KC_MPLY,   	KC_MNXT,  	KC_MUTE, 	KC_VOLD, 	KC_VOLU,	_______,	_______,    _______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 				_______,	_______,
	_______, 	KC_BTN2,    KC_MS_U,    KC_BTN1,    KC_WH_U,    KC_BTN3,	_______,   	_______,   	_______,   	_______,  	_______,   	DEV_RESET,	SLEEP_MODE, 			BAT_SHOW,	_______,
	_______,	KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_WH_D,    _______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 						KC_BTN1,	_______,
	KC_ACL2,				_______,   	_______,   	RGB_TEST,  	_______,   	BAT_NUM,   	_______,	MO(8), 		RGB_SPD,	RGB_SPI,	_______,				_______,	RGB_VAI,	TG(6),
	KC_ACL1,	_______,	_______,										_______, 							_______,	MO(7),   	_______,			    RGB_MOD,	RGB_VAD,    RGB_HUI),

// layer extra
[8] = LAYOUT_ansi_84(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 				_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 				_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,	_______, 	 						_______,	_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	SIDE_SPD,	SIDE_SPI,	_______,				_______,	SIDE_VAI,	_______,
	_______,	_______,	_______,										_______, 							_______,	MO(4),   	_______,				SIDE_MOD,	SIDE_VAD,   SIDE_HUI)
};
