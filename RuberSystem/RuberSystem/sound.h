#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <windows.h>

using namespace std;

class sound {
public:
	static void play_shooting() {
		PlaySound(TEXT("sound_fire.wav"), NULL, SND_ASYNC);
	}
	
	static void play_explosion() {
		PlaySound(TEXT("sound_explosion.wav"), NULL, SND_ASYNC);
	}

	static void play_spaceship_moving() {
		// PlaySound(TEXT("sound_spaceship_moving.wav"), NULL, SND_ASYNC);
	}

	static void play_in_space() {
		PlaySound(TEXT("sound_space.wav"), NULL, SND_LOOP | SND_ASYNC);
	}

	static void play_sound_missile_shooting() {
		PlaySound(TEXT("sound_missile.wav"), NULL, SND_ASYNC);
	}

	static void play_background() {
		PlaySound(TEXT("sound_background.wav"), NULL, SND_ASYNC);
	}
};

#endif