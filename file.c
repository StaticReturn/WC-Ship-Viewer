#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "main.h"


void verifyInputFile( int argc, const char *argv[] )
{
    int  calculatedFileSize, reportedFileSize;
    
    if( argc < 2 ) {   // Check we have at least one argument...
        fprintf( stderr, "ERROR:: Specify a inputFile to load!\n" );
		printUsage();
        exit( 1 );
    }
    
    if( (inputFile=fopen( argv[1], "rb") ) == NULL ) {  // Check if they gave us a valid filename.
        fprintf( stderr, "ERROR:: Couldn't open file: \'%s\'\n", argv[1] );
        exit( 1 );
    }
    
    fseek( inputFile, 0, SEEK_SET );  // go to begining of file??
    
    calculatedFileSize = readFourBytes();
    reportedFileSize   = getFileSize( &argv[ 1 ] );
    
    if( calculatedFileSize != reportedFileSize ) {
        fprintf( stderr, "ERROR: This does not appear to be a valid Wing Commander ship file.  Aborting.\n" );
        exit( 1 );
    }
}



/* Convert the Wing Commander inputFile header to its proper 32bit value and return that.
 * WC files in written in big endian format and intel uses little endian.
 */
int  readFourBytes()
{
    unsigned int result, byteOne, byteTwo, byteThree, byteFour; // The header is 4 bytes long.
    
    byteFour   = fgetc( inputFile );
    byteThree  = fgetc( inputFile ) << 8;
    byteTwo    = fgetc( inputFile ) << 16;
    byteOne    = fgetc( inputFile ) << 24;
    
    result = byteOne | byteTwo | byteThree | byteFour;
    
    return result;
}


short	readTwoBytes()
{
    unsigned char byteOne, byteTwo;
    short value;
    
    byteTwo = fgetc( inputFile );
    byteOne = fgetc( inputFile );
    
    value = (byteOne << 8) | byteTwo;
    
    return value;
}

unsigned char readOneByte()
{
    return fgetc( inputFile );
}

int convertThreeBytes( unsigned char *buffer )
{
    unsigned int byteOne, byteTwo, byteThree;
    int result;
    
    byteThree = buffer[0];
    byteTwo   = buffer[1] << 8;
    byteOne   = buffer[2] << 16;
    
    result = byteOne | byteTwo | byteThree;
    
    return result;
}



/* Given a filename, return its inputFile size.
 */
int getFileSize( const char *filename[] )
{
    struct stat fileStatus;
    
    if( stat( *filename, &fileStatus ) != 0 ) {
        fprintf( stderr, "Can not determin the size of: %s\n", *filename );
        exit( 1 );
    }
    
    return fileStatus.st_size;
}