#include <ncurses.h>
#include "ColorPrinting.hpp"

#include "Menu/_MenuGlobals.hpp"

#include "Menu/RootMenu.hpp"
#include "Menu/Submenu.hpp"

typedef std::shared_ptr<AbstractMenu> AbstractMenuPointer;

AbstractMenuPointer root;

void init_menu() {
    AbstractMenuPointer sub1 = Submenu::Instantiate("Submenu 1");
    AbstractMenuPointer sub2 = Submenu::Instantiate("Submenu 2");
    AbstractMenuPointer sub15 = Submenu::Instantiate("Submenu 1.5");

    root = RootMenu::Instantiate("Root");
    root->AddSubmenu(sub1);
    root->AddSubmenu(sub2);
    root->AddSubmenu(sub15, 1);
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
                //Menu::shouldContinue = false;
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