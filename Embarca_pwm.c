#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h" //biblioteca para gerenciamento de PWM
#include "pico/time.h" //biblioteca para gerenciamento de tempo
#include "hardware/irq.h" //biblioteca para gerenciamento de interrupções

const uint SERVO_MOTOR = 22;
const uint16_t PERIOD = 20000; // Período de 20ms para frequência de 50Hz
const float DIVIDER_PWM = 125.0; // Divisor de clock 
const uint16_t LED_STEP = 5; // Passo para movimento suave
uint16_t LED_LEVEL = 10000; // Ciclo ativo inicial

// Função para definir o ângulo do servo
void set_servo_angle(uint sliceNum, uint16_t duty_us) {
    uint16_t level = (duty_us * PERIOD) / 20000; // Converte microssegundos para nível PWM
    pwm_set_gpio_level(SERVO_MOTOR, level);
}

// Função para mover o servo suavemente entre dois ângulos
void move_servo_smoothly(uint sliceNum, uint16_t start_us, uint16_t end_us) {
    int step = (start_us < end_us) ? LED_STEP : -LED_STEP;
    for (uint16_t duty = start_us; (step > 0) ? (duty <= end_us) : (duty >= end_us); duty += step) {
        set_servo_angle(sliceNum, duty);
        sleep_ms(10);
    }
}

// Configuração do PWM
uint setup_pwm() {
    gpio_set_function(SERVO_MOTOR, GPIO_FUNC_PWM); // Habilitar o pino GPIO como PWM
    uint sliceNum = pwm_gpio_to_slice_num(SERVO_MOTOR); // Obter o canal PWM da GPIO

    pwm_config config = pwm_get_default_config(); // Obter a configuração padrão para o PWM
    pwm_config_set_clkdiv(&config, DIVIDER_PWM); // Definir o divisor de clock do PWM
    pwm_config_set_wrap(&config, PERIOD); // Definir o período do PWM
    pwm_init(sliceNum, &config, true); // Inicializar o PWM com as configurações do objeto

    return sliceNum;
}

int main() {
    stdio_init_all(); // Inicializar todas as funções padrão de entrada/saída
    uint sliceNum = setup_pwm(); // Configurar o PWM

    // Definir servo para 180 graus
    set_servo_angle(sliceNum, 2400);
    sleep_ms(5000);

    // Definir servo para 90 graus
    set_servo_angle(sliceNum, 1470);
    sleep_ms(5000);
    
    // Definir servo para 0 graus
    set_servo_angle(sliceNum, 500);
    sleep_ms(5000);

    // Mover servo suavemente entre 0 e 180 graus
    while (true) {
        move_servo_smoothly(sliceNum, 500, 2400);
        sleep_ms(100);
        move_servo_smoothly(sliceNum, 2400, 500);
        sleep_ms(100);
    }
}
