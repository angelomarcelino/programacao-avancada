/****************************************************************************
** Meta object code from reading C++ file 'whatsclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../whatsclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'whatsclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WhatsClient_t {
    QByteArrayData data[23];
    char stringdata[427];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_WhatsClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_WhatsClient_t qt_meta_stringdata_WhatsClient = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 18),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 21),
QT_MOC_LITERAL(4, 54, 18),
QT_MOC_LITERAL(5, 73, 13),
QT_MOC_LITERAL(6, 87, 7),
QT_MOC_LITERAL(7, 95, 1),
QT_MOC_LITERAL(8, 97, 25),
QT_MOC_LITERAL(9, 123, 22),
QT_MOC_LITERAL(10, 146, 22),
QT_MOC_LITERAL(11, 169, 17),
QT_MOC_LITERAL(12, 187, 11),
QT_MOC_LITERAL(13, 199, 27),
QT_MOC_LITERAL(14, 227, 27),
QT_MOC_LITERAL(15, 255, 30),
QT_MOC_LITERAL(16, 286, 23),
QT_MOC_LITERAL(17, 310, 23),
QT_MOC_LITERAL(18, 334, 29),
QT_MOC_LITERAL(19, 364, 3),
QT_MOC_LITERAL(20, 368, 6),
QT_MOC_LITERAL(21, 375, 24),
QT_MOC_LITERAL(22, 400, 25)
    },
    "WhatsClient\0interfaceConectada\0\0"
    "interfaceDesconectada\0RedesenhaConversas\0"
    "RedesenhaMsgs\0MsgErro\0S\0"
    "slotinterfaceDesconectada\0"
    "slotinterfaceConectada\0slotRedesenhaConversas\0"
    "slotRedesenhaMsgs\0slotMsgErro\0"
    "on_actionConectar_triggered\0"
    "on_actionNovaConv_triggered\0"
    "on_actionDesconectar_triggered\0"
    "on_actionSair_triggered\0on_enviarButton_clicked\0"
    "on_conversasTable_cellClicked\0row\0"
    "column\0on_msgEdit_returnPressed\0"
    "on_actionApagar_triggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WhatsClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06,
       3,    0,  105,    2, 0x06,
       4,    0,  106,    2, 0x06,
       5,    0,  107,    2, 0x06,
       6,    1,  108,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    0,  111,    2, 0x0a,
       9,    0,  112,    2, 0x0a,
      10,    0,  113,    2, 0x0a,
      11,    0,  114,    2, 0x0a,
      12,    1,  115,    2, 0x0a,
      13,    0,  118,    2, 0x08,
      14,    0,  119,    2, 0x08,
      15,    0,  120,    2, 0x08,
      16,    0,  121,    2, 0x08,
      17,    0,  122,    2, 0x08,
      18,    2,  123,    2, 0x08,
      21,    0,  128,    2, 0x08,
      22,    0,  129,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   19,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WhatsClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WhatsClient *_t = static_cast<WhatsClient *>(_o);
        switch (_id) {
        case 0: _t->interfaceConectada(); break;
        case 1: _t->interfaceDesconectada(); break;
        case 2: _t->RedesenhaConversas(); break;
        case 3: _t->RedesenhaMsgs(); break;
        case 4: _t->MsgErro((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slotinterfaceDesconectada(); break;
        case 6: _t->slotinterfaceConectada(); break;
        case 7: _t->slotRedesenhaConversas(); break;
        case 8: _t->slotRedesenhaMsgs(); break;
        case 9: _t->slotMsgErro((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->on_actionConectar_triggered(); break;
        case 11: _t->on_actionNovaConv_triggered(); break;
        case 12: _t->on_actionDesconectar_triggered(); break;
        case 13: _t->on_actionSair_triggered(); break;
        case 14: _t->on_enviarButton_clicked(); break;
        case 15: _t->on_conversasTable_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->on_msgEdit_returnPressed(); break;
        case 17: _t->on_actionApagar_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WhatsClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WhatsClient::interfaceConectada)) {
                *result = 0;
            }
        }
        {
            typedef void (WhatsClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WhatsClient::interfaceDesconectada)) {
                *result = 1;
            }
        }
        {
            typedef void (WhatsClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WhatsClient::RedesenhaConversas)) {
                *result = 2;
            }
        }
        {
            typedef void (WhatsClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WhatsClient::RedesenhaMsgs)) {
                *result = 3;
            }
        }
        {
            typedef void (WhatsClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WhatsClient::MsgErro)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject WhatsClient::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WhatsClient.data,
      qt_meta_data_WhatsClient,  qt_static_metacall, 0, 0}
};


const QMetaObject *WhatsClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WhatsClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WhatsClient.stringdata))
        return static_cast<void*>(const_cast< WhatsClient*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WhatsClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void WhatsClient::interfaceConectada()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WhatsClient::interfaceDesconectada()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WhatsClient::RedesenhaConversas()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void WhatsClient::RedesenhaMsgs()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void WhatsClient::MsgErro(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
