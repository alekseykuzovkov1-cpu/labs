#include "rect.hpp"
#include <iostream>

Rect::Rect() 
    : left(0), right(0), top(0), bottom(0)
{
    std::cout << "Конструктор по умолчанию для " << this << std::endl;
}

Rect::Rect(int l, int r, int t, int b) 
    : left(l), right(r), top(t), bottom(b)
{
    std::cout << "Параметризованный конструктор для " << this << " с параметрами: " << l << "," << r << "," << t << "," << b << std::endl;
}

Rect::Rect(const Rect& other)
    : left(other.left), right(other.right), top(other.top), bottom(other.bottom) 
{
    std::cout << "Конструктор копирования для " << this << " из " << &other << std::endl;
}

Rect::~Rect() {
    std::cout << "Деструктор для " << this << " с полями: " << left << "," << right << "," << top << "," << bottom << std::endl;
}

void Rect::set_all(int l, int r, int t, int b) {
    left = l;
    right = r;
    top = t;
    bottom = b;
    std::cout << "set_all вызван для " << this << " с параметрами: " << l << "," << r << "," << t << "," << b << std::endl;
}

void Rect::inflate(int amount) {
    left -= amount;
    right += amount;
    top -= amount;
    bottom += amount;
}

void Rect::inflate(int dw, int dh) {
    left -= dw;
    right += dw;
    top -= dh;
    bottom += dh;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    left -= d_left;
    right += d_right;
    top -= d_top;
    bottom += d_bottom;
}

void Rect::move(int dx, int dy) {
    left += dx;
    right += dx;
    top += dy;
    bottom += dy;
}

Rect bounding_rect(Rect r1, Rect r2) {   
    int min_left = std::min(r1.get_left(), r2.get_left());
    int max_right = std::max(r1.get_right(), r2.get_right());
    int min_top = std::min(r1.get_top(), r2.get_top());
    int max_bottom = std::max(r1.get_bottom(), r2.get_bottom());
    
    Rect result(min_left, max_right, min_top, max_bottom);
    std::cout << "  создан bounding rect: (" << min_left << "," << max_right 
              << ")-(" << min_top << "," << max_bottom << ")" << std::endl;
    
    return result;
}

void print_rect(const Rect& r) {
    std::cout << "Прямоугольник: ";
    std::cout << "left=" << r.get_left() << ", right=" << r.get_right();
    std::cout << ", top=" << r.get_top() << ", bottom=" << r.get_bottom();
    std::cout << std::endl;
}

void Rect::set_width(int new_width) {
    if (new_width < 0) {
        std::cout << "Ошибка: ширина не может быть отрицательной" << std::endl;
        return;
    }
    right = left + new_width;
}

void Rect::set_height(int new_height) {
    if (new_height < 0) {
        std::cout << "Ошибка: высота не может быть отрицательной" << std::endl;
        return;
    }
    bottom = top + new_height;
}