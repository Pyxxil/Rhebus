#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class DefinitionModel;
class DescriptionItem;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void customMenuRequested(QPoint);
  void addDefinition(bool);
  void editDefinition(bool);
  void copyDescription(bool);
  void addDefinitionWizardAccepted();

private:
  Ui::MainWindow *ui;
  DefinitionModel *definitionModel;
};

#endif // MAINWINDOW_HPP