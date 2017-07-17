#include "widget.h"
#include "ui_widget.h"
#include "treemodel.h"

#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  m_treeModel = new TreeModel(this);
  ui->treeView->setModel(m_treeModel);
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
  QFile f(filename);

  if (f.open(QFile::ReadOnly))
  {
    m_treeModel->parseCsvData(QString::fromUtf8(f.readAll()));
    ui->treeView->expandAll();
  }
}
