#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QBrush>
#include <QPen>

class QPainter;

class Shape {
public:
  Shape();
  Shape(const Shape &rhs) = default;
  Shape(Shape &&rhs) noexcept = default;

  Shape &operator=(const Shape &rhs) = default;
  Shape &operator=(Shape &&rhs) noexcept = default;

  enum ShapeType { Triangle, Line, Path, Rectangle, None };

  virtual ~Shape() {}

  virtual void draw(QPainter *) {}
  virtual void redraw(QPainter *) {}
  virtual void move(const QPoint &, QPainter *) {}
  virtual void setMovingStart(const QPoint &start) { movingStart = start; }

  virtual ShapeType type() { return None; }

  const QPoint &moveFrom() const { return movingStart; }

  void setPen(const QPen &pen) {
    this->pen = pen;
    this->penWidth = pen.width();
  }
  void setBrush(const QBrush &brush) { this->brush = brush; }

  virtual bool contains(const QPoint &) { return false; }

protected:
  QPen pen;
  QBrush brush;
  int penWidth;
  QPoint movingStart;
};

#endif // SHAPE_HPP
