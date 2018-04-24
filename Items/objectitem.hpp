#ifndef OBJECTITEM_HPP
#define OBJECTITEM_HPP

#include "Shapes/shape.hpp"
#include "layeritem.hpp"
#include "rootitem.hpp"

class ObjectItem : public RootItem {
public:
  explicit ObjectItem(LayerItem *parent, const QString &);

  const QList<QSharedPointer<Shape>> &shapes() const;
  void setShapes(const QList<QSharedPointer<Shape>> &shapes);

private:
  static qulonglong objectCount;
  QString mName;

  QList<QSharedPointer<Shape>> mShapes;
};

#endif // OBJECTITEM_HPP
