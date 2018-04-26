#include <QDebug>
#include <QPainter>
#include <QPolygon>

#include "triangle.hpp"

Triangle::Triangle(const QRect &tRect)
    : Shape(),
      polygon(QVector<QPoint>()
              << QPoint(tRect.left() + (tRect.width() / 2), tRect.top())
              << tRect.bottomLeft() << tRect.bottomRight()) {}

void Triangle::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  painter->drawPolygon(polygon);
}

/** Redraw this shape. This should only ever happen when the user has lifted
 * their mouse button.
 * @param painter The canvas to draw on
 */
void Triangle::redraw(QPainter *painter) {
  // Of course, we need to save the current painter because we do update it.
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  // Then restore it when returning.
  painter->restore();
}

void Triangle::move(const QPoint &point, QPainter *painter) {
  __move(point);
  setMovingStart(point);
  redraw(painter);
}

bool Triangle::contains(const QPoint &point) const {
  return polygon.containsPoint(point, Qt::OddEvenFill);
}

Triangle *Triangle::scaled() { return this; }

Triangle *Triangle::rotated() { return this; }

Triangle *Triangle::moveToRealZero(const QPoint &realZero) {
  Triangle *t = clone();
  t->setMovingStart(polygon.boundingRect().bottomLeft());
  t->__move(QPoint(realZero.x() + polygon.boundingRect().left(),
                   realZero.y() - (400 - polygon.boundingRect().right())));
  return t;
}

Triangle *Triangle::placeAt() { return this; }

void Triangle::__move(const QPoint &point) {
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  polygon.translate(dx, dy);
}
