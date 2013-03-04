/****************************************************************************
** Meta object code from reading C++ file 'AccWindow.h'
**
** Created: Fri Feb 22 21:21:28 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AccWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AccWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AccWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      21,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AccWindow[] = {
    "AccWindow\0\0checkCo()\0RecvInfosClient()\0"
};

void AccWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AccWindow *_t = static_cast<AccWindow *>(_o);
        switch (_id) {
        case 0: _t->checkCo(); break;
        case 1: _t->RecvInfosClient(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AccWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AccWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AccWindow,
      qt_meta_data_AccWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AccWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AccWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AccWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AccWindow))
        return static_cast<void*>(const_cast< AccWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int AccWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
