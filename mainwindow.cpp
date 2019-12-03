#include <QtWidgets>

#include "mainwindow.h"
#include "object.h"
#include "editor.h"
#include "timeline.h"

MainWindow::MainWindow()
{
    object = new Object;
    editor = new Editor(object);
    timeline = new Timeline;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(editor, 0, 0, 6, 1);
    layout->addWidget(timeline, 7, 0, 1, 1);

    QWidget *window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);

    setWindowTitle(tr("4n1m"));
    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    penColorAct = new QAction(tr("Color..."), this);
    penWidthAct = new QAction(tr("Pen Width..."), this);
    fillStyleAct = new QAction(tr("LassoFill Style..."), this);
    toolAsPenAct = new QAction(tr("Pen"), this);
    toolAsLassoFillAct = new QAction(tr("LassoFill"), this);
    toolAsEraserAct = new QAction(tr("Eraser"), this);
    clearScreenAct = new QAction(tr("Clear Screen"), this);
    nextFrameAct = new QAction(tr("Next"), this);
    previousFrameAct = new QAction(tr("Previous"), this);

    clearScreenAct->setShortcut(tr("W"));
    toolAsPenAct->setShortcut(Qt::Key_1);
    toolAsLassoFillAct->setShortcut(Qt::Key_2);
    toolAsEraserAct->setShortcut(Qt::Key_3);
    nextFrameAct->setShortcut(Qt::Key_Right);
    previousFrameAct->setShortcut(Qt::Key_Left);

    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));
    connect(fillStyleAct, SIGNAL(triggered()), this, SLOT(fillStyle()));
    connect(toolAsPenAct, SIGNAL(triggered()), editor, SLOT(setToolAsPen()));
    connect(toolAsLassoFillAct, SIGNAL(triggered()), editor, SLOT(setToolAsLassoFill()));
    connect(toolAsEraserAct, SIGNAL(triggered()), editor, SLOT(setToolAsEraser()));
    connect(clearScreenAct, SIGNAL(triggered()), editor, SLOT(clearImage()));
    connect(nextFrameAct, SIGNAL(triggered()), editor, SLOT(gotoNextFrame()));
    connect(previousFrameAct, SIGNAL(triggered()), editor, SLOT(gotoPreviousFrame()));
}

void MainWindow::createMenus()
{
    optionMenu = new QMenu(tr("Menu"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addAction(fillStyleAct);
    optionMenu->addSeparator();
    optionMenu->addAction(toolAsPenAct);
    optionMenu->addAction(toolAsLassoFillAct);
    optionMenu->addAction(toolAsEraserAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);
    optionMenu->addSeparator();
    optionMenu->addAction(nextFrameAct);
    optionMenu->addAction(previousFrameAct);

    menuBar()->addMenu(optionMenu);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(editor->getPenColor());
    if (newColor.isValid()) editor->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"), tr("Select pen width:"), editor->getPenWidth(), 1, 50, 1, &ok);
    if (ok) editor->setPenWidth(newWidth);
}

void MainWindow::fillStyle()
{
    bool ok;
    int newFillStyle = QInputDialog::getInt(this, tr("S"), tr("Select fill style"), editor->getFillStyle(), 1, 14, 1, &ok);
    if (ok) editor->setFillStyle(static_cast<Qt::BrushStyle>(newFillStyle));
}
