#ifndef PROGRAMWINDOW_HPP
#define PROGRAMWINDOW_HPP

#include <QColor>
#include <QWidget>

#include "Shapes/shape.hpp"

namespace Ui {
class ProgramWindow;
}

class ProgramWindow : public QWidget {
  Q_OBJECT

public:
  explicit ProgramWindow(QWidget *parent = 0);
  ~ProgramWindow();

  void addShape(const QList<QSharedPointer<Shape>> &);

  QColor getBackgroundColour() const { return backgroundColour; }
  void setBackgroundColour(const QColor &value) {
    backgroundColour = value;
    draw();
  }

  void draw();

  const QList<QList<QSharedPointer<Shape>>> &getShapes() const;
  void setShapes(const QList<QList<QSharedPointer<Shape>>> &shapes);

private:
  Ui::ProgramWindow *ui;
  QList<QList<QSharedPointer<Shape>>> mShapes;
  QImage image;
  QColor backgroundColour;
};

#endif // PROGRAMWINDOW_HPP
