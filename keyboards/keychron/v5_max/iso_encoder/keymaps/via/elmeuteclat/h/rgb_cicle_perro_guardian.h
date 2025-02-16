#ifndef RGB_CICLE_PERRO_GUARDIAN_h
#define RGB_CICLE_PERRO_GUARDIAN_H

// Prototipo de la funció
void RGB_CICLE_PERRO_GUARDIAN(bool inactiu );

// Globals locals
uint8_t pg_color_index = 0;
uint8_t pg_color_ant = 0;
uint8_t pg_color_pos = 0;

uint8_t posicio_perro = 0;
uint8_t posicio_ant = 0;
uint8_t posicio_pos = 0;



// -- Mi propio ciclo de colores --
void RGB_CICLE_PERRO_GUARDIAN(bool inactiu){
    
    // Cada 3 segons camviarem el color que ha de utilitzar-se
    if (timer_elapsed32(lapse_INTERVAL) > cicle_INTERVAL){ 
        lapse_INTERVAL = timer_read32();
        pg_color_index = (pg_color_index + 1) % RGB_COLOR_COUNT;  // canviem el color
        posicio_perro = (posicio_perro + 1) % TOTAL_CIRCUIT_CIRCULAR;              // menejem al gos

    }

    if (inactiu){
    // Si estem en modo inactiu, entonces pintem nosaltres, si no deixarem el automatic que estiga vigent
        // apaguem totes les tecles
        rgb_matrix_set_color_all(0,0,0); 
        
        // Alumbrem la tecla que "camina"
        rgb_matrix_set_color(
            circuit_circular[posicio_perro],
            rgb_colors[pg_color_index][0],
            rgb_colors[pg_color_index][1],
            rgb_colors[pg_color_index][2]
        );

    }
    
}

#endif // RGB_CICLE_SEMAFORO