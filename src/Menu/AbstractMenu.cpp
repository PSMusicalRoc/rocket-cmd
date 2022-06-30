#include "Menu/AbstractMenu.hpp"

void AbstractMenu::MoveDown() {
    this->_current_index++;
    if (this->_current_index >= this->_submenus.size()) {
        this->_current_index = 0;
    }
}

void AbstractMenu::MoveUp() {
    this->_current_index--;
    if (this->_current_index <= -1) {
        this->_current_index = this->_submenus.size() - 1;
    }
}