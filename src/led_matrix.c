
#include "led_matrix.h"

/* Definicao de constantes*/
const uint GPIO_LED_MTX = 7;

uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}



void matrix_turn_all(PIO pio, uint state_machine, double red, double green, double blue){
    uint32_t led_value = matrix_rgb(blue, red, green);

    for (int i = 0; i < MTX_NUM_LEDS; i++){
        pio_sm_put_blocking(pio, state_machine, led_value);
    }
}



void matrix_display_frame(PIO pio, uint state_machine, char frame[5][5]){

    int step, start, end, i, j;
    uint32_t led_value;

    for (i = 4; i >= 0; i--) {

        // Even rows are displayed left to right, odd rows right to left
        if (i & 1){
            step = 1;
            start = 0;
            end = 5;
        }else{
            step = -1;
            start = 4;
            end = -1;
        }

        for (j = start; j != end; j += step) {
            switch(frame[i][j]){
                case 'w':
                    led_value = matrix_rgb(0.05, 0.05, 0.05); // White
                    break;
                case 'r':
                    led_value = matrix_rgb(0, 0.05, 0);
                    break;
                case 'g':
                    led_value = matrix_rgb(0,0,0.05);
                    break;
                case 'b':
                    led_value = matrix_rgb(0.05, 0, 0);
                    break;
                case 'p':
                    led_value = matrix_rgb(0.05, 0.05, 0);
                    break;
                case 'y':
                    led_value = matrix_rgb(0, 0.05, 0.05);
                    break;
                default:
                    led_value = matrix_rgb(0, 0, 0); // Off
                    break;

            }
            pio_sm_put_blocking(pio, state_machine, led_value);
        }

    }
}