#pragma once

#include"GameMenu.h"
#include"Animator.h"
#include "HealthBarClass.h"
#include "GameSound.h"
#include<chrono>
#include<random>

class Engine
{
	// ���� ��������� �����
	long long null_number = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rnd= std::default_random_engine(static_cast<unsigned int>(null_number));
		
	sf::RenderWindow window;   // ������� ����������� ����
	GameSound gsound;          // �������� �������
	AssetManager manager;      // �������� ��������
	
	sf::Time BeeTime;          // ����� �����
    // ������ �����
	sf::Vector2i spriteSize= sf::Vector2i(100, 100);
	sf::Sprite BeeSprite;      
	Animator BeeAnim= Animator(BeeSprite);  // �������� �����


	bool direction = true;    // ����������� ����� �����
	float stepx = 0.0f;       // ����������� ����� �� �
	float stepy = 0.0f;       // ����������� ����� �� y
	bool diedBee = false;     // ����� ����� 
	bool mead = false;       // ���������� �������� ����

	sf::CircleShape flowers; // ������ ����� �������
	HealthBarClass barFlow = HealthBarClass(window, 1150, 330, true);        // ����� �������
	sf::CircleShape beehive= sf::CircleShape(30);
	HealthBarClass barBeehive= HealthBarClass(window, 250, 430, true, 30);        // ���������� ��� � ����
	HealthBarClass barBeehive2= HealthBarClass(window, 240, 430, true, 0.0f, 10); // ���� ���
	sf::RectangleShape beemead= sf::RectangleShape(sf::Vector2f(50, 50));         // ����� � ����
	sf::Texture beemeadtexture;
	sf::RectangleShape background_play= sf::RectangleShape(sf::Vector2f(1280, 720)); // ��� ����
	sf::Texture backgroundgame;
	
	sf::Texture blobTextur; // ����� �����
	std::array<sf::RectangleShape, 20> blob;

	// �������� �����
	sf::Vector2i SplashSize= sf::Vector2i(100, 50);
	sf::Sprite Splash;
	Animator SplashAnim= Animator(Splash);

	void resedBlob(int index);

	void input();
	void update(sf::Time const& deltaTime);
	void draw();

	void Gam�Menu();
	void Options();
	void About_Game();
	bool Gam�EndMenu(sf::String str, sf::Color col);
public:
	Engine()
	{
		BeeSprite.setOrigin(50, 50);
		BeeSprite.setPosition(90, 365);
		window.create(sf::VideoMode(1280, 720), L"����� �� ������", sf::Style::Fullscreen);
		window.setMouseCursorVisible(false);
		flowers.setRadius(50);
		flowers.setPosition(1050, 230);
		flowers.setFillColor(sf::Color(255, 255, 255, 0));
		barFlow.setColorBar(sf::Color(0, 189, 0), sf::Color(158, 63, 25), 3);
		beehive.setPosition(50, 340);
		beehive.setFillColor(sf::Color(255, 255, 255, 0));
		barBeehive.setColorBar(sf::Color(216, 212, 0), sf::Color(189, 116, 0), 3);
		barBeehive2.setColorBar(sf::Color(0, 189, 0), sf::Color(189, 116, 0), 3);
		beemeadtexture.loadFromFile("image/mead.png");
		beemead.setTexture(&beemeadtexture);
		backgroundgame.loadFromFile("image/background.jpg");
		background_play.setTexture(&backgroundgame);
		blobTextur.loadFromFile("image/blob.png");
		for (size_t i = 0; i < size(blob); i++) resedBlob(i);
		Splash.setOrigin(50, -20);
}

	void run();

};

