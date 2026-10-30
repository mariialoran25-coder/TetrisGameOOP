#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class ColorCode {
public:
    static sf::Color GetColorCode(const std::string& colorName);
};