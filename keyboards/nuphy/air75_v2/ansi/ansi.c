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

// FIXME: set mic identifier according to current device
// TODO: set LALT+esc to ALT+F4

#include "ansi.h"
#include "usb_main.h"

user_config_t   user_config;
DEV_INFO_STRUCT dev_info = {
    .rf_baterry = 100,
    .link_mode  = LINK_USB,
    .rf_state   = RF_IDLE,
};

bool f_bat_hold        = 0;
bool f_sys_show        = 0;
bool f_sleep_show      = 0;
bool f_send_channel    = 0;
bool f_dial_sw_init_ok = 0;
bool f_rf_sw_press     = 0;
bool f_dev_reset_press = 0;
bool f_rgb_test_press  = 0;
bool f_bat_num_show    = 0;

bool mic1_active = 1;
bool mic2_active = 1;
bool mic3_active = 1;
bool mic4_active = 1;
bool mic5_active = 1;

uint16_t       rf_linking_time       = 0;
uint16_t       rf_link_show_time     = 0;
uint8_t        rf_blink_cnt          = 0;
uint16_t       no_act_time           = 0;
uint8_t        rf_sw_temp            = 0;
uint16_t       dev_reset_press_delay = 0;
uint16_t       rf_sw_press_delay     = 0;
uint16_t       rgb_test_press_delay  = 0;
uint8_t        host_mode             = 0;
host_driver_t *m_host_driver         = 0;

extern bool               f_rf_new_adv_ok;
extern report_keyboard_t *keyboard_report;
extern uint8_t            bitkb_report_buf[32];
extern uint8_t            bytekb_report_buf[8];
extern uint8_t            side_mode;
extern uint8_t            side_light;
extern uint8_t            side_speed;
extern uint8_t            side_rgb;
extern uint8_t            side_colour;

void    dev_sts_sync(void);
void    rf_uart_init(void);
void    rf_device_init(void);
void    uart_send_report_func(void);
void    uart_receive_pro(void);
uint8_t uart_send_cmd(uint8_t cmd, uint8_t ack_cnt, uint8_t delayms);
void    uart_send_report(uint8_t report_type, uint8_t *report_buf, uint8_t report_size);
void    side_speed_contol(uint8_t dir);
void    side_light_contol(uint8_t dir);
void    side_colour_control(uint8_t dir);
void    side_mode_control(uint8_t dir);
void    side_led_show(void);
void    sleep_handle(void);
void    bat_led_close(void);
void    num_led_show(void);
void    rgb_test_show(void);

/**
 * @brief  gpio initial.
 */
void gpio_init(void) {
    /* enable led power driver  */
    setPinOutput(DRIVER_LED_CS_PIN);
    setPinOutput(DRIVER_SIDE_CS_PIN);
    writePinLow(DRIVER_LED_CS_PIN);
    writePinLow(DRIVER_SIDE_CS_PIN);
    /* set side led pin output low */
    setPinOutput(DRIVER_SIDE_PIN);
    writePinLow(DRIVER_SIDE_PIN);
    /* config RF module pin */
    setPinOutput(NRF_WAKEUP_PIN);
    writePinHigh(NRF_WAKEUP_PIN);
    setPinInputHigh(NRF_TEST_PIN);
    /* reset RF module */
    setPinOutput(NRF_RESET_PIN);
    writePinLow(NRF_RESET_PIN);
    wait_ms(50);
    writePinHigh(NRF_RESET_PIN);
    /* config dial switch pin */
    setPinInputHigh(DEV_MODE_PIN);
    setPinInputHigh(SYS_MODE_PIN);
    /* open led DC driver */
    setPinOutput(DC_BOOST_PIN);
    writePinHigh(DC_BOOST_PIN);
}

/**
 * @brief  long press key process.
 */
void long_press_key(void) {
    static uint32_t long_press_timer = 0;

    if (timer_elapsed32(long_press_timer) < 100) return;
    long_press_timer = timer_read32();

    // Open a new RF device
    if (f_rf_sw_press) {
        rf_sw_press_delay++;
        if (rf_sw_press_delay >= RF_LONG_PRESS_DELAY) {
            f_rf_sw_press = 0;

            dev_info.link_mode   = rf_sw_temp;
            dev_info.rf_channel  = rf_sw_temp;
            dev_info.ble_channel = rf_sw_temp;

            uint8_t timeout = 5;
            while (timeout--) {
                uart_send_cmd(CMD_NEW_ADV, 0, 1);
                wait_ms(20);
                uart_receive_pro();
                if (f_rf_new_adv_ok) break;
            }
        }
    } else {
        rf_sw_press_delay = 0;
    }

    // The device is restored to factory Settings
    if (f_dev_reset_press) {
        dev_reset_press_delay++;
        if (dev_reset_press_delay >= DEV_RESET_PRESS_DELAY) {
            f_dev_reset_press = 0;

            if (dev_info.link_mode != LINK_USB) {
                if (dev_info.link_mode != LINK_RF_24) {
                    dev_info.link_mode   = LINK_BT_1;
                    dev_info.ble_channel = LINK_BT_1;
                    dev_info.rf_channel  = LINK_BT_1;
                }
            } else {
                dev_info.ble_channel = LINK_BT_1;
                dev_info.rf_channel  = LINK_BT_1;
            }

            uart_send_cmd(CMD_SET_LINK, 10, 10);
            wait_ms(500);
            uart_send_cmd(CMD_CLR_DEVICE, 10, 10);

            void device_reset_show(void);
            void device_reset_init(void);

            eeconfig_init();
            device_reset_show();
            device_reset_init();

            if (dev_info.sys_sw_state == SYS_SW_MAC) {
                default_layer_set(1 << 0);
                keymap_config.nkro = 0;
            } else {
                default_layer_set(1 << 4);
                keymap_config.nkro = 1;
            }
        }
    } else {
        dev_reset_press_delay = 0;
    }

    // Enter the RGB test mode
    if (f_rgb_test_press) {
        rgb_test_press_delay++;
        if (rgb_test_press_delay >= RGB_TEST_PRESS_DELAY) {
            f_rgb_test_press = 0;
            rgb_test_show();
        }
    } else {
        rgb_test_press_delay = 0;
    }
}

/**
 * @brief  Release all keys, clear keyboard report.
 */
void break_all_key(void) {
    uint8_t report_buf[16];
    bool    nkro_temp = keymap_config.nkro;

    clear_weak_mods();
    clear_mods();
    clear_keyboard();

    keymap_config.nkro = 1;
    memset(keyboard_report, 0, sizeof(report_keyboard_t));
    host_keyboard_send(keyboard_report);
    wait_ms(10);

    keymap_config.nkro = 0;
    memset(keyboard_report, 0, sizeof(report_keyboard_t));
    host_keyboard_send(keyboard_report);
    wait_ms(10);

    keymap_config.nkro = nkro_temp;

    if (dev_info.link_mode != LINK_USB) {
        memset(report_buf, 0, 16);
        uart_send_report(CMD_RPT_BIT_KB, report_buf, 16);
        wait_ms(10);
        uart_send_report(CMD_RPT_BYTE_KB, report_buf, 8);
        wait_ms(10);
    }

    memset(bitkb_report_buf, 0, sizeof(bitkb_report_buf));
    memset(bytekb_report_buf, 0, sizeof(bytekb_report_buf));
}

/**
 * @brief  switch device link mode.
 * @param mode : link mode
 */
void switch_dev_link(uint8_t mode) {
    if (mode > LINK_USB) return;

    break_all_key();

    dev_info.link_mode = mode;

    dev_info.rf_state = RF_IDLE;
    f_send_channel    = 1;

    if (mode == LINK_USB) {
        host_mode = HOST_USB_TYPE;
        host_set_driver(m_host_driver);
        rf_link_show_time = 0;
    } else {
        host_mode = HOST_RF_TYPE;

        host_set_driver(0);
    }
}

/**
 * @brief  scan dial switch.
 */
void dial_sw_scan(void) {
    uint8_t         dial_scan       = 0;
    static uint8_t  dial_save       = 0xf0;
    static uint8_t  debounce        = 0;
    static uint32_t dial_scan_timer = 0;
    static bool     f_first         = true;

    if (!f_first) {
        if (timer_elapsed32(dial_scan_timer) < 20) return;
    }
    dial_scan_timer = timer_read32();

    setPinInputHigh(DEV_MODE_PIN);
    setPinInputHigh(SYS_MODE_PIN);

    if (readPin(DEV_MODE_PIN)) dial_scan |= 0X01;
    if (readPin(SYS_MODE_PIN)) dial_scan |= 0X02;

    if (dial_save != dial_scan) {
        break_all_key();

        no_act_time     = 0;
        rf_linking_time = 0;

        dial_save         = dial_scan;
        debounce          = 25;
        f_dial_sw_init_ok = 0;
        return;
    } else if (debounce) {
        debounce--;
        return;
    }

    if (dial_scan & 0x01) {
        if (dev_info.link_mode != LINK_USB) {
            switch_dev_link(LINK_USB);
        }
    } else {
        if (dev_info.link_mode != dev_info.rf_channel) {
            switch_dev_link(dev_info.rf_channel);
        }
    }

    if (dial_scan & 0x02) {
        if (dev_info.sys_sw_state != SYS_SW_MAC) {
            f_sys_show = 1;
            default_layer_set(1 << 0);
            dev_info.sys_sw_state = SYS_SW_MAC;
            keymap_config.nkro    = 0;
            break_all_key();
        }
    } else {
        if (dev_info.sys_sw_state != SYS_SW_WIN) {
            f_sys_show = 1;
            default_layer_set(1 << 4);
            dev_info.sys_sw_state = SYS_SW_WIN;
            keymap_config.nkro    = 1;
            break_all_key();
        }
    }

    if (f_dial_sw_init_ok == 0) {
        f_dial_sw_init_ok = 1;
        f_first           = false;

        if (dev_info.link_mode != LINK_USB) {
            host_set_driver(0);
        }
    }
}

/**
 * @brief  power on scan dial switch.
 */
void dial_sw_fast_scan(void) {
    {
        uint8_t dial_scan_dev  = 0;
        uint8_t dial_scan_sys  = 0;
        uint8_t dial_check_dev = 0;
        uint8_t dial_check_sys = 0;
        uint8_t debounce       = 0;

        setPinInputHigh(DEV_MODE_PIN);
        setPinInputHigh(SYS_MODE_PIN);

        // Debounce to get a stable state
        for (debounce = 0; debounce < 10; debounce++) {
            dial_scan_dev = 0;
            dial_scan_sys = 0;
            if (readPin(DEV_MODE_PIN))
                dial_scan_dev = 0x01;
            else
                dial_scan_dev = 0;
            if (readPin(SYS_MODE_PIN))
                dial_scan_sys = 0x01;
            else
                dial_scan_sys = 0;
            if ((dial_scan_dev != dial_check_dev) || (dial_scan_sys != dial_check_sys)) {
                dial_check_dev = dial_scan_dev;
                dial_check_sys = dial_scan_sys;
                debounce       = 0;
            }
            wait_ms(1);
        }

        // RF link mode
        if (dial_scan_dev) {
            if (dev_info.link_mode != LINK_USB) {
                switch_dev_link(LINK_USB);
            }
        } else {
            if (dev_info.link_mode != dev_info.rf_channel) {
                switch_dev_link(dev_info.rf_channel);
            }
        }

        // Win or Mac
        if (dial_scan_sys) {
            if (dev_info.sys_sw_state != SYS_SW_MAC) {
                default_layer_set(1 << 0);
                dev_info.sys_sw_state = SYS_SW_MAC;
                keymap_config.nkro    = 0;
                break_all_key();
            }
        } else {
            if (dev_info.sys_sw_state != SYS_SW_WIN) {
                // f_sys_show = 1;
                default_layer_set(1 << 4);
                dev_info.sys_sw_state = SYS_SW_WIN;
                keymap_config.nkro    = 1;
                break_all_key();
            }
        }
    }
}

/**
 * @brief  timer process.
 */
void timer_pro(void) {
    static uint32_t interval_timer = 0;
    static bool     f_first        = true;

    if (f_first) {
        f_first        = false;
        interval_timer = timer_read32();
        m_host_driver  = host_get_driver();
    }

    if (timer_elapsed32(interval_timer) < 10)
        return;
    else
        interval_timer = timer_read32();

    if (rf_link_show_time < RF_LINK_SHOW_TIME) rf_link_show_time++;

    if (no_act_time < 0xffff) no_act_time++;

    if (rf_linking_time < 0xffff) rf_linking_time++;
}

/**
 * @brief  londing eeprom data.
 */
void londing_eeprom_data(void) {
    eeconfig_read_user_datablock(&user_config);
    if (user_config.default_brightness_flag != 0xA5) {
        /* first power on, set rgb matrix brightness at middle level*/
        rgb_matrix_sethsv(255, 255, RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP * 2);
        user_config.default_brightness_flag = 0xA5;
        user_config.ee_side_mode            = side_mode;
        user_config.ee_side_light           = side_light;
        user_config.ee_side_speed           = side_speed;
        user_config.ee_side_rgb             = side_rgb;
        user_config.ee_side_colour          = side_colour;
        user_config.sleep_enable            = true;
        eeconfig_update_user_datablock(&user_config);
    } else {
        side_mode   = user_config.ee_side_mode;
        side_light  = user_config.ee_side_light;
        side_speed  = user_config.ee_side_speed;
        side_rgb    = user_config.ee_side_rgb;
        side_colour = user_config.ee_side_colour;
    }
}

/* qmk process record */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    no_act_time = 0;
    switch (keycode) {
        case RF_DFU:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) return false;
                uart_send_cmd(CMD_RF_DFU, 10, 20);
            }
            return false;

        case LNK_USB:
            if (record->event.pressed) {
                break_all_key();
            } else {
                dev_info.link_mode = LINK_USB;
                uart_send_cmd(CMD_SET_LINK, 10, 10);
            }
            return false;

        case LNK_RF:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    rf_sw_temp    = LINK_RF_24;
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case LNK_BLE1:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    if (dev_info.link_mode == LINK_BT_1) {
                        rf_sw_temp = LINK_RF_24;
                    } else {
                        rf_sw_temp = LINK_BT_1;
                    }
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case LNK_BLE2:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    if (dev_info.link_mode == LINK_BT_2) {
                        rf_sw_temp = LINK_RF_24;
                    } else {
                        rf_sw_temp = LINK_BT_2;
                    }
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case LNK_BLE3:
            if (record->event.pressed) {
                if (dev_info.link_mode != LINK_USB) {
                    if (dev_info.link_mode == LINK_BT_3) {
                        rf_sw_temp = LINK_RF_24;
                    } else {
                        rf_sw_temp = LINK_BT_3;
                    }
                    f_rf_sw_press = 1;
                    break_all_key();
                }
            } else if (f_rf_sw_press) {
                f_rf_sw_press = 0;

                if (rf_sw_press_delay < RF_LONG_PRESS_DELAY) {
                    dev_info.link_mode   = rf_sw_temp;
                    dev_info.rf_channel  = rf_sw_temp;
                    dev_info.ble_channel = rf_sw_temp;
                    uart_send_cmd(CMD_SET_LINK, 10, 20);
                }
            }
            return false;

        case MAC_TASK:
            if (record->event.pressed) {
                host_consumer_send(0x029F);
            } else {
                host_consumer_send(0);
            }
            return false;

        case MAC_SEARCH:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_SPACE);
                wait_ms(50);
                unregister_code(KC_LGUI);
                unregister_code(KC_SPACE);
            }
            return false;

        case MAC_VOICE:
            if (record->event.pressed) {
                host_consumer_send(0xcf);
            } else {
                host_consumer_send(0);
            }
            return false;

        case MAC_CONSOLE:
            if (record->event.pressed) {
                host_consumer_send(0x02A0);
            } else {
                host_consumer_send(0);
            }
            return false;

        case MAC_DND:
            if (record->event.pressed) {
                host_system_send(0x9b);
            } else {
                host_system_send(0);
            }
            return false;

        case MAC_PRT:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_3);
                wait_ms(50);
                unregister_code(KC_3);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return false;

        case MAC_PRTA:
            if (record->event.pressed) {
                if (dev_info.sys_sw_state == SYS_SW_WIN) {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    register_code(KC_S);
                    wait_ms(50);
                    unregister_code(KC_S);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_LGUI);
                }

                else {
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                    register_code(KC_4);
                    wait_ms(50);
                    unregister_code(KC_4);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_LGUI);
                }
            }
            return false;

        case SIDE_VAI:
            if (record->event.pressed) {
                side_light_contol(1);
            }
            return false;

        case SIDE_VAD:
            if (record->event.pressed) {
                side_light_contol(0);
            }
            return false;

        case SIDE_MOD:
            if (record->event.pressed) {
                side_mode_control(1);
            }
            return false;

        case SIDE_HUI:
            if (record->event.pressed) {
                side_colour_control(1);
            }
            return false;

        case SIDE_SPI:
            if (record->event.pressed) {
                side_speed_contol(1);
            }
            return false;

        case SIDE_SPD:
            if (record->event.pressed) {
                side_speed_contol(0);
            }
            return false;

        case DEV_RESET:
            if (record->event.pressed) {
                f_dev_reset_press = 1;
                break_all_key();
            } else {
                f_dev_reset_press = 0;
            }
            return false;

        case SLEEP_MODE:
            if (record->event.pressed) {
                if (user_config.sleep_enable)
                    user_config.sleep_enable = false;
                else
                    user_config.sleep_enable = true;
                f_sleep_show = 1;
                eeconfig_update_user_datablock(&user_config);
            }
            return false;

        case BAT_SHOW:
            if (record->event.pressed) {
                f_bat_hold = !f_bat_hold;
            }
            return false;

        case BAT_NUM:
            if (record->event.pressed) {
                f_bat_num_show = 1;
            } else {
                f_bat_num_show = 0;
            }
            return false;

        case RGB_TEST:
            if (record->event.pressed) {
                f_rgb_test_press = 1;
            } else {
                f_rgb_test_press = 0;
            }
            return false;

        case WIN_TASK:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB) SS_UP(X_LGUI));
            } else {
                // when keycode is released
            }
            return false;

        case WIN_SEARCH:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_SPACE) SS_UP(X_LALT));
            } else {
                // when keycode is released
            }
            return false;

        case WIN_VOICE:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_A) SS_UP(X_LSFT) SS_UP(X_LGUI));
                switch (dev_info.link_mode) {
                    case LINK_USB:
                        if (mic5_active) {
                            mic5_active = 0;
                        } else {
                            mic5_active = 1;
                        }
                        break;
                    case LINK_RF_24:
                        if (mic4_active) {
                            mic4_active = 0;
                        } else {
                            mic4_active = 1;
                        }
                        break;
                    case LINK_BT_1:
                        if (mic3_active) {
                            mic3_active = 0;
                        } else {
                            mic3_active = 1;
                        }
                        break;
                    case LINK_BT_2:
                        if (mic2_active) {
                            mic2_active = 0;
                        } else {
                            mic2_active = 1;
                        }
                        break;
                    case LINK_BT_3:
                        if (mic1_active) {
                            mic1_active = 0;
                        } else {
                            mic1_active = 1;
                        }
                        break;
                    default:
                        break;
                }

            } else {
                // when keycode is released
            }
            return false;

        case WIN_DND:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_N) SS_UP(X_LGUI) SS_DELAY(1000) SS_TAP(X_ENT) SS_DOWN(X_LGUI) SS_TAP(X_N) SS_UP(X_LGUI));
            } else {
                // when keycode is released
            }
            return false;

        case WIN_CONSOLE:
            if (record->event.pressed) {
                // when keycode is pressed
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_R) SS_UP(X_LGUI) SS_DELAY(500) "powershell" SS_TAP(X_ENT));
            } else {
                // when keycode is released
            }
            return false;

        case KC_ESC:
            if (record->event.pressed) {
                // when keycode is pressed
                const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();
                if (mods == MOD_BIT(KC_LALT)) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_F4) SS_UP(X_LALT));
                } else {
                    // SEND_STRING(SS_DOWN(X_ESC));
                }
            } else {
                // when keycode is released
                // SEND_STRING(SS_UP(X_ESC));
            }
            return false;

        case DEBUG_LAYER:
            if (record->event.pressed) {
                // when keycode is pressed
                char str[20];
                int  number = get_highest_layer(layer_state | default_layer_state);
                sprintf(str, "LAYER: %d", number);
                SEND_STRING(str);
            } else {
                // when keycode is released
            }
            return false;

        default:
            return true;
    }
}

bool rgb_matrix_indicators_user(void) {
    if (f_bat_num_show) {
        num_led_show();
    }
    rgb_matrix_set_color(RGB_MATRIX_LED_COUNT - 1, 0, 0, 0);

    // set rgb color according to the current layer
    switch (get_highest_layer(layer_state | default_layer_state)) {
        // layer 1 Mac
        case 0:
            rgb_matrix_set_color(73, 0, 0, 0); // layer TG
            break;
        // layer 1 Mac fn
        case 1:
            rgb_matrix_set_color(73, RGB_WHITE);  // layer TG
            rgb_matrix_set_color(44, RGB_YELLOW); // show battery
            rgb_matrix_set_color(43, RGB_YELLOW); // sleep mode
            rgb_matrix_set_color(42, RGB_YELLOW); // dev reset
            rgb_matrix_set_color(63, RGB_YELLOW); // rgb test
            rgb_matrix_set_color(65, RGB_YELLOW); // show battery percentage
            rgb_matrix_set_color(67, RGB_YELLOW); // layer extra
            rgb_matrix_set_color(68, RGB_RED);    // rgb speed down
            rgb_matrix_set_color(69, RGB_GREEN);  // rgb speed up
            rgb_matrix_set_color(72, RGB_GREEN);  // rgb light up
            rgb_matrix_set_color(75, RGB_RED);    // rgb light down
            rgb_matrix_set_color(74, RGB_YELLOW); // rgb hui
            rgb_matrix_set_color(76, RGB_YELLOW); // rgb mode
            if (dev_info.link_mode != LINK_USB && f_bat_num_show == 0) {
                rgb_matrix_set_color(26, RGB_GREEN); // RF
                rgb_matrix_set_color(27, RGB_BLUE);  // BLE3
                rgb_matrix_set_color(28, RGB_BLUE);  // BLE2
                rgb_matrix_set_color(29, RGB_BLUE);  // BLE1
            }
            break;
        // layer 2 Mac
        case 2:
            rgb_matrix_set_color(73, RGB_WHITE); // layer TG
            break;
        // layer 2 Mac fn
        case 3:
            rgb_matrix_set_color(73, RGB_WHITE);  // layer TG
            rgb_matrix_set_color(44, RGB_YELLOW); // show battery
            rgb_matrix_set_color(43, RGB_YELLOW); // sleep mode
            rgb_matrix_set_color(42, RGB_YELLOW); // dev reset
            rgb_matrix_set_color(63, RGB_YELLOW); // rgb test
            rgb_matrix_set_color(65, RGB_YELLOW); // show battery percentage
            rgb_matrix_set_color(67, RGB_YELLOW); // layer extra
            rgb_matrix_set_color(68, RGB_RED);    // rgb speed down
            rgb_matrix_set_color(69, RGB_GREEN);  // rgb speed up
            rgb_matrix_set_color(72, RGB_GREEN);  // rgb light up
            rgb_matrix_set_color(75, RGB_RED);    // rgb light down
            rgb_matrix_set_color(74, RGB_YELLOW); // rgb hui
            rgb_matrix_set_color(76, RGB_YELLOW); // rgb mode
            if (dev_info.link_mode != LINK_USB && f_bat_num_show == 0) {
                rgb_matrix_set_color(26, RGB_GREEN); // RF
                rgb_matrix_set_color(27, RGB_BLUE);  // BLE3
                rgb_matrix_set_color(28, RGB_BLUE);  // BLE2
                rgb_matrix_set_color(29, RGB_BLUE);  // BLE1
            }
            break;
        // layer 1 Win
        case 4:
            rgb_matrix_set_color(73, 0, 0, 0); // layer TG
            if (mic1_active && dev_info.link_mode == LINK_BT_1 || mic2_active && dev_info.link_mode == LINK_BT_2 || mic3_active && dev_info.link_mode == LINK_BT_3 || mic4_active && dev_info.link_mode == LINK_RF_24 || mic5_active && dev_info.link_mode == LINK_USB) {
                rgb_matrix_set_color(5, 0, 0, 0); // mic
            } else {
                rgb_matrix_set_color(5, RGB_WHITE); // mic
            }
            break;
        // layer 1 Win fn
        case 5:
            rgb_matrix_set_color(73, RGB_WHITE);  // layer TG
            rgb_matrix_set_color(44, RGB_YELLOW); // show battery
            rgb_matrix_set_color(43, RGB_YELLOW); // sleep mode
            rgb_matrix_set_color(42, RGB_YELLOW); // dev reset
            rgb_matrix_set_color(63, RGB_YELLOW); // rgb test
            rgb_matrix_set_color(65, RGB_YELLOW); // show battery percentage
            rgb_matrix_set_color(67, RGB_YELLOW); // layer extra
            rgb_matrix_set_color(68, RGB_RED);    // rgb speed down
            rgb_matrix_set_color(69, RGB_GREEN);  // rgb speed up
            rgb_matrix_set_color(72, RGB_GREEN);  // rgb light up
            rgb_matrix_set_color(75, RGB_RED);    // rgb light down
            rgb_matrix_set_color(74, RGB_YELLOW); // rgb hui
            rgb_matrix_set_color(76, RGB_YELLOW); // rgb mode
            if (dev_info.link_mode != LINK_USB && f_bat_num_show == 0) {
                rgb_matrix_set_color(26, RGB_GREEN); // RF
                rgb_matrix_set_color(27, RGB_BLUE);  // BLE3
                rgb_matrix_set_color(28, RGB_BLUE);  // BLE2
                rgb_matrix_set_color(29, RGB_BLUE);  // BLE1
            }
            if (mic1_active && dev_info.link_mode == LINK_BT_1 || mic2_active && dev_info.link_mode == LINK_BT_2 || mic3_active && dev_info.link_mode == LINK_BT_3 || mic4_active && dev_info.link_mode == LINK_RF_24 || mic5_active && dev_info.link_mode == LINK_USB) {
                rgb_matrix_set_color(5, 0, 0, 0); // mic
            } else {
                rgb_matrix_set_color(5, RGB_WHITE); // mic
            }
            break;
        // layer 2 Win
        case 6:
            rgb_matrix_set_color(73, RGB_WHITE); // layer TG
            if (mic1_active && dev_info.link_mode == LINK_BT_1 || mic2_active && dev_info.link_mode == LINK_BT_2 || mic3_active && dev_info.link_mode == LINK_BT_3 || mic4_active && dev_info.link_mode == LINK_RF_24 || mic5_active && dev_info.link_mode == LINK_USB) {
                rgb_matrix_set_color(5, 0, 0, 0); // mic
            } else {
                rgb_matrix_set_color(5, RGB_WHITE); // mic
            }
            break;
        // layer 2 Win fn
        case 7:
            rgb_matrix_set_color(73, 0, 0, 0);    // layer TG
            rgb_matrix_set_color(44, RGB_YELLOW); // show battery
            rgb_matrix_set_color(43, RGB_YELLOW); // sleep mode
            rgb_matrix_set_color(42, RGB_YELLOW); // dev reset
            rgb_matrix_set_color(63, RGB_YELLOW); // rgb test
            rgb_matrix_set_color(65, RGB_YELLOW); // show battery percentage
            rgb_matrix_set_color(67, RGB_YELLOW); // layer extra
            rgb_matrix_set_color(68, RGB_RED);    // rgb speed down
            rgb_matrix_set_color(69, RGB_GREEN);  // rgb speed up
            rgb_matrix_set_color(72, RGB_GREEN);  // rgb light up
            rgb_matrix_set_color(75, RGB_RED);    // rgb light down
            rgb_matrix_set_color(74, RGB_YELLOW); // rgb hui
            rgb_matrix_set_color(76, RGB_YELLOW); // rgb mode
            if (dev_info.link_mode != LINK_USB && f_bat_num_show == 0) {
                rgb_matrix_set_color(26, RGB_GREEN); // RF
                rgb_matrix_set_color(27, RGB_BLUE);  // BLE3
                rgb_matrix_set_color(28, RGB_BLUE);  // BLE2
                rgb_matrix_set_color(29, RGB_BLUE);  // BLE1
            }
            if (mic1_active && dev_info.link_mode == LINK_BT_1 || mic2_active && dev_info.link_mode == LINK_BT_2 || mic3_active && dev_info.link_mode == LINK_BT_3 || mic4_active && dev_info.link_mode == LINK_RF_24 || mic5_active && dev_info.link_mode == LINK_USB) {
                rgb_matrix_set_color(5, 0, 0, 0); // mic
            } else {
                rgb_matrix_set_color(5, RGB_WHITE); // mic
            }
            break;
        // layer extra
        case 8:
            rgb_matrix_set_color(0, RGB_WHITE);   // escape
            rgb_matrix_set_color(15, RGB_WHITE);  // delete
            rgb_matrix_set_color(68, RGB_RED);    // rgb side speed down
            rgb_matrix_set_color(69, RGB_GREEN);  // rgb side speed up
            rgb_matrix_set_color(72, RGB_GREEN);  // rgb side light up
            rgb_matrix_set_color(75, RGB_RED);    // rgb side light down
            rgb_matrix_set_color(74, RGB_YELLOW); // rgb side hui
            rgb_matrix_set_color(76, RGB_YELLOW); // rgb side mode
            break;
        default:
            break;
    }

    // set rgb color according to the current device connected
    if (dev_info.link_mode != LINK_USB) {
        switch (dev_info.link_mode) {
            case LINK_BT_1:
                rgb_matrix_set_color(16, RGB_WHITE);
                break;
            case LINK_BT_2:
                rgb_matrix_set_color(45, RGB_WHITE);
                break;
            case LINK_BT_3:
                rgb_matrix_set_color(46, RGB_WHITE);
                break;
            default:
                rgb_matrix_set_color(16, 0, 0, 0);
                rgb_matrix_set_color(45, 0, 0, 0);
                rgb_matrix_set_color(46, 0, 0, 0);
                break;
        }
    } else {
        rgb_matrix_set_color(16, 0, 0, 0);
        rgb_matrix_set_color(45, 0, 0, 0);
        rgb_matrix_set_color(46, 0, 0, 0);
    }
    return true;
}

/* qmk keyboard post init */
void keyboard_post_init_user(void) {
    gpio_init();
    rf_uart_init();
    wait_ms(500);
    rf_device_init();

    break_all_key();
    dial_sw_fast_scan();
    londing_eeprom_data();
}

/* qmk housekeeping task */
void housekeeping_task_user(void) {
    timer_pro();

    uart_receive_pro();

    uart_send_report_func();

    dev_sts_sync();

    long_press_key();

    dial_sw_scan();

    side_led_show();

    sleep_handle();
}
