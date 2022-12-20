#include <SFML/Graphics.hpp>
#include"GameMenu.h"

using namespace sf;

void InitText(Text & mtext,float xpos, float ypos,String str, int size_font=60, Color menu_text_color=Color::White,int bord=0, Color border_color = Color::Black)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);

}

void Gam�Start()
{
    RenderWindow Play(VideoMode(1280, 720), L"������� 1", Style::Fullscreen);

    RectangleShape background_play(Vector2f(1280, 720));
    Texture texture_play;
    if (!texture_play.loadFromFile("image/game.jpg")) std::cout << "No image is here";
   
    background_play.setTexture(&texture_play);

    while (Play.isOpen())
    {
        Event event_play;
        while (Play.pollEvent(event_play))
        {
            if (event_play.type == Event::Closed) Play.close();
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) Play.close();
            }
        }
        Play.clear();
        Play.draw(background_play);
        Play.display();
    }
}

void Options() 
{
    RenderWindow Options(VideoMode(1280, 720), L"���������", Style::Fullscreen);

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
    RenderWindow About(VideoMode(1280, 720), L"� ����", Style::Fullscreen);

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

int main()
{
    
    RenderWindow window(VideoMode(1280, 720), L"��� ����", Style::Fullscreen);
    window.setMouseCursorVisible(false);
   
    float center[4]{ 0,-100,-20,-30 };
    String name_menu[4]{ L"�����",L"���������", L"� ����",L"�����" };
    game::GameMenu mymenu(870, 250,80,100);
     
    for (int i = 0; i < 4; i++) { 
        mymenu.setPositionX(i, center[i]);
        mymenu.setStringMenu(i, name_menu[i]); }

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
    InitText(Titul,250,5,L"����� �� ������",100, Color::White,3);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close(); break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); break; }
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); break;}
                if (event.key.code == Keyboard::Return)
                {                  
                    switch (mymenu.getMainMenuPressed())
                    {
                    case 0:Gam�Start(); break;
                    case 1:Options(); break;
                    case 2:About_Game(); break;
                    case 3:window.close(); break;
                   
                    }  
                } break;
            }
        }
        
        window.clear(Color::Blue);
        window.draw(background);
        window.draw(Titul);
        mymenu.draw(window);        
        window.display();
    }
    return 0;
}