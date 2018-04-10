#include "rootdefinitionitem.hpp"
#include "shapeitem.hpp"

#include <QDebug>

RootDefinitionItem::RootDefinitionItem(RootItem *parent)
    : RootItem(QVector<QVariant>() << "Shapes", parent) {}

void RootDefinitionItem::addDefinition(const QString &name) {
  ShapeItem *def = new ShapeItem(this, name);
  mDefinitions.append(def);
  children().append(def);
}

ShapeItem *RootDefinitionItem::definition(int row) const {
  return definitions().at(row);
}
