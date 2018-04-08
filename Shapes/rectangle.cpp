#include "rectangle.hpp"

#include <QPainter>

Rectangle::Rectangle(const QRect &tRect) : Shape(), rect(tRect) {}

void Rectangle::draw(QPainter *painter) {
  pen = painter->pen();
  brush = painter->brush();

  painter->drawRect(rect);
}

void Rectangle::redraw(QPainter *painter) {
  painter->save();

  painter->setPen(pen);
  painter->setBrush(brush);
  draw(painter);

  painter->restore();
}
