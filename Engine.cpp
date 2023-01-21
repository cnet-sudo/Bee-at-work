#include "Engine.h"

void Engine::input()
{
    sf::Event event_play;

    while (window.pollEvent(event_play))
    {
        switch (event_play.type)
        {
        case sf::Event::KeyPressed:
            if (event_play.key.code == sf::Keyboard::Escape) {
                GamеMenu();
            }
            if (event_play.key.code == sf::Keyboard::Right) {
                if (BeeSprite.getPosition().x < 1100) stepx = 5.0f;
                if (!direction) {  BeeAnim.SwitchAnimation("idleForward"); direction = true;
                }
            }
            if (event_play.key.code == sf::Keyboard::Left)
            {
                if (BeeSprite.getPosition().x > 50)stepx = -5.0f;
                if (direction) {
                    BeeAnim.SwitchAnimation("idleBack"); direction = false;
                }
            }

            if (event_play.key.code == sf::Keyboard::Up) {
                if (BeeSprite.getPosition().y > 100) stepy = -5.0f;
            }
            if (event_play.key.code == sf::Keyboard::Down)
            {
                if (BeeSprite.getPosition().y < 620) stepy = 5.0f;
            }
            break;
        case sf::Event::KeyReleased:
            if (event_play.key.code == sf::Keyboard::Right) {
                stepx = 0.0f;

            }
            if (event_play.key.code == sf::Keyboard::Left)
            {
                stepx = 0.0f;

            }

            if (event_play.key.code == sf::Keyboard::Up) {
                stepy = 0.0f;
            }
            if (event_play.key.code == sf::Keyboard::Down)
            {
                stepy = 0.0f;

            }
            break;
        default:
            break;
        }
    }

}

void Engine::update(sf::Time const& deltaTime)
{
    gsound.play(0);
    
    if (diedBee) SplashAnim.Update(deltaTime);

    if (BeeSprite.getGlobalBounds().intersects(flowers.getGlobalBounds()) && !mead)
    {
        barFlow.changeOfbar(1, deltaTime);
        if (barFlow.getFull()) { mead = true; barFlow.reset(); }
    }
    if (!BeeSprite.getGlobalBounds().intersects(flowers.getGlobalBounds()) && barFlow.getSizeBar() != 0) barFlow.reset();

    if (mead && BeeSprite.getGlobalBounds().intersects(beehive.getGlobalBounds()))
    {
        if (barBeehive2.getFull())
        {
            mead = false;
            gsound.stop(3);
            barBeehive2.reset();
            barBeehive.changeOfbar(10);
            if (barBeehive.getFull())
            {
                gsound.stop(0);
                gsound.stop(1);
                if (GamеEndMenu( L"Вы выиграли !!!", sf::Color::Magenta))
                {
                    barBeehive.reset();
                    diedBee = false;
                    BeeSprite.setPosition(90, 365);
                    gsound.play(0);
                }
                else window.close();
            }
        }
        else { barBeehive2.changeOfbar(1, deltaTime); gsound.play(3); }
    }


    BeeTime += deltaTime;
    if (BeeTime > sf::milliseconds(20))
    {
        BeeTime = sf::milliseconds(0);

        if (!diedBee) BeeSprite.move(stepx, stepy);
        else
        {
            if (SplashAnim.getEndAnim()) {
                BeeSprite.setRotation(90);
                BeeSprite.move(0, 7);
                gsound.play(4);
                if (BeeSprite.getPosition().y > 720) {
                    gsound.stop(4);
                    if (barBeehive.getSizeBar() == 0)
                    {
                        gsound.stop(0);
                        if (GamеEndMenu(L"Вы проиграли !!!", sf::Color::Red))
                        {
                            gsound.play(0);
                            barBeehive.reset();
                            diedBee = false;
                            BeeSprite.setPosition(90, 365);
                        }
                        else window.close();
                    }
                    BeeSprite.setPosition(90, 365);
                    diedBee = false;
                    BeeSprite.setRotation(0);
                    BeeAnim.SwitchAnimation("idleForward");
                }
            }
        }
        for (size_t i = 0; i < size(blob); i++)
        {
            blob[i].move(0, 3);
            if (blob[i].getPosition().y > 720) resedBlob(i);
            
            if (blob[i].getGlobalBounds().intersects(BeeSprite.getGlobalBounds()) && !diedBee)
            {
                gsound.play(5);
                Splash.setPosition(blob[i].getPosition().x, blob[i].getPosition().y);
                SplashAnim.restart();
                resedBlob(i);
                diedBee = true; mead = false;
                if (barBeehive.getSizeBar() >= 10) barBeehive.changeOfbar(-10);
            }
        }

    }


    if (!diedBee) {
        BeeAnim.Update(deltaTime);
        if (BeeSprite.getPosition().x < 50) { BeeSprite.setPosition(50, BeeSprite.getPosition().y); }
        if (BeeSprite.getPosition().x > 1100) { BeeSprite.setPosition(1100, BeeSprite.getPosition().y); }
        if (BeeSprite.getPosition().y < 100) { BeeSprite.setPosition(BeeSprite.getPosition().x, 100); }
        if (BeeSprite.getPosition().y > 620) { BeeSprite.setPosition(BeeSprite.getPosition().x, 620); }
    }

    beemead.setPosition(BeeSprite.getPosition().x - 20, BeeSprite.getPosition().y + 40);

}

void Engine::draw()
{
    window.clear();
    window.draw(background_play);
    window.draw(flowers);
    window.draw(beehive);

    if (!mead && BeeSprite.getGlobalBounds().intersects(flowers.getGlobalBounds())) barFlow.draw();

    if (BeeSprite.getGlobalBounds().intersects(flowers.getGlobalBounds()))
    {
        gsound.play(2);
    }
    else
    {
        gsound.stop(2);
    }
    if (BeeSprite.getGlobalBounds().intersects(beehive.getGlobalBounds()))
    {
        gsound.play(1);
        barBeehive.draw();
        barBeehive2.draw();
    }
    else
    {
        gsound.stop(1);
    }

    window.draw(BeeSprite);

    if (mead)  window.draw(beemead);

    for (size_t i = 0; i < size(blob); i++)
    {
        window.draw(blob[i]);
    }

    if (diedBee) window.draw(Splash);


    window.display();
}

void Engine::GamеMenu()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), L"Пчела на работе", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    std::vector<sf::String> name_menu{ { L"Игра",L"Настройки", L"Правила",L"Выход" } };
    // Объект меню
    game::GameMenu mymenu(window, 950, 250, 80, 100, name_menu);
    // Установка цвета отображения меню
    mymenu.setColorTextMenu(sf::Color(227, 171, 0), sf::Color::Yellow, sf::Color::Black);
    mymenu.AlignMenu(2);

    sf::RectangleShape background(sf::Vector2f(1280, 720));
    sf::Texture texture_window;
    if (!texture_window.loadFromFile("image/bee1.jpg")) std::cout << "No image is here";
    background.setTexture(&texture_window);

    sf::Text Titul;
    sf::Font font;
    if (!font.loadFromFile("font/troika.otf"))
    {
        std::cout << "No font is here";
    }
    Titul.setFont(font);
    game::TextFormat FText;
    FText.menu_text_color = sf::Color(227, 171, 0);
    InitText(Titul, 270, 5, L"Пчела на работе", FText);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); break; }
                if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:  window.close(); return; break;
                    case 1:Options(); break;
                    case 2:About_Game(); break;
                    case 3:exit(0); break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }

}

void Engine::Options()
{
    sf::RenderWindow Options(sf::VideoMode(1280, 720), L"Настройки", sf::Style::Fullscreen);

    sf::RectangleShape background_opt(sf::Vector2f(1280, 720));
    sf::Texture texture_opt;
    if (!texture_opt.loadFromFile("image/menu1.jpg")) std::cout << "No image is here";

    background_opt.setTexture(&texture_opt);
    while (Options.isOpen())
    {
        sf::Event event_opt;
        while (Options.pollEvent(event_opt))
        {
            if (event_opt.type == sf::Event::Closed) Options.close();
            if (event_opt.type == sf::Event::KeyPressed)
            {
                if (event_opt.key.code == sf::Keyboard::Escape) Options.close();
            }
        }
        Options.clear();
        Options.draw(background_opt);
        Options.display();
    }

}

void Engine::About_Game()
{
    sf::RenderWindow About(sf::VideoMode(1280, 720), L"О игре", sf::Style::Fullscreen);

    sf::RectangleShape background_ab(sf::Vector2f(1280, 720));
    sf::Texture texture_ab;
    if (!texture_ab.loadFromFile("image/menu2.jpg")) std::cout << "No image is here";

    background_ab.setTexture(&texture_ab);

    while (About.isOpen())
    {
        sf::Event event_play;
        while (About.pollEvent(event_play))
        {
            if (event_play.type == sf::Event::Closed) About.close();
            if (event_play.type == sf::Event::KeyPressed)
            {
                if (event_play.key.code == sf::Keyboard::Escape) About.close();
            }
        }
        About.clear();
        About.draw(background_ab);
        About.display();
    }
}

bool Engine::GamеEndMenu(sf::String str, sf::Color col)
{
    std::vector<sf::String> name_menu{ { L"Рестарт",L"Выход"} };

    // Объект меню
    game::GameMenu mymenu(window, window.getSize().x / 2, 300, 45, 90, name_menu);
    // Установка цвета отображения меню
    mymenu.setColorTextMenu(sf::Color(227, 171, 0), sf::Color::Yellow, sf::Color::Black);
    mymenu.AlignMenu(2);

    sf::Text Titul;
    sf::Font font;

    if (!font.loadFromFile("font/troika.otf"))
    {
        std::cout << "No font is here";
    }
    Titul.setFont(font);
    game::TextFormat FText;
    FText.size_font = 60;
    FText.menu_text_color = col;
    InitText(Titul, 400, 200, str, FText);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); break; }
                if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:  return true; break;
                    case 1:  return false; break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }
        window.clear();
        window.draw(background_play);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
}


void Engine::run()
{
    GamеMenu();  // стартовое меню
    // Анимация капли    
    auto& idleSplash = SplashAnim.CreateAnimation("idleSplash", "image/maker.png", sf::seconds(1), false);
    idleSplash.AddFrames(sf::Vector2i(0, 0), SplashSize, 6, 1);
    // Анимация пчелы
    auto& idleForward = BeeAnim.CreateAnimation("idleForward", "image/SPRITESHEET.png", sf::seconds(1), true);
    idleForward.AddFrames(sf::Vector2i(0, 0), spriteSize, 6, 1);
    auto& idleBack = BeeAnim.CreateAnimation("idleBack", "image/SPRITESHEET.png", sf::seconds(1), true);
    idleBack.AddFrames(sf::Vector2i(0, 100), spriteSize, 6, 1);

    sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		
        input();
        update(dt);
        draw();
	}
}

void Engine::resedBlob(int index)
{
    std::uniform_int_distribution RndPosBlobX(350, 900);
    std::uniform_int_distribution RndPosBlobY(0, 1000);
    std::uniform_int_distribution RndPosBlobSize(1, 3);
    float blodSize;

    blob[index].setTexture(&blobTextur);
    blodSize = static_cast<float>(RndPosBlobSize(rnd));
    blob[index].setSize(sf::Vector2f(10.0f * blodSize, 20.0f * blodSize));
    blob[index].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd) * -1));

}
