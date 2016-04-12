/****************************************************************************
** Meta object code from reading C++ file 'mainview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../RaspGui/mainview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   25,   25,   25, 0x0a,
      26,   25,   25,   25, 0x0a,
      39,   25,   25,   25, 0x0a,
      54,   25,   25,   25, 0x0a,
      68,   25,   25,   25, 0x0a,
      79,   25,   25,   25, 0x0a,
      92,   25,   25,   25, 0x0a,
     103,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainView[] = {
    "MainView\0generateRooms()\0\0roomChange()\0"
    "updateStruct()\0updateRooms()\0updateDB()\0"
    "clearNames()\0addNames()\0spinValueChange()\0"
};

void MainView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainView *_t = static_cast<MainView *>(_o);
        switch (_id) {
        case 0: _t->generateRooms(); break;
        case 1: _t->roomChange(); break;
        case 2: _t->updateStruct(); break;
        case 3: _t->updateRooms(); break;
        case 4: _t->updateDB(); break;
        case 5: _t->clearNames(); break;
        case 6: _t->addNames(); break;
        case 7: _t->spinValueChange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainView,
      qt_meta_data_MainView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainView))
        return static_cast<void*>(const_cast< MainView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
