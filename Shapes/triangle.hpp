#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <QRect>

#include "shape.hpp"

class Triangle : public Shape {
public:
  explicit Triangle(const QRect &);
  ~Triangle() = default;

  Triangle(const Triangle &rhs) = default;
  Triangle(Triangle &&rhs) noexcept = default;

  Triangle &operator=(const Triangle &rhs) = default;
  Triangle &operator=(Triangle &&rhs) noexcept = default;

  void draw(QPainter *) override;
  void redraw(QPainter *) override;
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

private:
  QPolygon polygon;
};

#endif // TRIANGLE_HPP
