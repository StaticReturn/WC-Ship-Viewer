#include <stdio.h>
#include "main.h"


void showShip( long dataIndex )
{
    int x1, x2, y1, y2, key, vx, vy, x, y, a, b, i, carry;
    unsigned char buffer, buffer2;
    
    fseek( inputFile, dataIndex, SEEK_SET );
    
    x2 = readTwoBytes();
    x1 = readTwoBytes();
    y1 = readTwoBytes();
    y2 = readTwoBytes();
    
    initializeNewImage();
    
    
    while (1) //Cycle will put image on screen...
    {
        key		= readTwoBytes();
        carry	= key % 2;
        vx 		= readTwoBytes();
        vy		= readTwoBytes();
        
        if( key == 0 ) break;   // If we reached the end of image, lets end the routine
        
        x = x1;     // Let's not forget that 0 is also a position
        y = y1;
        x += vx;
        y += vy;
        a = 0;
        
        if( carry == 0 ) {
            for( a = 0; a < (key / 2); a++ ) {
                buffer = readOneByte();
                setOnePixel( x, y, buffer );
                x++;
            }
        }
        else {
            b = 0;
            while( b < (key / 2) ) {
                buffer = readOneByte();
                
                if( (buffer % 2) == 0 ) {
                    for( a = 0; a < (buffer / 2); a++ ) {
                        buffer2 = readOneByte();
                        setOnePixel( x, y, buffer2 );
                        b++;
                        x++;
                    }
                }
                else {
                    buffer2 = readOneByte();
                    
                    for( i = 0; i < (buffer / 2); i++ ) {
                        setOnePixel( x , y, buffer2 );
                        b++;
                        x++;
                    }
                }
            }
        }
    }
    
    showCurrrentImage();
}




int	getNumberOfImages( int fileType, const char *filename )
{
    return (fileType == PC_SHIP_FILE) ? IMGS_IN_PCS_FILE : IMGS_IN_MOST_FILES;
}