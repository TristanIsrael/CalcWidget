#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->textEdit->setText(ui->textEdit->toHtml().arg(QApplication::applicationVersion()));
    setWindowFlags(windowFlags() | Qt::Window | Qt::WindowStaysOnTopHint);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
