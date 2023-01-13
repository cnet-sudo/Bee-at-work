#include"GameMenu.h"
#include<iostream>
#include<vector>

using namespace sf;

struct TextFormat
{
    int size_font = 100;
    float bord = 3.0f;
    Color menu_text_color = Color::Yellow;
    Color border_color = Color::Black;
};

void InitText(Text& mtext, float xpos, float ypos, const String& str, TextFormat Ftext);

void Options();

void About_Game();

void GamеStart();

int main()
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
    TextFormat FText;
    FText.menu_text_color = Color(227, 171, 0);
    InitText(Titul,270,5,L"Пчела на работе",FText);

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
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:GamеStart(); break;
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
        mymenu.draw();        
        window.display();
    }
    return 0;
}

void GamеStart ()
{
    RenderWindow Play(VideoMode(1280, 720), L"Уровень 1", Style::Fullscreen);

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


void InitText(Text& mtext, float xpos, float ypos, const String& str, TextFormat Ftext)
{
    mtext.setCharacterSize(Ftext.size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(Ftext.menu_text_color);
    mtext.setOutlineThickness(Ftext.bord);
    mtext.setOutlineColor(Ftext.border_color);

}

