#pragma once

#include <string>
#include <map>

struct ColorPrinting {
public:

    enum ColorCode {
        RESET = 0,
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        PURPLE = 35,
        CYAN = 36,
        WHITE = 37
    };

    enum StyleCode {
        NONE = 0,
        LIGHT = 1,
        DARK = 2,
        ITALIC = 3,
        UNDERLINE = 4,
        SLOW_BLINK = 5,
        FAST_BLINK = 6,
        REVERSE = 7,
        HIDE = 8,
        CROSS = 9
    };
    static void print(std::string msg, ColorCode fg = RESET, ColorCode bg = RESET, StyleCode style = NONE);
    static void println(std::string msg, ColorCode fg = RESET, ColorCode bg = RESET, StyleCode style = NONE);
    static std::string getPrintOutput(std::string msg, ColorCode fg = RESET, ColorCode bg = RESET, StyleCode style = NONE);

private:
    static std::string genANSICode(ColorCode fg, ColorCode bg, StyleCode style);
};