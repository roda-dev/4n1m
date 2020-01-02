#include "mainwindow.h"
#include "animation.h"
#include "preview.h"
#include "commands.h"
#include "mainWidgets/editor.h"
#include "mainWidgets/timeline.h"
#include "mainWidgets/titlebar.h"
#include "mainWidgets/toolbar.h"

Toolbar::Toolbar(MainWindow* mw, QWidget* p): QWidget(p)
{
    mainwindow = mw;
    p = parent;
    setFocusPolicy(Qt::NoFocus);
    setGeometry(0, 40, 40, 300);

    pen = new ToolbarButton(mainwindow, this, 0, 0, 40, 40, ToolbarButtonStyle::TOOL_CURRENT, "P");
    line = new ToolbarButton(mainwindow, this, 0, 40, 40, 40, ToolbarButtonStyle::TOOL_NORMAL, "L");
    lassofill = new ToolbarButton(mainwindow, this, 0, 80, 40, 40, ToolbarButtonStyle::TOOL_NORMAL, "F");
    eraser = new ToolbarButton(mainwindow, this, 0, 120, 40, 40, ToolbarButtonStyle::TOOL_NORMAL, "E");
    other = new ToolbarButton(mainwindow, this, 0, 160, 40, 40, ToolbarButtonStyle::TOOL_NORMAL, "O");
    knockback = new ToolbarButton(mainwindow, this, 0, 200, 40, 40, ToolbarButtonStyle::TOOL_WHITE, "K");
    clearimage = new ToolbarButton(mainwindow, this, 0, 240, 40, 40, ToolbarButtonStyle::TOOL_RED, "X");
    undo = new ToolbarButton(mainwindow, this, 0, 280, 20, 20, ToolbarButtonStyle::SUB_NORMAL, "u");
    redo = new ToolbarButton(mainwindow, this, 20, 280, 20, 20, ToolbarButtonStyle::SUB_NORMAL, "r");

    connect(pen, &QAbstractButton::clicked, this, [this]{ mainwindow->getEditor()->setToolAsPen(); setCurrentTool(ToolbarTool::TOOL1); });
    connect(line, &QAbstractButton::clicked, this, [this]{ mainwindow->getEditor()->setToolAsLine(); setCurrentTool(ToolbarTool::TOOL2); });
    connect(lassofill, &QAbstractButton::clicked, this, [this]{ mainwindow->getEditor()->setToolAsLassoFill(); setCurrentTool(ToolbarTool::TOOL3); });
    connect(eraser, &QAbstractButton::clicked, this, [this]{ mainwindow->getEditor()->setToolAsEraser(); setCurrentTool(ToolbarTool::TOOL4); });
    connect(other, &QAbstractButton::clicked, this, [this]{ mainwindow->getEditor()->setToolAsEmpty(); setCurrentTool(ToolbarTool::TOOL5); });
    connect(knockback, &QAbstractButton::clicked, this, [this]{ this->mainwindow->getEditor()->knockback(); });
    connect(clearimage, &QAbstractButton::clicked, this, [this]{ this->mainwindow->getEditor()->clearImage(); });
    connect(undo, &QAbstractButton::clicked, this, [this]{ this->mainwindow->getUndoStack()->undo(); });
    connect(redo, &QAbstractButton::clicked, this, [this]{ this->mainwindow->getUndoStack()->redo(); });
}

void Toolbar::setCurrentTool(ToolbarTool t)
{
    currentTool = t;
    sub1()->hide(); sub1()->setText(""); sub1()->setIcon(QIcon());
    sub2()->hide(); sub2()->setText(""); sub2()->setIcon(QIcon());
    sub3()->hide(); sub3()->setText(""); sub3()->setIcon(QIcon());
    sub4()->hide(); sub4()->setText(""); sub4()->setIcon(QIcon());
    sub5()->hide(); sub5()->setText(""); sub5()->setIcon(QIcon());

    pen->setStyle();
    line->setStyle();
    lassofill->setStyle();
    eraser->setStyle();
    other->setStyle();

    QPixmap* colorIcon = new QPixmap(32, 32);

    switch (t) {
        case ToolbarTool::TOOL1: {
            pen->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            colorIcon->fill(mainwindow->getEditor()->getPenTool()->color().rgb());
            sub1()->show(); sub1()->setIcon(QIcon(*colorIcon));
            sub2()->show(); sub2()->setText(tr("O"));
            sub3()->show(); sub3()->setText(tr("W"));
            subtoolbar->setGeometry(40, 60, 40, 120);
            break;
       } case ToolbarTool::TOOL2: {
            line->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            colorIcon->fill(mainwindow->getEditor()->getLineTool()->color().rgb());
            sub1()->show(); sub1()->setIcon(QIcon(*colorIcon));
            sub2()->show(); sub2()->setText(tr("O"));
            sub3()->show(); sub3()->setText(tr("W"));
            subtoolbar->setGeometry(40, 60, 40, 120);
            break;
        } case ToolbarTool::TOOL3: {
            lassofill->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            colorIcon->fill(mainwindow->getEditor()->getLassoFillTool()->color().rgb());
            sub1()->show(); sub1()->setIcon(QIcon(*colorIcon));
            sub2()->show(); sub2()->setText(tr("O"));
            sub3()->show(); sub3()->setText(tr("S"));
            subtoolbar->setGeometry(40, 60, 40, 120);
            break;
        } case ToolbarTool::TOOL4: {
            eraser->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            sub1()->show(); sub1()->setText(tr("W"));
            subtoolbar->setGeometry(40, 60, 40, 40);
            break;
        } case ToolbarTool::TOOL5: {
            other->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            colorIcon->fill(mainwindow->getEditor()->getBackgroundColor().rgb());
            sub1()->show(); sub1()->setIcon(QIcon(*colorIcon));
            sub2()->show(); sub2()->setText(tr("O"));
            subtoolbar->setGeometry(40, 60, 40, 80);
            break;
        } default: break;
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

Subtoolbar::Subtoolbar(MainWindow* mw, QWidget* p): QWidget(p)
{
    mainwindow = mw;
    p = parent;
    setFocusPolicy(Qt::NoFocus);
    setGeometry(40, 60, 40, 200);

    QPixmap* colorIcon = new QPixmap(32, 32);
    colorIcon->fill(mainwindow->getEditor()->getPenTool()->color().rgb());

    p1 = new ToolbarButton(mainwindow, this, 0, 0, 40, 40, ToolbarButtonStyle::SUB_NORMAL);
    p2 = new ToolbarButton(mainwindow, this, 0, 40, 40, 40, ToolbarButtonStyle::SUB_NORMAL);
    p3 = new ToolbarButton(mainwindow, this, 0, 80, 40, 40, ToolbarButtonStyle::SUB_NORMAL);
    p4 = new ToolbarButton(mainwindow, this, 0, 120, 40, 40, ToolbarButtonStyle::SUB_NORMAL);
    p5 = new ToolbarButton(mainwindow, this, 0, 160, 40, 40, ToolbarButtonStyle::SUB_NORMAL);

    connect(p1, &QAbstractButton::clicked, this, [this]{ this->clickSubtool(ToolbarTool::SUB1); });
    connect(p2, &QAbstractButton::clicked, this, [this]{ this->clickSubtool(ToolbarTool::SUB2); });
    connect(p3, &QAbstractButton::clicked, this, [this]{ this->clickSubtool(ToolbarTool::SUB3); });
    connect(p4, &QAbstractButton::clicked, this, [this]{ this->clickSubtool(ToolbarTool::SUB4); });
    connect(p5, &QAbstractButton::clicked, this, [this]{ this->clickSubtool(ToolbarTool::SUB5); });
}

void Subtoolbar::clickSubtool(ToolbarTool sub)
{
    switch(toolbar->getCurrentTool())
    {
        case ToolbarTool::TOOL1:
            switch(sub){
                case ToolbarTool::SUB1: this->mainwindow->openPenColorWindow(); break;
                case ToolbarTool::SUB2: this->mainwindow->openPenOpacityWindow(); break;
                case ToolbarTool::SUB3: this->mainwindow->openPenWidthWindow(); break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        case ToolbarTool::TOOL2:
            switch(sub){
                case ToolbarTool::SUB1: this->mainwindow->openLineColorWindow(); break;
                case ToolbarTool::SUB2: this->mainwindow->openLineOpacityWindow(); break;
                case ToolbarTool::SUB3: this->mainwindow->openLineWidthWindow(); break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        case ToolbarTool::TOOL3:
            switch(sub){
                case ToolbarTool::SUB1: this->mainwindow->openLassofillColorWindow(); break;
                case ToolbarTool::SUB2: this->mainwindow->openLassofillOpacityWindow(); break;
                case ToolbarTool::SUB3: this->mainwindow->openLassofillStyleWindow(); break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        case ToolbarTool::TOOL4:
            switch(sub){
                case ToolbarTool::SUB1: this->mainwindow->openEraserWidthWindow(); break;
                case ToolbarTool::SUB2: break;
                case ToolbarTool::SUB3: break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        case ToolbarTool::TOOL5:
            switch(sub){
                case ToolbarTool::SUB1: this->mainwindow->openBackgroundColorWindow(); break;
                case ToolbarTool::SUB2: this->mainwindow->openBackgroundOpacityWindow(); break;
                case ToolbarTool::SUB3: break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        default:
            break;
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

ToolbarButton::ToolbarButton(MainWindow* mw, QWidget* p, int x, int y, int w, int h, ToolbarButtonStyle style, QString text, QIcon icon): QPushButton(p)
{
    mainwindow = mw;
    parent = p;
    setFocusPolicy(Qt::NoFocus);
    setGeometry(x, y, w, h);
    setText(text);
    setIcon(icon);
    setStyle(style);
}

void ToolbarButton::setStyle(ToolbarButtonStyle style)
{
    switch(style)
    {
        case TOOL_NORMAL:
            setStyleSheet("QPushButton{background-color:rgb(50,50,50);border:0px;color:rgb(210,210,210);font-size:12px;}");
            break;
        case TOOL_CURRENT:
            setStyleSheet("QPushButton{background-color:rgb(175,175,175);border:0px;color:rgb(50,50,50);font-size:12px;}");
            break;
        case TOOL_RED:
            setStyleSheet(
                "QPushButton{background-color:rgb(255,0,0);border:0px;color:white;font-size:12px;}\
                QPushButton:pressed{background-color:white;border:0px;color:rgb(50,50,50);}"
            );
            break;
        case TOOL_WHITE:
            setStyleSheet(
                "QPushButton{background-color:white;border:0px;color:black;font-size:12px;}\
                QPushButton:pressed{background-color:rgb(50,50,50);border:0px;color:white;}"
            );
            break;
        case SUB_NORMAL:
            setStyleSheet(
                "QPushButton{background-color:rgb(175,175,175);border:0px;color:rgb(50,50,50);font-size:10px;}\
                QPushButton:pressed{background-color:rgb(50,50,50);border:0px;color:rgb(210,210,210);font-size:10px;}"
            );
            break;
    }
}
