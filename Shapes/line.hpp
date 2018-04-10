#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

class Line : public Shape {
public:
  explicit Line(const QPoint &p, const QPoint &l);
  ~Line() = default;

  Line(const Line &rhs) = default;
  Line(Line &&rhs) noexcept = default;

  Line &operator=(const Line &rhs) = default;
  Line &operator=(Line &&rhs) noexcept = default;

  void draw(QPainter *);
  void redraw(QPainter *);
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

private:
  QPoint from;
  QPoint to;
};

#endif // LINE_HPP
