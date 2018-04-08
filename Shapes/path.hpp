#ifndef POINTS_HPP
#define POINTS_HPP

#include <QList>
#include <QPoint>

#include "shape.hpp"

class Path : public Shape {
public:
  Path(const QList<QPoint> &);
  ~Path() = default;

  void draw(QPainter *) override;
  void redraw(QPainter *) override;

  const QList<QPoint> &allPoints() const { return points; }

private:
  QList<QPoint> points;
};

#endif // POINTS_HPP
