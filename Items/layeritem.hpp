#ifndef LAYERITEM_HPP
#define LAYERITEM_HPP

#include "rootitem.hpp"

class LayerItem : public RootItem {
public:
  explicit LayerItem(RootItem *parent, const QString &tName);
  ~LayerItem() = default;

  bool isLayer() const final { return true; }
};

#endif // LAYERITEM_HPP
