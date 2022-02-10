#include <SDL/SDL.h>
#include <stdbool.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Window* game_window = NULL;
	
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* mario = NULL;

SDL_Surface* mario_jump = NULL;

SDL_Surface* cactus = NULL;

SDL_Rect cactus_position;
void cactus_pos_init(void)
{
	cactus_position.x = SCREEN_WIDTH/2 - 60 + 60; 
	cactus_position.y = SCREEN_HEIGHT/2 - 60 - 0; 
	cactus_position.w = SCREEN_WIDTH;
	cactus_position.h = SCREEN_HEIGHT;
}

SDL_Rect mario_position;

void mario_pos_init(void)
{
	mario_position.x = SCREEN_WIDTH/2 - 60; 
	mario_position.y = SCREEN_HEIGHT/2 - 60; 
	mario_position.w = SCREEN_WIDTH;
	mario_position.h = SCREEN_HEIGHT;
}

void clear_screen(void)
{
	SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF) );
}

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		game_window = SDL_CreateWindow( "Camel Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( game_window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface( game_window );
			clear_screen();
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	mario = SDL_LoadBMP( "mario.bmp" );
	cactus = SDL_LoadBMP( "cactus.bmp" );
	mario_jump = SDL_LoadBMP( "mario_jump.bmp" );
	
	if( mario == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "mario.bmp", SDL_GetError() );
		success = false;
	}

	if( cactus == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "cactus.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	SDL_FreeSurface( mario );
	mario = NULL;
	
	SDL_FreeSurface( cactus );
	cactus = NULL;

	SDL_DestroyWindow( game_window );
	game_window = NULL;

	SDL_Quit();
}

void jump_once(void)
{
	clear_screen();
	SDL_BlitSurface( mario_jump, NULL, gScreenSurface, &mario_position );
	SDL_BlitSurface( cactus, NULL, gScreenSurface, &cactus_position );
	SDL_UpdateWindowSurface( game_window );
}

int main( int argc, char* args[] )
{
	SDL_Event event;
        int quit = 0;
	int i;
        
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}

	if( !loadMedia() )
	{
		printf( "Failed to load media!\n" );
	}

	SDL_BlitSurface( cactus, NULL, gScreenSurface, NULL );
	cactus_pos_init();

	SDL_BlitSurface( mario_jump, NULL, gScreenSurface, NULL );
        
	while( !quit )
	{
		SDL_BlitSurface( mario, NULL, gScreenSurface, NULL );
		
		clear_screen();
		mario_pos_init();
		
		SDL_BlitSurface( mario, NULL, gScreenSurface, &mario_position );
		SDL_BlitSurface( cactus, NULL, gScreenSurface, &cactus_position );
		
		
		SDL_UpdateWindowSurface( game_window );

            if( SDL_PollEvent( &event ) )
	    {
                
                switch( event.type )
		{
                    case SDL_KEYDOWN:
			for(i = 0; i < 160; i++)
			{			
				mario_position.y -= 1;
	    			cactus_position.x = (cactus_position.x - 1);
	    			if (cactus_position.x <= 30)
					cactus_position.x = 600;
				jump_once();
				SDL_Delay(1);
			}
			for(i = 0; i < 160; i++)
			{			
				mario_position.y += 1;
	    			cactus_position.x = (cactus_position.x - 1);
	    			if (cactus_position.x <= 30)
					cactus_position.x = 600;
				jump_once();
				SDL_Delay(1);
			}
                        break;

                    case SDL_QUIT:
                        quit = 1;
                        break;
                }

            }
	    cactus_position.x = (cactus_position.x - 1);
	    if (cactus_position.x <= 30)
		cactus_position.x = 600;
	    clear_screen();

	    SDL_BlitSurface( mario, NULL, gScreenSurface, &mario_position );
	    SDL_BlitSurface( cactus, NULL, gScreenSurface, &cactus_position );
	    SDL_UpdateWindowSurface( game_window );
	    SDL_Delay(1);
		
		

        }

        /* Clean up */
        SDL_Quit();
        exit( 0 );

}
