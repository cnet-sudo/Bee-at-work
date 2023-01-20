#pragma once
#include<array>
#include<SFML/Audio.hpp>

class GameSound
{
	std::array<std::string, 6> namefilebuf{ "sound/d.wav" ,"sound/u.wav","sound/s.wav","sound/z.wav",
		"sound/svs.wav","sound/sh.wav" };
	std::array<sf::SoundBuffer, 6> buffer;
	std::array<sf::Sound, 6> GSound; 	
	bool s_onoffsou=true;
public:
	
	GameSound()
	{
		for (int i = 0; i < 6; i++) {
		if (!buffer[i].loadFromFile(namefilebuf[i])) exit(166);
		GSound[i].setBuffer(buffer[i]);
		if (i < 3) GSound[i].setLoop(true);
		}
	};

	void play(int index);
	void stop(int index);
	void OnOffSound(bool onoffsou);
};

