#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#use fast_io(b)   //Se emplea la directiva de Fast_io
#use fast_io(c)   //Se emplea la directiva de Fast_io
#use fast_io(d)   //Se emplea la directiva de Fast_io

unsigned int contadorDoscientos = 0, contadorQuinientos = 0, contadorSegundo = 0; //Declaramos nuestros contadores
int contador1 = 0, contador2 = 0, contador3 = 0;  //Declaramos tres contadores distintos para llevar control de nuestros delays
int numeros[10]=  //Declaramos nuestro vector con los valores de nuestros numeros en decimal
{
   254, 48, 109, 121, 51, 91, 95, 112, 127, 123 
}; //Declaramos nuestros numeros en decimal a partir de su valor en binario representado en el BCD 7 segmentos
#int_timer0 //Declaramos que nuestra siguiente instrucción es un Timer_0
void contadorTimer0(void) //Creamos una funcion para nuestro Timer_0
{
   contadorSegundo++; //Si hay una interrupcion, contador segundo se aumenta en 1
   contadorDoscientos++; //Si hay una interrupcion, contador de doscientos se aumenta en 1
   contadorQuinientos++; //Si hay una interrupcion, contador de quinientos se aumenta en 1
   if(contadorDoscientos == 2) //Si nuestro contador doscientos es igual a 2
   {
      contador1++; //Nuestro contador 1 se aumenta en 1
      contadorDoscientos = 0;
   }
   if(contadorQuinientos == 5) //Si nuestro contador quinientos es igual a 5
   {
      contador2++; //Nuestro contador 2 se aumenta en 1
      contadorQuinientos = 0;
   }
   if(contadorSegundo == 10) //Si nuestro contador doscientos es igual a 10
   {
      contador3++; //Nuestro contador 3 se aumenta en 1
      contadorSegundo = 0;
   }
   if(contador1 >= 10) //Si nuestro contador1 es mayor o igual a 10
   {
      contador1=0; //Nuestro contador 1 toma se reinicia y toma el valor de 0
   }
   if(contador2 >= 10) //Si nuestro contador2 es mayor o igual a 10
   {
      contador2=0; //Nuestro contador 1 toma se reinicia y toma el valor de 0
   }
   if(contador3 >= 10) //Si nuestro contador3 es mayor o igual a 10
   {
      contador3=0; //Nuestro contador 1 toma se reinicia y toma el valor de 0
   }
   set_timer0(8); //Aplicamos calculos y empleamos el prescaler de 8
   
}
void main(void) //Programa principal
{
   setup_oscillator(OSC_16MHZ); //Configuramos nuestro oscillador a 16MHZ
   set_tris_b(0x00); //Declaramos nuestros puertos en modo salida
   set_tris_c(0x00); //Declaramos nuestros puertos en modo salida 
   set_tris_d(0x00); //Declaramos nuestros puertos en modo salida
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_BIT); //Habilitamos el reloj interno, el prescaler 2 y los 8 bits a trabajar
   set_timer0(8); //Aplicamos calculos y empleamos el prescaler de 8
   enable_interrupts(GLOBAL); //Habilitamos interrupciones globales
   enable_interrupts(INT_TIMER0); //Habilitar la interrupcion int_timer0
   while(1) //Abrimos un ciclo infinito
   {
      output_b(numeros[contador1]); //Sacamos el valor de nuestro contador 1 a traves de enuestro puerto B
      output_c(numeros[contador2]); //Sacamos el valor de nuestro contador 2 a traves de enuestro puerto C
      output_d(numeros[contador3]); //Sacamos el valor de nuestro contador 3 a traves de enuestro puerto D 
   }
}