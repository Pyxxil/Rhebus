#include <QDebug>
#include <QPainter>
#include <QtMath>

#include "path.hpp"

Path::Path(const QList<QPoint> &p) : Shape(), points(p) {}

void Path::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  for (int i = 0; i < points.length() - 1; ++i) {
    painter->drawLine(points[i], points[i + 1]);
  }
}

void Path::redraw(QPainter *painter) {
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  painter->restore();
}

void Path::move(const QPoint &, QPainter *) {}

inline qreal distance(const QPoint &a, const QPoint &b) {
  const qreal dx = (a.x() - b.x());
  const qreal dy = (a.y() - b.y());
  return qSqrt(dx * dx + dy * dy);
}

bool Path::contains(const QPoint &point) const {
  for (int i = 0; i < points.length() - 1; ++i) {
    if ((distance(points[i], point) + distance(points[i + 1], point) -
         distance(points[i], points[i + 1])) <= (pen.widthF())) {
      return true;
    }
  }

  return false;
}
