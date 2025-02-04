# Clock e Temporizadores


## Vídeo Demonstrativo:

[Assista no Youtube](https://www.youtube.com/watch?v=O01UKLZ3Y6w)

Este repositório contém **duas tarefas** que demonstram o uso do Raspberry Pi Pico (ou placa compatível com RP2040) para controle de LEDs e uso de temporizadores ( *timers* ) e callbacks. Ambas estão escritas em linguagem C e utilizam o  **Pico SDK** .

---

## **Tarefa 1**

### Descrição

1. **Semáforo Básico**
   * O sistema inicia na cor  **vermelha** .
   * Após 3 segundos, muda para  **amarelo** .
   * Após mais 3 segundos, muda para  **verde** .
   * Após mais 3 segundos, retorna para vermelho, repetindo o ciclo.
2. **Temporizador de 3 segundos**
   * É utilizado um `repeating_timer` configurado para disparar a cada 3000 ms.
3. **Callback do Temporizador**
   * A cada disparo do temporizador, a função `callback_leds()` muda o estado do semáforo (vermelho → amarelo → verde → vermelho).
4. **Impressão na porta serial a cada 1 segundo**
   * No `while(true)` principal, a cada 1000 ms é impresso via `printf()` o LED que está atualmente aceso.

### Pontos Importantes

* **GPIOs** :
* `LED_R = 13`
* `LED_B = 12` (usado como amarelo no código)
* `LED_G = 11`
* **Requisitos de hardware** :
* 3 LEDs ou equivalentes ligados nas GPIOs configuradas, com resistores apropriados (dependendo da placa e do LED).
* **Como funciona** :
* Ao iniciar, somente o LED vermelho é ligado.
* A cada 3 segundos, a função de callback muda o LED aceso para o próximo estado.
* Paralelamente, o programa imprime no terminal (via USB) qual LED está aceso a cada segundo.

---

### Como Executar

1. **Clonar** este repositório ou copiar os arquivos para uma pasta local no seu computador.
2. **Abrir a pasta** no Visual Studio Code.
3. **Certificar-se** de ter instalado e configurado a **extensão “Raspberry Pi Pico”** no VSCode (que já inclui o Pico SDK).
4. **Na parte inferior do VSCode** (barra de status), selecione a placa “Raspberry Pi Pico” e aperte em **“Compile”** (ou “Build”) para gerar o arquivo `.uf2`.
5. **Carregar o `.uf2`** na placa Pico: coloque o Pico em **modo bootloader** (conecte-o ao USB segurando o botão BOOTSEL ou conforme sua placa), e arraste o arquivo `.uf2` para a unidade que aparecer no seu computador.
6. **Abrir um terminal serial** (via USB) para observar as mensagens impressas ou fazer interações adicionais conforme o projeto.

## **Tarefa 2**

### Descrição

1. **Sequência RGB Controlada por Botão**
   * Ao pressionar o botão (pino  **GPIO 5** ), inicia-se a sequência de LEDs:
     1. Todos acesos (R, G, B);
     2. Dois acesos (ex.: R, G);
     3. Um aceso (ex.: G);
     4. Todos apagados.
   * Cada etapa dura  **3 segundos** .
2. **Bloqueio de Reativação**
   * Enquanto a sequência estiver em execução, **não** é possível dispará-la novamente. Só quando todos os LEDs se apagarem é que um novo clique no botão terá efeito.
3. **Callback do Temporizador (Alarm)**
   * Usa `add_alarm_in_ms()` para agendar a mudança de estado após cada intervalo de 3 s.
   * A função `sequencia_led_callback()` é chamada para acender/apagar os LEDs conforme o estado.

### Pontos Importantes

* **GPIOs** :
* `LED_R = 13`
* `LED_G = 11`
* `LED_B = 12`
* `BOTAO_PIN = 5`
* **Debounce Simples** :
* O código faz um `sleep_ms(50)` para evitar leituras falsas de “ruído” ao pressionar o botão.
* **Variáveis de Controle** :
* `sequenciaAtiva`: Indica se a sequência está em andamento.
* `estadoLED`: Identifica qual passo da sequência deve ser executado no callback.

### Como Executar

1. **Clonar** este repositório ou copiar os arquivos para uma pasta local no seu computador.
2. **Abrir a pasta** no Visual Studio Code.
3. **Certificar-se** de ter instalado e configurado a **extensão “Raspberry Pi Pico”** no VSCode (que já inclui o Pico SDK).
4. **Na parte inferior do VSCode** (barra de status), selecione a placa “Raspberry Pi Pico” e aperte em **“Compile”** (ou “Build”) para gerar o arquivo `.uf2`.
5. **Carregar o `.uf2`** na placa Pico: coloque o Pico em **modo bootloader** (conecte-o ao USB segurando o botão BOOTSEL ou conforme sua placa), e arraste o arquivo `.uf2` para a unidade que aparecer no seu computador.
6. **Abrir um terminal serial** (via USB) para observar as mensagens impressas ou fazer interações adicionais conforme o projeto.
---

## Observações Gerais

* Ambos os exemplos utilizam a **biblioteca-padrão** do Pico, com destaque para:

* `pico/stdlib.h` (GPIO, sleep, etc.)
* `pico/time.h` (temporizadores e alarms)
* Certifique-se de que **a pinagem** corresponda ao seu hardware (especialmente se estiver usando alguma placa de expansão ou kit didático, como o BitDogLab).
* Recomenda-se uma fonte de alimentação **estável** e resistores em série nos LEDs, conforme a documentação do Pico e boas práticas de eletrônica.
* Você pode **observar a saída serial** (via USB) para debug ou mensagens adicionais.
* O **clock** do microcontrolador deve estar configurado corretamente pelo CMake do Pico SDK para funcionar com os delays e timers de forma previsível.

---

 **Autor (códigos de exemplo)** :

Heitor Rodrigues Lemos Dias
