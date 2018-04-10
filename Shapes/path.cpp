#include <QDebug>
#include <QPainter>
#include <QtMath>

#include "path.hpp"

Path::Path(const QList<QPoint> &p) : Shape(), mPoints(p) {
  for (int i = 0; i < p.length() - 1; ++i) {
    mLines.push_back(QLine(p[i], p[i + 1]));
  }
}

void Path::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  for (int i = 0; i < mLines.length(); ++i) {
    painter->drawLine(mLines[i]);
  }
}

void Path::redraw(QPainter *painter) {
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  painter->restore();
}

void Path::move(const QPoint &point, QPainter *painter) {
  int dy = qAbs(point.y() - movingStart.y());
  int dx = qAbs(point.x() - movingStart.x());

  if (point.x() < movingStart.x()) {
    dx = -dx;
  }

  if (point.y() < movingStart.y()) {
    dy = -dy;
  }

  for (auto &line : mLines) {
    line.translate(dx, dy);
  }

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

bool Path::contains(const QPoint &point) const {
  for (int i = 0; i < mLines.length(); ++i) {
    if (distance(mLines[i].p1(), mLines[i].p2(), point) <=
        (pen.width() / 4.0)) {
      return true;
    }
  }

  return false;
}
