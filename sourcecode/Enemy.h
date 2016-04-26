// Enemy Derived Class Header File

#include "Character.h"
using namespace std;

#ifndef ENEMY_H
#define ENEMY_H

class Enemy: public Character {
	
	public:
		Enemy(int=100, int=100);	                              // constructor
		void move(Character player, Character e2, Character e3);  // moves the enemy while checking for collisions
		// void enemyShoot(); not used
		SDL_Rect incomingBullet;

	private:
		int random;
		int ranCounter;
};

#endif
