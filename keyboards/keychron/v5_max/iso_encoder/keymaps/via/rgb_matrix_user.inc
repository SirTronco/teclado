RGB_MATRIX_EFFECT(perroguardian)

#ifdef  RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool perroguardian(effect_params_t* params){
            rgb_matrix_set_color_all(
            128,
            128,
            128
        );
        
    return true;

}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS