#ifndef ADDDEFINITIONWIZARD_HPP
#define ADDDEFINITIONWIZARD_HPP

#include <QWizard>

namespace Ui {
class AddDefinitionWizard;
}

#include "Shapes/shape.hpp"

class DescriptionItem;
class ShapeItem;

class AddDefinitionWizard : public QWizard {
  Q_OBJECT

public:
  explicit AddDefinitionWizard(QWidget *parent = 0);
  ~AddDefinitionWizard();

  const QString definitionName() const;
  const QList<QSharedPointer<Shape>> shapes() const;

  void setDefinitionName(const QString &);
  void setDescription(const DescriptionItem *);

  void setUpdater(ShapeItem *);
  ShapeItem *updater() const { return mUpdater; }

  void setShapes(const QList<QSharedPointer<Shape>> &shapes);

public slots:
  void openPenColourChooser();
  void openBrushColourChooser();

  void penColourChanged(QColor);
  void brushColourChanged(QColor);

signals:
  void updateSizes();

private:
  Ui::AddDefinitionWizard *ui;
  ShapeItem *mUpdater;
};

#endif // ADDDEFINITIONWIZARD_HPP
