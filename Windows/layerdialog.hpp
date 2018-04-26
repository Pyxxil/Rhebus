#ifndef LAYERDIALOG_HPP
#define LAYERDIALOG_HPP

#include <QDialog>

namespace Ui {
class LayerDialog;
} // namespace Ui

class LayerDialog : public QDialog {
  Q_OBJECT

public:
  explicit LayerDialog(QWidget *parent = nullptr);
  ~LayerDialog();

  QString getLayerName() const;

private:
  Ui::LayerDialog *ui;
};

#endif // LAYERDIALOG_HPP
