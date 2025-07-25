#ifndef EMBARCATECH_ESTACAO_METEOROLOGICA_H
#define EMBARCATECH_ESTACAO_METEOROLOGICA_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

#include "ssd1306.h"
#include "aht20.h" // Biblioteca para o sensor AHT20
#include "bmp280.h" // Biblioteca para o sensor BMP280
#include "led_matrix.h" // Biblioteca para a matriz de LEDs
#include "pio_matrix.pio.h" // Biblioteca para o PIO da matriz de LEDs

#include "lwipopts.h"
#include "pico/cyw43_arch.h" // Biblioteca para arquitetura Wi-Fi da Pico com CYW43
#include "lwip/tcp.h"        // Lightweight IP stack - fornece funções e estruturas para trabalhar com o protocolo TCP


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define I2C_PORT i2c0
#define I2C_SDA 0                   
#define I2C_SCL 1       

#define RED_LED_GPIO 13 // Pino do LED vermelho
#define GREEN_LED_GPIO 11 // Pino do LED verde
#define BLUE_LED_GPIO 12 // Pino do LED azul

#define BUTTONA_GPIO 5 // Pino do botão A
#define BUTTONB_GPIO 6 // Pino do botão B
#define DEBOUNCE_TIME 300 // Tempo de debounce em milissegundos

/* ------------------ Constantes ------------------ */
#define LED_PIN CYW43_WL_GPIO_LED_PIN // GPIO do CI CYW43

#define WIFI_SSID ""   // Nome da rede Wi-Fi
#define WIFI_PASSWORD "" // Senha da rede Wi-Fi


#define SEA_LEVEL_PRESSURE 101325.0 // Pressão atmosférica ao nível do mar em Pa
#define MIN_TEMPERATURE 10.0 // Temperatura mínima em graus Celsius
#define MAX_TEMPERATURE 40.0 // Temperatura máxima em graus Celsius
#define MIN_HUMIDITY 20.0 // Umidade mínima em porcentagem
#define MAX_HUMIDITY 90.0 // Umidade máxima em porcentagem


/* --------- Prototipo de funcoes -----------------*/
void i2c_setup();
void ssd1306_config_gpio(ssd1306_t *ssd);
double calculate_altitude(double pressure);


/* ------------------- Structs e enums -------------------*/
typedef enum {
    OFFSET_TEMP,
    OFFSET_HUM,
    LIMITS_TEMP,
    LIMITS_HUM,
} UpdateType_t;

typedef struct {
    float temperature_bmp;
    double altitude;
    AHT20_Data aht20_data;
    float temp_offset;
    float hum_offset;
    uint8_t status;
} Station_data_t;

typedef struct{
    float min_temperature;
    float max_temperature;
    float min_humidity;
    float max_humidity;
} Station_limits_t;

typedef struct {
    UpdateType_t type; // Tipo de atualização
    float min;
    float max;
} UpdateData_t;

struct http_state
{
    char response[8500];
    size_t len;
    size_t sent;
};


// Variáveis para controle de tempo de debounce dos botões
uint last_time_button_A = 0;

Station_data_t station_data_global; // Variável global para armazenar os dados da estação meteorológica
Station_limits_t station_limits_global; // Variável global para armazenar os limites de temperatura e umidade

SemaphoreHandle_t xStationDataMutex, xDisplayViewSemaphore, xStationLimitsMutex; // Semáforo para controle de acesso ao barramento I2C

QueueHandle_t xQueueStationStatus1, xQueueUpdateData; // Filas para comunicação entre tarefas

#endif // EMBARCATECH_ESTACAO_METEOROLOGICA_H
