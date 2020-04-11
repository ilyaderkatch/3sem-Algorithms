#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

const double eps = 1e-8;

struct Point {
  double x_;
  double y_;
  Point(double x, double y) : x_(x), y_(y) {}
  bool operator<(const Point &p) const {
    return this->y_ < p.y_ || (fabs(this->y_ - p.y_) < eps && this->x_ < p.x_);
  }
  Point operator-(const Point &p) const {
    return {this->x_ - p.x_, this->y_ - p.y_};
  }
  Point operator+(const Point &p) const {
    return {this->x_ + p.x_, this->y_ + p.y_};
  }
  bool IsRotateLess(const Point &p) const;
};

bool Point::IsRotateLess(const Point &p) const {
  if (this->y_ > 0 && p.y_ < 0) {
    return true;
  }
  if (this->y_ < 0 && p.y_ > 0) {
    return false;
  }
  if (fabs(this->y_) < eps && fabs(y_) < eps) {
    if (this->x_ >= 0 && p.x_ < 0) {
      return true;
    }
    if (this->x_ <= 0 && p.x_ > 0) {
      return false;
    }
  }
  double vec_mult = this->x_ * p.y_ - this->y_ * p.x_;
  if (fabs(vec_mult) < eps) {
    return false;
  }
  return vec_mult > 0;
}

void PolygonCyclicShift(vector<Point> &polygon) {
  Point min_point = polygon[0];
  size_t min_index = 0;
  for (size_t i = 0; i < polygon.size(); ++i) {
    if (polygon[i] < min_point) {
      min_point = polygon[i];
      min_index = i;
    }
  }
  vector<Point> copy_polygon = polygon;
  const size_t size = polygon.size();
  for (size_t i = 0; i < size; ++i) {
    polygon[i] = copy_polygon[(min_index + size - i) % size];
  }
  polygon.push_back(polygon[0]);
  polygon.push_back(polygon[1]);
}

vector<Point> MinkovskiSum(const vector<Point> &polygon1,
                           const vector<Point> &polygon2) {
  vector<Point> result;
  size_t i = 0;
  size_t j = 0;
  Point point1(0, 0);
  Point point2(0, 0);
  while ((i < polygon1.size() - 1 || j < polygon2.size() - 1) &&
         i + j < polygon1.size() + polygon2.size() - 3) {
    result.push_back(polygon1[i] + polygon2[j]);
    point1 = polygon1[i + 1] - polygon1[i];
    point2 = polygon2[j + 1] - polygon2[j];
    if (point1.IsRotateLess(point2)) {
      ++i;
    } else if (point2.IsRotateLess(point1)) {
      ++j;
    } else {
      ++i;
      ++j;
    }
  }
  return result;
}

bool IsDifferentSigns(double x, double y) {
  return (x <= 0 && y >= 0) || (x >= 0 && y <= 0);
}

bool IsZeroPointInPolygon(const vector<Point> &polygon) {
  for (size_t i = 0; i < polygon.size() - 1; ++i) {
    double vec_mult =
        polygon[i].x_ * polygon[i + 1].y_ - polygon[i].y_ * polygon[i + 1].x_;
    if (fabs(vec_mult) < eps) {
      if (!(IsDifferentSigns(polygon[i].x_, polygon[i + 1].x_) &&
            IsDifferentSigns(polygon[i].y_, polygon[i + 1].y_))) {
        return false;
      }
    } else if (vec_mult < 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int n;
  int m;
  vector<Point> polygon1;
  vector<Point> polygon2;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    double x;
    double y;
    cin >> x >> y;
    polygon1.emplace_back(x, y);
  }
  PolygonCyclicShift(polygon1);
  cin >> m;
  for (int i = 0; i < m; ++i) {
    double x;
    double y;
    cin >> x >> y;
    polygon2.emplace_back(-x, -y);
  }
  PolygonCyclicShift(polygon2);
  vector<Point> mink = MinkovskiSum(polygon1, polygon2);
  if (IsZeroPointInPolygon(mink)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
  return 0;
}