#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "rgb_cicle_comu.h"
#include "rgb_cicle_semaforo.h"
#include "rgb_cicle_perro_guardian.h"
#include "rgb_cicle_cerberos.h"
#include "rgb_estatic_gradient.h"


// -------------------- CICLO DE RGBS ------------------------------- 
#define INACTIVITAT_INTERVAL 3000   // Definim el interval en ms del que trigará en tornar al CICLE
#define DOBLE_PULSACIO 200          // Definim el interval en ms per a la doble pulsació del PPLS

// globals
uint32_t last_timer = 0;
uint32_t ultima_tecla_timer = 0;
uint32_t ultima_ppls_timer = 0;
bool inactiu_mode = false;

bool fn_pulsada = false;
bool rctl_pulsada = false;
bool ppls_pulsada = false;



// -------------------------------------------------   SCAN USER ---------------------------------------------
void matrix_scan_user(void){ 

    // DESACTIVAR les altres
    //if (rgb_matrix_get_mode() != RGB_MATRIX_SOLID_COLOR){
    //  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    //}

    // Comprovem si ha passat el temps de inactivitat per a passar a modo inactiu
    if (timer_elapsed32(ultima_tecla_timer) > INACTIVITAT_INTERVAL){
        inactiu_mode = true;
    }

    // Comprovem si la pulsació PPLS ha caducat
    if (timer_elapsed32(ultima_ppls_timer) > DOBLE_PULSACIO){
        if (ppls_pulsada) {
            tap_code16(LSFT(KC_PPLS)); // finalment mostrem el plus
        }
        
        ppls_pulsada = false; // ha passat el temps, perdem la pulsació
    }





    // Executem el rgb ELEGIT
    switch (cicle_ELEGIT)
    {
    case 1:
        RGB_CICLE_SEMAFORO(inactiu_mode);
        break;

    case 2:
        RGB_CICLE_PERRO_GUARDIAN(inactiu_mode);
        break;

    case 3:
        RGB_CICLE_CERBEROS(inactiu_mode, 0, 2, 3);
        break;

    case 4:
        RGB_ESTATIC_GRADIENT(inactiu_mode, 1);
        break;


    default:
        break;
    }

    
} // -------------------------------------------------   SCAN USER ---------------------------------------------



enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [MAC_BASE] = LAYOUT_iso_99(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            KC_DEL,   KC_HOME,  KC_END,     KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,                      KC_P7,    KC_P8,    KC_P9,      KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_NUHS,  KC_ENT,             KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,      KC_PENT,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT               ),

    [MAC_FN] = LAYOUT_iso_99(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             _______,  _______,  _______,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                      _______,  _______,  _______,    _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),

    [WIN_BASE] = LAYOUT_iso_99(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             KC_DEL,   KC_HOME,  KC_END,     KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,                      KC_P7,    KC_P8,    KC_P9,      KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_NUHS,  KC_ENT,             KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,      KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT            ),

    [WIN_FN] = LAYOUT_iso_99(
        QK_BOOT,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            KC_INS,  KC_PGUP,  KC_PGDN,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                      _______,  _______,  _______,    _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
 };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE



// ---------------------------- HOOK PULSACIONS TECLES ---------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Comprovem si s'ha pulsat alguna tecla, si es així, eixim del modo inactiu / reiniciem contador
    
    // Valor trivial. Si no es demostra el contrari, no anem a fer camvi de cicle, per lo tant eixim de mode inactiu
    bool es_un_camvi_de_cicle = false;

    switch (keycode)
    {
    case MO(WIN_FN):
        if (record->event.pressed) {
            fn_pulsada = true;
        }else{
            fn_pulsada = false;
        }
        es_un_camvi_de_cicle = true; // Ací, sí o sí, no podem eixir de inactiu, perque si no sempre eixirá cuan acabem de pulsar la secuencia
        break;

    case KC_RCTL:
        if (record->event.pressed) {
            rctl_pulsada = true;
        }else{
            rctl_pulsada = false;
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    case KC_P1:
        if (record->event.pressed) {
            if (fn_pulsada && rctl_pulsada){
                cicle_ELEGIT = 1;
                cicle_INTERVAL = 2000;
            }
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    case KC_P2:
        if (record->event.pressed) {
            if (fn_pulsada && rctl_pulsada){
                cicle_ELEGIT = 2;
                cicle_INTERVAL = 50;
            }
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    case KC_P3:
        if (record->event.pressed) {
            if (fn_pulsada && rctl_pulsada){
                cicle_ELEGIT = 3;
                cicle_INTERVAL = 80;
            }
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    case KC_P4:
        if (record->event.pressed) {
            if (fn_pulsada && rctl_pulsada){
                cicle_ELEGIT = 4;
                cicle_INTERVAL = 100;
            }
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    // Doble pulsació del + fará un :
    case KC_PPLS:
        if (record->event.pressed){
            // Primer comprovem si estem pulsats
            if (ppls_pulsada){ // Se considera que está dins del tiempo, ya que sigue pulsada
                tap_code16(LSFT(KC_DOT));
                ppls_pulsada = false; // hem pulsat la tecla, ja no la tenim pulsada

            }else{ //No estem pulsats, per lo tant pasem a pulsats
                ppls_pulsada = true;
                ultima_ppls_timer = timer_read32();
            }
            
            return false; // bloquejem la tecla actual en cualquier cas, ja que si tenim que imprimirla, será en el timeout
        }
        break;


    default:
        break;

    } // SWITCH

    //Comprovem si es un camvi de cicle, i si no, eixim de mode inactiu
    if (!es_un_camvi_de_cicle){
        ultima_tecla_timer = timer_read32();
        inactiu_mode = false; // Si no coincideix ninguna de les combinacions següents, parem el modo inactiu

    }
        
    

    // clang-format on (NI PAJOLERA LO QUE ES AÇÓ)
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

