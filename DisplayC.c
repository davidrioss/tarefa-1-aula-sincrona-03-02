/*
- monitor serial- digita o caractere e ele aparece no display ssd1306, um caractere por vez, se for numero tem que aparecer na matriz de led 5x5 tbm

- botão a - ligar e desligar o led verde, mensagem sobre o estado do led no display ssd1306 e texto descritivo no monitor serial

- botão b - ligar e desligar o led azul, mensagem sobre o estado do led no display ssd1306 e texto descritivo no monitor serial

*/
#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"


#define IS_RGBW false
#define NUM_PIXELS 25
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define LED_AZUL 12
#define LED_VERMELHO 13 
#define LED_VERDE 11
#define BOTAO_A 5
#define BOTAO_B 6
#define WS2812_PIN 7


// Variáveis globais
static volatile uint a = 0;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
ssd1306_t ssd; // Inicializa a estrutura do display

// Buffer para armazenar quais LEDs estão ligados matriz 5x5
bool led_buffer0[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};
bool led_buffer1[NUM_PIXELS] = {
    0, 0, 1, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 1, 1, 0, 0, 
    0, 0, 1, 0, 0
};
bool led_buffer2[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer3[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer4[NUM_PIXELS] = {
    0, 1, 0, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0
};bool led_buffer5[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 1, 1, 1, 0
};bool led_buffer6[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 1, 1, 1, 0
};bool led_buffer7[NUM_PIXELS] = {
    0, 1, 0, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 0, 0, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer8[NUM_PIXELS] = {
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};bool led_buffer9[NUM_PIXELS] = {
    0, 1, 0, 0, 0, 
    0, 0, 0, 1, 0, 
    0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0
};

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}


void set_one_led(uint8_t r, uint8_t g, uint8_t b, bool led_buffer[NUM_PIXELS])
{
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);

    // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (led_buffer[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
}

//função para ligar o led de acordo com o valor de a
void ligar_led(void)
{
    switch (a)
    {
    case 0:
        set_one_led(100, 0, 0, led_buffer0);
        break;
    case 1:
        set_one_led(0, 100, 0, led_buffer1);
        break;
    case 2:
        set_one_led(0, 0, 100, led_buffer2);
        break;
    case 3:
        set_one_led(0, 100, 100, led_buffer3);
        break;
    case 4:
        set_one_led(100, 100, 0, led_buffer4);
        break;
    case 5:
        set_one_led(100, 0, 100, led_buffer5);
        break;
    case 6:
        set_one_led(100, 100, 100, led_buffer6);
        break;
    case 7:
        set_one_led(100, 0, 0, led_buffer7);
        break;
    case 8:
        set_one_led(0, 100, 0, led_buffer8);
        break;
    case 9:
        set_one_led(0, 0, 100, led_buffer9);
        break;
    default:
        break;
    }
}

// Função de callback para a interrupção dos botões

void gpio_callback(uint gpio, uint32_t events) {
  // Obtém o tempo atual em microssegundos
  uint32_t current_time = to_us_since_boot(get_absolute_time());
  if (current_time - last_time > 200000) { // Debounce de 200ms
      last_time = current_time;
      // Verifica qual pino disparou a interrupção
      if (gpio == BOTAO_A) {
        if(gpio_get(LED_VERDE)){
          printf("Botão A pressionado. Desligando o LED verde\n");
          ssd1306_fill(&ssd, false); // Limpa o display
          ssd1306_draw_string(&ssd, "LED VERDE OFF", 8, 10); // Desenha uma string     
          ssd1306_send_data(&ssd); // Atualiza o display
          gpio_put(LED_VERDE, false);
        }else{
          printf("Botão A pressionado. Ligando o LED verde\n");
          ssd1306_fill(&ssd, false); // Limpa o display
          ssd1306_draw_string(&ssd, "LED VERDE ON", 8, 10); // Desenha uma string     
          ssd1306_send_data(&ssd); // Atualiza o display
          gpio_put(LED_VERDE, true);
        }
      } else if (gpio == BOTAO_B) {
        if(gpio_get(LED_AZUL)){
          printf("Botão B pressionado. Desligando o LED azul\n");
          ssd1306_fill(&ssd, false); // Limpa o display
          ssd1306_draw_string(&ssd, "LED AZUL OFF", 8, 10); // Desenha uma string     
          ssd1306_send_data(&ssd); // Atualiza o display
          gpio_put(LED_AZUL, false);
        }else{  
          printf("Botão B pressionado. Ligando o LED azul\n");
          ssd1306_fill(&ssd, false); // Limpa o display
          ssd1306_draw_string(&ssd, "LED AZUL ON", 8, 10); // Desenha uma string     
          ssd1306_send_data(&ssd); // Atualiza o display
          gpio_put(LED_AZUL, true);
        }
      }
  }
}



int main()
{
  stdio_init_all();

  // I2C Initialisation. Using it at 400Khz.
  i2c_init(I2C_PORT, 400 * 1000);
  
  //inicialização dos pinos
  gpio_init(LED_AZUL);
  gpio_set_dir(LED_AZUL, GPIO_OUT);
  gpio_put(LED_AZUL, 0);
  gpio_init(LED_VERMELHO);
  gpio_set_dir(LED_VERMELHO, GPIO_OUT);
  gpio_put(LED_VERMELHO, 0);
  gpio_init(LED_VERDE);
  gpio_set_dir(LED_VERDE, GPIO_OUT);
  gpio_put(LED_VERDE, 0);
  gpio_init(BOTAO_A);
  gpio_set_dir(BOTAO_A, GPIO_IN);
  gpio_pull_up(BOTAO_A);
  gpio_init(BOTAO_B);
  gpio_set_dir(BOTAO_B, GPIO_IN);
  gpio_pull_up(BOTAO_B);


  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
  gpio_pull_up(I2C_SDA); // Pull up the data line
  gpio_pull_up(I2C_SCL); // Pull up the clock line
  
  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
  ssd1306_config(&ssd); // Configura o display
  ssd1306_send_data(&ssd); // Envia os dados para o display

  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

  PIO pio = pio0;
  int sm = 0;
  uint offset = pio_add_program(pio, &ws2812_program);

  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);


  //configuração de interrupção dos botoes
  gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
  gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);


  while (true)
  {
    if (stdio_usb_connected())
    { // Certifica-se de que o USB está conectado
        char c;
        if (scanf("%c", &c) == 1)
        { // Lê caractere da entrada padrão
            printf("Recebido: '%c'\n", c);

            if (c>='0' && c<='9')
            {
              ssd1306_fill(&ssd, false); // Limpa o display
              ssd1306_draw_char(&ssd, c, 8, 10); // Desenha um caractere
              ssd1306_send_data(&ssd); // Atualiza o display
              a = c - '0'; // Converte o caractere para um número
              ligar_led();
            }
            else if ((c>='A' && c<='Z') || (c>='a' && c<='z'))
            {
              ssd1306_fill(&ssd, false); // Limpa o display
              ssd1306_draw_char(&ssd, c, 8, 10); // Desenha um caractere
              ssd1306_send_data(&ssd); // Atualiza o display
              set_one_led(0, 0, 0, led_buffer0);
            }
            
        }
    }
    sleep_ms(40);
  }
}