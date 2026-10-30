#pragma once
#include "ColorCode.h"
#include <iostream>
#include "string"
#include <SFML/Graphics.hpp>


sf::Color ColorCode::GetColorCode(const std::string& colorName) {
    if (colorName == "cyan")return sf::Color::Cyan;
    if (colorName == "blue")return sf::Color::Blue;
    if (colorName == "orange") return sf::Color(255, 165, 0);
    if (colorName == "yellow") return sf::Color::Yellow;
    if (colorName == "green") return sf::Color::Green;
    if (colorName == "purple") return sf::Color(128, 0, 128);
    if (colorName == "red") return sf::Color::Red;
    return sf::Color::White;
};