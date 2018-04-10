#ifndef ROOTDEFINITION_HPP
#define ROOTDEFINITION_HPP

#include "rootitem.hpp"

class ShapeItem;

class RootDefinitionItem : public RootItem {
public:
  explicit RootDefinitionItem(RootItem *parent);
  ~RootDefinitionItem() = default;

  void addDefinition(const QString &name);
  ShapeItem *definition(int row) const;

  const QList<ShapeItem *> definitions() const { return mDefinitions; }

private:
  QList<ShapeItem *> mDefinitions;
};

#endif // ROOTDEFINITION_HPP
