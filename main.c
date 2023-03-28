/*
 *	WC Ship Viewer by Gora Bernal
 *
 *	Based on the source code and documentation of:
 *		Mario "HCl" Brito <mbrito@student.dei.uc.pt>
 *		Maciek "Matrix" Korzeniowski <matrix3d@polbox.com>
 *		AKAImBatman
 *		delMar
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main( int argc, const char *argv[] ) {
    int i, j, flag, numberOfImages;
    long dataIndex, offset;
	unsigned char fileType, buffer[BUFFER_LENGTH] = {0,0,0,0};
    
    verifyInputFile( argc, argv );
	initGraphicsSystem();    

    fseek( inputFile, 4, SEEK_SET );  // Skip the first 4 bytes, which is the header of the file.

	fileType = readOneByte();

    if( fileType == MAGIC_NUMBER ) {
        fseek( inputFile, 20, SEEK_SET );
        flag = TRUE;
    } else {
        fseek( inputFile, 4, SEEK_SET );
        flag = FALSE;
    }
    
	numberOfImages = getNumberOfImages( fileType, argv[1] ); 

    for( i = 0; i < numberOfImages; i++ ) {

		for( j = 0; j < BUFFER_LENGTH - 1; j++ )
			buffer[j] = readOneByte();

		offset = (ftell(inputFile)) + 1;

        if( flag == FALSE )
            dataIndex = convertThreeBytes( buffer ) + 8;
        else
            dataIndex = convertThreeBytes( buffer ) + 16;
     
        showShip( dataIndex ); // Put the ship onto the screen.
        getch();  //Press Any Key To Continue
		fseek( inputFile, offset, SEEK_SET );
    }
    
    exit( 0 );
}


void	printUsage()
{
	fprintf( stderr, "Wing Commander Ship Viewer.  Version: %s\n", VERSION );
	fprintf( stderr, "Usage: wc <filename>\n\n" );
}