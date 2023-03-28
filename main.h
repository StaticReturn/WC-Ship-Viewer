#ifndef _MAIN_H_
#define _MAIN_H_

#define	VERSION				"0.1"


// Global Variables
#define TRUE				1
#define	FALSE				0


#define BUFFER_LENGTH   	4
#define IMGS_IN_MOST_FILES 	37		// 37 images in a SHIP_FILE and SHIP_TYPE_FILE
#define	IMGS_IN_PCS_FILE	4		// 4 images in a PC_SHIP_FILE
#define SHIP_FILE			0x9C	// Capital Ships
#define	PC_SHIP_FILE		0x2C	// Cockpits
#define	SHIP_TYPE_FILE		0x10	// Fighters
#define	MAGIC_NUMBER		0x10
#define MAX_X				320
#define MAX_Y				200
#define	THIRTY_TWO_BITS		32
#define NO_MASK				0
#define NO_FLAGS			0		


FILE			*inputFile;
struct	pixel	*image[MAX_X][MAX_Y];

// Function Prototypes
void			showShip( long dataIndex );
void			verifyInputFile( int argc, const char *argv[] );
void			setOnePixel( int x, int y, int color );
int				getFileSize( const char *filename[] );
short			readTwoBytes();
int				readFourBytes();
unsigned char	readOneByte();
int				convertThreeBytes( unsigned char *buffer );
int				getNumberOfImages( int fileType, const char *filename );
void			printUsage();

void			initGraphicsSystem();
void			setSDLpixel( int x, int y, int color );
void			loadWC1Palette();
int				scaleVGAValue( int color );
int				convertColorToPalette( int color );
void			initializeNewImage();
void			showCurrrentImage();

#endif	/* _MAIN_H_ */