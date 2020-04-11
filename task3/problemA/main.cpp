#include <cassert>
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const double eps = 1e-8;
const double c_1_divide_2 = 1.0 / 2;
const double c_2_divide_3 = 2.0 / 3;
const double c_1_divide_3 = 1.0 / 3;
const double c_1 = 1.0;
const double c_0 = 0.0;

struct Point {
  double x_;
  double y_;
  double z_;
  Point() = default;
  Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}
  Point operator-(const Point &p) const {
    return {x_ - p.x_, y_ - p.y_, z_ - p.z_};
  }
  Point operator+(const Point &p) const {
    return {x_ + p.x_, y_ + p.y_, z_ + p.z_};
  }
  double Norm() const { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
  friend std::istream &operator>>(std::istream &in, Point &point) {
    in >> point.x_ >> point.y_ >> point.z_;
    return in;
  }
};

struct Segment {
  Point left_;
  Point right_;
  Segment() = default;
  Segment(Point left, Point right) : left_(left), right_(right) {}
  friend std::istream &operator>>(std::istream &in, Segment &segment) {
    in >> segment.left_ >> segment.right_;
    return in;
  }
};

Point DivideSegment(Segment segment, double coef) {
  assert(c_0 <= coef && coef <= c_1);
  return {coef * segment.left_.x_ + (1 - coef) * segment.right_.x_,
          coef * segment.left_.y_ + (1 - coef) * segment.right_.y_,
          coef * segment.left_.z_ + (1 - coef) * segment.right_.z_};
}
double Distance(Point end1, Point end2) { return (end1 - end2).Norm(); }

double FindDistanceFromPoint(Point point_a, Segment segment) {
  while (Distance(segment.left_, segment.right_) >= eps) {
    Point left = DivideSegment(segment, c_2_divide_3);
    Point right = DivideSegment(segment, c_1_divide_3);
    if (Distance(point_a, left) < Distance(point_a, right)) {
      segment.right_ = right;
    } else {
      segment.left_ = left;
    }
  }
  return Distance(point_a, DivideSegment(segment, c_1_divide_2));
}

double FindDistanceBetweenSegments(Segment seg1, Segment seg2) {
  while (Distance(seg1.left_, seg1.right_) >= eps) {
    Point left = DivideSegment(seg1, c_2_divide_3);
    Point right = DivideSegment(seg1, c_1_divide_3);
    if (FindDistanceFromPoint(left, seg2) <
        FindDistanceFromPoint(right, seg2)) {
      seg1.right_ = right;
    } else {
      seg1.left_ = left;
    }
  }
  return FindDistanceFromPoint(DivideSegment(seg1, c_1_divide_2), seg2);
}

int main() {
  Segment seg1;
  Segment seg2;
  cin >> seg1 >> seg2;
  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.setf(std::ios::showpoint);
  cout << FindDistanceBetweenSegments(seg1, seg2) << endl;
  return 0;
}