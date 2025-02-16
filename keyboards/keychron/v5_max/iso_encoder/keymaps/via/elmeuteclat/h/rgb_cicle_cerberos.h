#ifndef RGB_CICLE_CERBEROS_h
#define RGB_CICLE_CERBEROS_H

// Prototipo de la funció
void RGB_CICLE_CERBEROS(bool inactiu, uint8_t color1, uint8_t color2, uint8_t color3  );

// Globals locals
uint8_t color_index = 0;
uint8_t cb_color_ant = 0;
uint8_t cb_color_pos = 0;

uint8_t posicio_1 = 0;
uint8_t posicio_2 = TOTAL_CIRCUIT_CIRCULAR / 3;
uint8_t posicio_3 = TOTAL_CIRCUIT_CIRCULAR / 3 * 2;

// Fixem el patró de percentatges
#define TOTAL_PERCENTS 8
float percents_brillo [TOTAL_PERCENTS] = {0.02, 0.04, 0.08, 0.1, 0.4, 1.0, 0.08, 0.02 };




// -- Mi propio ciclo de colores --
void RGB_CICLE_CERBEROS(bool inactiu, uint8_t color_1, uint8_t color_2, uint8_t color_3){
    
    // Cada INTERVAL Menejarem als tres gossos
    if (timer_elapsed32(lapse_INTERVAL) > cicle_INTERVAL){
        lapse_INTERVAL = timer_read32();

        // Perro 1
        posicio_1 = (posicio_1 + 1) % TOTAL_CIRCUIT_CIRCULAR;              // menejem al gos

        // Perro 2
        posicio_2 = (posicio_2 + 1) % TOTAL_CIRCUIT_CIRCULAR;              // menejem al gos

        // Perro 3
        posicio_3 = (posicio_3 + 1) % TOTAL_CIRCUIT_CIRCULAR;              // menejem al gos

        /*
        // Cacular colors anterior y posterior
        cb_color_ant = (cb_color_index - 1) % RGB_COLOR_COUNT;
        cb_color_pos = (cb_color_index + 1) % RGB_COLOR_COUNT;

        // Calcular posició anterior y posterior
        posicio_ant = (posicio_perro - 1 ) % TOTAL_CIRCUIT_CIRCULAR;
        posicio_pos = (posicio_perro + 1) % TOTAL_CIRCUIT_CIRCULAR;
        */
    }

    if (inactiu){
    // Si estem en modo inactiu, entonces pintem nosaltres, si no deixarem el automatic que estiga vigent
        // apaguem totes les tecles
        rgb_matrix_set_color_all(0,0,0); 

        // dibuixem una estela de degradat de color (10 pasos)
        for (uint8_t bucle = 0; bucle < TOTAL_PERCENTS; bucle ++){
        //percent_brillo = bucle / 9.0; // Si no no forsa la operació a FLOAT
        // Perro 1
        rgb_matrix_set_color(
            circuit_circular[(posicio_1 + bucle) % TOTAL_CIRCUIT_CIRCULAR],
            rgb_colors[color_1][0] * percents_brillo[bucle],
            rgb_colors[color_1][1] * percents_brillo[bucle],
            rgb_colors[color_1][2] * percents_brillo[bucle]
        );

        // Perro 2
        rgb_matrix_set_color(
            circuit_circular[(posicio_2 + bucle) % TOTAL_CIRCUIT_CIRCULAR],
            rgb_colors[color_2][0] * percents_brillo[bucle],
            rgb_colors[color_2][1] * percents_brillo[bucle],
            rgb_colors[color_2][2] * percents_brillo[bucle]

        );

        // Perro 3
        rgb_matrix_set_color(
            circuit_circular[(posicio_3 + bucle) % TOTAL_CIRCUIT_CIRCULAR],
            rgb_colors[color_3][0] * percents_brillo[bucle],
            rgb_colors[color_3][1] * percents_brillo[bucle],
            rgb_colors[color_3][2] * percents_brillo[bucle]
        );
        } // FOR
        /*
        // Alumbrem la tecla que "camina"
        rgb_matrix_set_color(
            circuit_circular[posicio_perro],
            rgb_colors[cb_color_index][0],
            rgb_colors[cb_color_index][1],
            rgb_colors[cb_color_index][2]
        );

        // Penumbrem la tecla anterior
        rgb_matrix_set_color(
            circuit_circular[posicio_ant],
            rgb_colors[cb_color_ant][0] * 0.2,
            rgb_colors[cb_color_ant][1] * 0.2,
            rgb_colors[cb_color_ant][2] * 0.2
        );

        // Penumbrem la tecla posteior
        rgb_matrix_set_color(
            circuit_circular[posicio_pos],
            rgb_colors[cb_color_pos][0] * 0.2,
            rgb_colors[cb_color_pos][1] * 0.2,
            rgb_colors[cb_color_pos][2] * 0.2
        );
        */

    } // IF
    
} // PROCEDURE

#endif // RGB_CICLE_CERBEROS