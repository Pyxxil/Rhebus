#ifndef DEFINITIONITEM_HPP
#define DEFINITIONITEM_HPP

#include <QList>
#include <QVariant>
#include <QVector>

#include "rootdefinition.hpp"
#include "rootitem.hpp"

class Shape;
class DescriptionItem;

class DefinitionItem : public RootItem {
public:
  explicit DefinitionItem(RootDefinition *parent, const QString &tName);
  ~DefinitionItem() { qDeleteAll(descriptions); }

  RootDefinition *parent() { return mParent; }
  const QString &name() const { return mName; }

  void addDescription(const QList<QSharedPointer<Shape>> &);

  DescriptionItem *description(int number);
  QVariant data(int column) const;
  int childCount() const;
  int childNumber();
  int columnCount() const;

private:
  RootDefinition *mParent;
  QString mName;

  QList<DescriptionItem *> descriptions;
};

#endif // DEFINITIONITEM_HPP
