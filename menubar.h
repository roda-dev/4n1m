#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QWidget>
#include <QMenuBar>

class Menubar : public QMenuBar
{
    Q_OBJECT

public:
    Menubar(QWidget* = nullptr);

protected:

private:

};

#endif // MENUBAR_H
