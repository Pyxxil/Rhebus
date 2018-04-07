#include "rootdefinition.hpp"
#include "definitionitem.hpp"

#include <QDebug>

RootDefinition::RootDefinition(RootItem *parent)
    : RootItem(QVector<QVariant>() << "Definitions", parent) {}

void RootDefinition::addDefinition(const QString &name) {
  DefinitionItem *def = new DefinitionItem(this, name);
  mDefinitions.append(def);
  children().append(def);
}

DefinitionItem *RootDefinition::definition(int row) const {
  return definitions().at(row);
}
