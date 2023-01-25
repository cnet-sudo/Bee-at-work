#include "Engine.h"

void Engine::input() 
{
    sf::Event event_play;

    while (window->pollEvent(event_play))
    {
        switch (event_play.type)
        {
        case sf::Event::KeyPressed:
            if (event_play.key.code == sf::Keyboard::Escape) {
                window->setActive(false); Gam�Menu();
            }
            if (event_play.key.code == sf::Keyboard::Right) {
                Bee->MoveRight();
               
            }
            if (event_play.key.code == sf::Keyboard::Left)
            {
                Bee->MoveLeft();
               
            }

            if (event_play.key.code == sf::Keyboard::Up) {
                Bee->MoveUp();
              
            }
            if (event_play.key.code == sf::Keyboard::Down)
            {
                Bee->MoveDown();
               
            }
            break;
        case sf::Event::KeyReleased:
            if (event_play.key.code == sf::Keyboard::Right) {
               
                Bee->setStepx(0);
            }
            if (event_play.key.code == sf::Keyboard::Left)
            {
                
                Bee->setStepx(0);
            }

            if (event_play.key.code == sf::Keyboard::Up) {
               
                Bee->setStepy(0);
            }
            if (event_play.key.code == sf::Keyboard::Down)
            {
                
                Bee->setStepy(0);
            }
            break;
        default:
            break;
        }
    }

}

void Engine::update(sf::Time const& deltaTime)
{
    auto SPBee = Bee->getBee();  // ������ �� ������ �����

    barTime.changeOfbar(-0.005, deltaTime);  // ����� ����
    
    auto sizeBarTime = barTime.getSizeBar();
    if (sizeBarTime <25 && barTime.getColorHelth() != sf::Color::Red) barTime.setColorBar(sf::Color::Red, sf::Color(158, 63, 25), 3);
    if (sizeBarTime <50 && sizeBarTime > 40 && barTime.getColorHelth()!= sf::Color::Yellow) barTime.setColorBar(sf::Color::Yellow, sf::Color(158, 63, 25), 3);
    
    if (barTime.getEmpty()) Lost(); 

    gsound->play(0); // ��� �����
    

    if (SPBee.getGlobalBounds().intersects(flowers.getGlobalBounds()) && !Bee->getMead())
    {
        barFlow.changeOfbar(1, deltaTime);
        if (barFlow.getFull()) { Bee->setmead(true); barFlow.reset(); }
    }

    if (!SPBee.getGlobalBounds().intersects(flowers.getGlobalBounds()) && barFlow.getSizeBar() != 0) barFlow.reset();
    if (!SPBee.getGlobalBounds().intersects(beehive.getGlobalBounds()) && barBeehive2.getSizeBar() != 0) gsound->stop(3);

    if (Bee->getMead() && SPBee.getGlobalBounds().intersects(beehive.getGlobalBounds()))
    {
        if (barBeehive2.getFull())
        {
            Bee->setmead(false);
            gsound->stop(3);
            barBeehive2.reset();
            barBeehive.changeOfbar(10);
            if (barBeehive.getFull())
            {
                gsound->stop(0);
                gsound->stop(1);
                
                if (Gam�EndMenu(strgameEnd[0][language], sf::Color::Magenta))
                {
                    resetGame();
                    gsound->play(0);
                }
                else window->close();
            }
        }
        else { barBeehive2.changeOfbar(1, deltaTime); gsound->play(3); }
    }

    Bee->update(deltaTime);
    
    BeeTime += deltaTime;

    if (BeeTime > sf::milliseconds(20))
    {
        BeeTime = sf::milliseconds(0);

        if (Bee->getreturnBee()) { if (barBeehive.getSizeBar() == 0) Lost(); Bee->setreturnBee(false); }
                
          
    for (size_t i = 0; i < size(blob); i++)
    {
        blob[i].move(0, speedBlob[i]);
        if (blob[i].getPosition().y > 720) resetBlob(i);
        if (!Bee->getdiedBee()) {
        if (blob[i].getGlobalBounds().intersects(SPBee.getGlobalBounds()))
        {
            gsound->play(5);
            Bee->startDied(blob[i].getPosition().x, blob[i].getPosition().y);
            Bee->setdiedBee(true);
            Bee->setmead(false);
            barBeehive2.reset();
            resetBlob(i);
            if (barBeehive.getSizeBar() >= 10) barBeehive.changeOfbar(-10);
        }
        }
     }
      }
 }


void Engine::draw()
{
    auto SPBee = Bee->getBee();
    window->clear();
    window->draw(background_play);
    window->draw(flowers);
    window->draw(beehive);

    if (!Bee->getMead() && SPBee.getGlobalBounds().intersects(flowers.getGlobalBounds())) barFlow.draw();

    if (SPBee.getGlobalBounds().intersects(flowers.getGlobalBounds()))
    {
        gsound->play(2);
    }
    else
    {
        gsound->stop(2);
    }
    if (SPBee.getGlobalBounds().intersects(beehive.getGlobalBounds()))
    {
        gsound->play(1);
        barBeehive.draw();
        barBeehive2.draw();
    }
    else
    {
        gsound->stop(1);
    }

    Bee->draw();

   

    for (size_t i = 0; i < size(blob); i++)
    {
        window->draw(blob[i]);
    }

   

    barTime.draw();
    window->display();
}

void Engine::Gam�Menu()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), L"����� �� ������", sf::Style::Fullscreen);
    window.requestFocus();
    window.setActive(true);
    window.setMouseCursorVisible(false);

    std::vector<std::vector<sf::String>>name_menu{ { L"����",L"���������", L"�������",L"�����" },
        { L"���",L"������������", L"�������",L"�����" },{ L"Game",L"Settings", L"Rules",L"Exit" } };
    std::array<sf::String, 3> str{ L"����� �� ������",L"������ �� �����", L"Bee at work" };
    bool switch_language = false; // ����� �����
    // ������ ����
    game::GameMenu mymenu(window, 950, 250, 80, 100, name_menu[language]);
    // ��������� ����� ����������� ����

    mymenu.setColorTextMenu(sf::Color(227, 171, 0), sf::Color::Yellow, sf::Color::Black);
    mymenu.AlignMenu(2);

    sf::RectangleShape background(sf::Vector2f(1280, 720));
        
    background.setTexture(& AssetManager::GetTexture("image/bee1.jpg"));

    sf::Text Titul;
    Titul.setFont(AssetManager::GetFont("font/troika.otf"));
    game::TextFormat FText;
    FText.menu_text_color = sf::Color(227, 171, 0);
    InitText(Titul, 640 - (Titul.getLocalBounds().width / 2), 5, str[language], FText);
    Titul.setString(str[language]);
    Titul.setPosition(640 - (Titul.getLocalBounds().width / 2), 5);
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
                    case 1:Options(); switch_language = true; break;
                    case 2:About_Game(); break;
                    case 3:exit(0); break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }
        if (switch_language) {
           
                for (int i = 0; i < 4; i++) mymenu.setNameMenu(name_menu[language][i], i);
                mymenu.AlignMenu(2);
                Titul.setString(str[language]);
                Titul.setPosition(640 - (Titul.getLocalBounds().width / 2), 5);              
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
    sf::RenderWindow Options(sf::VideoMode(1280, 720), L"���������", sf::Style::Fullscreen);
    Options.requestFocus();
    sf::RectangleShape background_opt(sf::Vector2f(1280, 720));
   
    bool switch_language = true; // ����� �����
    std::vector<sf::String> name_menu{ { L"-----",L"-----"} };
    

    bool onoff = gsound->getOnOffSound();
    
    background_opt.setTexture(&AssetManager::GetTexture("image/menu1.jpg"));
    
    // ������ ����
    game::GameMenu optmenu(Options, 640, 250, 80, 100, name_menu);
    // ��������� ����� ����������� ����
    optmenu.setColorTextMenu(sf::Color::Cyan, sf::Color::Magenta, sf::Color::Black);
    optmenu.AlignMenu(2);
    sf::Text Titul;
   
    Titul.setFont(AssetManager::GetFont("font/troika.otf"));
    game::TextFormat FText;
    FText.menu_text_color = sf::Color::Cyan;
    InitText(Titul, 640- (Titul.getLocalBounds().width/2), 5, L"���������", FText);
    
    while (Options.isOpen())
    {
        sf::Event event;
        while (Options.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Escape) Options.close();
                if (event.key.code == sf::Keyboard::Up) { optmenu.MoveUp(); break; }
                if (event.key.code == sf::Keyboard::Down) { optmenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
                    if (!optmenu.getSelectedMenuNumber()) {
                        switch_language = true;
                        if (language < 2) language++; else language = 0;
                    }
                    else 
                    {
                        onoff = !onoff;
                        gsound->OnOffSound(onoff);
                    }
                    
                } break;
            default:break;
            }
        }
        if (switch_language) {
switch (language)
    {
    case 0: 
        optmenu.setNameMenu(L"���� - �������",0);
        if (gsound->getOnOffSound()) optmenu.setNameMenu(L"���� - �������", 1);
        else optmenu.setNameMenu(L"���� - ��������", 1);
        Titul.setString(L"���������");
        optmenu.AlignMenu(2);
        Titul.setPosition(640 - (Titul.getLocalBounds().width / 2), 5);
        break;
    case 1:
        optmenu.setNameMenu(L"���� - ���������", 0);
        if (gsound->getOnOffSound()) optmenu.setNameMenu(L"���� - ��������", 1);
        else optmenu.setNameMenu(L"���� - ��������", 1);
        Titul.setString(L"������������");
        optmenu.AlignMenu(2);
        Titul.setPosition(640 - (Titul.getLocalBounds().width / 2), 5);
        break;
    case 2:
        optmenu.setNameMenu(L"Language - english", 0);
        if (gsound->getOnOffSound()) optmenu.setNameMenu(L"Sound - on", 1);
        else optmenu.setNameMenu(L"Sound - off", 1);
        Titul.setString(L"Settings");
        optmenu.AlignMenu(2);
        Titul.setPosition(640 - (Titul.getLocalBounds().width / 2), 5);
        break;
    default:
        break;
    }
}
        Options.clear();
        Options.draw(background_opt);
        Options.draw(Titul);
        optmenu.draw();
        Options.display();
    }

}

void Engine::About_Game()
{
    sf::RenderWindow About(sf::VideoMode(1280, 720), L"� ����", sf::Style::Fullscreen);
    About.requestFocus();
    sf::RectangleShape background_ab(sf::Vector2f(1280, 720));
    
    switch (language)
    {
    case 0:
        background_ab.setTexture(&AssetManager::GetTexture("image/menu2.jpg"));
        break;
    case 1:
        background_ab.setTexture(&AssetManager::GetTexture("image/menu22.jpg"));
        break;
    case 2:
        background_ab.setTexture(& AssetManager::GetTexture("image/menu21.jpg"));
        break;
    default:
        break;
    }
    

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

bool Engine::Gam�EndMenu(sf::String str, sf::Color col)
{
    std::vector<std::vector<sf::String>> name_menu{ {{ L"�������",L"�����"},{ L"�������",L"�����"},{ L"Restart",L"Exit"} } };

    // ������ ����
    game::GameMenu mymenu(*window, static_cast<float>(window->getSize().x / 2), 300, 45, 90, name_menu[language]);
    // ��������� ����� ����������� ����
    mymenu.setColorTextMenu(sf::Color(227, 171, 0), sf::Color::Yellow, sf::Color::Black);
    mymenu.AlignMenu(2);

    sf::Text Titul;
  
    Titul.setFont(AssetManager::GetFont("font/troika.otf"));
    game::TextFormat FText;
    FText.size_font = 60;
    FText.menu_text_color = col;
    FText.border_color = sf::Color::White;
    InitText(Titul, 640 - (Titul.getLocalBounds().width / 2), 200, str, FText);
    Titul.setPosition(640 - (Titul.getLocalBounds().width / 2), 200);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) { mymenu.MoveUp(); break; }
                if (event.key.code == sf::Keyboard::Down) { mymenu.MoveDown(); break; }
                if (event.key.code == sf::Keyboard::Return)
                {
                    if (mymenu.getSelectedMenuNumber()) return false; else return true;
                    
                } break;
            default:break;
            }
        }
        window->clear();
        window->draw(background_play);
        window->draw(Titul);
        mymenu.draw();
        window->display();
    }
}

void Engine::Lost()
{
    gsound->stop(0);
    if (Gam�EndMenu(strgameEnd[1][language], sf::Color::Black))
    {
        gsound->play(0);
        resetGame();
    }
    else window->close();
}


void Engine::run()
{
    Gam�Menu();  // ��������� ����
    
    sf::Clock clock;
	while (window->isOpen())
	{
		sf::Time dt = clock.restart();
		
        input();
        update(dt);
        draw();
	}
}

void Engine::resetBlob(size_t index)
{
    std::uniform_int_distribution RndPosBlobX(350, 900);
    std::uniform_int_distribution RndPosBlobY(100, 1000);
    std::uniform_int_distribution RndPosBlobSize(1, 3);
    
    float blodSize;

    if (!blob[index].getTexture()) blob[index].setTexture(&AssetManager::GetTexture("image/blob.png"));
    blodSize = static_cast<float>(RndPosBlobSize(rnd));
    speedBlob[index] = blodSize;
    if (blodSize == 3) blodSize=2.5;
    blob[index].setSize(sf::Vector2f(15.0f * (blodSize), 30.0f * (blodSize)));
    blob[index].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd) * -1));

}

void Engine::resetGame()
{
    barBeehive.reset();
    barTime.reset();
    barTime.setColorBar(sf::Color(0, 189, 0), sf::Color(158, 63, 25), 3);
    gsound->AllStop();
    Bee->reset();
}
