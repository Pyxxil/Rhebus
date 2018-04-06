#ifndef LINE_HPP
#define LINE_HPP

#include "shape.hpp"

class Line : public Shape
{
public:
  explicit Line(const QPoint &p, const QPoint &l);
  ~Line() = default;

  void draw(QPainter *);
  void redraw(QPainter *);

private:
  QPoint from;
  QPoint to;
};

#endif // LINE_HPP
