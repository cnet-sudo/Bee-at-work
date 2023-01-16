#include"GameMenu.h"
#include"Animator.h"
#include<iostream>
#include<chrono>
#include<random>
#include<array>

using namespace sf;
using namespace std;

void Options();

void About_Game();

void GamеMenu();


int main()
{   
    GamеMenu();
    AssetManager manager;
    long long null_number = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rnd(static_cast<unsigned int>(null_number));
    uniform_int_distribution RndPosBlobX(350, 900);
    uniform_int_distribution RndPosBlobY(0, 1000);
    uniform_int_distribution RndPosBlobSize(1, 3);
    
    RenderWindow Play(VideoMode(1280, 720), L"Игра", Style::Fullscreen);

    RectangleShape background_play(Vector2f(1280, 720));
    Texture backgroundgame;
    backgroundgame.loadFromFile("image/background.jpg");
    background_play.setTexture(&backgroundgame);

    Texture blobTextur;
    blobTextur.loadFromFile("image/blob.png");
    array<RectangleShape,20> blob;
    float blodSize;
    for (size_t i = 0; i < size(blob); i++)
    {
        blob[i].setTexture(&blobTextur);
        blodSize = static_cast<float>(RndPosBlobSize(rnd));
        blob[i].setSize(Vector2f(10.0f* blodSize,20.0f* blodSize));
        blob[i].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd)*-1));
    }
    
    // Анимация брызг
    Vector2i SplashSize(100, 50);
    Sprite Splash;
    Splash.setOrigin(50, 25);
    Animator SplashAnim(Splash);
    auto& idleSplash = SplashAnim.CreateAnimation("idleSplash", "image/maker.png", seconds(1), false);
    idleSplash.AddFrames(Vector2i(0, 0), SplashSize, 5, 1);

    Vector2i spriteSize(117,119);
    Sprite BeeSprite;
    BeeSprite.setOrigin(50,50);
    BeeSprite.setPosition(100, 350);
    Animator BeeAnim(BeeSprite);
    auto& idleForward = BeeAnim.CreateAnimation("idleForward","image/SPRITESHEET.png",seconds(1),true);
    idleForward.AddFrames(Vector2i(0,0), spriteSize,6,1);
    auto& idleBack = BeeAnim.CreateAnimation("idleBack", "image/SPRITESHEET.png", seconds(1), true);
    idleBack.AddFrames(Vector2i(0,120), spriteSize,6,1);
    Clock clock;
    Time BeeTime;
    bool direction = true;
    float stepx=0.0f;
    float stepy=0.0f;
    bool diedBee = false;
    while (Play.isOpen())
    {
        Event event_play;
        while (Play.pollEvent(event_play))
        {
            switch (event_play.type)
            {
            case Event::Closed:Play.close(); break;
            case Event::KeyPressed:
                if (event_play.key.code == Keyboard::Escape) { GamеMenu(); }
                if (event_play.key.code == Keyboard::Right) {
                    if (BeeSprite.getPosition().x < 1080) stepx = 5.0f;
                    if (!direction) {
                        BeeAnim.SwitchAnimation("idleForward"); direction = true;
                    }
                }
                if (event_play.key.code == Keyboard::Left)
                {
                    if (BeeSprite.getPosition().x > 50)stepx = -5.0f;
                    if (direction) {
                        BeeAnim.SwitchAnimation("idleBack"); direction = false;
                    }
                }

                if (event_play.key.code == Keyboard::Up) {
                    if (BeeSprite.getPosition().y > 200) stepy = -5.0f;
                }
                if (event_play.key.code == Keyboard::Down)
                {
                    if (BeeSprite.getPosition().y < 520) stepy = 5.0f;
                }
                break;
            case Event::KeyReleased:
                if (event_play.key.code == Keyboard::Right) {
                     stepx = 0.0f;
                    
                }
                if (event_play.key.code == Keyboard::Left)
                {
                    stepx = 0.0f;
                    
                }

                if (event_play.key.code == Keyboard::Up) {
                    stepy = 0.0f;
                }
                if (event_play.key.code == Keyboard::Down)
                {
                    stepy = 0.0f;

                }
                break;
            default:
                break;
            }           
        }
         Time deltaTime = clock.restart();   
         if (diedBee) SplashAnim.Update(deltaTime);
         BeeTime += deltaTime;

         if (BeeTime > milliseconds(20))
         {
             BeeTime = milliseconds(0);
             
             if (!diedBee) BeeSprite.move(stepx, stepy); 
             else 
             {
                
                 BeeSprite.move(0, 7);
                 if (BeeSprite.getPosition().y > 700) { BeeSprite.setPosition(100, 350); 
                 diedBee = false; 
                 BeeSprite.setRotation(0);
                 BeeAnim.SwitchAnimation("idleForward");
                 }
             }     
            for (size_t i = 0; i < size(blob); i++)
             {
                 blob[i].move(0,5);
                 if (blob[i].getPosition().y > 720) 
                 {blob[i].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd) * -1));
                 blodSize = static_cast<float>(RndPosBlobSize(rnd));
                 blob[i].setSize(Vector2f(10 * blodSize, 20 * blodSize));
                 }

                 if (blob[i].getGlobalBounds().intersects(BeeSprite.getGlobalBounds())&& !diedBee)
                 {
                     Splash.setPosition(blob[i].getPosition().x, blob[i].getPosition().y);
                     blob[i].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd) * -1));
                     blodSize = static_cast<float>(RndPosBlobSize(rnd));
                         blob[i].setSize(Vector2f(10 * blodSize, 20 * blodSize));
                         diedBee = true;
                         BeeSprite.setRotation(90);
                 }
             }
         }
         
        if (!diedBee){
            BeeAnim.Update(deltaTime);
         if (BeeSprite.getPosition().x < 50) { BeeSprite.setPosition(50, BeeSprite.getPosition().y); }
         if (BeeSprite.getPosition().x > 1080) { BeeSprite.setPosition(1080, BeeSprite.getPosition().y); }
         if (BeeSprite.getPosition().y < 200) { BeeSprite.setPosition(BeeSprite.getPosition().x, 200); }
         if (BeeSprite.getPosition().y > 520 ) { BeeSprite.setPosition(BeeSprite.getPosition().x, 520); }
                    }

        Play.clear();
        Play.draw(background_play);
        Play.draw(BeeSprite);
        for (size_t i = 0; i < size(blob); i++)
        {
            Play.draw(blob[i]);
        }
        Play.draw(Splash);
        Play.display();
    }
    return 0;
}

void GamеMenu()
{

    RenderWindow window(VideoMode(1280, 720), L"Пчела на работе", Style::Fullscreen);
    window.setMouseCursorVisible(false);

    std::vector<String> name_menu{ { L"Старт",L"Настройки", L"О игре",L"Выход" } };
    // Объект меню
    game::GameMenu mymenu(window, 950, 250, 80, 100, name_menu);
    // Установка цвета отображения меню
    mymenu.setColorTextMenu(Color(227, 171, 0), Color::Yellow, Color::Black);
    mymenu.AlignMenu(2);

    RectangleShape background(Vector2f(1280, 720));
    Texture texture_window;
    if (!texture_window.loadFromFile("image/bee1.jpg")) std::cout << "No image is here";
    background.setTexture(&texture_window);

    Text Titul;
    Font font;
    if (!font.loadFromFile("font/troika.otf"))
    {
        std::cout << "No font is here";
    }
    Titul.setFont(font);
    game::TextFormat FText;
    FText.menu_text_color = Color(227, 171, 0);
    InitText(Titul, 270, 5, L"Пчела на работе", FText);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); break; }
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); break; }
                if (event.key.code == Keyboard::Return)
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

        window.clear(Color::Blue);
        window.draw(background);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
    
}

void Options()
{
    RenderWindow Options(VideoMode(1280, 720), L"Настройки", Style::Fullscreen);

    RectangleShape background_opt(Vector2f(1280, 720));
    Texture texture_opt;
    if (!texture_opt.loadFromFile("image/menu1.jpg")) std::cout << "No image is here";

    background_opt.setTexture(&texture_opt);
    while (Options.isOpen())
    {
        Event event_opt;
        while (Options.pollEvent(event_opt))
        {
            if (event_opt.type == Event::Closed) Options.close();
            if (event_opt.type == Event::KeyPressed)
            {
                if (event_opt.key.code == Keyboard::Escape) Options.close();
            }
        }
        Options.clear();
        Options.draw(background_opt);
        Options.display();
    }

}


void About_Game()
{
    RenderWindow About(VideoMode(1280, 720), L"О игре", Style::Fullscreen);

    RectangleShape background_ab(Vector2f(1280, 720));
    Texture texture_ab;
    if (!texture_ab.loadFromFile("image/menu2.jpg")) std::cout << "No image is here";

    background_ab.setTexture(&texture_ab);

    while (About.isOpen())
    {
        Event event_play;
        while (About.pollEvent(event_play))
        {
            if (event_play.type == Event::Closed) About.close();
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) About.close();
            }
        }
        About.clear();
        About.draw(background_ab);
        About.display();
    }
}




