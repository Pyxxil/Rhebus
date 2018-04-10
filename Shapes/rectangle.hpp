#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

#include <QRect>

class QPainter;

class Rectangle : public Shape {
public:
  explicit Rectangle(const QRect &);
  ~Rectangle() = default;

  Rectangle(const Rectangle &rhs) = default;
  Rectangle(Rectangle &&rhs) noexcept = default;

  Rectangle &operator=(const Rectangle &rhs) = default;
  Rectangle &operator=(Rectangle &&rhs) noexcept = default;

  void draw(QPainter *painter) override;
  void redraw(QPainter *painter) override;
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

private:
  QRect rect;
};

#endif // RECTANGLE_HPP
