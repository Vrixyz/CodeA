/****************************************************************************
** Meta object code from reading C++ file 'nm.h'
**
** Created: Tue Mar 5 16:17:15 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Nm[] = {

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
       4,    3,    3,    3, 0x0a,
      24,    3,    3,    3, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Nm[] = {
    "Nm\0\0ReceiveFromServer()\0SocError()\0"
};

void Nm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Nm *_t = static_cast<Nm *>(_o);
        switch (_id) {
        case 0: _t->ReceiveFromServer(); break;
        case 1: _t->SocError(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Nm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Nm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Nm,
      qt_meta_data_Nm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Nm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Nm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Nm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Nm))
        return static_cast<void*>(const_cast< Nm*>(this));
    return QObject::qt_metacast(_clname);
}

int Nm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
