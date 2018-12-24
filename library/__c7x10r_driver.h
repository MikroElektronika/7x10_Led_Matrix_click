/*
    __c7x10r_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __c7x10r_driver.h
@brief    7x10_R Driver
@mainpage 7x10_R Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   C7X10R
@brief      7x10_R Click Driver
@{

| Global Library Prefix | **C7X10R** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jan 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"
#include "stdbool.h"
#ifndef _C7X10R_H_
#define _C7X10R_H_

/** 
 * @macro T_C7X10R_P
 * @brief Driver Abstract type 
 */
#define T_C7X10R_P    const uint8_t*

/** @defgroup C7X10R_COMPILE Compilation Config */              /** @{ */

   #define   __C7X10R_DRV_SPI__                            /**<     @macro __C7X10R_DRV_SPI__  @brief SPI driver selector */
//  #define   __C7X10R_DRV_I2C__                            /**<     @macro __C7X10R_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __C7X10R_DRV_UART__                           /**<     @macro __C7X10R_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup C7X10R_VAR Variables */                           /** @{ */

extern const uint8_t _C7X10R_SPEED_SLOW;
extern const uint8_t _C7X10R_SPEED_MED;
extern const uint8_t _C7X10R_SPEED_FAST;

                                                                       /** @} */
/** @defgroup C7X10R_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup C7X10R_INIT Driver Initialization */              /** @{ */

#ifdef   __C7X10R_DRV_SPI__
void c7x10r_spiDriverInit(T_C7X10R_P gpioObj, T_C7X10R_P spiObj);
#endif
#ifdef   __C7X10R_DRV_I2C__
void c7x10r_i2cDriverInit(T_C7X10R_P gpioObj, T_C7X10R_P i2cObj, uint8_t slave);
#endif
#ifdef   __C7X10R_DRV_UART__
void c7x10r_uartDriverInit(T_C7X10R_P gpioObj, T_C7X10R_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void c7x10r_gpioDriverInit(T_C7X10R_P gpioObj);
                                                                       /** @} */
/** @defgroup C7X10R_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Refresh display
 *
 * Draws content of frame buffer.
 *
 * @note 
 * Needs to be called as frequently as possible.
 */
bool c7x10r_refreshDisplay( void );

/**
 * @brief Clear display
 *
 * Clears content of frame buffer.
 */
void c7x10r_clearDisplay( void );

/**
 * @brief Draws a pixel
 *
 * Pixel provided will be placed inside frame buffer.
 *
 * @param[in] row   matrix row
 * @param[in] col   matrix column
 *
 * @note 
 * Minimum row value is 1 Maximum is 7
 * Minimum col value is 1 Maximum is 10
 */
void c7x10r_drawPixel( uint8_t row, uint8_t col );

/**
 * @brief Write Text
 *
 * Text will be placed inside internal text buffer, but first two 
 * characters are automaticly placen inside frame buffer.
 *
 * @param[in] txt    text to be written
 */
void c7x10r_drawText( char *txt );

/**
 * @brief Draws numbers
 *
 * Provided numbers are converted and placed inside frame buffer.
 *
 * @param[in] num    number to draw
 */
void c7x10r_drawNumber( uint8_t num );

/**
 * @brief Enable scrolling feature
 *
 * This operation requires calling of ```c7x10y_tick``` function after each 
 * scroll step or from interrupt routine.
 *
 * @param[in] speed    scrolling speed 
 *
 * @note Scrolling speed depends of provided speed and already defined constants
 * should be used as argument. Also scroll speed depends of ```c7x10y_tick``` calling
 * frequency.
 */
void c7x10r_scrollEnable( uint8_t speed );

/**
 * @brief Disables scrolling
 */
void c7x10r_scrollDisable( void );

/**
 * @brief Tick called to control scrolling speed
 *
 * This function is used on the scrolling feature.  It is to be called
 * after starting the scroll and around each display refresh. It does not
 * need to be called if scrolling is not needed.
 */
void c7x10r_tick( void );





                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_7x10_R_STM.c
    @example Click_7x10_R_TIVA.c
    @example Click_7x10_R_CEC.c
    @example Click_7x10_R_KINETIS.c
    @example Click_7x10_R_MSP.c
    @example Click_7x10_R_PIC.c
    @example Click_7x10_R_PIC32.c
    @example Click_7x10_R_DSPIC.c
    @example Click_7x10_R_AVR.c
    @example Click_7x10_R_FT90x.c
    @example Click_7x10_R_STM.mbas
    @example Click_7x10_R_TIVA.mbas
    @example Click_7x10_R_CEC.mbas
    @example Click_7x10_R_KINETIS.mbas
    @example Click_7x10_R_MSP.mbas
    @example Click_7x10_R_PIC.mbas
    @example Click_7x10_R_PIC32.mbas
    @example Click_7x10_R_DSPIC.mbas
    @example Click_7x10_R_AVR.mbas
    @example Click_7x10_R_FT90x.mbas
    @example Click_7x10_R_STM.mpas
    @example Click_7x10_R_TIVA.mpas
    @example Click_7x10_R_CEC.mpas
    @example Click_7x10_R_KINETIS.mpas
    @example Click_7x10_R_MSP.mpas
    @example Click_7x10_R_PIC.mpas
    @example Click_7x10_R_PIC32.mpas
    @example Click_7x10_R_DSPIC.mpas
    @example Click_7x10_R_AVR.mpas
    @example Click_7x10_R_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __c7x10r_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */