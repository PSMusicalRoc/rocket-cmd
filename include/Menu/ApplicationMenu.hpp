#pragma once

#include "Menu/AbstractMenu.hpp"
#include <string>

class ApplicationMenu : public AbstractMenu
{
private:
    std::string _command_on_select;

protected:
    ApplicationMenu(std::string displayName, std::string command);

public:
    static std::shared_ptr<AbstractMenu> Instantiate(std::string displayName, std::string command = "");
    void AddSubmenu(std::shared_ptr<AbstractMenu> submenu, int place = -1) override;
    void Back() override;
    void Select() override;
    void OnSelected() override;
};