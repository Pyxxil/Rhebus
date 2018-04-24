#include "objectitem.hpp"

ObjectItem::ObjectItem(LayerItem *parent, const QString &)
    : RootItem(QVector<QVariant>() << QString(), parent),
      mName(QString("Object%1").arg(objectCount)) {
  ++objectCount;
  setData(0, mName);
}

const QList<QSharedPointer<Shape>> &ObjectItem::shapes() const {
  return mShapes;
}

void ObjectItem::setShapes(const QList<QSharedPointer<Shape>> &shapes) {
  mShapes = shapes;
}

qulonglong ObjectItem::objectCount{0};
