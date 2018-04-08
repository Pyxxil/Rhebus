#ifndef DEFINITIONITEM_HPP
#define DEFINITIONITEM_HPP

#include <QList>
#include <QVariant>
#include <QVector>

#include "rootdefinitionitem.hpp"
#include "rootitem.hpp"

class Shape;
class DescriptionItem;

class DefinitionItem : public RootItem {
public:
  explicit DefinitionItem(RootDefinitionItem *parent, const QString &tName);
  ~DefinitionItem() { qDeleteAll(descriptions); }

  RootDefinitionItem *parent() { return mParent; }
  const QString &name() const { return mName; }

  void addDescription(const QList<QSharedPointer<Shape>> &);

  DescriptionItem *description(int number);
  QVariant data(int column) const;
  int childCount() const;
  int childNumber();
  int columnCount() const;

private:
  RootDefinitionItem *mParent;
  QString mName;

  QList<DescriptionItem *> descriptions;
};

#endif // DEFINITIONITEM_HPP
