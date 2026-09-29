#include "MacOsGlobalHotkey.h"
#include <Carbon/Carbon.h>
#include <QMetaObject>
#include <QKeySequence>

class MacOsGlobalHotkey::Private
{
public:
    EventHotKeyRef hotKey = nullptr;
    EventHandlerRef eventHandler = nullptr;
    MacOsGlobalHotkey *q = nullptr;
};

static OSStatus hotKeyHandler(
    EventHandlerCallRef,
    EventRef event,
    void *userData)
{
    auto *self = static_cast<MacOsGlobalHotkey *>(userData);

    EventHotKeyID hotKeyId;

    GetEventParameter(
        event,
        kEventParamDirectObject,
        typeEventHotKeyID,
        nullptr,
        sizeof(hotKeyId),
        nullptr,
        &hotKeyId
    );

    if (hotKeyId.id == 1) {
        QMetaObject::invokeMethod(
            self,
            &MacOsGlobalHotkey::activated,
            Qt::QueuedConnection
        );
    }

    return noErr;
}

MacOsGlobalHotkey::MacOsGlobalHotkey(QObject *parent)
    : QObject(parent),
      d(new Private)
{
    d->q = this;

    EventTypeSpec eventType;
    eventType.eventClass = kEventClassKeyboard;
    eventType.eventKind = kEventHotKeyPressed;

    InstallEventHandler(
        GetApplicationEventTarget(),
        NewEventHandlerUPP(hotKeyHandler),
        1,
        &eventType,
        this,
        &d->eventHandler
    );
}

MacOsGlobalHotkey::~MacOsGlobalHotkey()
{
    unregisterHotkey();

    if (d->eventHandler) {
        RemoveEventHandler(d->eventHandler);
    }

    delete d;
}

bool MacOsGlobalHotkey::registerHotkey(const QKeySequence& sequence) const
{
    if (sequence.isEmpty() || sequence.count() != 1)
        return false;

    const QKeyCombination combination = sequence[0];
    const Qt::Key key = combination.key();
    const Qt::KeyboardModifiers qtModifiers = combination.keyboardModifiers();

    unsigned int modifiers = 0;

    if (qtModifiers & Qt::ControlModifier)
        modifiers |= controlKey;

    if (qtModifiers & Qt::AltModifier)
        modifiers |= optionKey;

    if (qtModifiers & Qt::ShiftModifier)
        modifiers |= shiftKey;

    if (qtModifiers & Qt::MetaModifier)
        modifiers |= cmdKey;

    const unsigned int keyCode = qtKeyToMacKeyCode(key);

    if (keyCode == UINT_MAX)
        return false;

    return registerHotkey(keyCode, modifiers);
}

bool MacOsGlobalHotkey::registerHotkey(unsigned int keyCode, unsigned int modifiers) const
{
    unregisterHotkey();

    EventHotKeyID hotKeyId;
    hotKeyId.signature = 'CWHT';
    hotKeyId.id = 1;

    OSStatus status = RegisterEventHotKey(
        keyCode,
        modifiers,
        hotKeyId,
        GetApplicationEventTarget(),
        0,
        &d->hotKey
    );

    return status == noErr;
}

void MacOsGlobalHotkey::unregisterHotkey() const
{
    if (d->hotKey) {
        UnregisterEventHotKey(d->hotKey);
        d->hotKey = nullptr;
    }
}

unsigned int MacOsGlobalHotkey::qtKeyToMacKeyCode(Qt::Key key) const
{
    switch (key) {
    case Qt::Key_A: return kVK_ANSI_A;
    case Qt::Key_B: return kVK_ANSI_B;
    case Qt::Key_C: return kVK_ANSI_C;
    case Qt::Key_D: return kVK_ANSI_D;
    case Qt::Key_E: return kVK_ANSI_E;
    case Qt::Key_F: return kVK_ANSI_F;
    case Qt::Key_G: return kVK_ANSI_G;
    case Qt::Key_H: return kVK_ANSI_H;
    case Qt::Key_I: return kVK_ANSI_I;
    case Qt::Key_J: return kVK_ANSI_J;
    case Qt::Key_K: return kVK_ANSI_K;
    case Qt::Key_L: return kVK_ANSI_L;
    case Qt::Key_M: return kVK_ANSI_M;
    case Qt::Key_N: return kVK_ANSI_N;
    case Qt::Key_O: return kVK_ANSI_O;
    case Qt::Key_P: return kVK_ANSI_P;
    case Qt::Key_Q: return kVK_ANSI_Q;
    case Qt::Key_R: return kVK_ANSI_R;
    case Qt::Key_S: return kVK_ANSI_S;
    case Qt::Key_T: return kVK_ANSI_T;
    case Qt::Key_U: return kVK_ANSI_U;
    case Qt::Key_V: return kVK_ANSI_V;
    case Qt::Key_W: return kVK_ANSI_W;
    case Qt::Key_X: return kVK_ANSI_X;
    case Qt::Key_Y: return kVK_ANSI_Y;
    case Qt::Key_Z: return kVK_ANSI_Z;
    case Qt::Key_0: return kVK_ANSI_0;
    case Qt::Key_1: return kVK_ANSI_1;
    case Qt::Key_2: return kVK_ANSI_2;
    case Qt::Key_3: return kVK_ANSI_3;
    case Qt::Key_4: return kVK_ANSI_4;
    case Qt::Key_5: return kVK_ANSI_5;
    case Qt::Key_6: return kVK_ANSI_6;
    case Qt::Key_7: return kVK_ANSI_7;
    case Qt::Key_8: return kVK_ANSI_8;
    case Qt::Key_9: return kVK_ANSI_9;
    case Qt::Key_Space:     return kVK_Space;
    case Qt::Key_Return:    return kVK_Return;
    case Qt::Key_Enter:     return kVK_ANSI_KeypadEnter;
    case Qt::Key_Tab:       return kVK_Tab;
    case Qt::Key_Backspace: return kVK_Delete;
    case Qt::Key_Delete:    return kVK_ForwardDelete;
    case Qt::Key_Escape:    return kVK_Escape;
    case Qt::Key_Left:  return kVK_LeftArrow;
    case Qt::Key_Right: return kVK_RightArrow;
    case Qt::Key_Up:    return kVK_UpArrow;
    case Qt::Key_Down:  return kVK_DownArrow;
    case Qt::Key_F1:  return kVK_F1;
    case Qt::Key_F2:  return kVK_F2;
    case Qt::Key_F3:  return kVK_F3;
    case Qt::Key_F4:  return kVK_F4;
    case Qt::Key_F5:  return kVK_F5;
    case Qt::Key_F6:  return kVK_F6;
    case Qt::Key_F7:  return kVK_F7;
    case Qt::Key_F8:  return kVK_F8;
    case Qt::Key_F9:  return kVK_F9;
    case Qt::Key_F10: return kVK_F10;
    case Qt::Key_F11: return kVK_F11;
    case Qt::Key_F12: return kVK_F12;
    default:
        return UINT_MAX;
    }
}