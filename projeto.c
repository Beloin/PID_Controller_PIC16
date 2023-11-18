#include <16f874.h>

#device adc=8
#use delay(clock=1000000)
#fuses XT,NOWDT,NOPUT


// Equation defined in README.md, found in matlab c2d(...)in non-canonical representation
// uk = 0.05843*e_k1 - uk_1

void main(){
	int ref = 127;
	float uk_1 = 0, ek = 0, ek_1 = 0, yk = 0;
	char out;

	setup_adc_ports(ALl_ANALOG);
	setup_adc(ADC_CLOCK_INTERNAL);
	set_adc_channel(0); // or 1?
	delay_ms(1)
	setup_timer_2(T2_DIV_BY_4, 65, 1);
	setup_ccp1(CCP_PWM);
	set_pwm1_duty(127); // ALready sets initial value, as half of the input voltage.
	enable_interrupts(GLOBAL | INT_TIMER2);
	
	// TODO: Implement timer instead of delay... Timers rock!!
	while (1) {
		delay_ms(1); // So our "timer" is 1ms, since we calculated it in the Dz
		yk = read_adc();
		ek = ref - yk; // ref is already in 8Bits format, but if it was voltage, we would need to convert 5v to 8 bits (Scales from 0-12v to 0-255)
		uk = 0.05843*e_k1 - uk_1; // TODO: Is uk_1 = 0 appropriate when the first data arrives? Should we use it as uk_1 = ref?
		
		out = (int)uk;
		if (out > 255) uk = 255;
		if (out < 0) uk = 0;

		set_pwm1_duty(out);

		uk_1 = uk;
		ek_1 = ek;
	}

}