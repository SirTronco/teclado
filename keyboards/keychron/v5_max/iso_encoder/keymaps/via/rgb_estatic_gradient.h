#ifndef RGB_ESTATIC_GRADIENT_H
#define RGB_ESTATIC_GRADIENT_H

// Prototipo de la funció
void RGB_ESTATIC_GRADIENT(bool inactiu, uint8_t coloret);

// Globals locals
uint8_t posicio = 0;

// colors que triem per al gradient
uint8_t parcial = 0;

// -- UN AUMENT GRADUAL DEL BRILLO
void RGB_ESTATIC_GRADIENT(bool inactiu, uint8_t coloret){
    
    if (inactiu){
        // Fem de una senbtà
        // apaguem totes les tecles
        rgb_matrix_set_color_all(0,0,0);  

        // Recorrem tot el circuit
        for (uint8_t bucle = 0; bucle < 10; bucle++){
            
            // calculem el % del brillo, segons el index del bucle
            parcial = (10-bucle)*10; // bucle / TOTAL_CIRCUIT_CIRCULAR;

            rgb_matrix_set_color(
                circuit_circular[bucle],        // posició del circuit
                rgb_colors[coloret][0] / parcial,
                rgb_colors[coloret][1] / parcial,
                rgb_colors[coloret][2] / parcial
            );

/*              rgb_colors[coloret][0] * parcial,
                rgb_colors[coloret][1] * parcial,
                rgb_colors[coloret][2] * parcial
*/

        } // FOR

    } // IF
    
} // VOID

#endif // RGB_CICLE_CERBEROS