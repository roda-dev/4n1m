#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "mainwindow.h"

class ToolbarButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int bgColorAnim READ getBgColor WRITE setBgColor)
    Q_PROPERTY(int letterColorAnim READ getLetterColor WRITE setLetterColor)

public:
    ToolbarButton(MainWindow*, QWidget*, int, int, int, int, ToolbarButtonStyle = ToolbarButtonStyle::TOOL_TEXT, QString = "", QImage i = QImage(1, 1, QImage::Format_ARGB32));
    void setStyle(ToolbarButtonStyle s = ToolbarButtonStyle::TOOL_TEXT){ style = s; update(); };
    void setText(QString t = ""){ text = t; }
    void setImage(QImage i = QImage(1, 1, QImage::Format_ARGB32)){ image = i; }

    int getBgColor() { return bgColor.red(); }
    void setBgColor(int a) { bgColor.setRgb(a, a ,a); update();}
    int getLetterColor() { return letterColor.red(); }
    void setLetterColor(int a) { letterColor.setRgb(a, a ,a); update();}

    void setIsCurrent(bool);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    MainWindow* mainwindow;
    QString text;
    QImage image;
    ToolbarButtonStyle style;

    QColor bgColor;
    QColor letterColor;
    int isCurrent = false;

    QPropertyAnimation* bgAnim = new QPropertyAnimation(this, "bgColorAnim");
    QPropertyAnimation* letterAnim = new QPropertyAnimation(this, "letterColorAnim");
};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

class Subtoolbar : public QWidget
{
    Q_OBJECT
public:
    Subtoolbar(MainWindow*, QWidget*);
    void setToolbar(Toolbar* t) { toolbar = t;}
    void clickSubtool(ToolbarTool);
    void hideProperties();
    ToolbarButton* subtool1;
    ToolbarButton* subtool2;
    ToolbarButton* subtool3;
    ToolbarButton* subtool4;
    ToolbarButton* subtool5;
    ToolbarButton* penOpacityProperty;
    ToolbarButton* penWidthProperty;
    ToolbarButton* lineOpacityProperty;
    ToolbarButton* lineWidthProperty;
    ToolbarButton* lassoOpacityProperty;
    ToolbarButton* eraserWidthProperty;
    ToolbarButton* bgOpacityProperty;

private:
    MainWindow* mainwindow;
    QWidget* parent;
    Toolbar* toolbar;
};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

class Toolbar : public QWidget
{
    Q_OBJECT
public:
    Toolbar(MainWindow*, QWidget*);
    void setSuboolbar(Subtoolbar* s) { subtoolbar = s; }
    Editor* editor() {return mainwindow->editor; }
    ToolbarTool getCurrentTool() { return currentTool; }
    void setCurrentTool(ToolbarTool t);
    ToolbarButton* sub1() { return subtoolbar->subtool1; }
    ToolbarButton* sub2() { return subtoolbar->subtool2; }
    ToolbarButton* sub3() { return subtoolbar->subtool3; }
    ToolbarButton* sub4() { return subtoolbar->subtool4; }
    ToolbarButton* sub5() { return subtoolbar->subtool5; }
    ToolbarButton* tool1;
    ToolbarButton* tool2;
    ToolbarButton* tool3;
    ToolbarButton* tool4;
    ToolbarButton* tool5;
    ToolbarButton* tool6;
    ToolbarButton* tool7;

private:
    ToolbarTool currentTool = ToolbarTool::TOOL1;
    MainWindow* mainwindow;
    QWidget* parent;
    Subtoolbar* subtoolbar;
};

#endif
