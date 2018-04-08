#include "rootdefinitionitem.hpp"
#include "definitionitem.hpp"

#include <QDebug>

RootDefinitionItem::RootDefinitionItem(RootItem *parent)
    : RootItem(QVector<QVariant>() << "Definitions", parent) {}

void RootDefinitionItem::addDefinition(const QString &name) {
  DefinitionItem *def = new DefinitionItem(this, name);
  mDefinitions.append(def);
  children().append(def);
}

DefinitionItem *RootDefinitionItem::definition(int row) const {
  return definitions().at(row);
}
