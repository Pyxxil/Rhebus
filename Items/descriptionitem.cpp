#include "descriptionitem.hpp"
#include "definitionitem.hpp"

#include <QPainter>

DescriptionItem::DescriptionItem(DefinitionItem *parent)
    : RootItem(QVector<QVariant>() << "draw", parent) {}

void DescriptionItem::render(QPainter *painter) {
  foreach (QSharedPointer<Shape> shape, mShapes) { shape->redraw(painter); }
}
