#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_csvBrowseButton_clicked()
{
  QString filename = QFileDialog::getOpenFileName(this,
                                                  tr("Open CSV file"),
                                                  QString(),
                                                  tr("CSV file") + " (*.csv)");

  if (filename.isNull()) return;
  ui->csvLineEdit->setText(filename);
  parseCsv(filename);
}

void Widget::on_csvLineEdit_returnPressed()
{
  parseCsv(ui->csvLineEdit->text());
}

void Widget::parseCsv(const QString &filename)
{
  qDebug() << filename;
  // Parse CSV here
}
