#ifndef RGB_CICLE_COMU_H
#define RGB_CICLE_COMU_H

//Globals comú a tots els efectos
uint16_t cicle_INTERVAL = 30;
uint32_t lapse_INTERVAL = 0;
uint8_t cicle_ELEGIT = 2;

#define MAXIM_CICLE_INTERVAL 3000
#define MINIM_CICLE_INTERVAL 30
// Matriu de colors (static para que sea sólo de este archivo)
#define RGB_COLOR_COUNT 10          // Definim el total de cicles que tenim
const uint8_t rgb_colors[RGB_COLOR_COUNT][3] = {
    {255, 0, 0},    // Roig
    {0, 255, 0},    // Verd
    {0, 0, 255},    // Blau
    {255, 255, 0},  // Groc
    {0, 255, 255},  // Cyan
    {255, 0, 255},  // Magenta
    {255, 255, 255},// Blanc
    {128, 0, 128},  // Púrpura
    {0, 128, 128},  // Aguamarina
    {128, 128, 0}   // Oliva
};

// Matriu de circuit de tecles CIRCULAR
#define TOTAL_CIRCUIT_CIRCULAR 35  // Definim el total de cicles que tenim
const uint8_t circuit_circular[TOTAL_CIRCUIT_CIRCULAR] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,   // Esquerra a dreta superior
    33, 67, 85,                                             // Baixem per la dreta
    97, 96 ,95 ,94, 93, 92, 91, 90, 89, 88, 87, 86,         // Dreta a esquerra inferior
    68, 51, 34, 16                                          // Pujem per la esquerra
};


#endif // RGB_CICLE_COMU_H
