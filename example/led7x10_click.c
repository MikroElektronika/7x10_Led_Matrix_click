/*******************************************************************************
* Title                 :   7x10R click Example
* Filename              :   led7x10_click.c
* Author                :   RBL
* Origin Date           :   10/11/2015
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description 
*  10/11/16         .1              RBL      Module Created.
*
*******************************************************************************/
/** 
 * @file led7x10_click.c
 * @brief Example of multiplexed 7 x 10 led matrix control 
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "s7x10r_hw.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
enum
{
    TEST_STAGE1,
    TEST_STAGE2,
    TEST_STAGE3,
    TEST_STAGE4
};

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit SxT_CS at GPIOD_ODR.B13;
sbit SxT_RST at GPIOC_ODR.B2;
sbit SxT_ROW_RST at GPIOA_ODR.B0;
sbit SxT_ROW_CLK at GPIOA_ODR.B4;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void system_init( void );
void test1_pixels( void );
void test2_text( void );
void test3_scrolling( void );
void test4_numbers( void );
void init_timer2( void );

/******************************************************************************
* Function Definitions
*******************************************************************************/
//Timer2 Prescaler :599; Preload = 62499; Actual Interrupt Time = 50 ms
void init_timer2()
{
    RCC_APB1ENR.TIM2EN = 1;
    TIM2_CR1.CEN = 0;
    TIM2_PSC = 19;
    TIM2_ARR = 59999;
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
    s7x10r_draw_txt( "  Mikro Elektronika  . Happy" );
    s7x10r_scroll_enable( S7X10R_FAST );
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
    int stage = TEST_STAGE1;
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

void timer2_interrupt() iv IVT_INT_TIM2
{
    TIM2_SR.UIF = 0;
    s7x10r_tick();
}

/*************** END OF FUNCTIONS ***************************************************************************/

