/****************************************************************************
* Title                 :   SPI Hardware Access Layer
* Filename              :   spi_hal.h
* Author                :   RBL
* Origin Date           :   28/08/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  23/08/15          .1         RL      Generic SPI Interface
*
*****************************************************************************/
/**
 *  
 *  @brief This represents a generic SPI read/write interface
 *  for multiple platforms
 *
 *  This implimentation assumes that all SPI bus hardware has been
 *  initialized outside of this module.
 *
 *  @date 28 Aug 2015
 *  @author Richard Lowe
 *  @copyright GNU Public License
 *
 *  @version .1 - Initial testing and verification
 *
 *  @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    7x10 R Click
 *   SW:              ARM 4.5.2
 *
 */
#ifndef S7X10R_HAL_H
#define S7X10R_HAL_H

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
 * @brief Hardware initialization
 *
 */
int s7x10r_hw_spi_init( void );

/**
 * @brief Reset SPI
 */
void s7x10r_hw_spi_reset( void );

/**
 * @brief hw_spi_hal_write
 *
 * @param buff - bytes to transfer to display
 */
void s7x10r_hw_spi_hal_write( uint8_t *buff );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/