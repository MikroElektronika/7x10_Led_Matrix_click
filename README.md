![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# 7x10_R Click

- **CIC Prefix**  : C7X10R
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : Jan 2018.

---

### Software Support

We provide a library for the 7x10_R Click on our [LibStock](https://libstock.mikroe.com/projects/view/1582/7x10-r-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library carries all functions necessary for complete control over the 7x10 R click. 
There is also an additional font header file which carries 5x7 letter definitions.

Key functions :

- ``` void c7x10r_drawPixel( uint8_t row, uint8_t col ) ``` - Draws a pixel
- ``` void c7x10r_drawText( char *txt ) ``` - Write Text
- ``` void c7x10r_drawNumber( uint8_t num ) ``` - Draws numbers

**Examples Description**

The application is composed of three sections :

- System Initialization - GPIO and SPI bus initialization
- Application Initialization - Driver initialization
- Application Task - (code snippet)
  1. Text scrolling
  2. Counts from 0 to 10
  3. Displays random pixels


```.c
void applicationTask()
{
    uint8_t i;
    uint8_t j;
    uint8_t endOp;

// SCROLL PROCEDURE
    endOp = 1;
    c7x10r_drawText( &mikroe_txt[0] );
    c7x10r_scrollEnable( _C7X10R_SPEED_MED );
    while (0 != endOp)
    {
        endOp = c7x10r_refreshDisplay();
        c7x10r_tick();
        Delay_ms( 1 );

    }
    c7x10r_scrollDisable();
    c7x10r_clearDisplay();

// COUNTER PROCEDURE
    for (i = 0; i < 11; i++)
    {
        c7x10r_clearDisplay();
        c7x10r_drawNumber( i );

        for (j = 0; j < 30; ++j)
        {
            c7x10r_refreshDisplay();
            Delay_ms( 1 );
        }
    }
    c7x10r_clearDisplay();

// PIXELS PROCEDURE
    c7x10r_drawPixel( 2, 3 );
    c7x10r_drawPixel( 2, 8 );
    c7x10r_drawPixel( 6, 3 );
    c7x10r_drawPixel( 6, 8 );
    for (i = 0; i < 255; i++)
    {
        c7x10r_refreshDisplay();
        Delay_ms( 1 );
    }
    c7x10r_clearDisplay();
}
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1582/7x10-r-click) page.

Other mikroE Libraries used in the example:

- SPI

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
