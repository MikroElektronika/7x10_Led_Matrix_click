#include "Click_7x10_R_types.h"


const uint32_t _C7X10R_SPI_CFG[ 3 ] = 
{ 
        _SPI_MASTER_CLK_RATIO_2,
        _SPI_CFG_POLARITY_IDLE_HIGH |
        _SPI_CFG_PHASE_CAPTURE_RISING | 
        _SPI_CFG_SS_AUTO_DISABLE | 
        _SPI_CFG_FIFO_DISABLE, 
        _SPI_SS_LINE_NONE 
};
