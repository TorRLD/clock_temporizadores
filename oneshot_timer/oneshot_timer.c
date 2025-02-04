/*
 * Exemplo de solução para a tarefa:
 *  - Ao pressionar o botão (GPIO 5), inicia-se a sequência de estados dos LEDs RGB:
 *    1) Todos acesos (R, G, B);
 *    2) Dois LEDs acesos (por ex.: R, G);
 *    3) Um LED aceso (por ex.: G);
 *    4) Todos apagados.
 *  - Cada estado dura 3 segundos (3000 ms).
 *  - Enquanto a sequência estiver em execução, não é possível iniciá-la novamente (uma nova
 *    pressão do botão só é válida após o término da sequência).
 *
 * Por: Heitor Rodrigues Lemos Dias
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definições de pinos conforme o seu hardware (ex.: BitDogLab)
#define LED_R      13
#define LED_G      11
#define LED_B      12
#define BOTAO_PIN  5

// Intervalo de atraso entre estados (em ms)
#define TEMPO_MS 3000

// Variáveis globais para controlar a sequência
static bool sequenciaAtiva = false;  // Indica se a sequência de LEDs está em execução
static int estadoLED = 0;            // Controla qual etapa da sequência está ativa

// Função de callback do temporizador (alarm) que gerencia a mudança de estado dos LEDs
int64_t sequencia_led_callback(alarm_id_t id, void *user_data) {
    estadoLED++;  // Avança para o próximo estado

    switch (estadoLED) {
        case 1:
            // Estado 1: acende todos os LEDs (R, G, B)
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 1);
            add_alarm_in_ms(TEMPO_MS, sequencia_led_callback, NULL, false);
            break;

        case 2:
            // Estado 2: mantém dois LEDs acesos (ex.: R, G)
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 0);
            add_alarm_in_ms(TEMPO_MS, sequencia_led_callback, NULL, false);
            break;

        case 3:
            // Estado 3: mantém apenas um LED aceso (ex.: G)
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 0);
            add_alarm_in_ms(TEMPO_MS, sequencia_led_callback, NULL, false);
            break;

        case 4:
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 0);
            gpio_put(LED_B, 0);
            // Fim da sequência
            sequenciaAtiva = false;
            estadoLED = 0;
            break;

        default:
            // Se algo estranho acontecer, interrompe
            sequenciaAtiva = false;
            estadoLED = 0;
            break;
    }

    return 0;
}

int main() {
    // Inicializa a interface padrão (printf, etc.)
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 0);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_put(LED_G, 0);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_B, 0);

    // Configura o pino do botão como entrada + pull-up interno
    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    while (true) {
        // Verifica se o botão foi pressionado (nível baixo) e se não há sequência em execução
        if (gpio_get(BOTAO_PIN) == 0 && !sequenciaAtiva) {
            // Debounce simples
            sleep_ms(50);
            // Verifica novamente se continua pressionado
            if (gpio_get(BOTAO_PIN) == 0 && !sequenciaAtiva) {
                // Inicia a sequência
                sequenciaAtiva = true;
                estadoLED = 0;
                // Agenda o primeiro callback para daqui a TEMPO_MS milissegundos
                add_alarm_in_ms(TEMPO_MS, sequencia_led_callback, NULL, false);
            }
        }

        // Pequeno atraso para evitar uso excessivo da CPU
        sleep_ms(10);
    }

    return 0; // Em tese, nunca chegaremos aqui por conta do loop infinito
}
