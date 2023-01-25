#include "GameSound.h"

void GameSound::play(int index) 
{
	if (GSound[index].getStatus() == sf::SoundSource::Status::Stopped  && s_onoffsou) GSound[index].play();
}

void GameSound::stop(int index) 
{
	if (GSound[index].getStatus() == sf::SoundSource::Status::Playing) GSound[index].stop();
}

void GameSound::OnOffSound(bool onoffsou) 
{
	if (onoffsou) 
	{
		s_onoffsou = true;
		if (GSound[0].getStatus() == sf::SoundSource::Status::Stopped) GSound[0].play();
	}
	else 
	{
		s_onoffsou = false;
		for (int i = 0; i < 6; i++) if (GSound[i].getStatus() == sf::SoundSource::Status::Playing) GSound[i].stop();
	}
}

void GameSound::AllStop()
{
	for (int i = 0; i < 6; i++) if (GSound[i].getStatus() == sf::SoundSource::Status::Playing) GSound[i].stop();
}
