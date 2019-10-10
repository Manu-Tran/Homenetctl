#ifndef CORE_HPP
#define CORE_HPP

#include <tuple>

int add(int a, int b);

class Vector2 {
    private:
        float m_x;
        float m_y;

    public:
        Vector2(float x, float y);
        ~Vector2();
        void set(float x, float y);
        std::tuple<float, float> get();
};

#endif
