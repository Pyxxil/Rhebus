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

void Rectangle::move(const QPoint &, QPainter *) {}

static inline qreal distance(const QPoint &a, const QPoint &b) {
  const qreal dx = (a.x() - b.x());
  const qreal dy = (a.y() - b.y());
  return qSqrt(dx * dx + dy * dy);
}

bool Rectangle::contains(const QPoint &point) const {
  const auto &topLeft = rect.topLeft();
  const auto &topRight = rect.topRight();
  const auto &bottomLeft = rect.bottomLeft();
  const auto &bottomRight = rect.bottomRight();

  return (distance(topLeft, point) + distance(topRight, point) ==
          distance(topLeft, topRight)) ||
         (distance(topRight, point) + distance(bottomRight, point) ==
          distance(topRight, bottomRight)) ||
         (distance(bottomRight, point) + distance(bottomLeft, point) ==
          distance(bottomRight, bottomLeft)) ||
         (distance(topLeft, point) + distance(bottomLeft, point) ==
          distance(bottomLeft, topLeft));
}
