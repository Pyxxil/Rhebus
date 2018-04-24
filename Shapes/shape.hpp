#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QBrush>
#include <QPen>

class QPainter;

class Shape {
public:
  Shape();
  Shape(const Shape &rhs) = default;
  Shape(Shape &&rhs) = default;

  Shape &operator=(const Shape &rhs) = default;
  Shape &operator=(Shape &&rhs) noexcept = default;

  enum ShapeType { Triangle, Line, Path, Rectangle, None };

  virtual ~Shape() {}

  virtual void draw(QPainter *) {}
  virtual void redraw(QPainter *) {}
  virtual void move(const QPoint &, QPainter *) {}
  virtual void setMovingStart(const QPoint &start) { movingStart = start; }

  virtual Shape *scaled() = 0;
  virtual Shape *rotated() = 0;
  virtual Shape *moveToRealZero(const QPoint &) = 0;
  virtual Shape *placeAt() = 0;

  virtual ShapeType type() { return None; }

  const QPoint &moveFrom() const { return movingStart; }

  void setPen(const QPen &pen) {
    this->pen = pen;
    this->penWidth = pen.width();
  }
  void setBrush(const QBrush &brush) { this->brush = brush; }

  virtual bool contains(const QPoint &) const { return false; }
  virtual Shape *clone() const = 0;

  virtual QString name() const = 0;

  virtual void __move(const QPoint &point) = 0;

protected:
  QPen pen;
  QBrush brush;
  int penWidth;
  QPoint movingStart;
};

#endif // SHAPE_HPP
