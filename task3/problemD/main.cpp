#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::fabs;
using std::hash;
using std::max;
using std::min;
using std::pair;
using std::queue;
using std::sort;
using std::stack;
using std::unordered_map;
using std::vector;

const double inf = 1e9;
const double eps = 1e-9;
const size_t count_faces_of_tetrahedron = 4;
const size_t precision = 12;

struct Point {
  double x_;
  double y_;
  double z_;
  size_t index_;
  Point() : x_(inf), y_(inf), z_(inf), index_(0) {}
  Point(double x, double y, double z, size_t index)
      : x_(x), y_(y), z_(z), index_(index) {}
  bool operator<(const Point &p) const { return index_ < p.index_; }
  bool operator==(const Point &p) const {
    return fabs(x_ - p.x_) < eps && fabs(y_ - p.y_) < eps &&
           fabs(z_ - p.z_) < eps;
  }
  Point operator-(const Point &p) const {
    return {x_ - p.x_, y_ - p.y_, z_ - p.z_, index_ - p.index_};
  }
  Point operator+(const Point &p) const {
    return {x_ + p.x_, y_ + p.y_, z_ + p.z_, index_ + p.index_};
  }
  Point operator-() const { return {-x_, -y_, -z_, 0}; }
  Point operator=(Point p) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = p.z_;
    index_ = p.index_;
    return *this;
  }
};

struct OrientedSegment {
  Point end1_;
  Point end2_;
  OrientedSegment() = default;
  OrientedSegment(Point end1, Point end2) : end1_(end1), end2_(end2) {}
  OrientedSegment operator-() const { return {end2_, end1_}; }
};

struct Triangle {
  Point v1_;
  Point v2_;
  Point v3_;
  size_t neighbour1_;
  size_t neighbour2_;
  size_t neighbour3_;
  OrientedSegment intersect_neighbour1_;
  OrientedSegment intersect_neighbour2_;
  OrientedSegment intersect_neighbour3_;

  Triangle()
      : neighbour1_(static_cast<size_t>(inf)),
        neighbour2_(static_cast<size_t>(inf)),
        neighbour3_(static_cast<size_t>(inf)){};
  Triangle(Point v1, Point v2, Point v3)
      : v1_(v1),
        v2_(v2),
        v3_(v3),
        neighbour1_(static_cast<size_t>(inf)),
        neighbour2_(static_cast<size_t>(inf)),
        neighbour3_(static_cast<size_t>(inf)){};
  bool operator<(const Triangle &tr) const {
    return v1_ < tr.v1_ || (v1_ == tr.v1_ && v2_ < tr.v2_) ||
           (v1_ == tr.v1_ && v2_ == tr.v2_ && v3_ < tr.v3_);
  }
  bool operator==(const Triangle &tr) const {
    return v1_ == tr.v1_ && v2_ == tr.v2_ && v3_ == tr.v3_;
  }

  void SwapNeighbour(size_t old, size_t update);
};

void Triangle::SwapNeighbour(size_t old, size_t update) {
  if (neighbour1_ == old) {
    neighbour1_ = update;
  } else if (neighbour2_ == old) {
    neighbour2_ = update;
  } else {
    neighbour3_ = update;
  }
}

Point VectorMult(const Point &a, const Point &b) {
  return {a.y_ * b.z_ - a.z_ * b.y_, a.z_ * b.x_ - a.x_ * b.z_,
          a.x_ * b.y_ - a.y_ * b.x_, 0};
}

double ScalarMult(const Point &a, const Point &b) {
  return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_;
}

bool IsTriangleVisible(Point view, Triangle tr) {
  Point normal = VectorMult(tr.v3_ - tr.v2_, tr.v1_ - tr.v2_);
  return ScalarMult(normal, view - tr.v1_) > 0 &&
         ScalarMult(normal, view - tr.v2_) > 0 &&
         ScalarMult(normal, view - tr.v3_) > 0;
}

Triangle MakeNewTriangle(OrientedSegment s, Point p) {
  if (min(p.index_, min(s.end1_.index_, s.end2_.index_)) == p.index_) {
    return {p, s.end2_, s.end1_};
  }
  if (min(p.index_, min(s.end1_.index_, s.end2_.index_)) == s.end1_.index_) {
    return {s.end1_, p, s.end2_};
  }
  return {s.end2_, s.end1_, p};
}

template <>
class std::hash<Point> {
 public:
  size_t operator()(const Point &p) const {
    size_t h1 = hash<double>()(p.x_);
    size_t h2 = hash<double>()(p.y_);
    size_t h3 = hash<double>()(p.z_);
    return h1 * h2 * h3;
  }
};

template <>
class std::hash<Triangle> {
 public:
  size_t operator()(const Triangle &tr) const {
    size_t h1 = hash<Point>()(tr.v1_);
    size_t h2 = hash<Point>()(tr.v2_);
    size_t h3 = hash<Point>()(tr.v3_);
    return h1 * h2 * h3;
  }
};

template <typename T>
struct Triple {
  T first_;
  T second_;
  T third_;
  Triple(T first, T second, T third)
      : first_(first), second_(second), third_(third){};
};

class ConflictGraph {
 private:
  unordered_map<size_t, Triangle> convex_hill_;
  vector<Point> ordered_points_;
  vector<size_t> vision_horizont_;
  vector<size_t> last_added_faces_ = {0, 1, 2, 3};
  size_t last_num_face_ = count_faces_of_tetrahedron;

  void ConnectNewTrianglesByEnd2(size_t new_triangle_index,
                                 Point horizont_point, Point p);
  void ConnectNewTrianglesByEnd1(size_t new_triangle_index,
                                 Point horizont_point, Point p);
  void AddTriangle(Point p, OrientedSegment oriented_s, size_t old_triangle,
                   size_t neigh_triangle);
  void AddTwoFaces(Triangle &tr, Triple<size_t> neigh,
                   Triple<OrientedSegment> seg);
  size_t FindVisionFace(Point p);
  void ProcessNeighbour(Point p, size_t current_triangle, queue<size_t> &q,
                        size_t neighbour_triangle,
                        OrientedSegment common_segment);
  void AddPoint(Point p);

 public:
  explicit ConflictGraph(const vector<Point> &ordered_points);
  vector<Triple<size_t>> OutputHill();
};

ConflictGraph::ConflictGraph(const vector<Point> &ordered_points) {
  ordered_points_ = ordered_points;
  vector<Point> sort_by_index = {ordered_points_[0], ordered_points_[1],
                                 ordered_points_[2], ordered_points_[3]};
  sort(sort_by_index.begin(), sort_by_index.end());
  vision_horizont_.resize(ordered_points_.size(), static_cast<size_t>(inf));
  Point normal = VectorMult(sort_by_index[1] - sort_by_index[0],
                            sort_by_index[2] - sort_by_index[0]);
  Triangle first_face;
  if (ScalarMult(sort_by_index[0] - sort_by_index[3], normal) < 0) {
    first_face = Triangle(sort_by_index[0], sort_by_index[2], sort_by_index[1]);
  } else {
    first_face = Triangle(sort_by_index[0], sort_by_index[1], sort_by_index[2]);
  }
  Triangle f1 =
      MakeNewTriangle({first_face.v1_, first_face.v2_}, sort_by_index[3]);
  Triangle f2 =
      MakeNewTriangle({first_face.v2_, first_face.v3_}, sort_by_index[3]);
  Triangle f3 =
      MakeNewTriangle({first_face.v3_, first_face.v1_}, sort_by_index[3]);
  convex_hill_ = {{0, first_face}, {1, f1}, {2, f2}, {3, f3}};
  AddTwoFaces(convex_hill_[0], {1, 2, 3},
              {{first_face.v1_, first_face.v2_},
               {first_face.v2_, first_face.v3_},
               {first_face.v3_, first_face.v1_}});
  AddTwoFaces(convex_hill_[1], {0, 3, 2},
              {{first_face.v2_, first_face.v1_},
               {first_face.v1_, sort_by_index[3]},
               {sort_by_index[3], first_face.v2_}});
  AddTwoFaces(convex_hill_[2], {0, 1, 3},
              {{first_face.v3_, first_face.v2_},
               {first_face.v2_, sort_by_index[3]},
               {sort_by_index[3], first_face.v3_}});
  AddTwoFaces(convex_hill_[3], {0, 2, 1},
              {{first_face.v1_, first_face.v3_},
               {first_face.v3_, sort_by_index[3]},
               {sort_by_index[3], first_face.v1_}});
  for (size_t i = last_num_face_; i < ordered_points_.size(); ++i) {
    AddPoint(ordered_points_[i]);
  }
}

void ConflictGraph::AddTwoFaces(Triangle &tr, Triple<size_t> neigh,
                                Triple<OrientedSegment> seg) {
  tr.neighbour1_ = neigh.first_;
  tr.neighbour2_ = neigh.second_;
  tr.neighbour3_ = neigh.third_;
  tr.intersect_neighbour1_ = seg.first_;
  tr.intersect_neighbour2_ = seg.second_;
  tr.intersect_neighbour3_ = seg.third_;
}

void ConflictGraph::ConnectNewTrianglesByEnd1(size_t new_triangle_index,
                                              Point horizont_point, Point p) {
  if (vision_horizont_[horizont_point.index_] == static_cast<size_t>(inf)) {
    vision_horizont_[horizont_point.index_] = new_triangle_index;
  } else {
    if (convex_hill_[vision_horizont_[horizont_point.index_]].neighbour2_ ==
        static_cast<size_t>(inf)) {
      convex_hill_[vision_horizont_[horizont_point.index_]].neighbour2_ =
          new_triangle_index;
      convex_hill_[vision_horizont_[horizont_point.index_]]
          .intersect_neighbour2_ = {horizont_point, p};
    } else {
      convex_hill_[vision_horizont_[horizont_point.index_]].neighbour3_ =
          new_triangle_index;
      convex_hill_[vision_horizont_[horizont_point.index_]]
          .intersect_neighbour3_ = {horizont_point, p};
    }

    if (convex_hill_[new_triangle_index].neighbour2_ ==
        static_cast<size_t>(inf)) {
      convex_hill_[new_triangle_index].neighbour2_ =
          vision_horizont_[horizont_point.index_];
      convex_hill_[new_triangle_index].intersect_neighbour2_ = {p,
                                                                horizont_point};
    } else {
      convex_hill_[new_triangle_index].neighbour3_ =
          vision_horizont_[horizont_point.index_];
      convex_hill_[new_triangle_index].intersect_neighbour3_ = {p,
                                                                horizont_point};
    }
    vision_horizont_[horizont_point.index_] = static_cast<size_t>(inf);
  }
}

void ConflictGraph::ConnectNewTrianglesByEnd2(size_t new_triangle_index,
                                              Point horizont_point, Point p) {
  if (vision_horizont_[horizont_point.index_] == static_cast<size_t>(inf)) {
    vision_horizont_[horizont_point.index_] = new_triangle_index;
  } else {
    if (convex_hill_[vision_horizont_[horizont_point.index_]].neighbour2_ ==
        static_cast<size_t>(inf)) {
      convex_hill_[vision_horizont_[horizont_point.index_]].neighbour2_ =
          new_triangle_index;
      convex_hill_[vision_horizont_[horizont_point.index_]]
          .intersect_neighbour2_ = {p, horizont_point};
    } else {
      convex_hill_[vision_horizont_[horizont_point.index_]].neighbour3_ =
          new_triangle_index;
      convex_hill_[vision_horizont_[horizont_point.index_]]
          .intersect_neighbour3_ = {p, horizont_point};
    }

    if (convex_hill_[new_triangle_index].neighbour2_ ==
        static_cast<size_t>(inf)) {
      convex_hill_[new_triangle_index].neighbour2_ =
          vision_horizont_[horizont_point.index_];
      convex_hill_[new_triangle_index].intersect_neighbour2_ = {horizont_point,
                                                                p};
    } else {
      convex_hill_[new_triangle_index].neighbour3_ =
          vision_horizont_[horizont_point.index_];
      convex_hill_[new_triangle_index].intersect_neighbour3_ = {horizont_point,
                                                                p};
    }
    vision_horizont_[horizont_point.index_] = static_cast<size_t>(inf);
  }
}

void ConflictGraph::AddTriangle(Point p, OrientedSegment oriented_s,
                                size_t old_triangle, size_t neigh_triangle) {
  Triangle new_tr = MakeNewTriangle(-oriented_s, p);
  convex_hill_.emplace(last_num_face_, new_tr);
  convex_hill_[neigh_triangle].SwapNeighbour(old_triangle, last_num_face_);
  convex_hill_[last_num_face_].neighbour1_ = neigh_triangle;
  convex_hill_[last_num_face_].intersect_neighbour1_ = oriented_s;
  ConnectNewTrianglesByEnd1(last_num_face_, oriented_s.end1_, p);
  ConnectNewTrianglesByEnd2(last_num_face_, oriented_s.end2_, p);
  last_added_faces_.push_back(last_num_face_);
  ++last_num_face_;
}

size_t ConflictGraph::FindVisionFace(Point p) {
  for (size_t last_added_face : last_added_faces_) {
    if (IsTriangleVisible(p, convex_hill_[last_added_face])) {
      return last_added_face;
    }
  }
  return static_cast<size_t>(inf);
}

void ConflictGraph::ProcessNeighbour(Point p, size_t current_triangle,
                                     queue<size_t> &q,
                                     size_t neighbour_triangle,
                                     OrientedSegment common_segment) {
  if (convex_hill_.find(neighbour_triangle) == convex_hill_.end()) {
    return;
  }

  if (!IsTriangleVisible(p, convex_hill_[neighbour_triangle])) {
    AddTriangle(p, common_segment, current_triangle, neighbour_triangle);
  } else {
    q.push(neighbour_triangle);
  }
}

void ConflictGraph::AddPoint(Point p) {
  size_t vision_face = FindVisionFace(p);
  if (vision_face == static_cast<size_t>(inf)) {
    return;
  }
  last_added_faces_.clear();
  queue<size_t> q;
  q.push(vision_face);
  while (!q.empty()) {
    size_t current_triangle = q.front();
    q.pop();
    if (convex_hill_.find(current_triangle) == convex_hill_.end()) {
      continue;
    }
    ProcessNeighbour(p, current_triangle, q,
                     convex_hill_[current_triangle].neighbour1_,
                     convex_hill_[current_triangle].intersect_neighbour1_);
    ProcessNeighbour(p, current_triangle, q,
                     convex_hill_[current_triangle].neighbour2_,
                     convex_hill_[current_triangle].intersect_neighbour2_);
    ProcessNeighbour(p, current_triangle, q,
                     convex_hill_[current_triangle].neighbour3_,
                     convex_hill_[current_triangle].intersect_neighbour3_);
    convex_hill_.erase(current_triangle);
  }
}

vector<Triple<size_t>> ConflictGraph::OutputHill() {
  vector<Triple<size_t>> result;
  for (auto i = convex_hill_.begin(); i != convex_hill_.end(); ++i) {
    result.emplace_back(i->second.v1_.index_, i->second.v2_.index_,
                        i->second.v3_.index_);
  }
  return result;
}

bool Compare(Point p1, Point p2) {
  return p1.x_ < p2.x_ || (fabs(p1.x_ - p2.x_) < eps && p1.y_ < p2.y_) ||
         (fabs(p1.x_ - p2.x_) < eps && fabs(p1.y_ - p2.y_) < eps &&
          p1.z_ < p2.z_);
}

bool CompareByAngle(Point p1, Point p2) {
  return p1.y_ / p1.x_ < p2.y_ / p2.x_;
}

void SortByAngle(vector<Point> &points) {
  Point first = points[0];
  for (size_t i = 1; i < points.size(); ++i) {
    points[i] = points[i] - first;
  }
  sort(points.begin() + 1, points.end(), CompareByAngle);
  for (size_t i = 1; i < points.size(); ++i) {
    points[i] = points[i] + first;
  }
}

double VectorMult2(Point p1, Point p2) { return p1.x_ * p2.y_ - p1.y_ * p2.x_; }

vector<size_t> PlainConvexHull(vector<Point> &points) {
  stack<Point> hull;
  points.push_back(points[0]);
  hull.push(points[0]);
  hull.push(points[1]);
  Point last_point1 = points[0];
  Point last_point2 = points[1];
  for (size_t i = 2; i < points.size(); ++i) {
    while (VectorMult2(points[i] - last_point2, last_point1 - last_point2) <
           0.0) {
      last_point2 = last_point1;
      hull.pop();
      hull.pop();
      last_point1 = hull.top();
      hull.push(last_point2);
    }
    hull.push(points[i]);
    last_point1 = last_point2;
    last_point2 = points[i];
  }
  vector<size_t> res;
  while (hull.size() != 1) {
    res.push_back(hull.top().index_);
    hull.pop();
  }
  points.pop_back();
  return res;
}

double CountAvgVoronoy(const vector<Point> &points) {
  if (points.size() < count_faces_of_tetrahedron) {
    return 0.0;
  }
  auto points_by_angle = points;
  SortByAngle(points_by_angle);
  ConflictGraph dim3_hull(points);
  vector<int> polygon_deg(points.size(), 0);
  vector<Triple<size_t>> faces = dim3_hull.OutputHill();
  for (size_t i = 0; i < faces.size(); ++i) {
    ++polygon_deg[faces[i].first_];
    ++polygon_deg[faces[i].second_];
    ++polygon_deg[faces[i].third_];
  }
  vector<size_t> non_polygon_points = PlainConvexHull(points_by_angle);
  if (non_polygon_points.size() == points.size()) {
    return 0.0;
  }
  vector<bool> is_polygon(points.size(), true);
  for (size_t i = 0; i < non_polygon_points.size(); ++i) {
    is_polygon[non_polygon_points[i]] = false;
  }
  int count_segments = 0;
  for (size_t i = 0; i < points.size(); ++i) {
    if (is_polygon[i]) {
      count_segments += polygon_deg[i];
    }
  }
  return static_cast<double>(count_segments) /
         static_cast<double>(points.size() - non_polygon_points.size());
}

int main() {
  vector<Point> points;
  double x;
  double y;
  int i = 0;
  while (cin >> x) {
    cin >> y;
    points.emplace_back(x, y, x * x + y * y, i);
    ++i;
  }
  sort(points.begin(), points.end(), Compare);
  std::cout.precision(precision);
  cout << CountAvgVoronoy(points) << endl;
  return 0;
}
