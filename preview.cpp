#include <QtWidgets>
#include "preview.h"
#include "object.h"

Preview::Preview(Object *o, QWidget *parent) : QWidget(parent)
{
    setObject(o);
    QTimer *timer = new QTimer();
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(play()));
    timer->start(48);
}

void Preview::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    object->isKeyframe(currentPosition) ?
    painter.drawImage(event->rect(), *object->getKeyframeImageAt(currentPosition), event->rect()) :
    painter.drawImage(event->rect(), *object->getKeyframeImageAt(object->getPrevKeyframePos(currentPosition)), event->rect());
}

void Preview::focusOutEvent(QFocusEvent*){}

void Preview::play()
{
    currentPosition += 1;
    if (currentPosition > object->getLastKeyframePos()) currentPosition = 0;
    update();
}

void Preview::pause(){}
