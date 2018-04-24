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
  Rectangle(Rectangle &&rhs) = default;

  Rectangle &operator=(const Rectangle &rhs) = default;
  Rectangle &operator=(Rectangle &&rhs) noexcept = default;

  void draw(QPainter *painter) override;
  void redraw(QPainter *painter) override;
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

  Rectangle *clone() const final { return new Rectangle(*this); }
  QString name() const final { return "Rectangle"; }

  Rectangle *scaled() final;
  Rectangle *rotated() final;
  Rectangle *moveToRealZero(const QPoint &) final;
  Rectangle *placeAt() final;

  void __move(const QPoint &point) final;

private:
  QRect rect;
};

#endif // RECTANGLE_HPP
