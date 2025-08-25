#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QDialog>

namespace Ui {
class Properties;
}

class Properties : public QDialog
{
    Q_OBJECT

public:
    explicit Properties(QWidget *parent = nullptr);
    ~Properties() override;
    Ui::Properties* getUi(){
        return ui;
    }
private:
    Ui::Properties *ui;
};

#endif // PROPERTIES_H
