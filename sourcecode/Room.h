// Room Base Class Header File

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Character.h"
using namespace std;

#ifndef ROOM_H
#define ROOM_H

class Room{

	public:
		Room(string="");     // constructor
		~Room();    // deconstructor

	private:
		Room* left = NULL;   // points to room at the left
		Room* right = NULL;  // points to room at the right
		Room* up = NULL;     // points to room above
		SDL_Surface *background = NULL;   // background image
		SDL_Surface *window = NULL;       // window
		SDL_Surface *character = NULL;  // character surface
		SDL_Event event;      // the event structure (to handle key presses)
		Character player;    // main player
		void play();         // plays the game

		bool init();           // initilizes SDL
		SDL_Surface *load_image(string filename);  // loads image to surface
		void apply_surface( int, int, SDL_Surface*, SDL_Surface*);  // applies image to surface
		bool update_screen();   // updates screen
};

#endif
