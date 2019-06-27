#include "buzzer.h"
#include <pwm.h>

void set_buzzer_pwm(struct sensor_configuration* config,int pulse_width){
    if(pwm_pin_set_usec(config->buzzer,config->buzzer_pin,PWM_PERIOD,pulse_width)){
        printk("pwm pin set failed\n");
    }
}
