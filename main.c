#include <16F874.h>

#device adc=8
#use delay(clock = 1000000)
#fuses XT, NOWDT, NOPUT

// Equation defined in README.md, found in matlab c2d(...) in non-canonical representation
// uk = 0.05843*e_k1 + uk_1

void main()
{
	int ref = 127;
	float uk = 0, uk_1 = 0, ek = 0, ek_1 = 0, yk = 0;
	unsigned char out;

	setup_adc_ports(ALL_ANALOG);
	setup_adc(ADC_CLOCK_INTERNAL);
	set_adc_channel(0);

	delay_ms(1);
	setup_timer_2(T2_DIV_BY_4, 65, 1); // 250Khz
	setup_ccp1(CCP_PWM);
	// 1ms -> 50% UP -> .5ms
	set_pwm1_duty(127); // ALready sets initial value, as half of the input voltage.

	while (1)
	{
		delay_ms(1);
		yk = read_adc();
		ek = ref - yk;
		uk = (0.005843 * ek_1) + uk_1;

		out = (unsigned char)uk;
		if (out > 255)
			uk = 255;
		if (out < 0)
			uk = 0;

		set_pwm1_duty(out);

		uk_1 = uk;
		ek_1 = ek;
	}
}
