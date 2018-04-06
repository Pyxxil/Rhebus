#include <QPainter>

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
