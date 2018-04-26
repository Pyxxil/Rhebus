#include "descriptionitem.hpp"
#include "shapeitem.hpp"

#include <QPainter>

DescriptionItem::DescriptionItem(ShapeItem *parent)
    : RootItem(QVector<QVariant>() << "draw", parent), mParent{parent} {}

void DescriptionItem::render(QPainter *painter) {
  foreach (QSharedPointer<Shape> shape, mShapes) { shape->redraw(painter); }
}
