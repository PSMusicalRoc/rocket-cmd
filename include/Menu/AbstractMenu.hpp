#pragma once

#include <vector>

class AbstractMenu
{
protected:
    std::vector<AbstractMenu> _submenus;
    int _current_index = 0;

public:
    virtual void AddSubmenu(AbstractMenu &submenu);
    void AddControl();
};