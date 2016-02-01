/****************************************************************************
* Title                 :   7x10 R Click
* Filename              :   s7x10r_hw.h
* Author                :   RL
* Origin Date           :   05/11/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  05/11/15         .1           RL           Created without scrolling
*
*****************************************************************************/
/**
 * @file s7x10r_hw.h
 * @brief Library for 7x10 Red Led Matrix
 *
 * @mainpage
 * @section Intro
 * 7x10 R click carries a matrix of 70 red LEDs driven by a pair of 8-bit serial-in, 
 * parallel-out shift registers, a Darlington Transistor array and a Johnson counter. 
 * The click communicates with the target MCU through the mikroBUS™ SPI interface 
 * (SCK, SDO, SDI), with additional functionality provided by R CLK, MR#, LATCH and 
 * R RST pins. 7x10 R click is designed to use either a 3.3V or a 5V power supply.
 * 
 * @section Essential Features
 * 7x5 is a standard resolution for displaying ASCII characters, so 7x10 click is 
 * essentially a dual-character display capable of showing letters in more readable 
 * typefaces compared to a 14-segment display. The dot matrix can also show scrolling 
 * text, thus fitting longer messages in small space. 
 * 
 * The pair of 8-bit serial-in, 
 * parallel-out shift registers drive the display. The current amplification necessary 
 * for driving the LEDs is performed by a Darlington Transistor array while a Johnson 
 * counter performs the necessary LED multiplex.
 * 
 * @section Manual
 * 7x10 R click features an SMD jumper (zero ohm resistor) that let’s you switch  
 * between a 3.3V or a 5V power supply.
 *
 * @section Application
 * Applications
 *
 * 7x5 dot matrix text display for user interfaces, for example on vending machines. 
 *
 *
 * Key features
 * - A pair of red 7x5 LED matrices
 * - SPI interface (plus MR#, LATCH and R RST pins)
 * - 3.3V or 5V power supply
 *
 * Key benefits
 * - Displays letters in highly readable format
 * - Scrolling text capability
 * - Ready-to-use examples save development time
 * - Supported in all MikroElektronika compilers
 *
 * @section Details
 * @ref example
 *
 * @date 5 Nov 2015
 * @author Richard Lowe
 * @copyright GNU Public License
 *
 * @version .1 - Initial testing and verification
 *
 * @note Test configuration:
 *  MCU:             STM32F107VC
 *  Dev.Board:       EasyMx Pro v7
 *  Oscillator:      72 Mhz internal
 *  Ext. Modules:    7x10 R Click
 *  SW:              ARM 4.5.2
 *
 */
#ifndef S7X10R_HW_H_
#define S7X10R_HW_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * @enum Speeds of scroll
 */
typedef enum
{
    S7X10R_SLOW,  /**< Scroll columns at 1 per second */
    S7X10R_MED,   /**< Scroll columns at 2 per second */
    S7X10R_FAST   /**< Scroll columns at 3 per second */
} s7x10r_speed_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the display
 *
 * @note SPI bus must be initialized before calling.
 *
 * @code
 * ...
 * SPI_Init();
 * s7x10r_init();
 * @endcode
 */
void s7x10r_init( void );

/**
 * @brief Refeshes display
 *
 * @note Needs to be called as frequently as possible.
 *
 * @code
 * while( 1 )
 * {
 *     s7x10r_display();
 * }
 * @endcode
 */
void s7x10r_display( void );

/**
 * @brief Clears display
 */
void s7x10r_clear_display( void );

/**
 * @brief Draws a pixel at specified x, y location
 * @param row - x
 * @param col - y
 * @code
 * s7x10r_draw_pix( 1, 3 ); // Lights pixel on row 1 column 3
 * @endcode
 * @note min x value is 1 max is 7, min y value is 1 max is 10
 */
void s7x10r_draw_pix( uint8_t row, uint8_t col );

/**
 * @brief Write Text on the display
 * @param txt 
 */
void s7x10r_draw_txt( char *txt );

/**
 * @brief Draws numbers on the display
 * @param num - max number is 99
 */
void s7x10r_draw_num( uint8_t num );

/**
 * @brief Enable scrolling feature
 * @param speed
 * @val S7X10R_SLOW
 * @val S7X10R_MED
 * @val S7X10R_FAST
 */
void s7x10r_scroll_enable( s7x10r_speed_t speed );

/**
 * @brief Disables scrolling
 */
void s7x10r_scroll_disable( void );

/**
 * @brief Tick called in ISR
 *
 * This function is used on the scrolling feature.  It is to be called
 * from the interrupt and does not need to be called is scrolling is not
 * needed.
 */
void s7x10r_tick( void );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/

/**  
 * @page example Example
 * 
 *  
 * @section Code Example 
 * @code
#include <stdint.h>
#include "s7x10r_hw.h"

sbit SxT_CS at GPIOD_ODR.B13;
sbit SxT_RST at GPIOC_ODR.B2;
sbit SxT_ROW_RST at GPIOA_ODR.B0;
sbit SxT_ROW_CLK at GPIOA_ODR.B4;

enum
{
    TEST_STAGE1,
    TEST_STAGE2,
    TEST_STAGE3,
    TEST_STAGE4
};

void system_init( void );
void test1_pixels( void );
void test2_text( void );
void test3_scrolling( void );
void test4_numbers( void );
void init_timer2( void );

//Timer2 Prescaler :599; Preload = 62499; Actual Interrupt Time = 100 ms
void init_timer2()
{
    RCC_APB1ENR.TIM2EN = 1;
    TIM2_CR1.CEN = 0;
    TIM2_PSC = 239;
    TIM2_ARR = 62499;
    NVIC_IntEnable(IVT_INT_TIM2);
    TIM2_DIER.UIE = 1;
    TIM2_CR1.CEN = 1;
}

void system_init()
{
    GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_13);   // Set CS pin as output
    GPIO_Digital_Output(&GPIOC_ODR, _GPIO_PINMASK_2);    // Set RST pin as output
    GPIO_Digital_Output(&GPIOA_ODR, _GPIO_PINMASK_0);    // Set PWM pin as output
    GPIO_Digital_Output(&GPIOA_ODR, _GPIO_PINMASK_4);    // Set PWM pin as output

    // Initialize SPI
    SPI3_Init_Advanced( _SPI_FPCLK_DIV16, _SPI_MASTER | _SPI_8_BIT |
                        _SPI_CLK_IDLE_LOW | _SPI_FIRST_CLK_EDGE_TRANSITION |
                        _SPI_MSB_FIRST | _SPI_SS_DISABLE | _SPI_SSM_ENABLE |
                        _SPI_SSI_1, &_GPIO_MODULE_SPI3_PC10_11_12);

    s7x10r_init();
    init_timer2();
    EnableInterrupts();
}

void test1_pixels()
{
    static uint8_t x = 1, y = 0;
    s7x10r_clear_display();

    if( y++ > 10 )
    {
        y = 1;
        x++;
    }

    if( x >= 8 )
        x = 1;

    s7x10r_draw_pix( x, y );
}

void test2_text()
{
    s7x10r_draw_txt( "MikroElektronika" );
}

void test3_scrolling()
{
    s7x10r_draw_txt( "MikroElektronika" );
    s7x10r_scroll_enable( S7X10R_MED );
}

void test4_numbers()
{
    static uint8_t num;

    s7x10r_clear_display();
    s7x10r_draw_num( num );
    num++;

    if( num > 99 )
        num = 0;
}

void main()
{
    uint16_t counter = 0;
    uint16_t test_counter = 0;
    uint16_t stage = TEST_STAGE1;
    uint8_t called = 0;

    system_init();
    s7x10r_clear_display();

    while( 1 )
    {
        if( !( counter % 20 ) )
        {
            if( test_counter >= 100 )
            {
                stage++;
                s7x10r_scroll_disable();

                if( stage > TEST_STAGE4 )
                {
                    stage = TEST_STAGE1;
                    called = 0;
                }

                test_counter = 0;
            }

            switch( stage )
            {
            case TEST_STAGE1:
                test1_pixels();
                break;
            case TEST_STAGE2:
                test2_text();
                break;
            case TEST_STAGE3:
                if( !called )
                {
                    test3_scrolling();
                    called = 1;
                }
                break;
            case TEST_STAGE4:
                test4_numbers();
                break;
            }

            test_counter++;
        }

        s7x10r_display();
        counter++;
    }
}

void Timer2_interrupt() iv IVT_INT_TIM2
{
    TIM2_SR.UIF = 0;
    s7x10r_tick();
}
 * @endcode
 */