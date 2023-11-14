#include "16F874.h"

#device adc=8
#use delay(clock=10000000)

#fuses XT,NOWDT,NOPUT


void main() {
   int i = 0;
   long int tensao[5];
   long int media_tensao;
   char media;

   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0); // read_adc();

   delay_us(100);
   output_high(PIN_C0);

   while(1) {

   }

}
