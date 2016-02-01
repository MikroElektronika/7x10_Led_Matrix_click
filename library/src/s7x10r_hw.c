/*******************************************************************************
* Title                 :   Implimentation for 7x10 R Click
* Filename              :   s7x10r_hw.c
* Author                :   RBL
* Origin Date           :   05/11/2015
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  05/11/15            .1         RL          Created
*
*******************************************************************************/
/**
 * @file s7x10r_hw.c
 *
 * @brief
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <string.h>
#include <stdbool.h>
#include "s7x10r_hw.h"
#include "s7x10r_hal.h"
#include "7x5font.h"

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
static uint8_t frame[7][2];
static uint8_t text_frame[7][40];
static uint8_t text_length;

static bool scroll;
volatile uint16_t timer_tick;
static s7x10r_speed_t scroll_speed;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void shift_frame( void );

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void shift_frame()
{
    /*
    1. Shift right 1 from index 1
    2. Capture shifted bit from index 1
    3. Mask 0x40 from index 0 and or captured value
    4. Shift index 0 1
    */
    static uint16_t position = 0;
    static uint8_t character = 0;
    uint8_t carry;
    int row, col;
        
    for( row = 0; row < 7; row++ )
    {
        for( col = 1; col > -1; col-- )
        {
            frame[row][col] >>= 1;           // Pop the bit off
            
            if( col == 1 )
            {
                carry = frame[row][0];
                carry &= 0x01;
                carry <<= 4;
            }
            else
            {
                carry = text_frame[row][!( character % 2 ) ? character + 3 : character + 1 ];
                carry &= ( 1 << position );
                carry <<= ( 4 - position );
            }

            frame[row][col] |= carry;
        }
    }

    position++;

    if( position > 4 )
    {
        position = 0;
        character++;

        if( character > text_length )
        {
            for( row = 0; row < 7; row++ )
            {
                for( col = 0; col < 2; col++ )
                {
                    frame[row][col] = text_frame[row][col];
                }
            }
            character = 0;
        }
    }
}

void s7x10r_init()
{
    s7x10r_hw_spi_init();
}

void s7x10r_display()
{
    if( scroll )
    {
        switch( scroll_speed )
        {
        case S7X10R_SLOW:
            if( timer_tick > 7 )
            {
                shift_frame();
                timer_tick = 0;
            }
            break;
        case S7X10R_MED:
            if( timer_tick > 5 )
            {
                shift_frame();
                timer_tick = 0;
            }
            break;
        case S7X10R_FAST:
            if( timer_tick > 1 )
            {
                shift_frame();
                timer_tick = 0;
            }
            break;
        }

        s7x10r_hw_spi_hal_write( frame );
    } else {
        s7x10r_hw_spi_hal_write( frame );
    }
}

void s7x10r_clear_display()
{
    memset( frame, 0, sizeof( frame ) );
}

void s7x10r_draw_pix( uint8_t row, uint8_t col )
{
    if( row > 7 || col > 10 || row == 0 || col == 0 )
        return;

    if( col < 6 )
        frame[ row - 1 ][ 1 ] |= 0x01 << ( col - 1 );
    else
        frame[ row - 1 ][ 0 ] |= 0x01 << ( col - 6 );
}

void s7x10r_draw_txt( char* txt )
{
    char *ptr_txt = txt;
    uint8_t const *ptr_font = font;
    int i, j, char_count;
    text_length = strlen( txt );

    if( text_length > 40 )
        text_length = 40;

    memset( text_frame, 0, sizeof( text_frame ) );

    for( char_count = 0; char_count < text_length; char_count++ )
    {
        ptr_font = &font[ *( ptr_txt++ ) * 8 ];

        if( !( char_count % 2 ) ) {
            for( i = 0; i < 7; i++ )
                text_frame[i][ ( char_count + 1 ) ] = *( ptr_font++ );
        } else {
            for( i = 0; i < 7; i++ )
                text_frame[i][ ( char_count - 1 ) ] = *( ptr_font++ );
        }
    }

    for( i = 0; i < 7; i++ )
    {
        for( j = 0; j < 2; j++ )
        {
            frame[i][j] = text_frame[i][j];
        }
    }
}


void s7x10r_draw_num( uint8_t num )
{
    uint8_t const *ptr_font = font;
    int i;

    if( num > 99 )
        return;

    if( num < 10 )
    {
        ptr_font = &font[( num + 48 ) * 8 ];

        for( i = 0; i < 7; i++ )
            frame[i][0] = *( ptr_font++ );
    } else {
        int tmp_num = num / 10;
        ptr_font = &font[( tmp_num + 48 ) * 8 ];

        for( i = 0; i < 7; i++ )
            frame[i][1] = *( ptr_font++ );

        tmp_num = num % 10;
        ptr_font = &font[( tmp_num + 48 ) * 8 ];

        for( i = 0; i < 7; i++ )
            frame[i][0] = *( ptr_font++ );
    }
}

void s7x10r_scroll_enable( s7x10r_speed_t speed )
{
    scroll = true;
    scroll_speed = speed;
    timer_tick = 0;
}

void s7x10r_scroll_disable()
{
    scroll = false;
}

void s7x10r_tick()
{
    timer_tick++;
}

/*************** END OF FUNCTIONS ***************************************************************************/