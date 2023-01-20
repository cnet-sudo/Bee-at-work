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
	}
	else 
	{
		s_onoffsou = false;
	}
}