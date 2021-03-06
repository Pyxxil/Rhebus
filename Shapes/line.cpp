#include <QDebug>
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
  __move(point);
  setMovingStart(point);
  redraw(painter);
}

static inline qreal distance(const QPoint &pb, const QPoint &pc,
                             const QPoint &pa) {
  const qreal a = pb.y() - pc.y();
  const qreal b = pc.x() - pb.x();
  const qreal c = pb.x() * pc.y() - pc.x() * pb.y();

  return qAbs(a * pa.x() + b * pa.y() + c) / qSqrt(a * a + b * b);
}

bool Line::contains(const QPoint &point) const {
  auto d = distance(line.p1(), line.p2(), point);
  return d <= (pen.width() / 2.0) &&
         QRect(line.p1(), line.p2()).contains(point);
}

Line *Line::scaled() { return this; }

Line *Line::rotated() { return this; }

Line *Line::moveToRealZero(const QPoint &) { return this; }

Line *Line::placeAt() { return this; }

void Line::__move(const QPoint &point) {
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  line.translate(dx, dy);
}
