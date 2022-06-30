#include "Menu/Submenu.hpp"
#include "Menu/_MenuGlobals.hpp"

Submenu::Submenu(std::string displayName)
    :AbstractMenu(displayName)
{}

std::shared_ptr<AbstractMenu> Submenu::Instantiate(std::string displayName) {
    Submenu m(displayName);
    std::shared_ptr<AbstractMenu> s = std::make_shared<Submenu>(m);
    return s;
}

void Submenu::AddSubmenu(std::shared_ptr<AbstractMenu> submenu, int place) {
    submenu->SetParent(this);
    if (place < 0) {
        this->_submenus.push_back(submenu);
    } else {
        this->_submenus.insert(this->_submenus.begin() + place, submenu);
    }
}

void Submenu::Back() {
    Menu::CURRENT_MENU = this->_parent;
}

void Submenu::Select() {
    Menu::CURRENT_MENU = _submenus.at(_current_index).get();
    this->_submenus.at(_current_index)->OnSelected();
}

void Submenu::OnSelected() {
}