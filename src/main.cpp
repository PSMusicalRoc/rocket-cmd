#include <ncurses.h>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include "ColorPrinting.hpp"

#include "Menu/_MenuGlobals.hpp"

#include "Menu/RootMenu.hpp"
#include "Menu/Submenu.hpp"

typedef std::shared_ptr<AbstractMenu> AbstractMenuPointer;

AbstractMenuPointer root;

void _recurse_create_menu(nlohmann::json& pos, AbstractMenuPointer current_menu) {
    if (pos["submenus"].is_array())
    {
        // Step 4: Introduce an iterative loop
        for (int i = 0; i < pos["submenus"].size(); i++)
        {
            AbstractMenuPointer new_menu = Submenu::Instantiate(pos["submenus"][i]["title"]);
            current_menu->AddSubmenu(new_menu);
            _recurse_create_menu(pos["submenus"][i], new_menu);
        }
    }
}

void init_menu() {
    std::fstream file;
    file.open("res/menu.json");
    if (file.is_open())
    {
        nlohmann::json menu_file;
        nlohmann::json current_json;
        
        
        // Step 1: Get Root and JSON file
        file >> menu_file;
        if (!menu_file["title"].is_string())
        {
            std::cout << "Could not load json file?" << std::endl;
        }
        root = RootMenu::Instantiate(menu_file["title"]);



        // Step 2: Set current menu to root and current json
        // to root position
        current_json = nlohmann::json(menu_file);

        

        // Step 3: Check if current_json["submenus"] is a list
        _recurse_create_menu(menu_file, root);
    }
    
}


int main() {
    init_menu();

    initscr();
    clear();
	noecho();
	cbreak();
    keypad(stdscr, true);

    int TERM_HEIGHT, TERM_WIDTH;
    getmaxyx(stdscr, TERM_HEIGHT, TERM_WIDTH); 

    while (Menu::shouldContinue) {
        if (Menu::CURRENT_MENU == nullptr) {
            Menu::shouldContinue = false;
            continue;
        }

        int centered_x = (TERM_WIDTH - Menu::CURRENT_MENU->GetDisplayName().size()) / 2;
        mvprintw(0, centered_x, Menu::CURRENT_MENU->GetDisplayName().c_str());
        for (int i = 0; i < TERM_WIDTH; i++) {
            mvprintw(1, i, "-");
        }

        for (int i = 0; i < Menu::CURRENT_MENU->GetNumElements(); i++)
        {
            if (Menu::CURRENT_MENU->GetIsSelected(i)) {
                attron(A_REVERSE);
                mvprintw(i + 4, 5, Menu::CURRENT_MENU->GetSubmenuAtIndex(i)->GetDisplayName().c_str());
                attroff(A_REVERSE);
            } else {mvprintw(i + 4, 5, Menu::CURRENT_MENU->GetSubmenuAtIndex(i)->GetDisplayName().c_str());}
        }

        refresh();
        int temp;
        switch (int k = getch())
        {
            case KEY_DOWN:
                Menu::CURRENT_MENU->MoveDown();
                break;
            case KEY_UP:
                Menu::CURRENT_MENU->MoveUp();
                break;
            case 97: //A
                clear();
                Menu::CURRENT_MENU->Back();
                break;
            case 10: //Enter
                //Menu::shouldContinue = false;
                clear();
                Menu::CURRENT_MENU->Select();
                break;
            case 27: //ESC
                nodelay(stdscr, true);
                temp = getch();
                nodelay(stdscr, false);
                if (temp == -1) {Menu::shouldContinue = false;}
                break;
            default:
                break;
        }
    }


    refresh();
    endwin();

    return 0;
}