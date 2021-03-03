/*
 * Project name:
     Mmc_Fat16_Test (Demonstration on usage of Mmc_Fat16 library)
 * Copyright:
     (c) MikroElektronika, 2010
  * Revision History:
      20080930:
        - initial release;
 * Description:
     This project consists of several blocks that demonstrate various aspects of
     usage of the Mmc_Fat16 library. These are:
     - Creation of new file and writing down to it;
     - Opening existing file and re-writing it (writing from start-of-file);
     - Opening existing file and appending data to it (writing from end-of-file);
     - Opening a file and reading data from it (sending it to USART terminal);
     - Creating and modifying several files at once;
     - Reading file contents;
     - Deleting file(s);
     - Creating the swap file (see Help for details);
 * Test configuration:
     MCU:             ATmega128
                      http://www.atmel.com/dyn/resources/prod_documents/doc2467.pdf
     Dev.Board:       BIGAVR6 - ac:MMC
                      http://www.mikroe.com/bigavr/
     Oscillator:      External clock, 08.00000 MHz
     Ext. Modules:    On-board MMC/SD module
     SW:              mikroC PRO for AVR
                      http://www.mikroe.com/mikroc/avr/
 * NOTES:
     - Make sure that MMC card is properly formatted (to FAT16 or just FAT)
       before testing it on this example.
     - Connect RS232 cable and turn on RS232A switches SW13.5 and SW13.6
     - Turn on MMC switches SW15.3, SW15.4, SW15.5, SW15.6 and SW15.7
     - This example expects MMC card to be inserted before reset, otherwise,
       the FAT_ERROR message is displayed.
 */

// MMC module connections
sbit Mmc_Chip_Select at PORTB4_bit;
sbit Mmc_Chip_Select_Direction at DDB4_bit;
// eof MMC module connections

const LINE_LEN = 43;
char err_txt[20]       = "FAT16 not found";
char file_contents[LINE_LEN] = "XX MMC/SD FAT16 library by Anton Rieckert\n";
char           filename[14] = "MIKRO00x.TXT";    // File names
unsigned short loop, loop2;
unsigned long  i, size;
char           Buffer[512];
char buff[512];
int channels;
int samplerate;
char * riff="RIFF";
char * wave = "WAVE";
char character;

  char *f="test2.wav";
char  dbuffer[512];
volatile int counter=0;
int sw=0;
int sizecount=1;
int lastsw;
void PrintHex(unsigned char i) {
  unsigned char hi,lo;

  hi = i & 0xF0;                           // High nibble
  hi = hi >> 4;
  hi = hi + '0';
  if (hi>'9') hi=hi+7;
  lo = (i & 0x0F) + '0';                   // Low nibble
  if (lo>'9') lo=lo+7;

  UART1_Write(hi);
  UART1_Write(lo);
}

void Timer1Overflow_ISR() org IVT_ADDR_TIMER1_COMPA {

PORTA=~PORTA;
Mmc_Fat_Read(&character);
PORTD=character;
PORTC=character;

}


// Main. Uncomment the function(s) to test the desired operation(s)
void main() {
SREG_I_bit=0;
  DDRA=0xFF;
  DDRD=0xFF;
  DDRC=0xff;

  //DDRB   = 0xFF;                // set PORTB as output

  PORTA=0;
                     // clear PORTB

                 // Interrupt enable
  //TOIE1_bit  = 1;               // Timer1 overflow interrupt enable


  // Initialize UART1 module
 // UART1_Init(9600);
  //Delay_ms(10);
  TCCR1A= 0;
  TCCR1B=10;
  TIMSK=0x10;
  OCR1AL=90;
  OCR1AH= 0 ;

  //UART1_Write_Line("MCU-Started");               // MCU present report

  // Initialize SPI1 module
  SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV128, _SPI_CLK_LO_LEADING);

  // use fat16 quick format instead of init routine if a formatting is needed
  Mmc_Fat_Init();
    // reinitialize spi at higher speed
    SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV2, _SPI_CLK_LO_LEADING);
    //--- Test start
   // UART1_Write_Line("Test Start.");
    //--- Test routines. Uncomment them one-by-one to test certain features
    //readfile

  Mmc_Fat_Assign(f, 0);
  Mmc_Fat_Reset(&size);                          // To read file, procedure returns size of file

  //Mmc_Fat_ReadN(dbuffer,256);

  for (i=0;i<78;i++){
  Mmc_Fat_Read(&character);
  }
  SREG_I_bit = 1;


    //readfile
  //  UART1_Write_Line("Test End.");
  }