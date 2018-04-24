#ifndef DEFINITIONITEM_HPP
#define DEFINITIONITEM_HPP

#include <QList>
#include <QVariant>
#include <QVector>

#include "rootdefinitionitem.hpp"
#include "rootitem.hpp"

class Shape;
class DescriptionItem;

class ShapeItem : public RootItem {
public:
  explicit ShapeItem(RootDefinitionItem *parent, const QString &tName);
  ~ShapeItem();

  const QString &name() const { return mName; }

  void addDescription(const QList<QSharedPointer<Shape>> &);

  DescriptionItem *description(int number);
  QVariant data(int column) const;
  int childCount() const;
  int childNumber();
  int columnCount() const { return 1; }

  bool isDefinition() const final { return true; }

private:
  QString mName;

  QList<DescriptionItem *> descriptions;
};

#endif // DEFINITIONITEM_HPP
