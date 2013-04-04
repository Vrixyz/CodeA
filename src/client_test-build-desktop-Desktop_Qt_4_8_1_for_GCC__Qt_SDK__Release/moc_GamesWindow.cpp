/****************************************************************************
** Meta object code from reading C++ file 'GamesWindow.h'
**
** Created: Tue Apr 2 18:20:42 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/GamesWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GamesWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GamesWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      23,   12,   12,   12, 0x0a,
      34,   12,   12,   12, 0x0a,
      48,   12,   12,   12, 0x0a,
      62,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GamesWindow[] = {
    "GamesWindow\0\0sendMsg()\0RecvData()\0"
    "tryToCoGame()\0refreshServ()\0"
    "tryToMatchmaking()\0"
};

void GamesWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GamesWindow *_t = static_cast<GamesWindow *>(_o);
        switch (_id) {
        case 0: _t->sendMsg(); break;
        case 1: _t->RecvData(); break;
        case 2: _t->tryToCoGame(); break;
        case 3: _t->refreshServ(); break;
        case 4: _t->tryToMatchmaking(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GamesWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GamesWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GamesWindow,
      qt_meta_data_GamesWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GamesWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GamesWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GamesWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GamesWindow))
        return static_cast<void*>(const_cast< GamesWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int GamesWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
