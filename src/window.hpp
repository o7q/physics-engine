#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "solver.hpp"
#include "math_utils.hpp"

#include <iostream>
#include <string>
#include <chrono>

class Window
{
public:
    Window(int width, int height);

private:
    sf::RenderWindow m_window;
    Solver m_solver;
    float m_dt;
};