/****************************************************************************
** Meta object code from reading C++ file 'SimNode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SimNode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimNode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimNode_t {
    QByteArrayData data[10];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimNode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimNode_t qt_meta_stringdata_SimNode = {
    {
QT_MOC_LITERAL(0, 0, 7), // "SimNode"
QT_MOC_LITERAL(1, 8, 15), // "slot_subscriber"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 20), // "slot_only_subscriber"
QT_MOC_LITERAL(4, 46, 23), // "slot_recv_subsubscriber"
QT_MOC_LITERAL(5, 70, 25), // "slot_command_subpublisher"
QT_MOC_LITERAL(6, 96, 21), // "slot_feedbutton_group"
QT_MOC_LITERAL(7, 118, 2), // "id"
QT_MOC_LITERAL(8, 121, 26), // "slot_feedpause_buttongroup"
QT_MOC_LITERAL(9, 148, 25) // "slot_feedstop_buttongroup"

    },
    "SimNode\0slot_subscriber\0\0slot_only_subscriber\0"
    "slot_recv_subsubscriber\0"
    "slot_command_subpublisher\0"
    "slot_feedbutton_group\0id\0"
    "slot_feedpause_buttongroup\0"
    "slot_feedstop_buttongroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimNode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SimNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimNode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_subscriber(); break;
        case 1: _t->slot_only_subscriber(); break;
        case 2: _t->slot_recv_subsubscriber(); break;
        case 3: _t->slot_command_subpublisher(); break;
        case 4: _t->slot_feedbutton_group((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_feedpause_buttongroup(); break;
        case 6: _t->slot_feedstop_buttongroup(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SimNode::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SimNode.data,
    qt_meta_data_SimNode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimNode.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SimNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
