#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QApplication>
#include <QWindow>
#include <QDesktopWidget>
#include <QStyle>
#include <QMainWindow>
#include <QVector>
#include <QUndoView>
#include <QMap>
#include <QList>
#include <QString>
#include <QImage>
#include <QPoint>
#include <QDebug>
#include <QUndoStack>
#include <QUndoCommand>
#include <QPainter>
#include <QObject>
#include <QWidget>
#include <QMenuBar>
#include <QColor>

class Editor;
class Timeline;
class Animation;
class Preview;
class Titlebar;
class Toolbar;
class Subtoolbar;
class Layer;
class Frame;

enum SelectionState {
    STATE_SELECTING,
    STATE_SELECTED,
    STATE_EMPTY
};

enum Tool {
    EMPTY,
    PEN,
    LASSOFILL,
    ERASER,
    SELECT,
    LINE
};

enum ToolbarTool {
    TOOL1,
    TOOL2,
    TOOL3,
    TOOL4,
    TOOL6,
    TOOL5,
    SUB1,
    SUB2,
    SUB3,
    SUB4,
    SUB5
};

enum ToolbarButtonStyle {
    TOOL_CURRENT,
    TOOL_TEXT,
    TOOL_WHITE,
    TOOL_RED,
    SUB_ICON,
    SUB_TEXTICON,
    SUB_TOGGLE,
    SUB_EMPTY
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    Animation* animation;
    QUndoStack* undostack;
    Editor* editor;
    Timeline* timeline;
    Titlebar* titlebar;
    Toolbar* toolbar;
    Subtoolbar* subtoolbar;

    int getFPS() { return FPS; }
    QRect getWindowDimensions() { return windowDimensions; }
    bool isOnTop = false;

public slots:
    void openUndoAmountWindow();
    void openKnockbackAmountWindow();
    void openChangeFPSWindow();
    void openPreviewWindow();
    void openUndoStackWindow();
    void toggleStayOnTop();

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    int FPS = 24;
    int undostackSize = 30;
    QRect windowDimensions = QRect(-870, 400, 850, 650);
};

#endif
