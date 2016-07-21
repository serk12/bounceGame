#include "generator.h"
#include "ui_generator.h"

Generator::Generator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);
}

Generator::~Generator()
{
    delete ui;
}
