#include "lib/include.h"

extern void Configurar_UART1(void)
{
    //CONFIGURACIÓN DE LOS PINES
    SYSCTL->RCGCUART  = (1<<1); //Paso 1 (RCGCUART) pag.389 UART/modulo1 0->desabilitar 1->habilitar
    SYSCTL->RCGCGPIO |= (1<<1); //Paso 2 (RCGCGPIO) pag.382 Habilita clock port B
    //(GPIOAFSEL) pag.770 Enable alternate function
    GPIOB->AFSEL = (1<<1) | (1<<0);
    // Indico la recepción y transmisión
    GPIOB->DIR |= (0<<0) | (1<<1); // recepcion -> 0, transmisión -> 1 
    // Desabilitar resistencias pull - up y pull - down
    GPIOB->PUR |= (0<<0) | (0<<1);
    GPIOB->PDR |= (0<<0) | (0<<1);
    //GPIO Port Control (GPIOPCTL) PB0-> U1Rx PB1-> U1Tx pag.744
    GPIOB->PCTL = (GPIOB->PCTL&0xFFFFFF00) | 0x00000011;// (1<<0) | (1<<4);//0x00000011
    // GPIO Habilitar pin digital (GPIODEN) pag.743/781
    GPIOB->DEN = (1<<0) | (1<<1);//PB1 PB0
    //UART1 UART Control (UARTCTL) pag.1188 (deshabilitar)
    UART1->CTL = (0<<9) | (0<<8) | (0<<0);

    //CONFIGURACIÓN DEL PERIFERICO UART
    // Desabilita/Limpia los registros pag. 918
    UART1->CTL = (0<<9) | (0<<8) | (0<<0); //bit 9 es de Tx, bit 8 de Rx, y 0 al uart en genral. 

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*     velocidad  (estandar*baud Rate)
    BRD = 25,000,000 / (16 * 57600) = 27.1     Jorge(yo): 25MHZ Baud-rate 57600
    UARTFBRD[DIVFRAC] = integer(0.1 * 64 + 0.5) = 7
                                0.1 -> part. decimal*/
    UART1->IBRD = 27;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART1->FBRD = 7;  /* (parte fraccionaria del calculo) */
    //  UART Line Control (UARTLCRH) pag.916 bits
    UART1->LCRH = (0x3<<5); //Para que se tengan 8 bits, y |(1<<4); 
                            // Se activa el bit de paridad pero solo con el uart0
    //  UART Clock Configuration(UARTCC) pag.939
    UART1->CC =(0<<0); /*PARA USAR EL RELOJ INTERNO*/
    //Deshabilita UART1 UART Control (UARTCTL) pag.918
    UART1->CTL = (1<<0) | (1<<8) | (1<<9); //Habilitar los pines de recepción

}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;  //BANDERA
    char c;  
    while((UART1->FR & (1<<4)) != 0 ); //se mantiene en el ciclo cuando no llega un dato 
    v = UART1->DR & 0xFF; //DR - registro del dato y 0xff es la mascara 
    c = v; //convertir el entero a caracter
    return c; //solo regresa un caracter 
}
extern void printChar(char c) //mandar un caracter
{
    while((UART1->FR & (1<<5)) != 0 ); //pregunta si el dato 5 está desocupado, si lo está sigue con la linea de datos y transmite
    UART1->DR = c; 
}
/*extern void printString(char* string)  //para enviar cadena 
{
    while(*string) //string es la direccion de memoria para saber si está vacía o no, si está vacia se sale del ciclo
    {
        printChar(*(string++)); 
    }
}
extern char * readString(char delimitador) //para invertir 
{

   int i=0;
   char *string = (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       *(string+i) = c;
       i++;
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
   }
   return string;
}*/
//Imprimir cadena de caracteres
extern void printString(char* string, int tamano)
{
    int i = 0;
    while(string[i]>47)
    {
        printChar(string[i]);
        i++;
    }
}
extern int readString(char delimitador, char *string) //AQUI LEEMOS EL AREGLO NOMBRE Y CALCULAMOS CUANTOS ELEMTOS TIENE
{

   int i=0;
   char c = readChar();
   while(c != delimitador)
   {
       string[i] = c;
       i++;
       c = readChar();
   }
   return i;
}
//Experimento 2
//El envio es su nombre  (rave) 
// invertirlo y regresarlo con numeros consecutivos
// entre letras (e1v2a3r) 

extern void NomInvert(char *Name, int tamano)
{
int i = 1;
int a = 1;
int b = 0;
int paro = 0;
int Size;
Size = tamano;
// Se delimita el tamaño del array donde se guardara el nombre invertido con los números
if (tamano < 10)
    
        tamano = tamano + (tamano - 1);// Nombres cortos
    else
    {
        tamano = 18 + ((tamano - 9)*3);// Nombres largos
    }    
        char invertir[tamano];// Se crea vector con el tamaño del nombre
    
while(i < tamano) // El ciclo invierte el nombre y coloca los números entre las letras
{
if (paro == 0 )//Invierte el nombre
{
	invertir[b] = Name[Size-i];
	i = i + 1;
	b = b + 1;
    paro = 1;
}
else // Se colocan los números en el nombre a invertir
{
	paro = 0;
	invertir[b]= a +'0';
	a = a + 1;
	b = b + 1;
}
}
// Se reasigna el valor del array invert para mandarlo a llamar después
  for(int j=0; j<=(tamano-1); j++)
{
    Name[j]=invertir[j];
} 
  for(int n=tamano ;n <= 100;n++)/*Se rellena el vector*/
    Name[n] = 0;
return;

} 