/*
 * Exemplo de solução para o projeto:
 *  1) O acionamento dos LEDs (sinais do semáforo) deve iniciar na cor vermelha,
 *     passando posteriormente para amarelo e, em seguida, verde.
 *  2) O temporizador deve ser ajustado para um atraso de 3 segundos (3000 ms).
 *  3) A mudança de estado dos LEDs deve ser implementada na função de call-back
 *     do temporizador (repeating_timer_callback()).
 *  4) A rotina principal, dentro do while, deve imprimir alguma informação na
 *     porta serial a cada 1 segundo (1000 ms).
 *
 * Por: Heitor Rodrigues Lemos Dias
 */


#include "pico/stdlib.h"
#include <stdio.h>


#define LED_R 13
#define LED_G 11
#define LED_B 12



bool callback_leds();

int main() {

  stdio_init_all();

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
  gpio_init(LED_B);
  gpio_set_dir(LED_B, GPIO_OUT);

  
  gpio_put(LED_R, 1);
  gpio_put(LED_G, 0);
  gpio_put(LED_B, 0);
  

  
  static struct repeating_timer timer;


  add_repeating_timer_ms(3000, callback_leds, NULL, &timer);

  uint32_t ultimo_print = to_ms_since_boot(get_absolute_time());

  const uint32_t INTERVALO = 1000;

  while (true) {
      
      uint32_t agora = to_ms_since_boot(get_absolute_time());

      
      if (agora - ultimo_print >= INTERVALO) {
          
          ultimo_print = agora;

          
          printf("%s\n", gpio_get(LED_R) ? "LED Vermelho está aceso"
                 : gpio_get(LED_G)      ? "LED Verde está aceso"
                 : gpio_get(LED_B)      ? "LED Amarelo está aceso"
                                        : "Nenhum LED está aceso");
      }

       
      tight_loop_contents();
  }


  return 0;

}

bool callback_leds(struct repeating_timer *t) {
    
    if(gpio_get(LED_R)){
        gpio_put(LED_R, 0);
        gpio_put(LED_G, 0);
        gpio_put(LED_B, 1);
    } else if(gpio_get(LED_B)){
        gpio_put(LED_B, 0);
        gpio_put(LED_R, 0);
        gpio_put(LED_G, 1);
    } else if(gpio_get(LED_G)){
        gpio_put(LED_G, 0);
        gpio_put(LED_B, 0);
        gpio_put(LED_R, 1);
    }
    return true; // Retorna 'true' para continuar repetindo
}

