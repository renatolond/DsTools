/****************************************************************************
** Meta object code from reading C++ file 'spritesgraphicsview.h'
**
** Created: Tue Aug 24 22:38:02 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "spritesgraphicsview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spritesgraphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpritesGraphicsView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_SpritesGraphicsView[] = {
    "SpritesGraphicsView\0"
};

const QMetaObject SpritesGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_SpritesGraphicsView,
      qt_meta_data_SpritesGraphicsView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpritesGraphicsView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpritesGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpritesGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpritesGraphicsView))
        return static_cast<void*>(const_cast< SpritesGraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int SpritesGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
