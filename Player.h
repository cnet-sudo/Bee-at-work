#pragma once
#include"Animator.h"
#include "HealthBarClass.h"
#include "GameSound.h"
class Player
{
    sf::RenderWindow & window;   // ссылка на графическое окно
	GameSound & gsound;
	sf::Time BeeTime;          // Общее время
	sf::Sprite BeeSprite;
	Animator BeeAnim = Animator(BeeSprite);  // Анимация пчелы

	bool returnBee = false;   // Возрождение пчелы
	float stepx = 0.0f;       // Перемещение пчелы по х
	float stepy = 0.0f;       // Перемещение пчелы по y
	bool diedBee = false;     // Жизнь пчелы 
	bool mead = false;       // Наполнение корзинки мёдом

	sf::RectangleShape beemead = sf::RectangleShape(sf::Vector2f(50, 50));         // Ведро с мёдом
	
	// Анимация брызг
	sf::Sprite Splash;
	Animator SplashAnim = Animator(Splash);
	
	
public:

	explicit Player(sf::RenderWindow& mywindow, GameSound& mygsound): window(mywindow),gsound(mygsound)
	{
		BeeSprite.setOrigin(50, 50);
		BeeSprite.setPosition(90, 365);
		// Анимация капли  
		auto spriteSize = sf::Vector2i(100, 100);
		auto SplashSize = sf::Vector2i(100, 50);
		auto& idleSplash = SplashAnim.CreateAnimation("idleSplash", "image/maker.png", sf::seconds(1), false);
		idleSplash.AddFrames(sf::Vector2i(0, 0), SplashSize, 6, 1);
		// Анимация пчелы
		auto& idleForward = BeeAnim.CreateAnimation("idleForward", "image/SPRITESHEET.png", sf::seconds(1), true);
		idleForward.AddFrames(sf::Vector2i(0, 0), spriteSize, 6, 1);
		auto& idleBack = BeeAnim.CreateAnimation("idleBack", "image/SPRITESHEET.png", sf::seconds(1), true);
		idleBack.AddFrames(sf::Vector2i(0, 100), spriteSize, 6, 1);
		beemead.setTexture(&AssetManager::GetTexture("image/mead.png"));
	}

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void startDied(float x, float y);
	void setStepx(float x);
	void setStepy(float y);
	void setdiedBee(bool diedVarible);
	void setmead( bool meadVarible);
	void setreturnBee(bool ret);
	void update(sf::Time const& deltaTime);
	void draw();

	bool getMead() const 
	{
		return mead;
	}
	 
	bool getdiedBee() const
	{
		return diedBee;
	}

	bool getreturnBee() const
	{
		return returnBee;
	}
	
	
	sf::Sprite& getBee() 
	{
		return BeeSprite;
	}
};

