//
//  Vec2.cpp
//  minimi-engine
//
//  Created by Ramy Zhang on 2024-09-20.
//

#include "Vec2.hpp"

Vec2 Vec2::operator + (const Vec2& rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float& rhs) const {
    return Vec2(x * rhs, y * rhs);
}

Vec2& Vec2::add(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::subtract(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2& Vec2::scale(const float& rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

Vec2& Vec2::rotate(const float& deg) {
    float rads = deg * M_PI / 180.0;
    x = cosf(rads) * x - sinf(rads) * y;
    y = sinf(rads) * x + cosf(rads) * y;
    return *this;
}

float Vec2::distance(const Vec2& v) const {
    return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
}

Vec2& Vec2::normalize() {
    float norm = sqrt(x * x + y * y);
    x = x / norm;
    y = y / norm;
    return *this;
}
