#include <QDebug>
#include <QPainter>
#include <QtMath>

#include "path.hpp"

Path::Path(const QList<QPoint> &p) : mPoints(p) {
  for (int i = 0; i < p.length() - 1; ++i) {
    mLines.push_back(QLine(p[i], p[i + 1]));
  }

  auto &&[min_x, max_x] =
      min_max_pair(mLines.front().x1(), mLines.front().x2());
  auto &&[min_y, max_y] =
      min_max_pair(mLines.front().y1(), mLines.front().y2());

  for (int i = 1; i < mLines.length(); ++i) {
    const auto &line = mLines[i];
    auto &&[_min_x, _max_x] = min_max_pair(line.x1(), line.x2());
    auto &&[_min_y, _max_y] = min_max_pair(line.y1(), line.y2());

    if (_min_x < min_x) {
      min_x = _min_x;
    }
    if (_max_x > max_x) {
      max_x = _max_x;
    }
    if (_min_y < min_y) {
      min_y = _min_y;
    }
    if (_max_y > max_y) {
      max_y = _max_y;
    }
  }

  height = max_y - min_y;
  width = max_x - min_x;

  topLeft = QPoint(min_x, min_y);
  bottomRight = QPoint(max_x, max_y);
}

void Path::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  for (auto &&mLine : mLines) {
    painter->drawLine(mLine);
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

bool Path::contains(const QPoint &point) const {
  for (int i = 0; i < mLines.length(); ++i) {
    auto d = distance(mLines[i].p1(), mLines[i].p2(), point);
    if (d <= (pen.width() / 2.0)) {
      QRect r(mLines[i].p1(), mLines[i].p2());
      r.setWidth(static_cast<int>(pen.width() / 2.0));
      r.setHeight(static_cast<int>(pen.width() / 2.0));
      if (r.contains(point)) {
        return true;
      }
    }
  }

  return false;
}

Path *Path::scaled() { return this; }

Path *Path::rotated() { return this; }

Path *Path::moveToRealZero(const QPoint &realZero) {
  Path *p = clone();
  QRect rect(topLeft, bottomRight);
  qDebug() << "rect is:" << rect;
  qDebug() << "Top Left, Bottom Right" << topLeft << ',' << bottomRight;
  p->setMovingStart(rect.bottomLeft());
  p->__move(QPoint(realZero.x() + topLeft.x(),
                   realZero.y() - (400 - bottomRight.y())));
  return p;
}

Path *Path::placeAt() { return this; }

void Path::__move(const QPoint &point) {
  qDebug() << "Moving to" << point;
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
}

int Path::getHeight() const { return height; }

void Path::setHeight(int value) { height = value; }

int Path::getWidth() const { return width; }

void Path::setWidth(int value) { width = value; }
