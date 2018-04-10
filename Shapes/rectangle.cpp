#include "rectangle.hpp"

#include <QPainter>
#include <QtMath>

Rectangle::Rectangle(const QRect &tRect) : Shape(), rect(tRect) {}

void Rectangle::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  painter->drawRect(rect);
}

void Rectangle::redraw(QPainter *painter) {
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  painter->restore();
}

void Rectangle::move(const QPoint &point, QPainter *) {
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  rect.translate(dx, dy);
  setMovingStart(point);
  redraw(painter);
}

static inline qreal distance(const QPoint &a, const QPoint &b) {
  const qreal dx = (a.x() - b.x());
  const qreal dy = (a.y() - b.y());
  return qSqrt(dx * dx + dy * dy);
}

bool Rectangle::contains(const QPoint &point) const {
  return rect.contains(point);
}
