/****************************************************************************
** Meta object code from reading C++ file 'MyPublisherFullSpeedThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MyPublisherFullSpeedThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyPublisherFullSpeedThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyPublisherFullSpeedThread_t {
    QByteArrayData data[8];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPublisherFullSpeedThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPublisherFullSpeedThread_t qt_meta_stringdata_MyPublisherFullSpeedThread = {
    {
QT_MOC_LITERAL(0, 0, 26), // "MyPublisherFullSpeedThread"
QT_MOC_LITERAL(1, 27, 16), // "slotsimPublisher"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 12), // "slotsimPause"
QT_MOC_LITERAL(4, 58, 11), // "slotsimGoOn"
QT_MOC_LITERAL(5, 70, 11), // "slotsimQuit"
QT_MOC_LITERAL(6, 82, 9), // "ishistory"
QT_MOC_LITERAL(7, 92, 3) // "num"

    },
    "MyPublisherFullSpeedThread\0slotsimPublisher\0"
    "\0slotsimPause\0slotsimGoOn\0slotsimQuit\0"
    "ishistory\0num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPublisherFullSpeedThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,    7,

       0        // eod
};

void MyPublisherFullSpeedThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyPublisherFullSpeedThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotsimPublisher(); break;
        case 1: _t->slotsimPause(); break;
        case 2: _t->slotsimGoOn(); break;
        case 3: _t->slotsimQuit(); break;
        case 4: { bool _r = _t->ishistory((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyPublisherFullSpeedThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MyPublisherFullSpeedThread.data,
    qt_meta_data_MyPublisherFullSpeedThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyPublisherFullSpeedThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPublisherFullSpeedThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyPublisherFullSpeedThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyPublisherFullSpeedThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
