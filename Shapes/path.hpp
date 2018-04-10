#ifndef POINTS_HPP
#define POINTS_HPP

#include <QList>
#include <QPoint>

#include "shape.hpp"

class Path : public Shape {
public:
  Path(const QList<QPoint> &);
  ~Path() = default;

  Path(const Path &rhs) = default;
  Path(Path &&rhs) noexcept = default;

  Path &operator=(const Path &rhs) = default;
  Path &operator=(Path &&rhs) noexcept = default;

  void draw(QPainter *) override;
  void redraw(QPainter *) override;
  void move(const QPoint &, QPainter *) final;

  bool contains(const QPoint &) const final;

  const QList<QPoint> &allPoints() const { return points; }

private:
  QList<QPoint> points;
};

#endif // POINTS_HPP
