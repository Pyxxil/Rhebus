#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QBrush>
#include <QPen>

class QPainter;

class Shape {
public:
  Shape();
  virtual ~Shape() {}

  virtual void draw(QPainter *) = 0;
  virtual void redraw(QPainter *) = 0;

protected:
  QPen pen;
  QBrush brush;
  int penWidth;

private:
};

#endif // SHAPE_HPP
