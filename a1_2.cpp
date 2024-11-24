#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <iomanip>

struct Circle {
  double x, y, r;
};

bool isInnerCircle(const double px, const double py, const Circle &c) {
  const double dx = px - c.x;
  const double dy = py - c.y;
  return dx * dx + dy * dy <= c.r * c.r;
}

bool isInIntersection(const double px, const double py, const std::vector<Circle> &cs) {
  for (const auto &c: cs) {
    if (!isInnerCircle(px, py, c)) {
      return false;
    }
  }
  return true;
}

double monteCarloEstimate(const std::vector<Circle> &cs, int p) {
  const double minX = 2 - sqrt(5) / 2,
      minY = 1.5 - sqrt(5) / 2,
      maxX = 2,
      maxY = 2;
  std::mt19937 gen(100);
  std::uniform_real_distribution<double> dX(minX, maxX);
  std::uniform_real_distribution<double> dY(minY, maxY);
  int count = 0;
  for (int i = 0; i < p; ++i) {
    double px = dX(gen);
    double py = dY(gen);
    if (isInIntersection(px, py, cs)) {
      ++count;
    }
  }
  double a = (maxX - minX) * (maxY - minY);
  return a * count / p;
}

int main() {
  std::vector<Circle> circles = {
    {1, 1, 1},
    {1.5, 2, std::sqrt(5) / 2},
    {2, 1.5, std::sqrt(5) / 2}
  };
  const int step = 500;
  const int maxPoints = 100000;
  for (int numPoints = 100; numPoints <= maxPoints; numPoints += step) {
    double estimatedArea = monteCarloEstimate(circles, numPoints);
    std::cout << numPoints << " " << std::fixed << std::setprecision(6) << estimatedArea << std::endl;
  }

  return 0;
}
