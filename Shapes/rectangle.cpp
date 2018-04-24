#include "rectangle.hpp"

#include <QDebug>
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

void Rectangle::__move(const QPoint &point) {
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  rect.translate(dx, dy);
}

void Rectangle::move(const QPoint &point, QPainter *painter) {
  __move(point);
  setMovingStart(point);
  redraw(painter);
}

bool Rectangle::contains(const QPoint &point) const {
  return rect.contains(point);
}

Rectangle *Rectangle::scaled() { return this; }

Rectangle *Rectangle::rotated() { Rectangle *rec = clone(); }

Rectangle *Rectangle::moveToRealZero(const QPoint &realZero) {
  Rectangle *rec = clone();
  rec->setMovingStart(QPoint(0, 0));
  rec->__move(realZero);
  return rec;
}

Rectangle *Rectangle::placeAt() { return this; }
