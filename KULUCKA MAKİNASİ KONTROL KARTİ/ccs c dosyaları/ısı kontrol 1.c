#include <ýsý kontrol 1.h>
long sayac=0;
int16 adc_giris=0;
float sicaklik=0,voltaj=0;
#define motor pin_a1//viyol motoru
#define isitici pin_a2//rezistans 
#INT_RTCC
void  RTCC_isr(void) // tmr0 kesme alt programi 1sn=1000ms,1dk=60000ms,1saat=3600000ms,2saat=7200000ms
{
sayac++;//sayac degerini 1 artir 
if(sayac==7200000);//2 saat olunca
{
for(int i=0;i++;i<30)//30 saniye motor calisir
{
output_high(motor);//motor lojik 1
delay_ms(1000);
}
output_low(motor);//motor lojik 0
sayac=0;// sayac degerini baþa döndür
}


}

#INT_AD//analog dijital donusumden sonra olusan kesme
void  AD_isr(void) 
{
  if(sicaklik<37.0)//sicaklik kontrolu
      {
      output_high(pin_a2);//a2 portu lojik 1
      delay_ms(100);
     
      }
      else
      {
      output_low(pin_a2);
      delay_ms(100);
      }
      
}

void main()
{  
   
   setup_adc_ports(sAN0);//a0 bacagi analog giris 
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //65,5 ms overflow


   enable_interrupts(INT_RTCC);
   enable_interrupts(INT_AD);
   enable_interrupts(GLOBAL);

   while(TRUE)
   {
      
      set_adc_channel(0);//a0 bacagý secildi
      delay_us(20);
      adc_giris=read_adc();//adc okuma degeri degiskene aktarildi
      voltaj=adc_giris*(5.0/1024.0)*1000;// voltaj okumak icin yapilan hesap
      sicaklik=(voltaj/10);//sicaklik ölçümü
    
      }

}
