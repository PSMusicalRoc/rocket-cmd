#include "Menu/RootMenu.hpp"
#include "Menu/Submenu.hpp"
#include "Menu/_MenuGlobals.hpp"

RootMenu::RootMenu(std::string displayName)
    :AbstractMenu(displayName)
{}

std::shared_ptr<AbstractMenu> RootMenu::Instantiate(std::string displayName) {
    RootMenu m(displayName);
    std::shared_ptr<AbstractMenu> s = std::make_shared<RootMenu>(m);
    Menu::CURRENT_MENU = s.get();
    return s;
}

void RootMenu::AddSubmenu(std::shared_ptr<AbstractMenu> submenu, int place) {
    submenu->SetParent(this);
    if (place < 0) {
        this->_submenus.push_back(submenu);
    } else {
        this->_submenus.insert(this->_submenus.begin() + place, submenu);
    }
}

void RootMenu::Back() {
    //Do nothing, is root
}

void RootMenu::Select() {
    Menu::CURRENT_MENU = _submenus.at(_current_index).get();
    this->_submenus.at(_current_index)->OnSelected();
}

void RootMenu::OnSelected() {
    //Do nothing, will never be selected
}