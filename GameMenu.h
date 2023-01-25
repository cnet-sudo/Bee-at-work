#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

namespace game {

	class GameMenu
	{
		float menu_X;                                     // Координаты меню по X
		float menu_Y;				                      // Координаты меню по Y
		int menu_Step;                                    // Расстояние между пунктами меню
		int max_menu;                                     // Максимальное количество пунктов меню
		int size_font;                                    // Размер шрифта
		int mainMenuSelected;                             // Номер текущего пункта меню                                 
		std::vector<sf::Text> mainMenu;                   // Динамический массив названий меню

		sf::Color menu_text_color = sf::Color::White;      // Цвет меню
		sf::Color chose_text_color = sf::Color::Yellow;    // Цвет выбора меню
		sf::Color border_color = sf::Color::Black;         // Цвет обводки текста

		// Настройка текста меню
		void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const;

		sf::RenderWindow& mywindow;                       // Ссылка на графическое окно
	public:

		GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name);

		void draw();                                     // Рисуем меню

		void MoveUp();                                   // Перемещение выбора меню вверх

		void MoveDown();                                 // Перемещение выбора меню вниз

		// Цвет элементов игрового меню
		void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);
		void setNameMenu(sf::String const& name, int index);
		void AlignMenu(int posx);       // Выравнивание положения меню (по левому по правому по центру)

		int getSelectedMenuNumber() const     // Возвращает номер выбраного элемента
		{
			return mainMenuSelected;
		}


	};
    
	struct TextFormat
	{
		int size_font = 100;
		float bord = 3.0f;
		sf::Color menu_text_color = sf::Color::Yellow;
		sf::Color border_color = sf::Color::Black;
	};

	void InitText(sf::Text& mtext, float xpos, float ypos, const sf::String& str, TextFormat Ftext);

}
