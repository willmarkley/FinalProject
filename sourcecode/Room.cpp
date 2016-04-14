// Room Class Implementation File

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Room.h"
#include "Character.h"
#include "Timer.h"
using namespace std;

const int ROOM_WIDTH = 640;     // room width
const int ROOM_HEIGHT = 480;    // room height
const int ROOM_BPP = 32;        // room bits per pixel
const int WINDOW_WIDTH = 640;   // window width
const int WINDOW_HEIGHT = 480;  // window height
const int WINDOW_BPP = 32;      // window bits per pixel
const int FRAMES_PER_SECOND = 20;  // frame rate

Room::Room(string filename){    // constructor
	init();
	background = load_image(filename);
	apply_surface(0,0,background,window);
	update_screen();
	character=load_image("fi.bmp");
	play();
}

Room::~Room(){    // deconstructor
	SDL_FreeSurface(character);
	SDL_FreeSurface(background);
	SDL_FreeSurface(window);
	SDL_Quit();
}

void Room::play(){ 
    Timer fps;   // frame rate regulator								// NOT SURE IF WE NEED TIMER  (or any calls to fps)
	bool QUIT=false;

	while(!QUIT){
		fps.start();   // start the frame timer
		while( SDL_PollEvent( &event ) )   // execute while there is an event that needs to be handled
		{
		    player.handle_input( &event );         // handle the characters events

		    if( event.type == SDL_QUIT ){  // closed window
		        QUIT = true;
		    }
		}

		apply_surface(0,0,background,window);
		player.move();  // move player according to input
		apply_surface(player.getX(),player.getY(),character,window);
		update_screen();
		
// NOT SURE IF WE NEED this block		//Cap the frame rate
		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
        	SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
}


/*
	Graphics functions
*/


bool Room::init(){           // initilizes SDL
 	// initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    // set up the screen
    window = SDL_SetVideoMode( ROOM_WIDTH, ROOM_HEIGHT, ROOM_BPP, SDL_SWSURFACE );

    // if there was an error in setting up the window
    if( window == NULL )
    {
        return false;
    }

    // set the window caption
    SDL_WM_SetCaption( "GAME", NULL );

    // successful initilization
    return true;
}


SDL_Surface* Room::load_image(string filename){  // loads image to surface
	//The temporary storage for loaded image
	SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}


void Room::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination){
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, NULL, destination, &offset );
}


bool Room::update_screen(){
	if( SDL_Flip( window ) == -1 )
	{
		return false;
	}

	return true;
}

