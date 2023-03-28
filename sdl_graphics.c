#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "palette.h"

SDL_Surface		*WCimage 	= NULL;
SDL_Window		*window		= NULL;
SDL_Renderer	*renderer	= NULL;
SDL_Texture		*texture	= NULL;


#define		PALETTE_SIZE	256
int	r_palette[PALETTE_SIZE];
int g_palette[PALETTE_SIZE];
int b_palette[PALETTE_SIZE];
int rgb_palette[PALETTE_SIZE];


void initGraphicsSystem()
{
	if( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
		fprintf( stderr, "Could not initialize SDL.  Error: %s\n", SDL_GetError() );
		return;
	}

	if( (window = SDL_CreateWindow("Wing Commander Thingy", 100, 100, 640, 480, SDL_WINDOW_SHOWN)) == NULL ) {
		fprintf( stderr, "Could not create a SDL window.  Error:  %s", SDL_GetError() );
		return;
	}

	if( (renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL ) {
		fprintf( stderr, "Could not create a SDL renderer.  Error:  %s", SDL_GetError() );
		return;
	}

	loadWC1Palette();
}

void shutdownGraphicsSystem()
{
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}


/* All our pixels are 32 bits.  Always.
 *
 */
void setSDLpixel( int x, int y, int color )
{
	
    Uint8 * pixel = (Uint8*)WCimage->pixels;
    pixel += (y * WCimage->pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}

void loadWC1Palette()
{
	int i;

	for( i = 0; i < PALETTE_SIZE; i++ ) {
		r_palette[i]	= scaleVGAValue( wc1palette[ (i * 3) ] );
        g_palette[i]    = scaleVGAValue( wc1palette[ (i * 3) + 1 ] );
        b_palette[i]    = scaleVGAValue( wc1palette[ (i * 3) + 2 ] );
		rgb_palette[i]	= 0xFF000000 | (r_palette[i] << 16 ) | (g_palette[i] << 8) | b_palette[i];
	}
}

/*
 *
 */
int convertColorToPalette( int color )
{
	return rgb_palette[ color ];
}

/*
 *
 */
void showCurrrentImage()
{
	if( texture != NULL )
		SDL_DestroyTexture( texture );

	texture = SDL_CreateTextureFromSurface( renderer, WCimage );

	if( texture == NULL  ) {
        fprintf( stderr, "Could not initialize SDL texture.  Error: %s\n", SDL_GetError() );
		return;
	}
 
 SDL_RenderClear( renderer );
 SDL_RenderCopy( renderer, texture, NULL, NULL );
 SDL_RenderPresent( renderer );
}


void initializeNewImage()
{
	if( WCimage != NULL )
		SDL_FreeSurface( WCimage );

    if( (WCimage = SDL_CreateRGBSurface( NO_FLAGS, MAX_X, MAX_Y, THIRTY_TWO_BITS, NO_MASK, NO_MASK, NO_MASK, NO_MASK)) == NULL)  {
        fprintf( stderr, "Could not initialize SDL.  Error: %s\n", SDL_GetError() );
    }
}

/*
 * Scales the 6 bit VGA value to an 8 bit color value.
 */
int scaleVGAValue(int color)
{
	return (color * 256 / 64);  // or color * 4
}