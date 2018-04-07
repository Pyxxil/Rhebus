#include <QDebug>
#include <QMenu>
#include <QMouseEvent>

#include "definitionview.hpp"
#include "rootitem.hpp"

DefinitionView::DefinitionView(QWidget *parent) : QTreeView(parent) {
  setContextMenuPolicy(Qt::CustomContextMenu);
}

void DefinitionView::mousePressEvent(QMouseEvent *event) {
  QModelIndex index = indexAt(event->pos());

  if (index.isValid()) {
    if (event->button() == Qt::LeftButton) {
      if (static_cast<RootItem *>(index.internalPointer())->isDescription()) {
        emit render(static_cast<DescriptionItem *>(index.internalPointer()));
      }
    }
  }

  QTreeView::mousePressEvent(event);
}
