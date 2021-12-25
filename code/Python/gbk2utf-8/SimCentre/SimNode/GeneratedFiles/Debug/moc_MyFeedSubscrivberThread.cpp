/****************************************************************************
** Meta object code from reading C++ file 'MyFeedSubscrivberThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyFeedSubscrivberThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyFeedSubscrivberThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyFeedSubscriverThread_t {
    QByteArrayData data[10];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyFeedSubscriverThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyFeedSubscriverThread_t qt_meta_stringdata_MyFeedSubscriverThread = {
    {
QT_MOC_LITERAL(0, 0, 22), // "MyFeedSubscriverThread"
QT_MOC_LITERAL(1, 23, 18), // "workFinishedSignal"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 3), // "str"
QT_MOC_LITERAL(4, 47, 16), // "slotsimPublisher"
QT_MOC_LITERAL(5, 64, 12), // "slotsimPause"
QT_MOC_LITERAL(6, 77, 11), // "slotsimGoOn"
QT_MOC_LITERAL(7, 89, 11), // "slotsimQuit"
QT_MOC_LITERAL(8, 101, 7), // "history"
QT_MOC_LITERAL(9, 109, 20) // "generateRandomNumber"

    },
    "MyFeedSubscriverThread\0workFinishedSignal\0"
    "\0str\0slotsimPublisher\0slotsimPause\0"
    "slotsimGoOn\0slotsimQuit\0history\0"
    "generateRandomNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyFeedSubscriverThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x0a /* Public */,
       5,    0,   53,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Int,

       0        // eod
};

void MyFeedSubscriverThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyFeedSubscriverThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->workFinishedSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotsimPublisher(); break;
        case 2: _t->slotsimPause(); break;
        case 3: _t->slotsimGoOn(); break;
        case 4: _t->slotsimQuit(); break;
        case 5: { bool _r = _t->history();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->generateRandomNumber();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyFeedSubscriverThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyFeedSubscriverThread::workFinishedSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyFeedSubscriverThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MyFeedSubscriverThread.data,
    qt_meta_data_MyFeedSubscriverThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyFeedSubscriverThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyFeedSubscriverThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyFeedSubscriverThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyFeedSubscriverThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MyFeedSubscriverThread::workFinishedSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
