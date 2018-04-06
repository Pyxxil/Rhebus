#ifndef DEFINITIONITEM_HPP
#define DEFINITIONITEM_HPP

#include <QList>
#include <QVariant>
#include <QVector>

class DefinitionItem
{
public:
  explicit DefinitionItem(const QVector<QVariant> &data, DefinitionItem *parent);
  ~DefinitionItem();

  DefinitionItem *child(int number);
  DefinitionItem *parent();
  int childCount() const;
  int columnCount() const;
  int childNumber() const;

  QVariant data(int column) const;

  bool insertChildren(int position, int count, int columns);
  bool insertColumns(int position, int columns);
  bool removeChildren(int position, int count);
  bool removeColumns(int position, int columns);
  bool setData(int column, const QVariant &value);

private:
  QList<DefinitionItem *> childItems;
  QVector<QVariant> itemData;
  DefinitionItem *parentItem;
};

#endif // DEFINITIONITEM_HPP
