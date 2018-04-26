#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QBrush>
#include <QPen>

class QPainter;

/*!
 * \brief Create a pair of the max and minimum values between a and b
 * \param a
 * \param b
 * \return Returns a std::pair of the form { min, max }
 */
constexpr std::pair<int, int> min_max_pair(int a, int b) {
  return a < b ? std::make_pair(a, b) : std::make_pair(b, a);
}

constexpr std::pair<QPoint, QPoint> min_max_pair(QPoint a, QPoint b) {
  auto &&[min_x, max_x] = min_max_pair(a.x(), a.y());
  auto &&[min_y, max_y] = min_max_pair(a.y(), b.y());
  return std::make_pair(QPoint(min_x, min_y), QPoint(max_x, max_y));
}

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
