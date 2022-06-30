#pragma once

#include <vector>
#include <memory>
#include <string>

class AbstractMenu
{
protected:
    std::string displayName = "Menu";

    AbstractMenu* _parent;
    std::vector<std::shared_ptr<AbstractMenu>> _submenus;
    int _current_index = 0;

    AbstractMenu(std::string displayName)
        :displayName(displayName) {}

public:
    bool GetIsSelected(int place) {if (place == _current_index) return true; else return false;}
    std::shared_ptr<AbstractMenu> GetSubmenuAtIndex(int index) {return _submenus.at(index);}
    std::string GetDisplayName() {return displayName;}
    int GetNumElements() {return _submenus.size();}

    void SetParent(AbstractMenu* parent) {this->_parent = parent;}
    AbstractMenu* GetParent() {return this->_parent;}

    virtual void AddSubmenu(std::shared_ptr<AbstractMenu> submenu, int place = -1) = 0;
    void MoveUp();
    void MoveDown();
    virtual void Back() = 0;
    virtual void Select() = 0;
    virtual void OnSelected() = 0;
};