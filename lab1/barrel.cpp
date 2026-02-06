#include "barrel.hpp"
#include <stdexcept>
#include <algorithm>

// Конструктор по умолчанию - пустая бочка
Barrel::Barrel() : volume_(0), alcohol_(0) {}

// Бочка заданного объема (пустая)
Barrel::Barrel(double volume) : volume_(volume), alcohol_(0) {
    if (volume < 0) {
        throw std::invalid_argument("Объем бочки не может быть отрицательным");
    }
}

// Бочка с заданным количеством спирта
Barrel::Barrel(double volume, double alcohol) : volume_(volume), alcohol_(alcohol) {
    if (volume < 0) {
        throw std::invalid_argument("Объем бочки не может быть отрицательным");
    }
    if (alcohol < 0) {
        throw std::invalid_argument("Количество спирта не может быть отрицательным");
    }
    if (alcohol > volume) {
        throw std::invalid_argument("Количество спирта не может превышать объем бочки");
    }
}

// Получить концентрацию спирта в процентах
double Barrel::get_concentration() const {
    if (volume_ <= 0) return 0.0;
    return (alcohol_ / volume_) * 100.0;
}

// Взять определенное количество жидкости из бочки
// Возвращает количество взятого спирта
double Barrel::take(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Нельзя взять отрицательное количество");
    }
    
    // Нельзя взять больше, чем есть в бочке
    amount = std::min(amount, volume_);
    
    // Вычисляем, сколько спирта мы берем (пропорционально концентрации)
    double alcohol_taken = (alcohol_ / volume_) * amount;
    
    // Уменьшаем объем и количество спирта
    volume_ -= amount;
    alcohol_ -= alcohol_taken;
    
    return alcohol_taken;
}

// Перелить жидкость из другой бочки в эту
void Barrel::pour_from(Barrel& other, double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Нельзя перелить отрицательное количество");
    }
    
    // Берем жидкость из другой бочки
    double alcohol_taken = other.take(amount);
    
    // Добавляем в эту бочку
    volume_ += amount;
    alcohol_ += alcohol_taken;
    
}