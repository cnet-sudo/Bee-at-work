#include "GameMenu.h"


void game::GameMenu::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const
{
	text.setFont(AssetManager::GetFont("font/troika.otf"));
	text.setFillColor(menu_text_color);
	text.setString(str);
	text.setCharacterSize(size_font);
	text.setOutlineThickness(3);
	text.setOutlineColor(border_color);
	text.setPosition(xpos, ypos);
}

void game::GameMenu::AlignMenu(int posx)
{

	float nullx = 0;

	for (int i = 0; i < max_menu; i++) {

		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 2:
			nullx = menu_X - (mainMenu[i].getLocalBounds().width / 2);
			break;
		default:break;
		}

		mainMenu[i].setPosition(nullx, mainMenu[i].getPosition().y);
	}

}

game::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name)
	:menu_X(menux), menu_Y(menuy), menu_Step(step), max_menu(static_cast<int>(name.size())), size_font(sizeFont), mainMenu(name.size()), mywindow(window)
{
	for (int i = 0, ypos = static_cast<int>(menu_Y); i < max_menu; i++, ypos += menu_Step)
		setInitText(mainMenu[i], name[i], menu_X, static_cast<float>(ypos));
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}

void game::GameMenu::MoveUp()
{
	mainMenuSelected--;

	if (mainMenuSelected >= 0) {
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
		mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
	}
	else
	{
		mainMenu[0].setFillColor(menu_text_color);
		mainMenuSelected = max_menu - 1;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
}

void game::GameMenu::MoveDown()
{
	mainMenuSelected++;

	if (mainMenuSelected < max_menu) {
		mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}
	else
	{
		mainMenu[max_menu - 1].setFillColor(menu_text_color);
		mainMenuSelected = 0;
		mainMenu[mainMenuSelected].setFillColor(chose_text_color);
	}

}


void game::GameMenu::draw()
{
	for (int i = 0; i < max_menu; i++) mywindow.draw(mainMenu[i]);
}

void game::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	menu_text_color = menColor;
	chose_text_color = ChoColor;
	border_color = BordColor;

	for (int i = 0; i < max_menu; i++) {
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}

void game::GameMenu::setNameMenu(sf::String const& name, int index)
{
	mainMenu[index].setString(name);
}

void game::InitText(sf::Text& mtext, float xpos, float ypos, const sf::String& str, game::TextFormat Ftext)
{
	mtext.setCharacterSize(Ftext.size_font);
	mtext.setPosition(xpos, ypos);
	mtext.setString(str);
	mtext.setFillColor(Ftext.menu_text_color);
	mtext.setOutlineThickness(Ftext.bord);
	mtext.setOutlineColor(Ftext.border_color);
}

