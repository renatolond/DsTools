/****************************************************************************
** Meta object code from reading C++ file 'tabbg.h'
**
** Created: Tue Aug 24 18:25:28 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tabbg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabbg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TabBG[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      29,    6,    6,    6, 0x08,
      54,    6,    6,    6, 0x08,
      79,    6,    6,    6, 0x08,
     107,   99,    6,    6, 0x08,
     132,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TabBG[] = {
    "TabBG\0\0on_btExport_clicked()\0"
    "on_btExportPng_clicked()\0"
    "on_btHighlight_clicked()\0on_btDump_clicked()\0"
    "checked\0on_btPaint_toggled(bool)\0"
    "on_btConvert_clicked()\0"
};

const QMetaObject TabBG::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TabBG,
      qt_meta_data_TabBG, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TabBG::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TabBG::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TabBG::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TabBG))
        return static_cast<void*>(const_cast< TabBG*>(this));
    return QWidget::qt_metacast(_clname);
}

int TabBG::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_btExport_clicked(); break;
        case 1: on_btExportPng_clicked(); break;
        case 2: on_btHighlight_clicked(); break;
        case 3: on_btDump_clicked(); break;
        case 4: on_btPaint_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: on_btConvert_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
