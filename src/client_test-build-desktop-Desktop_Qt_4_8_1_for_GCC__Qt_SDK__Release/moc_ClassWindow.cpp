/****************************************************************************
** Meta object code from reading C++ file 'ClassWindow.h'
**
** Created: Tue Apr 2 18:20:44 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/ClassWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClassWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,
      43,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClassWindow[] = {
    "ClassWindow\0\0choiceClass1()\0choiceClass2()\0"
    "choiceClass3()\0"
};

void ClassWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClassWindow *_t = static_cast<ClassWindow *>(_o);
        switch (_id) {
        case 0: _t->choiceClass1(); break;
        case 1: _t->choiceClass2(); break;
        case 2: _t->choiceClass3(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ClassWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClassWindow,
      qt_meta_data_ClassWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassWindow))
        return static_cast<void*>(const_cast< ClassWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClassWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
