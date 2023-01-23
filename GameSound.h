#pragma once
#include<array>
#include<SFML/Audio.hpp>
#include "AssetManager.h"

class GameSound
{
	std::array<sf::Sound, 6> GSound; 	
	bool s_onoffsou=true;
public:
	
	bool getOnOffSound() const
	{
		return s_onoffsou;
	}

	GameSound()
	{
		std::array<std::string, 6> namefilebuf{ "sound/d.wav" ,"sound/u.wav","sound/s.wav","sound/z.wav","sound/svs.wav","sound/sh.wav" };
		
		for (int i = 0; i < 6; i++) {
		GSound[i].setBuffer(AssetManager::GetSoundBuffer(namefilebuf[i]));
		if (i < 3) GSound[i].setLoop(true);
		}
	};

	void play(int index);
	void stop(int index);
	void OnOffSound(bool onoffsou);
};

