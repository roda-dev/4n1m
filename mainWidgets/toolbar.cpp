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
    setGeometry(0, 50, 40, 280);

    tool1 = new ToolbarButton(mainwindow, this, 0,  0,  40, 40, ToolbarButtonStyle::TOOL_CURRENT, "P");
    tool2 = new ToolbarButton(mainwindow, this, 0,  40, 40, 40, ToolbarButtonStyle::TOOL_TEXT, "L");
    tool3 = new ToolbarButton(mainwindow, this, 0,  80, 40, 40, ToolbarButtonStyle::TOOL_TEXT, "F");
    tool4 = new ToolbarButton(mainwindow, this, 0, 120, 40, 40, ToolbarButtonStyle::TOOL_TEXT, "E");
    tool5 = new ToolbarButton(mainwindow, this, 0, 160, 40, 40, ToolbarButtonStyle::TOOL_TEXT, "O");
    tool6 = new ToolbarButton(mainwindow, this, 0, 200, 40, 40, ToolbarButtonStyle::TOOL_WHITE, "K");
    tool7 = new ToolbarButton(mainwindow, this, 0, 240, 40, 40, ToolbarButtonStyle::TOOL_RED, "X");

    connect(tool1, &QAbstractButton::clicked, this, [this]{ editor()->setToolAsPen(); setCurrentTool(ToolbarTool::TOOL1); });
    connect(tool2, &QAbstractButton::clicked, this, [this]{ editor()->setToolAsLine(); setCurrentTool(ToolbarTool::TOOL2); });
    connect(tool3, &QAbstractButton::clicked, this, [this]{ editor()->setToolAsLassoFill(); setCurrentTool(ToolbarTool::TOOL3); });
    connect(tool4, &QAbstractButton::clicked, this, [this]{ editor()->setToolAsEraser(); setCurrentTool(ToolbarTool::TOOL4); });
    connect(tool5, &QAbstractButton::clicked, this, [this]{ editor()->setToolAsEmpty(); setCurrentTool(ToolbarTool::TOOL5); });
    connect(tool6, &QAbstractButton::clicked, this, [this]{ editor()->knockback(); });
    connect(tool7, &QAbstractButton::clicked, this, [this]{ editor()->clearImage(); });
}

void Toolbar::setCurrentTool(ToolbarTool t)
{
    currentTool = t;
    sub1()->hide();
    sub2()->hide();
    sub3()->hide();
    sub4()->hide();
    sub5()->hide();
    tool1->setStyle();
    tool2->setStyle();
    tool3->setStyle();
    tool4->setStyle();
    tool5->setStyle();

    QImage* colorIcon = new QImage(26, 26, QImage::Format_ARGB32);
        colorIcon->fill(QColor(Qt::transparent));
        QPainter colorPainter(colorIcon);
    QImage* styleIcon = new QImage(26, 26, QImage::Format_ARGB32);
        QPainter stylePainter(styleIcon);
        styleIcon->fill(QColor(Qt::transparent));
        stylePainter.setPen(QPen(Qt::transparent, 1));
    QImage* widthIcon = new QImage(20, 20, QImage::Format_ARGB32);
        QPainter widthPainter(widthIcon);
        widthIcon->fill(QColor(Qt::transparent));
        widthPainter.setPen(QPen(Qt::black, 3));
        widthPainter.drawLine(0, 10, 20, 10);
    QImage* opacityIcon = new QImage(20, 20, QImage::Format_ARGB32);
        QPainter opacityPainter(opacityIcon);
        opacityIcon->fill(QColor(Qt::transparent));
        opacityPainter.setPen(QPen(Qt::black));
        opacityPainter.drawEllipse(0,0, 19, 19);
        opacityPainter.setBrush(Qt::black);
        opacityPainter.drawPie(0, 0, 19, 19, 90*16, 180*16);

    switch (t) {
        case ToolbarTool::TOOL1: {
            QString penOpacity = QString::fromUtf8((std::to_string((editor()->getPenTool()->color().alpha()*100)/255) + "%").c_str());
            QString penWidth = QString::fromUtf8((std::to_string(editor()->getPenTool()->width())).c_str());
            colorPainter.setPen(editor()->getPenTool()->color());
            colorPainter.setBrush(editor()->getPenTool()->color());
            colorPainter.drawEllipse(0, 0, 25, 25);
            tool1->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            sub1()->show(); sub1()->setImage(*colorIcon); sub1()->setStyle(SUB_ICON);
            sub2()->show(); sub2()->setText(penOpacity); sub2()->setImage(*opacityIcon); sub2()->setStyle(SUB_TEXTICON);
            sub3()->show(); sub3()->setText(penWidth); sub3()->setImage(*widthIcon); sub3()->setStyle(SUB_TEXTICON);
            subtoolbar->setGeometry(40, 70, 40, 120);
            break;
       } case ToolbarTool::TOOL2: {
            QString lineOpacity = QString::fromUtf8((std::to_string((editor()->getLineTool()->color().alpha()*100)/255) + "%").c_str());
            QString lineWidth = QString::fromUtf8((std::to_string(editor()->getLineTool()->width())).c_str());
            colorPainter.setPen(editor()->getLineTool()->color());
            colorPainter.setBrush(editor()->getLineTool()->color());
            colorPainter.drawEllipse(0,0, 25, 25);
            tool2->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            sub1()->show(); sub1()->setImage(*colorIcon); sub1()->setStyle(SUB_ICON);
            sub2()->show(); sub2()->setText(lineOpacity); sub2()->setImage(*opacityIcon); sub2()->setStyle(SUB_TEXTICON);
            sub3()->show(); sub3()->setText(lineWidth); sub3()->setImage(*widthIcon); sub3()->setStyle(SUB_TEXTICON);
            subtoolbar->setGeometry(40, 70, 40, 120);
            break;
        } case ToolbarTool::TOOL3: {
            QString fillOpacity = QString::fromUtf8((std::to_string((editor()->getLassoFillTool()->color().alpha()*100)/255) + "%").c_str());
            colorPainter.setPen(editor()->getLassoFillTool()->color());
            colorPainter.setBrush(editor()->getLassoFillTool()->color());
            colorPainter.drawEllipse(0,0, 25, 25);
            stylePainter.setBrush(QBrush(Qt::black, editor()->getLassoFillTool()->style()));
            stylePainter.drawRect(1, 1, 24, 24);
            tool3->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            sub1()->show(); sub1()->setImage(*colorIcon); sub1()->setStyle(SUB_ICON);
            sub2()->show(); sub2()->setText(fillOpacity); sub2()->setImage(*opacityIcon); sub2()->setStyle(SUB_TEXTICON);
            sub3()->show(); sub3()->setImage(*styleIcon); sub3()->setStyle(SUB_ICON);
            subtoolbar->setGeometry(40, 70, 40, 120);
            break;
        } case ToolbarTool::TOOL4: {
            QString eraserWidth = QString::fromUtf8((std::to_string(editor()->getEraserTool()->width())).c_str());
            tool4->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            sub1()->show(); sub1()->setText(eraserWidth); sub1()->setImage(*widthIcon); sub1()->setStyle(SUB_TEXTICON);
            subtoolbar->setGeometry(40, 70, 40, 40);
            break;
        } case ToolbarTool::TOOL5: {
            QString backgroundOpacity = QString::fromUtf8((std::to_string((editor()->getBackgroundColor().alpha()*100)/255) + "%").c_str());
            colorPainter.setBrush(editor()->getBackgroundColor());
            colorPainter.setPen(editor()->getBackgroundColor());
            colorPainter.drawEllipse(0,0, 25, 25);
            tool5->setStyle(ToolbarButtonStyle::TOOL_CURRENT);
            sub1()->show(); sub1()->setImage(*colorIcon); sub1()->setStyle(SUB_ICON);
            sub2()->show(); sub2()->setText(backgroundOpacity); sub2()->setImage(*opacityIcon); sub2()->setStyle(SUB_TEXTICON);
            subtoolbar->setGeometry(40, 70, 40, 80);
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
    setGeometry(40, 80, 40, 200);

    subtool1 = new ToolbarButton(mainwindow, this, 0, 0, 40, 40, ToolbarButtonStyle::SUB_ICON);
    subtool2 = new ToolbarButton(mainwindow, this, 0, 40, 40, 40, ToolbarButtonStyle::SUB_ICON);
    subtool3 = new ToolbarButton(mainwindow, this, 0, 80, 40, 40, ToolbarButtonStyle::SUB_ICON);
    subtool4 = new ToolbarButton(mainwindow, this, 0, 120, 40, 40, ToolbarButtonStyle::SUB_ICON);
    subtool5 = new ToolbarButton(mainwindow, this, 0, 160, 40, 40, ToolbarButtonStyle::SUB_ICON);

    connect(subtool1, &QAbstractButton::clicked, this, [this]{ clickSubtool(ToolbarTool::SUB1); });
    connect(subtool2, &QAbstractButton::clicked, this, [this]{ clickSubtool(ToolbarTool::SUB2); });
    connect(subtool3, &QAbstractButton::clicked, this, [this]{ clickSubtool(ToolbarTool::SUB3); });
    connect(subtool4, &QAbstractButton::clicked, this, [this]{ clickSubtool(ToolbarTool::SUB4); });
    connect(subtool5, &QAbstractButton::clicked, this, [this]{ clickSubtool(ToolbarTool::SUB5); });
}

void Subtoolbar::clickSubtool(ToolbarTool sub)
{
    switch(toolbar->getCurrentTool())
    {
        case ToolbarTool::TOOL1:
            switch(sub){
                case ToolbarTool::SUB1: mainwindow->openPenColorWindow(); break;
                case ToolbarTool::SUB2: mainwindow->openPenOpacityWindow(); break;
                case ToolbarTool::SUB3: mainwindow->openPenWidthWindow(); break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        case ToolbarTool::TOOL2:
            switch(sub){
                case ToolbarTool::SUB1: mainwindow->openLineColorWindow(); break;
                case ToolbarTool::SUB2: mainwindow->openLineOpacityWindow(); break;
                case ToolbarTool::SUB3: mainwindow->openLineWidthWindow(); break;
                case ToolbarTool::SUB4: break;
                case ToolbarTool::SUB5: break;
                default: break;
            } break;
        case ToolbarTool::TOOL3:
            switch(sub){
                case ToolbarTool::SUB1: mainwindow->openLassofillColorWindow(); break;
                case ToolbarTool::SUB2: mainwindow->openLassofillOpacityWindow(); break;
                case ToolbarTool::SUB3: mainwindow->openLassofillStyleWindow(); break;
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
                case ToolbarTool::SUB1: mainwindow->openBackgroundColorWindow(); break;
                case ToolbarTool::SUB2: mainwindow->openBackgroundOpacityWindow(); break;
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

ToolbarButton::ToolbarButton(MainWindow* mw, QWidget* p, int x, int y, int w, int h, ToolbarButtonStyle style, QString t, QImage img): QPushButton(p)
{
    mainwindow = mw;
    parent = p;
    setFocusPolicy(Qt::NoFocus);
    setGeometry(x, y, w, h);
    setText(t);
    setImage(img);
    setStyle(style);
}

void ToolbarButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPainterPath path;
    QFont font = painter.font();
    font.setKerning(true);

    switch(style)
    {
        case TOOL_TEXT:
            path.addRect(0, 0, width(), height());
            painter.fillPath(path, QColor(50, 50, 50));
            font.setPixelSize(12);
            painter.setFont(font);
            painter.setPen(QColor(175, 175, 175));
            painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, text);
            break;
        case TOOL_CURRENT:
            path.addRect(0, 0, width(), height());
            painter.fillPath(path, QColor(175, 175, 175));
            font.setPixelSize(12);
            painter.setFont(font);
            painter.setPen(QColor(50, 50, 50));
            painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, text);
            break;
        case TOOL_RED:
            setStyleSheet(
                "QPushButton{background-color:rgb(255,0,0);border:0px;color:white;font-size:12px;}\
                QPushButton:pressed{background-color:white;border:0px;color:rgb(50,50,50);}"
            );
            QPushButton::paintEvent(event);
            break;
        case TOOL_WHITE:
            setStyleSheet(
                "QPushButton{background-color:white;border:0px;color:black;font-size:12px;}\
                QPushButton:pressed{background-color:rgb(50,50,50);border:0px;color:white;}"
            );
            QPushButton::paintEvent(event);
            break;
        case SUB_ICON:
            path.addRect(0, 0, width(), height());
            painter.fillPath(path, QColor(175, 175, 175));
            painter.drawImage(QPoint(7,7), image);
            break;
        case SUB_TEXTICON:
            path.addRect(0, 0, width(), height());
            painter.fillPath(path, QColor(175, 175, 175));
            painter.drawImage(QPoint(10,4), image);
            font.setPixelSize(11);
            painter.setFont(font);
            painter.setPen(QColor(50, 50, 50));
            painter.drawText(QRect(0, 25, width(), 11), Qt::AlignCenter, text);
            break;
        case SUB_TOGGLE:
            break;
    }
}
