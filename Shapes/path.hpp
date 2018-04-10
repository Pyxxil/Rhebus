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

  const QList<QLine> &lines() const { return mLines; }
  const QList<QPoint> &points() const { return mPoints; }

private:
  QList<QLine> mLines;
  QList<QPoint> mPoints;
};

#endif // POINTS_HPP
