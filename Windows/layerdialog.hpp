#ifndef LAYERDIALOG_HPP
#define LAYERDIALOG_HPP

#include <QDialog>

namespace Ui {
class LayerDialog;
}

class LayerDialog : public QDialog {
  Q_OBJECT

public:
  explicit LayerDialog(QWidget *parent = 0);
  ~LayerDialog();

  QString getLayerName() const;

private:
  Ui::LayerDialog *ui;
};

#endif // LAYERDIALOG_HPP
