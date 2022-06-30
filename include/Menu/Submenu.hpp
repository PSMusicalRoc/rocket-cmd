#pragma once

#include "Menu/AbstractMenu.hpp"

class Submenu : public AbstractMenu {
protected:
    Submenu(std::string displayName);

public:
    static std::shared_ptr<AbstractMenu> Instantiate(std::string displayName);
    void AddSubmenu(std::shared_ptr<AbstractMenu> submenu, int place = -1) override;
    void Back() override;
    void Select() override;
    void OnSelected() override;
};