/****************************************************************************
** Meta object code from reading C++ file 'simcentre.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../simcentre.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simcentre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimCentre_t {
    QByteArrayData data[10];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimCentre_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimCentre_t qt_meta_stringdata_SimCentre = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SimCentre"
QT_MOC_LITERAL(1, 10, 14), // "slot_publisher"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "slot_pause_publisher"
QT_MOC_LITERAL(4, 47, 19), // "slot_stop_publisher"
QT_MOC_LITERAL(5, 67, 18), // "slot_cor_publisher"
QT_MOC_LITERAL(6, 86, 23), // "slot_recv_pubsubscriber"
QT_MOC_LITERAL(7, 110, 25), // "slot_command_pubpublisher"
QT_MOC_LITERAL(8, 136, 18), // "slot_skp_publisher"
QT_MOC_LITERAL(9, 155, 19) // "slot_only_publisher"

    },
    "SimCentre\0slot_publisher\0\0"
    "slot_pause_publisher\0slot_stop_publisher\0"
    "slot_cor_publisher\0slot_recv_pubsubscriber\0"
    "slot_command_pubpublisher\0slot_skp_publisher\0"
    "slot_only_publisher"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimCentre[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SimCentre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimCentre *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_publisher(); break;
        case 1: _t->slot_pause_publisher(); break;
        case 2: _t->slot_stop_publisher(); break;
        case 3: _t->slot_cor_publisher(); break;
        case 4: _t->slot_recv_pubsubscriber(); break;
        case 5: _t->slot_command_pubpublisher(); break;
        case 6: _t->slot_skp_publisher(); break;
        case 7: _t->slot_only_publisher(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SimCentre::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SimCentre.data,
    qt_meta_data_SimCentre,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimCentre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimCentre::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimCentre.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SimCentre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
