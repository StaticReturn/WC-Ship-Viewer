#include <stdio.h>
#include "main.h"


void setOnePixel( int x, int y, int color )
{   
    setSDLpixel( x, y, convertColorToPalette( color ) );
}