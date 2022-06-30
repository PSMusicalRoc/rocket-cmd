#pragma once

#include <memory>
#include "Menu/AbstractMenu.hpp"

struct Menu {
    static AbstractMenu* CURRENT_MENU;
    static bool shouldContinue;
};