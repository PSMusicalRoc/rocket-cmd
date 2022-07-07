#include "Menu/ApplicationMenu.hpp"
#include "Menu/_MenuGlobals.hpp"
#include <ncurses.h>

ApplicationMenu::ApplicationMenu(std::string displayName, std::string command)
    :AbstractMenu(displayName), _command_on_select(command) {}

std::shared_ptr<AbstractMenu> ApplicationMenu::Instantiate(std::string displayName, std::string command)
{
    ApplicationMenu m(displayName, command);
    std::shared_ptr<AbstractMenu> s = std::make_shared<ApplicationMenu>(m);
    //Menu::CURRENT_MENU = s.get();
    return s;
}

void ApplicationMenu::AddSubmenu(std::shared_ptr<AbstractMenu> submenu, int place)
{
    //Cannot add submenus to application
    //so nothing here
}

void ApplicationMenu::Back()
{
    //Should not be going back, should not
    //be set as main thing :/
}

void ApplicationMenu::Select()
{
    //Will never happen, this should not be the main menu
}

void ApplicationMenu::OnSelected()
{
    Menu::CURRENT_MENU = _parent;
    system(_command_on_select.c_str());

    // Reset menu back to working
    initscr();
    clear();
	noecho();
	cbreak();
    keypad(stdscr, true);
}