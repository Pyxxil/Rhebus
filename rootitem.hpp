#ifndef ROOTITEM_HPP
#define ROOTITEM_HPP

#include <QList>

class DefinitionItem;

class RootItem
{
public:
  explicit RootItem(const QVector<QVariant> &data, RootItem *parent);
  ~RootItem();

  DefinitionItem *child(int number);
  RootItem *parent();
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
  RootItem *parentItem;
};

#endif // ROOTITEM_HPP
