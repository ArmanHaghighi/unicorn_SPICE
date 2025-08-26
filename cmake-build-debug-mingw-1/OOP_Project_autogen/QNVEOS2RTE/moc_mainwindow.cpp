/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../View/spice/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Spice__MainWindow_t {
    QByteArrayData data[55];
    char stringdata0[916];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Spice__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Spice__MainWindow_t qt_meta_stringdata_Spice__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Spice::MainWindow"
QT_MOC_LITERAL(1, 18, 28), // "nodeNamePropagationRequested"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 5), // "Node*"
QT_MOC_LITERAL(4, 54, 6), // "source"
QT_MOC_LITERAL(5, 61, 4), // "name"
QT_MOC_LITERAL(6, 66, 22), // "on_actionNew_triggered"
QT_MOC_LITERAL(7, 89, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(8, 113, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(9, 137, 28), // "on_actionTransient_triggered"
QT_MOC_LITERAL(10, 166, 27), // "on_actionAc_Sweep_triggered"
QT_MOC_LITERAL(11, 194, 27), // "on_actionDc_Sweep_triggered"
QT_MOC_LITERAL(12, 222, 24), // "on_actionPhase_triggered"
QT_MOC_LITERAL(13, 247, 25), // "on_actionEscape_triggered"
QT_MOC_LITERAL(14, 273, 25), // "on_actionResistor_toggled"
QT_MOC_LITERAL(15, 299, 4), // "arg1"
QT_MOC_LITERAL(16, 304, 25), // "on_actionInductor_toggled"
QT_MOC_LITERAL(17, 330, 26), // "on_actionDuplicate_toggled"
QT_MOC_LITERAL(18, 357, 23), // "on_actionDelete_toggled"
QT_MOC_LITERAL(19, 381, 21), // "on_actionWire_toggled"
QT_MOC_LITERAL(20, 403, 26), // "on_actionCapacitor_toggled"
QT_MOC_LITERAL(21, 430, 28), // "on_actionAdd_Element_toggled"
QT_MOC_LITERAL(22, 459, 20), // "on_actionGnd_toggled"
QT_MOC_LITERAL(23, 480, 18), // "handleMouseRelease"
QT_MOC_LITERAL(24, 499, 12), // "QMouseEvent*"
QT_MOC_LITERAL(25, 512, 5), // "event"
QT_MOC_LITERAL(26, 518, 16), // "createJunctionAt"
QT_MOC_LITERAL(27, 535, 8), // "scenePos"
QT_MOC_LITERAL(28, 544, 10), // "createWire"
QT_MOC_LITERAL(29, 555, 5), // "start"
QT_MOC_LITERAL(30, 561, 3), // "end"
QT_MOC_LITERAL(31, 565, 13), // "wireStartNode"
QT_MOC_LITERAL(32, 579, 25), // "handleNodeNamePropagation"
QT_MOC_LITERAL(33, 605, 29), // "on_actionAdd_Cursor_triggered"
QT_MOC_LITERAL(34, 635, 32), // "on_actionRemove_Cursor_triggered"
QT_MOC_LITERAL(35, 668, 21), // "on_actionSnap_toggled"
QT_MOC_LITERAL(36, 690, 23), // "on_actionCursor_toggled"
QT_MOC_LITERAL(37, 714, 31), // "on_actionVoltageProbe_triggered"
QT_MOC_LITERAL(38, 746, 7), // "checked"
QT_MOC_LITERAL(39, 754, 31), // "on_actionCurrentProbe_triggered"
QT_MOC_LITERAL(40, 786, 29), // "on_actionPowerProbe_triggered"
QT_MOC_LITERAL(41, 816, 20), // "onAddElementAccepted"
QT_MOC_LITERAL(42, 837, 4), // "type"
QT_MOC_LITERAL(43, 842, 2), // "n1"
QT_MOC_LITERAL(44, 845, 2), // "n2"
QT_MOC_LITERAL(45, 848, 5), // "value"
QT_MOC_LITERAL(46, 854, 9), // "onRunTran"
QT_MOC_LITERAL(47, 864, 5), // "tstop"
QT_MOC_LITERAL(48, 870, 2), // "dt"
QT_MOC_LITERAL(49, 873, 10), // "probeNodes"
QT_MOC_LITERAL(50, 884, 6), // "onWave"
QT_MOC_LITERAL(51, 891, 4), // "node"
QT_MOC_LITERAL(52, 896, 15), // "QVector<double>"
QT_MOC_LITERAL(53, 912, 1), // "t"
QT_MOC_LITERAL(54, 914, 1) // "v"

    },
    "Spice::MainWindow\0nodeNamePropagationRequested\0"
    "\0Node*\0source\0name\0on_actionNew_triggered\0"
    "on_actionOpen_triggered\0on_actionSave_triggered\0"
    "on_actionTransient_triggered\0"
    "on_actionAc_Sweep_triggered\0"
    "on_actionDc_Sweep_triggered\0"
    "on_actionPhase_triggered\0"
    "on_actionEscape_triggered\0"
    "on_actionResistor_toggled\0arg1\0"
    "on_actionInductor_toggled\0"
    "on_actionDuplicate_toggled\0"
    "on_actionDelete_toggled\0on_actionWire_toggled\0"
    "on_actionCapacitor_toggled\0"
    "on_actionAdd_Element_toggled\0"
    "on_actionGnd_toggled\0handleMouseRelease\0"
    "QMouseEvent*\0event\0createJunctionAt\0"
    "scenePos\0createWire\0start\0end\0"
    "wireStartNode\0handleNodeNamePropagation\0"
    "on_actionAdd_Cursor_triggered\0"
    "on_actionRemove_Cursor_triggered\0"
    "on_actionSnap_toggled\0on_actionCursor_toggled\0"
    "on_actionVoltageProbe_triggered\0checked\0"
    "on_actionCurrentProbe_triggered\0"
    "on_actionPowerProbe_triggered\0"
    "onAddElementAccepted\0type\0n1\0n2\0value\0"
    "onRunTran\0tstop\0dt\0probeNodes\0onWave\0"
    "node\0QVector<double>\0t\0v"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Spice__MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  174,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  179,    2, 0x08 /* Private */,
       7,    0,  180,    2, 0x08 /* Private */,
       8,    0,  181,    2, 0x08 /* Private */,
       9,    0,  182,    2, 0x08 /* Private */,
      10,    0,  183,    2, 0x08 /* Private */,
      11,    0,  184,    2, 0x08 /* Private */,
      12,    0,  185,    2, 0x08 /* Private */,
      13,    0,  186,    2, 0x08 /* Private */,
      14,    1,  187,    2, 0x08 /* Private */,
      16,    1,  190,    2, 0x08 /* Private */,
      17,    1,  193,    2, 0x08 /* Private */,
      18,    1,  196,    2, 0x08 /* Private */,
      19,    1,  199,    2, 0x08 /* Private */,
      20,    1,  202,    2, 0x08 /* Private */,
      21,    1,  205,    2, 0x08 /* Private */,
      22,    1,  208,    2, 0x08 /* Private */,
      23,    1,  211,    2, 0x08 /* Private */,
      26,    1,  214,    2, 0x08 /* Private */,
      28,    3,  217,    2, 0x08 /* Private */,
      28,    2,  224,    2, 0x28 /* Private | MethodCloned */,
      32,    2,  229,    2, 0x08 /* Private */,
      33,    0,  234,    2, 0x08 /* Private */,
      34,    0,  235,    2, 0x08 /* Private */,
      35,    1,  236,    2, 0x08 /* Private */,
      36,    1,  239,    2, 0x08 /* Private */,
      37,    1,  242,    2, 0x08 /* Private */,
      39,    1,  245,    2, 0x08 /* Private */,
      40,    1,  248,    2, 0x08 /* Private */,
      41,    5,  251,    2, 0x08 /* Private */,
      46,    3,  262,    2, 0x08 /* Private */,
      50,    3,  269,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, 0x80000000 | 24,   25,
    0x80000000 | 3, QMetaType::QPointF,   27,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,   29,   30,   31,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   29,   30,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Double,   42,    5,   43,   44,   45,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::QStringList,   47,   48,   49,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 52, 0x80000000 | 52,   51,   53,   54,

       0        // eod
};

void Spice::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->nodeNamePropagationRequested((*reinterpret_cast< Node*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->on_actionNew_triggered(); break;
        case 2: _t->on_actionOpen_triggered(); break;
        case 3: _t->on_actionSave_triggered(); break;
        case 4: _t->on_actionTransient_triggered(); break;
        case 5: _t->on_actionAc_Sweep_triggered(); break;
        case 6: _t->on_actionDc_Sweep_triggered(); break;
        case 7: _t->on_actionPhase_triggered(); break;
        case 8: _t->on_actionEscape_triggered(); break;
        case 9: _t->on_actionResistor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_actionInductor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_actionDuplicate_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_actionDelete_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_actionWire_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_actionCapacitor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_actionAdd_Element_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_actionGnd_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->handleMouseRelease((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 18: { Node* _r = _t->createJunctionAt((*reinterpret_cast< const QPointF(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Node**>(_a[0]) = std::move(_r); }  break;
        case 19: _t->createWire((*reinterpret_cast< Node*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2])),(*reinterpret_cast< Node*(*)>(_a[3]))); break;
        case 20: _t->createWire((*reinterpret_cast< Node*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2]))); break;
        case 21: _t->handleNodeNamePropagation((*reinterpret_cast< Node*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 22: _t->on_actionAdd_Cursor_triggered(); break;
        case 23: _t->on_actionRemove_Cursor_triggered(); break;
        case 24: _t->on_actionSnap_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_actionCursor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_actionVoltageProbe_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_actionCurrentProbe_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_actionPowerProbe_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->onAddElementAccepted((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 30: _t->onRunTran((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 31: _t->onWave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2])),(*reinterpret_cast< QVector<double>(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(Node * , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::nodeNamePropagationRequested)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Spice::MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Spice__MainWindow.data,
    qt_meta_data_Spice__MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Spice::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Spice::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Spice__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Spice::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void Spice::MainWindow::nodeNamePropagationRequested(Node * _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Spice__SchematicView_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Spice__SchematicView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Spice__SchematicView_t qt_meta_stringdata_Spice__SchematicView = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Spice::SchematicView"
QT_MOC_LITERAL(1, 21, 12), // "mousePressed"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 48, 5), // "event"
QT_MOC_LITERAL(5, 54, 13) // "mouseReleased"

    },
    "Spice::SchematicView\0mousePressed\0\0"
    "QMouseEvent*\0event\0mouseReleased"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Spice__SchematicView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Spice::SchematicView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SchematicView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mousePressed((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseReleased((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SchematicView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SchematicView::mousePressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SchematicView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SchematicView::mouseReleased)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Spice::SchematicView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_Spice__SchematicView.data,
    qt_meta_data_Spice__SchematicView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Spice::SchematicView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Spice::SchematicView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Spice__SchematicView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int Spice::SchematicView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Spice::SchematicView::mousePressed(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Spice::SchematicView::mouseReleased(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
