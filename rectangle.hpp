#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

#include <QRect>

class QPainter;

class Rectangle : public Shape
{
public:
  explicit Rectangle(const QRect &);
  ~Rectangle() = default;

  void draw(QPainter *painter) override;
  void redraw(QPainter *painter) override;

private:
  QRect rect;
};

#endif // RECTANGLE_HPP
