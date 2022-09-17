#pragma once

#include <ostream>

class Vector3D {
  public:
    Vector3D() = default;
    Vector3D(const float &x, const float &y, const float &z);
    ~Vector3D();
    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    friend std::ostream &operator<<(std::ostream &out, const Vector3D &v);

  private:
    float x;
    float y;
    float z;
};
