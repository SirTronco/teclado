#ifndef RGB_CICLE_SEMAFORO_H
#define RGB_CICLE_SEMAFORO_H

// Prototipo de la funció
void RGB_CICLE_SEMAFORO(bool inactiu);

// Globals locals
uint8_t semaforo_color_index = 0;


// -- Mi propio ciclo de colores --
void RGB_CICLE_SEMAFORO(bool inactiu){
    
    // Cada 3 segons camviarem el color que ha de utilitzar-se
    if (timer_elapsed32(lapse_INTERVAL) > cicle_INTERVAL){
        lapse_INTERVAL = timer_read32();
        semaforo_color_index = (semaforo_color_index + 1) % RGB_COLOR_COUNT;
    }

    if (inactiu){
    // Si estem en modo inactiu, entonces pintem nosaltres, si no deixarem el automatic que estiga vigent
        rgb_matrix_set_color_all(
            rgb_colors[semaforo_color_index][0],
            rgb_colors[semaforo_color_index][1],
            rgb_colors[semaforo_color_index][2]
        );
    }
    
}

#endif // RGB_CICLE_SEMAFORO