#ifndef SERVERSELECTION_H
#define SERVERSELECTION_H

#include <QWidget>

namespace Ui {
class serverselection;
}

class serverselection : public QWidget
{
    Q_OBJECT
    
public:
    explicit serverselection(QWidget *parent = 0);
    ~serverselection();
    
private:
    Ui::serverselection *ui;
};

#endif // SERVERSELECTION_H
