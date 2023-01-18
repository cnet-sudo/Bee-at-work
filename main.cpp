#include"GameMenu.h"
#include"Animator.h"
#include "HealthBarClass.h"
#include<iostream>
#include<chrono>
#include<random>
#include<array>
#include<Windows.h>

using namespace sf;
using namespace std;

void Options();

void About_Game();

void GamеMenu();

bool GamеEndMenu(RenderWindow & window, RectangleShape & bacground, String str, Color col);


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
    Play.setMouseCursorVisible(false);

    CircleShape flowers(50);
    flowers.setPosition(1050, 230);
    flowers.setFillColor(Color(255,255,255,0));

    HealthBarClass barFlow(Play, 1150, 330, true);
    barFlow.setColorBar(Color(0, 189, 0), Color(158, 63, 25), 3);
    bool mead=false;  // Наполнение корзинки мёдом
    
    CircleShape beehive(30);
    beehive.setPosition(50, 340);
    beehive.setFillColor(Color(255, 255, 255, 0));


    HealthBarClass barBeehive(Play, 250, 430, true,90);   // Количество мёда в улии
    barBeehive.setColorBar(Color(216, 212, 0), Color(189, 116, 0), 3);
    HealthBarClass barBeehive2(Play, 240, 430, true,0.0f,10);
    barBeehive2.setColorBar(Color(0, 189, 0), Color(189, 116, 0), 3);
    
    RectangleShape beemead(Vector2f(50, 50));
    Texture beemeadtexture;
    beemeadtexture.loadFromFile("image/mead.png");
    beemead.setTexture(&beemeadtexture);

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
    Splash.setOrigin(50,-20);
    Animator SplashAnim(Splash);
    auto& idleSplash = SplashAnim.CreateAnimation("idleSplash", "image/maker.png", seconds(1), false);
    idleSplash.AddFrames(Vector2i(0, 0), SplashSize, 6, 1);

    Vector2i spriteSize(100,100);
    Sprite BeeSprite;
    BeeSprite.setOrigin(50,50);
    BeeSprite.setPosition(90, 365);
    Animator BeeAnim(BeeSprite);
    auto& idleForward = BeeAnim.CreateAnimation("idleForward","image/SPRITESHEET.png",seconds(1),true);
    idleForward.AddFrames(Vector2i(0,0), spriteSize,6,1);
    auto& idleBack = BeeAnim.CreateAnimation("idleBack", "image/SPRITESHEET.png", seconds(1), true);
    idleBack.AddFrames(Vector2i(0,100), spriteSize,6,1);
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
                    if (BeeSprite.getPosition().x < 1100) stepx = 5.0f;
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
                    if (BeeSprite.getPosition().y > 100) stepy = -5.0f;
                }
                if (event_play.key.code == Keyboard::Down)
                {
                    if (BeeSprite.getPosition().y < 620) stepy = 5.0f;
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
                 barBeehive2.reset();
                 barBeehive.changeOfbar(10);
                 if (barBeehive.getFull())
                 {
                     if (GamеEndMenu(Play, background_play, L"Вы выиграли !!!", Color::Magenta))
                     {
                         barBeehive.reset();
                         diedBee = false;
                         BeeSprite.setPosition(90, 365);
                     }
                     else Play.close();
                 }
             } 
             else barBeehive2.changeOfbar(1, deltaTime);
        }

         
         BeeTime += deltaTime;
         if (BeeTime > milliseconds(20))
         {
             BeeTime = milliseconds(0);
             
             if (!diedBee ) BeeSprite.move(stepx, stepy);
             else 
             {
                 if (SplashAnim.getEndAnim()) {
                 BeeSprite.setRotation(90);
                 BeeSprite.move(0, 7);
                 if (BeeSprite.getPosition().y > 720) { 
                 
                 if (barBeehive.getSizeBar() == 0)
                 {
                     if (GamеEndMenu(Play, background_play, L"Вы проиграли !!!", Color::Red))
                     {
                         barBeehive.reset();
                         diedBee = false;
                         BeeSprite.setPosition(90, 365);
                     }
                     else Play.close();
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
                 blob[i].move(0,3);
                 if (blob[i].getPosition().y > 720) 
                 {blob[i].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd) * -1));
                 blodSize = static_cast<float>(RndPosBlobSize(rnd));
                 blob[i].setSize(Vector2f(10 * blodSize, 20 * blodSize));
                 }

                 if (blob[i].getGlobalBounds().intersects(BeeSprite.getGlobalBounds())&& !diedBee)
                 {
                     Splash.setPosition(blob[i].getPosition().x, blob[i].getPosition().y);
                     SplashAnim.restart();
                         blob[i].setPosition(static_cast<float>(RndPosBlobX(rnd)), static_cast<float>(RndPosBlobY(rnd) * -1));
                         blodSize = static_cast<float>(RndPosBlobSize(rnd));
                         blob[i].setSize(Vector2f(10 * blodSize, 20 * blodSize));
                         diedBee = true; mead = false;
                         if (barBeehive.getSizeBar() != 0) barBeehive.changeOfbar(10);
                 }
             }

         }
         
        

        if (!diedBee){
            BeeAnim.Update(deltaTime);
         if (BeeSprite.getPosition().x < 50) { BeeSprite.setPosition(50, BeeSprite.getPosition().y); }
         if (BeeSprite.getPosition().x > 1100) { BeeSprite.setPosition(1100, BeeSprite.getPosition().y); }
         if (BeeSprite.getPosition().y < 100) { BeeSprite.setPosition(BeeSprite.getPosition().x, 100); }
         if (BeeSprite.getPosition().y > 620 ) { BeeSprite.setPosition(BeeSprite.getPosition().x, 620); }
                    }
 
        
        beemead.setPosition(BeeSprite.getPosition().x-20, BeeSprite.getPosition().y + 40);

        Play.clear();
        Play.draw(background_play);
        Play.draw(flowers);
        Play.draw(beehive);
        
        if (!mead && BeeSprite.getGlobalBounds().intersects(flowers.getGlobalBounds())) barFlow.draw();
        
        if (BeeSprite.getGlobalBounds().intersects(beehive.getGlobalBounds()))
        {
            barBeehive.draw();
            barBeehive2.draw();
        }
        
        Play.draw(BeeSprite);
        if (mead)  Play.draw(beemead);
        for (size_t i = 0; i < size(blob); i++)
        {
            Play.draw(blob[i]);
        }
        if (diedBee) Play.draw(Splash);
         
        
        Play.display();
    }
    return 0;
}


bool GamеEndMenu(RenderWindow& window, RectangleShape& bacground, String str, Color col)
{
    std::vector<String> name_menu{ { L"Начать игру заново",L"Выход"}};
   
    // Объект меню
    game::GameMenu mymenu(window, window.getSize().x/2, 300, 45, 90, name_menu);
    // Установка цвета отображения меню
    mymenu.setColorTextMenu(Color(227, 171, 0), Color::Yellow, Color::Black);
    mymenu.AlignMenu(2);
    
    Text Titul;
    Font font;

    if (!font.loadFromFile("font/troika.otf"))
    {
        std::cout << "No font is here";
    }
    Titul.setFont(font);
    game::TextFormat FText;
    FText.size_font = 60;
    FText.menu_text_color = col;
    InitText(Titul,400, 200, str, FText);

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
                    case 0:  return true; break;
                    case 1:  return false; break;
                    default:break;
                    }
                } break;
            default:break;
            }
        }
        

        window.clear();
        window.draw(bacground);
        window.draw(Titul);
        mymenu.draw();
        window.display();
    }
    }



void GamеMenu()
{

    RenderWindow window(VideoMode(1280, 720), L"Пчела на работе", Style::Fullscreen);
    window.setMouseCursorVisible(false);

    std::vector<String> name_menu{ { L"Игра",L"Настройки", L"Правила",L"Выход" } };
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




