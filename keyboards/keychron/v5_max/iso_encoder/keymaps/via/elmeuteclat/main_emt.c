#include QMK_KEYBOARD_H
#include "keychron_common.h"

#include "h/rgb_cicle_comu.h"
#include "h/rgb_cicle_semaforo.h"
#include "h/rgb_cicle_perro_guardian.h"
#include "h/rgb_cicle_cerberos.h"
#include "h/rgb_estatic_gradient.h"



// -------------------- CICLO DE RGBS ------------------------------- 
#define INACTIVITAT_INTERVAL 3000   // Definim el interval en ms del que trigará en tornar al CICLE
#define DOBLE_PULSACIO 200          // Definim el interval en ms per a la doble pulsació del PPLS

// El nostre propi enumerador de capes
enum emt_capes {
    EMT_MAC_BASE,
    EMT_MAC_FN,
    EMT_WIN_BASE,
    EMT_WIN_FN,
};



// globals
uint32_t last_timer = 0;
uint32_t ultima_tecla_timer = 0;
uint32_t ultima_ppls_timer = 0;
bool inactiu_mode = false;

bool fn_pulsada = false;
bool rctl_pulsada = false;
bool lctl_pulsada = false;
bool lalt_pulsada = false;
bool lsft_pulsada = false;
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

// Tots les intervencions del teclat han de anar abans de la última process_record_keychron_common, ja que esta funció anul·la
// cualsevol altra pulsació. No sé perqué ho fan, pero de moment es el que hi ha

// ---------------------------- HOOK ENCODER ---------------------------------

bool encoder_update_user(uint8_t index, bool clockwise) {
 
    if (lsft_pulsada) {  // Si SHIFT está presionado
        tap_code(clockwise ? KC_WH_R : KC_WH_L);  // Scroll horizontal

        return false; // bloquejem el valor per defecte
    }
    
    if (lctl_pulsada) {  // Si CTRL está presionado
        if (clockwise) {
            tap_code(KC_WH_U);  // SCROLL UP
        } else {
            tap_code(KC_WH_D);  // SCROLL AVALL
        }
        return false; // bloquejem el valor per defecte
    }
 
    
    // Si estem en la capa WIN_FN, cambib
    if (layer_state_is(EMT_WIN_FN)) {  // Si FN está presionado
        if (clockwise) {
            rgb_matrix_increase_val(); // Aumenta el brillo
    
        } else {
            rgb_matrix_decrease_val(); // Disminuye el brillo
    
        }
        return false; // Evita que haga otra acción // bloquejem el valor per defecte
    }

    /*
    // Si ninguna de les anterios es cumpleix, manejará el volumen
    if (clockwise) {
        tap_code(KC_VOLU);  // Subir volumen
    } else {
        tap_code(KC_VOLD);  // Bajar volumen
    }*/
    return true;  // Si no es cumpleix ninguna de dalt, torne el valor per defecte (o volumen o RGB)
}


// ---------------------------- HOOK PULSACIONS TECLES ---------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Comprovem si s'ha pulsat alguna tecla, si es així, eixim del modo inactiu / reiniciem contador
    
    // Valor trivial. Si no es demostra el contrari, no anem a fer camvi de cicle, per lo tant eixim de mode inactiu
    bool es_un_camvi_de_cicle = false;

    switch (keycode)
    {
    /*
    case KC_MUTE:
        cicle_ELEGIT = 3;
        cicle_INTERVAL = 80;
    break;
*/
    // --------------- TECLES ESPECIALS -----------------
    case MO(EMT_WIN_FN):
        if (record->event.pressed) {
            fn_pulsada = true;
        }else{
            fn_pulsada = false;
        }
        es_un_camvi_de_cicle = true; // Ací, sí o sí, no podem eixir de inactiu, perque si no sempre eixirá cuan acabem de pulsar la secuencia
        break;

    case KC_LALT:
        if (record->event.pressed) {
            lalt_pulsada = true;        }else{
            lalt_pulsada = false;
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    
    case KC_LSFT:
        if (record->event.pressed) {
            lsft_pulsada = true;
        }else{
            lsft_pulsada = false;
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;


    case KC_RCTL:
        if (record->event.pressed) {
            rctl_pulsada = true;
        }else{
            rctl_pulsada = false;
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;

    case KC_LCTL:
        if (record->event.pressed) {
            lctl_pulsada = true;
        }else{
            lctl_pulsada = false;
        }
        es_un_camvi_de_cicle = fn_pulsada;
        break;


    // Tecles extra --------------------------------------
    case KC_DEL:    // convertir en INS
        if (record->event.pressed){
            if (lalt_pulsada){
                tap_code16(KC_INS);
            }
        }
        break;

    case KC_HOME:   // convertir en RE-PAG
        if (record->event.pressed){
            if (lalt_pulsada){
                tap_code(KC_PGUP);
            }
        }
        break;

    case KC_END:    // convertir en AV-PAG
        if (record->event.pressed){
            if (lalt_pulsada){
                tap_code(KC_PGDN);
            }
        }
        break;

    // ----------- PROGRAMES DE LLUM PERSONALITZATS
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
        if (record->event.pressed) {            if (fn_pulsada && rctl_pulsada){
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
        
    

    // clang-format on
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}


