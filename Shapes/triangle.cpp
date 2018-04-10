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
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  polygon.translate(dx, dy);
  setMovingStart(point);
  redraw(painter);
}

bool Triangle::contains(const QPoint &point) const {
  qDebug() << "My polygon:" << polygon;
  return polygon.containsPoint(point, Qt::OddEvenFill);
}
