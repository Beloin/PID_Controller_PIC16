#include <16f874A.h>
#device adc=8

#use delay(clock=1000000)
#fuses XT,NOWDT,NOPUT


void main(){
	int ref = 127;
	float uk_1 = 0, ek = 0, ek_1 = 0, yk = 0;
	char out;

	setup_adc_ports(ALl_ANALOG);
	setup_adc(ADC_CLOCK_INTERNAL);
	set_adc_channel(0); // or 1
	delay_ms(1)
	setup_timer_2(T2_DIV_BY_4, 65, 1);
	setup_ccp1(CCP_PWM);
	set_pwm1_duty(127);
	enable_interrupts(GLOBAL | INT_TIMER2);
	
	while (1) {
		delay_ms(1);
		yk = read_adc
	}

}