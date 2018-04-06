#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <QRect>

#include "shape.hpp"

class Triangle : public Shape
{
public:
  explicit Triangle(const QRect &);
  ~Triangle() = default;

  void draw(QPainter *) override;
  void redraw(QPainter *) override;

private:
  QRect rect;
};

#endif // TRIANGLE_HPP
