#include "LineEdit.h"
#include <QDebug>
#include <QKeyEvent>

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}

void LineEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
    if(event->matches(QKeySequence::Copy)) {
        qDebug() << "Copy value in the clipboard";
        emit copyToClipboard();
    }
}
