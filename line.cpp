#include <QPainter>

#include "line.hpp"

Line::Line(const QPoint &p, const QPoint &l) : Shape(), from(p), to(l) {}

void Line::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  painter->drawLine(from, to);
}

void Line::redraw(QPainter *painter) {
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  painter->restore();
}
