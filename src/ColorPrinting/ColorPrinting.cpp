#include "ColorPrinting.hpp"

#include <iostream>

void ColorPrinting::print(std::string msg, ColorCode fg, ColorCode bg, StyleCode style) {
    //std::cout << colorStringMap.at(code) << msg << colorStringMap.at(ColorCode::NORM);
    std::cout << genANSICode(fg, bg, style) << msg << "\x1b[m";
}

void ColorPrinting::println(std::string msg, ColorCode fg, ColorCode bg, StyleCode style) {
    //std::cout << colorStringMap.at(code) << msg << colorStringMap.at(ColorCode::NORM) << std::endl;
    print(msg, fg, bg, style);
    std::cout << std::endl;
}

std::string ColorPrinting::genANSICode(ColorCode fg, ColorCode bg, StyleCode style) {
    std::string out = "\x1b[";
    out += (style != StyleCode::NONE) ? std::to_string(style) + ";" : "";
    out += (fg != RESET) ? std::to_string(fg) + ";" : "";
    out += (bg != RESET) ? std::to_string(bg + 10) : "";
    
    if (out.back() == ';') {
        out.pop_back();
    }

    out += "m";
    return out;
};