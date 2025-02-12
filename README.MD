# Controle de Ângulo de Servomotor com Raspberry Pi Pico W

Este projeto utiliza o módulo PWM do microcontrolador RP2040 para controlar o ângulo de um servomotor. A simulação é feita utilizando o simulador de eletrônica online Wokwi.

## Componentes

1. Microcontrolador Raspberry Pi Pico W
2. Servomotor – motor micro servo padrão – Wokwi

## Requisitos

1. Definir a frequência de PWM para aproximadamente 50Hz (período de 20ms) na GPIO 22.
2. Ajustar o ciclo ativo do módulo PWM para controlar o ângulo do servomotor:
   - 2.400µs (0,12%) para 180 graus
   - 1.470µs (0,0735%) para 90 graus
   - 500µs (0,025%) para 0 graus
3. Criar uma rotina para movimentação periódica do braço do servomotor entre os ângulos de 0 e 180 graus com movimentação suave.

## Instruções de Uso

### Pré-requisitos

- Raspberry Pi Pico W
- Pico SDK configurado no seu ambiente de desenvolvimento
- Simulador Wokwi (opcional para simulação)

### Compilação e Execução

1. Clone o repositório do projeto:
    ```sh
    git clone <URL_DO_REPOSITORIO>
    cd <NOME_DO_REPOSITORIO>
    ```

2. Crie um diretório de build e navegue até ele:
    ```sh
    mkdir build
    cd build
    ```

3. Configure o projeto com CMake:
    ```sh
    cmake ..
    ```

4. Compile o projeto:
    ```sh
    make
    ```

5. Carregue o binário gerado no Raspberry Pi Pico W ou execute a simulação wokwi.

### Funcionamento

1. O programa inicializa o PWM na GPIO 22 com uma frequência de 50Hz.
2. O servo é ajustado para 180 graus, 90 graus e 0 graus, com uma pausa de 5 segundos entre cada ajuste.
3. Após os ajustes iniciais, o servo se move suavemente entre 0 e 180 graus continuamente.

### Vídeo demostração 

 [Vídeo do Projeto](https://youtu.be/MR9-v-_7Od0).

