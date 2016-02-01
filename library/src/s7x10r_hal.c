/*******************************************************************************
* Title                 :   Hardware Layer
* Filename              :   s7x10r_hal.c
* Author                :   RBL
* Origin Date           :   10/11/2015
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  10/11/15         .1              RBL     Module Created.
*
*******************************************************************************/
/**
 * @file s7x10r_hal.c
 *
 * @brief 7 x 10 LED Matrix hardware layer
 *
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "s7x10r_hal.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/


/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
#if defined( __MIKROC_PRO_FOR_ARM__ )
#if defined( STM32F107VC ) || defined( STM32F407VG ) || \
    defined( STM32F030C6 ) || defined( STM32F746VG )
static void ( *spi_write_p )( unsigned int data_out );

#elif defined( LM3S1165 ) || defined( TM4C129ENCZAD )
static void ( *spi_write_p )( unsigned int data_out );
#endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )
static void( *spi_write_p )( unsigned char data_out );

#elif defined( __MIKROC_PRO_FOR_PIC__ )
static void ( *spi_write_p )( unsigned char data_out );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void ( *spi_write_p )( unsigned long data_out );

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )
static void ( *spi_write_p )( unsigned int data_out );

#elif defined( __MIKROC_PRO_FOR_8051__ )

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static void( *spi_write_p )( unsigned char dataOut );
#elif defined ( __GNUC__ )

#define spi_write_p

#endif

#if defined(__MIKROC_PRO_FOR_ARM__)   || \
    defined(__MIKROC_PRO_FOR_AVR__)   || \
    defined(__MIKROC_PRO_FOR_8051__)  || \
    defined(__MIKROC_PRO_FOR_FT90x__)  || \
    defined(__MIKROC_PRO_FOR_DSPIC__) || \
    defined(__MIKROC_PRO_FOR_PIC32__) || \
    defined(__MIKROC_PRO_FOR_PIC__)
// Pin Definitions
extern sfr sbit SxT_CS;
extern sfr sbit SxT_RST;
extern sfr sbit SxT_ROW_RST;
extern sfr sbit SxT_ROW_CLK;

// SPI bus variables
static spi_write_t _hal_spi_write;

#elif defined(__GNUC__)
extern uint8_t bits;
extern uint32_t speed;
extern uint16_t delay;
extern char *spi_file_descriptor;

#endif

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void latch( void );
static void row_reset( void );
static void row_clock( void );
static void hal_reset( void );

#if defined( __GNUC__ )
static void transfer( int fd, uint8_t const * tx,
                      uint8_t const *rx, size_t len );
const char *byte_to_binary( int x );
#endif
/******************************************************************************
* Function Definitions
*******************************************************************************/
static void latch()
{
#if __GNUC__

#else
    SxT_CS = 0;
    asm { nop };
    asm { nop };
    asm { nop };
    SxT_CS = 1;
    #if defined (__MIKROC_PRO_FOR_8051__ )
    Delay_500us();
    Delay_500us();
    #else
    Delay_1ms();
    #endif
#endif
}

static void row_reset()
{
#if __GNUC__

#else
    SxT_ROW_RST = 1;
    Delay_1us();
    SxT_ROW_RST = 0;
#endif
}

static void row_clock()
{
#if __GNUC__

#else
    SxT_ROW_CLK = 1;
    Delay_1us();
    SxT_ROW_CLK = 0;
#endif
}

static void hal_reset()
{
#if __GNUC__

#else
    SxT_RST = 0;
    asm { nop };
    asm { nop };
    asm { nop };
    SxT_RST = 1;
#endif
}

/********************************
 *******Implimentations**********
 *******************************/
int s7x10r_hw_spi_init()
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_PIC__ )   || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
        spi_write_p = SPI_Wr_Ptr;
#elif defined( __MIKROC_PRO_FOR_FT90x__ )
        spi_write_p = SPIM_Wr_Ptr;
#endif
    if( spi_write_p == 0 )
        return -1;

    hal_reset();

    return 0;
}

void s7x10r_hw_spi_reset()
{
    hal_reset();
}

void s7x10r_hw_spi_hal_write( uint8_t *buff )
{
#if defined( __GNUC__ )
       
#else
    uint8_t *ptr = buff;
    int i;

    hal_reset();
    row_reset();

    for( i = 0; i < 7; i++ )
    {
        spi_write_p( *( ptr++ ) );
        spi_write_p( *( ptr++ ) );
        latch();
        row_clock();
    }

#endif
    return;
}

/*************** END OF FUNCTIONS ***************************************************************************/