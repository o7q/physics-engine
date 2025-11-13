#pragma once

template <typename T>
struct Vec2
{
    T x, y;

    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &other) const { return Vec2<T>(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2 &other) const { return Vec2<T>(x - other.x, y - other.y); }
    Vec2 operator*(const Vec2 &other) const { return Vec2<T>(x * other.x, y * other.y); }
    Vec2 operator/(const Vec2 &other) const { return Vec2<T>(x / other.x, y / other.y); }

    Vec2 operator+(const T &v) const { return Vec2<T>(x + v, y + v); }
    Vec2 operator-(const T &v) const { return Vec2<T>(x - v, y - v); }
    Vec2 operator*(const T &v) const { return Vec2<T>(x * v, y * v); }
    Vec2 operator/(const T &v) const { return Vec2<T>(x / v, y / v); }

    Vec2 negate() const { return Vec2<T>(-x, -y); }
};

template <typename T>
struct Bounds2
{
    Bounds2() = default;
    Bounds2(Vec2<T> a, Vec2<T> b)
    {
        set(a, b);
    }

    void set(Vec2<T> a, Vec2<T> b)
    {
        m_a = a;
        m_b = b;
        m_size = b - a;
        m_midpoint = (a + b) / static_cast<T>(2);
    }

    Vec2<T> size() const
    {
        return m_size;
    }

    Vec2<T> midpoint() const
    {
        return m_midpoint;
    }

    float top() const { return m_a.y; }
    float bottom() const { return m_b.y; }
    float left() const { return m_a.x; }
    float right() const { return m_b.x; }

private:
    Vec2<T> m_a, m_b;
    Vec2<T> m_size;
    Vec2<T> m_midpoint;
};

#include <random>

namespace Random
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    inline void seed()
    {
        gen.seed(rd());
    }

    inline int genInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(gen);
    }

    inline float genFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }
}