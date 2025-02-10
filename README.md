# DisplayC - Manipulação da Placa BitDogLab com Raspberry Pi Pico W

## Descrição

O **DisplayC.c** é um programa desenvolvido para manipular os componentes da **placa BitDogLab** utilizando o **Raspberry Pi Pico W**. Ele permite controlar um **painel de LEDs 5x5**, um **LED RGB** e **botões físicos** da placa. Além disso, exibe informações em um **display OLED SSD1306** e responde a comandos via **USB**.

## Funcionalidades

- Controle de **LEDs individuais** (verde e azul) através de botões físicos.
- Exibição de caracteres no **display OLED SSD1306** via comunicação **I2C**.
- Manipulação de um **painel de LEDs 5x5** para exibir padrões numéricos de 0 a 9.
- Resposta a comandos recebidos via **USB**, acendendo LEDs e atualizando o display.

## Componentes Utilizados

- **Raspberry Pi Pico W**
- **Placa BitDogLab**


## Dependências

Antes de compilar e rodar o programa, certifique-se de ter instalado:

- **SDK do Raspberry Pi Pico** ([Guia de instalação](https://github.com/raspberrypi/pico-sdk))

- **Bibliotecas adicionais**:
  - `pico/stdlib.h`
  - `hardware/i2c.h`
  - `hardware/pio.h`
  - `hardware/timer.h`
  - `hardware/clocks.h`
  - `ssd1306.h`
  - `font.h`
  - `ws2812.pio.h`

## Configuração dos Pinos

| Componente        | Pino GPIO |
|-------------------|----------|
| I2C SDA          | 14       |
| I2C SCL          | 15       |
| LED Azul         | 12       |
| LED Vermelho     | 13       |
| LED Verde        | 11       |
| Botão A          | 5        |
| Botão B          | 6        |
| WS2812 (LED RGB) | 7        |

## Como Compilar e Executar

1. **Configure o ambiente de desenvolvimento** do Raspberry Pi Pico seguindo a documentação oficial.
2. Clone este repositório:
3. Compile o código utilizando a extensão do Raspberry Pi Pico
4. Carregue o firmware no Raspberry Pi Pico:
    Conecte o Pico W no modo USB (pressione BOOTSEL ao conectar).
    Copie o arquivo DisplayC.uf2 para o dispositivo RPI-RP2.
    O programa iniciará automaticamente e responderá a entradas via USB e botões físicos.

## Exemplo de Uso
- Pressionar Botão A liga/desliga o LED Verde e exibe no display.
- Pressionar Botão B liga/desliga o LED Azul e exibe no display.
- Digitar números via USB acende padrões numéricos no painel de LEDs.
- Digitar letras via USB apaga os LEDs da matriz e exibe as letras no painel.

## Autor
Desenvolvido por David Rios

📌 Observação: Este projeto foi desenvolvido para testes e aprendizado com a BitDogLab e Raspberry Pi Pico W.


## Link do vídeo
- Link do vídeo de demonstração: <https://youtu.be/yb_NPk-QaaI>