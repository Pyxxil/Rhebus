#ifndef ROOTDEFINITION_HPP
#define ROOTDEFINITION_HPP

#include "rootitem.hpp"

class DefinitionItem;

class RootDefinition : public RootItem {
public:
  explicit RootDefinition(RootItem *parent);
  ~RootDefinition() = default;

  void addDefinition(const QString &name);
  DefinitionItem *definition(int row) const;

  const QList<DefinitionItem *> definitions() const { return mDefinitions; }

private:
  QList<DefinitionItem *> mDefinitions;
};

#endif // ROOTDEFINITION_HPP
