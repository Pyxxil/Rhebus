#ifndef DEFINITIONVIEW_HPP
#define DEFINITIONVIEW_HPP

#include <QTreeView>

class DescriptionItem;

class DefinitionView : public QTreeView {
  Q_OBJECT
public:
  explicit DefinitionView(QWidget *parent = nullptr);

  void mousePressEvent(QMouseEvent *event) override;

signals:
  void render(DescriptionItem *);
};

#endif // DEFINITIONVIEW_HPP
