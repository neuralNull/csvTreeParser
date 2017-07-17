#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class TreeModel;

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private slots:
  void on_csvBrowseButton_clicked();
  void on_csvLineEdit_returnPressed();
  void parseCsv(const QString &filename);

private:
  Ui::Widget *ui;
  TreeModel *m_treeModel;
};

#endif // WIDGET_H
