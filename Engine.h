#pragma once
#include "AssetManager.h"
#include"GameMenu.h"
#include"Animator.h"
#include "HealthBarClass.h"
#include "GameSound.h"
#include<chrono>
#include<random>
#include <memory>

class Engine
{
	AssetManager manager;      // �������� ��������
	// ���� ��������� �����
	long long null_number = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rnd= std::default_random_engine(static_cast<unsigned int>(null_number));
	
	std::unique_ptr<sf::RenderWindow> window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), L"����� �� ������", sf::Style::Fullscreen);
	
	GameSound gsound;          // �������� �������
	sf::Time BeeTime;          // ����� �����
    // ������ �����
	sf::Sprite BeeSprite;      
	Animator BeeAnim = Animator(BeeSprite);  // �������� �����
	
	int language = 0;          // ����
	bool direction = true;    // ����������� ����� �����
	float stepx = 0.0f;       // ����������� ����� �� �
	float stepy = 0.0f;       // ����������� ����� �� y
	bool diedBee = false;     // ����� ����� 
	bool mead = false;       // ���������� �������� ����

	sf::CircleShape flowers; // ������ ����� �������
	HealthBarClass barFlow = HealthBarClass(*window, 1150, 330, true);        // ����� �������
	sf::CircleShape beehive= sf::CircleShape(30);
	HealthBarClass barBeehive= HealthBarClass(*window, 250, 430, true, 30);        // ���������� ��� � ����
	HealthBarClass barBeehive2= HealthBarClass(*window, 238, 430, true, 0.0f, 10.0f); // ���� ���
	HealthBarClass barTime = HealthBarClass(*window, 25, 680, false, 100,30.0f,3);    // ����� �� ���� �������
	sf::RectangleShape beemead= sf::RectangleShape(sf::Vector2f(50, 50));         // ����� � ����
	
	sf::RectangleShape background_play= sf::RectangleShape(sf::Vector2f(1280, 720)); // ��� ����
		
	std::array<sf::RectangleShape, 20> blob;

	// �������� �����
	sf::Sprite Splash;
	Animator SplashAnim= Animator(Splash);

	void resetBlob(size_t index);
	void resetGame();

	void input();
	void update(sf::Time const& deltaTime);
	void draw();

	void Gam�Menu();
	void Options();
	void About_Game();
	bool Gam�EndMenu(sf::String str, sf::Color col);
	void Lost();
public:
	Engine()
	{
		BeeSprite.setOrigin(50, 50);
		BeeSprite.setPosition(90, 365);
		this->window->setMouseCursorVisible(false);
		flowers.setRadius(50);
		flowers.setPosition(1050, 230);
		flowers.setFillColor(sf::Color(255, 255, 255, 0));
		barFlow.setColorBar(sf::Color(0, 189, 0), sf::Color(158, 63, 25), 3);
		barTime.setColorBar(sf::Color(0, 189, 0), sf::Color(158, 63, 25), 3);
		beehive.setPosition(50, 340);
		beehive.setFillColor(sf::Color(255, 255, 255, 0));
		barBeehive.setColorBar(sf::Color(216, 212, 0), sf::Color(189, 116, 0), 3);
		barBeehive2.setColorBar(sf::Color(0, 189, 0), sf::Color(189, 116, 0), 3);
		beemead.setTexture(&AssetManager::GetTexture("image/mead.png"));
		background_play.setTexture(&AssetManager::GetTexture("image/background.jpg"));
		for (size_t i = 0; i < size(blob); i++) resetBlob(i);
		Splash.setOrigin(50, -20);
}

	
	void run();

};

