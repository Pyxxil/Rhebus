#include "layeritem.hpp"

LayerItem::LayerItem(RootItem *parent, const QString &tName)
    : RootItem(QVector<QVariant>() << tName, parent) {}
