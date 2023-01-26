#include "lib/include.h"

int main(void)
{
    // uint16_t valor = 0;
    char c='5';
    int tamano = 100;
    char Name[tamano];
    Configurar_PLL(_25MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART1();//Yo FCLK 25MHZ Baudrate 57600

    //Experimento 1
    //  Configurar_UART1(); //Jorge,Alberto,Navarro,Saul,Fabela -fclk 25MHZ Baud-rate 57600
    //  Configurar_UART7(); //Angel,Fernanda,Sonia,Aleidis,Monse -fclk 50MHZ Baud-rate 57600
    //  Configurar_UART4(); //Argelia,Roxana,Yesica,Vanesa,Christian,Abiu -fclk 10MHZ Baud-rate 4800
    //  Configurar_UART2(); //Brizet,Monse,Luis,Majo,Alonso -fclk 40MHZ Baud-rate 115200
    //  Configurar_UART3(); //Jesus,Yesica,Carlos,Dulce,Rodolfo,Leonardo -fclk 80MHZ Baud-rate 19200
    //  Configurar_UART2(); //Andrea,Avila,Pamela,Paulina -fclk 50MHZ Baud-rate 57600
    //  Configurar_UART5(); //Hector,Cecilia,Carolina,Jozzafat -fclk 40MHZ Baud-rate 28800
    Configurar_GPIO();
   // Homogeneidad();
    //printString("Holis Bolis");
    //printChar(c); 
    //printChar(b);
    //printString("\n");  //Para enviar salto de linea 
   // char *arr = readString(',');
   // printString(&arr[0]);
    while(1)
    {
         c = readChar();
         switch(c)
         {
             case 'r':
                 //GPIODATA port F 662
                 printChar('a');
                 GPIOF->DATA = (1<<1); // Prende led rojo
                 break;
             case 'b':
                 //GPIODATA port F 662
                 printChar('b');
                 GPIOF->DATA = (1<<2); // Prende led azul
                 break;
             case 'g':
                 //GPIODATA port F 662
                 printChar('c');
                 GPIOF->DATA = (1<<3);// Prende led verde
                 break;
           case 'F':
                 GPIOF->DATA = (1<<1) | (1<<2); // Prende de color moradito
                 tamano = readString('.',&Name[0]);// Mide el tamaño del string
                 NomInvert(&Name[0], tamano);//Invierte y añade los números
                 printString(&Name[0], tamano);// Imprime el string
                 break;

         }
    }

}
