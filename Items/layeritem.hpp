#ifndef LAYERITEM_HPP
#define LAYERITEM_HPP

#include "rootitem.hpp"

class LayerItem : public RootItem {
public:
  explicit LayerItem(RootItem *parent, const QString &tName);
  ~LayerItem() = default;
};

#endif // LAYERITEM_HPP
