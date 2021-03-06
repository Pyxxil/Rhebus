#ifndef OBJECTDIALOG_HPP
#define OBJECTDIALOG_HPP

#include <QDialog>

class LayerItem;

namespace Ui {
class ObjectDialog;
}

class ObjectDialog : public QDialog {
  Q_OBJECT

public:
  explicit ObjectDialog(QWidget *parent = 0);
  ~ObjectDialog();

  void addObject(const QString &);
  QString selected() const;

  LayerItem *getUpdater() const;
  void setUpdater(LayerItem *value);

private:
  Ui::ObjectDialog *ui;
  LayerItem *updater;
};

#endif // OBJECTDIALOG_HPP
