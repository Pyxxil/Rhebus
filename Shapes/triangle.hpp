#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <QRect>

#include "shape.hpp"

class Triangle : public Shape {
public:
  explicit Triangle(const QRect &);
  ~Triangle() override = default;

  Triangle(const Triangle &rhs) = default;
  Triangle(Triangle &&rhs) = default;

  Triangle &operator=(const Triangle &rhs) = default;
  Triangle &operator=(Triangle &&rhs) noexcept = default;

  void draw(QPainter *) override;
  void redraw(QPainter *) override;
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

  Triangle *clone() const final { return new Triangle(*this); }
  QString name() const final { return "Triangle"; }

  Triangle *scaled() final;
  Triangle *rotated() final;
  Triangle *moveToRealZero(const QPoint &) final;
  Triangle *placeAt() final;

  void __move(const QPoint &point) final;

private:
  QPolygon polygon;
};

#endif // TRIANGLE_HPP
