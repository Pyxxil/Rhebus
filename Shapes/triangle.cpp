#include <QDebug>
#include <QPainter>

#include "triangle.hpp"

Triangle::Triangle(const QRect &tRect) : Shape(), rect(tRect) {}

void Triangle::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  QPainterPath path;
  path.moveTo(rect.left() + (rect.width() / 2), rect.top());
  path.lineTo(rect.bottomLeft());
  path.lineTo(rect.bottomRight());
  path.lineTo(rect.left() + (rect.width() / 2), rect.top());

  painter->drawPath(path);
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
