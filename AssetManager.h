#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<map>


class AssetManager
{
public:
	AssetManager();

	static sf::Texture& GetTexture(std::string const& filename);
	static sf::SoundBuffer& GetSoundBuffer(std::string const&filename);
	static sf::Font& GetFont(std::string const& filename);

private:

	std::map<std::string, sf::Texture> m_Textures;
	std::map<std::string, sf::SoundBuffer> m_SoundBuffer;
	std::map<std::string, sf::Font> m_Fonts;
	// AssetManager является одноэлементным, поэтому одновременно можно работать с одним элементом
	//sInstacne содержит статический указатель на единственный экземпляр диспетчера
	static AssetManager* sInstance;
};

#endif