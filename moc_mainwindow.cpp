/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   11,   11,   11, 0x0a,
      56,   11,   11,   11, 0x0a,
      74,   11,   11,   11, 0x0a,
      86,   11,   11,   11, 0x0a,
      98,   11,   11,   11, 0x0a,
     111,   11,   11,   11, 0x0a,
     130,   11,   11,   11, 0x0a,
     138,   11,   11,   11, 0x0a,
     155,   11,   11,   11, 0x0a,
     166,   11,   11,   11, 0x0a,
     189,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0dataAcquired()\0timeout()\0"
    "startReadingPort()\0stopReadingPort()\0"
    "saveCurve()\0loadCurve()\0clearCurve()\0"
    "selectSerialPort()\0about()\0onDataReceived()\0"
    "calculer()\0onSendCommandPressed()\0"
    "updateQuery()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->dataAcquired(); break;
        case 1: _t->timeout(); break;
        case 2: _t->startReadingPort(); break;
        case 3: _t->stopReadingPort(); break;
        case 4: _t->saveCurve(); break;
        case 5: _t->loadCurve(); break;
        case 6: _t->clearCurve(); break;
        case 7: _t->selectSerialPort(); break;
        case 8: _t->about(); break;
        case 9: _t->onDataReceived(); break;
        case 10: _t->calculer(); break;
        case 11: _t->onSendCommandPressed(); break;
        case 12: _t->updateQuery(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::dataAcquired()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
