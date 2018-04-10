#include <QPainter>
#include <QtMath>

#include "line.hpp"

Line::Line(const QPoint &p, const QPoint &l) : Shape(), line(p, l) {}

void Line::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  painter->drawLine(line);
}

void Line::redraw(QPainter *painter) {
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  painter->restore();
}

void Line::move(const QPoint &point, QPainter *painter) {
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  line.translate(dx, dy);
  setMovingStart(point);
  redraw(painter);
}

static inline qreal distance(const QPoint &pa, const QPoint &pb,
                             const QPoint &pc) {
  const qreal a = pb.y() - pc.y();
  const qreal b = pc.x() - pb.x();
  const qreal c = pb.x() * pc.y() - pc.x() * pb.y();

  return qAbs(a * pa.x() + b * pa.y() + c) / qSqrt(a * a + b * b);
}

bool Line::contains(const QPoint &point) const {
  return distance(line.p1(), line.p2(), point) <= (pen.width() / 2.0);
}
