#ifndef BASE_H_
#define BASE_H_

namespace base {
class Point {
public:
  Point() = default;
  Point(float x, float y) : x_(x), y_(y){};
  float x() { return x_; }
  float y() { return y_; }

private:
  float x_;
  float y_;
};
} // namespace base
#endif // BASE_H_