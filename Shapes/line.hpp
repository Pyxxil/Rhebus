#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

class Line : public Shape {
public:
  Line(const QPoint &p, const QPoint &l);
  ~Line() = default;

  Line(const Line &rhs) = default;
  Line(Line &&rhs) = default;

  Line &operator=(const Line &rhs) = default;
  Line &operator=(Line &&rhs) noexcept = default;

  void draw(QPainter *);
  void redraw(QPainter *);
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

  Line *clone() const final { return new Line(*this); }
  QString name() const final { return "Line"; }

  Line *scaled() final;
  Line *rotated() final;
  Line *moveToRealZero(const QPoint &) final;
  Line *placeAt() final;

  void __move(const QPoint &point) final;

private:
  QLine line;
};

#endif // LINE_HPP
