#include "window.hpp"

Window::Window(int width, int height)
{
    sf::Vector2u window_size(width, height);

    Bounds2<float> bounds(Vec2<float>(window_size.x / 2.0f - 550, window_size.y / 2.0f - 300),
                          Vec2<float>(window_size.x / 2.0f + 550, window_size.y / 2.0f + 300));

    m_solver.setBounds(bounds);
    m_window.create(sf::VideoMode(window_size), "Physics Simulator");
    m_window.setFramerateLimit(60);

    while (m_window.isOpen())
    {
        std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();

        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }

        m_window.clear(sf::Color::Black);
        m_solver.update(m_window, m_dt);
        m_solver.render(m_window);
        m_window.display();

        std::chrono::steady_clock::time_point frame_end = std::chrono::steady_clock::now();

        const float seconds_per_frame = std::chrono::duration_cast<std::chrono::duration<float>>(frame_end - frame_start).count();

        float fps = 1.0f / seconds_per_frame;
        // m_dt = 60.0f / fps;
        m_dt = 1;
    }
}