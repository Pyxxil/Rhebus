#ifndef DESCRIPTIONRENDERER_HPP
#define DESCRIPTIONRENDERER_HPP

#include <QWidget>

class DescriptionItem;

class DescriptionRenderer : public QWidget {
  Q_OBJECT
public:
  explicit DescriptionRenderer(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event);

signals:

public slots:
  void renderDescription(DescriptionItem *desc);
  void changeSize();

private:
  const DescriptionItem *description;
  QPixmap pixmap;
  QImage image;
};

#endif // DESCRIPTIONRENDERER_HPP
