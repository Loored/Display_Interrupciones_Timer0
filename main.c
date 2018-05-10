#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)


//Se emplea la directiva de Fast_io
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)

//Se declara un arreglo que alamcene los numeros que se mostraran en el display.
int array[]={
    0x00,//num0
    0x01,//num1
    0x02,//num2
    0x03,//num3
    0x04,//num4
    0x05,//num5
    0x06,//num6
    0x07,//num7
    0x08,//num8
    0x09 //num9
};

//Declaramos las variables que se utilizaran,
int numeroUno = 0;//Puerto de salida
int desbordamiento = 0;//Puerto a nivel bajo en todos los pines

//Se crea la funcion para el primer display de 500ms
void funcionDisplay500ms (void){
    set_tris_b(0x00);//Puerto de salida
    output_b(0x00);//Puerto a nivel bajo en todos los pines
    
    //Valor de prescaler de 2
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2|RTCC_8_BIT);
    
    //Valor de timer0 aplicando formula es 6
    set_timer0(6);
}

void funcionDisplay200ms (void){
    set_tris_c(0x00);//Puerto de salida
    output_c(0x00);//Puerto a nivel bajo en todos los pines
    
    //Valor de prescaler de 2
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2|RTCC_8_BIT);
    
    //Valor de timer0 aplicando formula es 156
    set_timer0(156);
}

void funcionDisplay1s (void){
    set_tris_d(0x00);
    output_d(0x00);
    
    //Valor de prescaler de 1
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1|RTCC_8_BIT);
    
    //Valor de timer0 aplicando formula es 256
    set_timer0(256);
}

//Se activa la funcion del timer0
#int_timer0

void isr_interrupcionTimer0 (void){ //Se crea la funcion
    
    //Se va incrementando la variable desbordamiento        
    desbordamiento++;
    if(desbordamiento == 9){//Cuando desbordamiento llegue a 9
        desbordamiento = 0;//Se retorna a 0
    }
}

//enable_interrupts(int_timer0);//Se activa la funcion interrupcion
//enable_interrupts(global);//Se activa la funcion que desactiva la funcion

void main (void){
    
   setup_oscillator(OSC_16MHZ);
   setup_adc_ports(NO_ANALOGS);

   while(1){
       
       output_b(array[numeroUno]);
       delay_ms(500);
       
      
       output_c(array[numeroUno]);
       delay_ms(200);
       
       
       output_d(array[numeroUno]);
       delay_ms(1000);
   }
}
  void funcionDisplay500ms();
  void funcionDisplay200ms();
  void funcionDisplay1s();
