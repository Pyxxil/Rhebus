#ifndef ROOTDEFINITION_HPP
#define ROOTDEFINITION_HPP

#include "rootitem.hpp"

class DefinitionItem;

class RootDefinitionItem : public RootItem {
public:
  explicit RootDefinitionItem(RootItem *parent);
  ~RootDefinitionItem() = default;

  void addDefinition(const QString &name);
  DefinitionItem *definition(int row) const;

  const QList<DefinitionItem *> definitions() const { return mDefinitions; }

private:
  QList<DefinitionItem *> mDefinitions;
};

#endif // ROOTDEFINITION_HPP
