#pragma once

#include <QObject>

class MacOsGlobalHotkey : public QObject
{
    Q_OBJECT

public:
    explicit MacOsGlobalHotkey(QObject *parent = nullptr);
    ~MacOsGlobalHotkey();

    bool registerHotkey(const QKeySequence& sequence) const;
    bool registerHotkey(unsigned int keyCode, unsigned int modifiers) const;
    void unregisterHotkey() const;

private:
    unsigned int qtKeyToMacKeyCode(Qt::Key key) const;

signals:
    void activated();

private:
    class Private;
    Private *d;
};