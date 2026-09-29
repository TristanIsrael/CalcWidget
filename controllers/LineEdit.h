#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    LineEdit(QWidget* parent = 0);

signals:
    void copyToClipboard();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // LINEEDIT_H
