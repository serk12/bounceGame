#ifndef GENERATOR_H
#define GENERATOR_H

#include <QWidget>

namespace Ui {
class Generator;
}

class Generator : public QWidget
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = 0);
    ~Generator();

private:
    Ui::Generator *ui;
};

#endif // GENERATOR_H
