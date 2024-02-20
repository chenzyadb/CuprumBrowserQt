/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../windows/MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[36];
    char stringdata0[11];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[23];
    char stringdata5[6];
    char stringdata6[22];
    char stringdata7[5];
    char stringdata8[27];
    char stringdata9[11];
    char stringdata10[17];
    char stringdata11[28];
    char stringdata12[27];
    char stringdata13[8];
    char stringdata14[17];
    char stringdata15[13];
    char stringdata16[10];
    char stringdata17[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 20),  // "Browser_onUrlChanged"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 3),  // "url"
        QT_MOC_LITERAL(37, 22),  // "Browser_onTitleChanged"
        QT_MOC_LITERAL(60, 5),  // "title"
        QT_MOC_LITERAL(66, 21),  // "Browser_onIconChanged"
        QT_MOC_LITERAL(88, 4),  // "icon"
        QT_MOC_LITERAL(93, 26),  // "Browser_onNewWindowCreated"
        QT_MOC_LITERAL(120, 10),  // "CuWebView*"
        QT_MOC_LITERAL(131, 16),  // "newBrowserWindow"
        QT_MOC_LITERAL(148, 27),  // "Browser_onDownloadRequested"
        QT_MOC_LITERAL(176, 26),  // "QWebEngineDownloadRequest*"
        QT_MOC_LITERAL(203, 7),  // "request"
        QT_MOC_LITERAL(211, 16),  // "ChangeTopWindow_"
        QT_MOC_LITERAL(228, 12),  // "CuTabButton*"
        QT_MOC_LITERAL(241, 9),  // "tabButton"
        QT_MOC_LITERAL(251, 20)   // "RemoveBrowserWindow_"
    },
    "MainWindow",
    "Browser_onUrlChanged",
    "",
    "url",
    "Browser_onTitleChanged",
    "title",
    "Browser_onIconChanged",
    "icon",
    "Browser_onNewWindowCreated",
    "CuWebView*",
    "newBrowserWindow",
    "Browser_onDownloadRequested",
    "QWebEngineDownloadRequest*",
    "request",
    "ChangeTopWindow_",
    "CuTabButton*",
    "tabButton",
    "RemoveBrowserWindow_"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x08,    1 /* Private */,
       4,    1,   59,    2, 0x08,    3 /* Private */,
       6,    1,   62,    2, 0x08,    5 /* Private */,
       8,    1,   65,    2, 0x08,    7 /* Private */,
      11,    1,   68,    2, 0x08,    9 /* Private */,
      14,    1,   71,    2, 0x08,   11 /* Private */,
      17,    1,   74,    2, 0x08,   13 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QIcon,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'Browser_onUrlChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>,
        // method 'Browser_onTitleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'Browser_onIconChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QIcon &, std::false_type>,
        // method 'Browser_onNewWindowCreated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CuWebView *, std::false_type>,
        // method 'Browser_onDownloadRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWebEngineDownloadRequest *, std::false_type>,
        // method 'ChangeTopWindow_'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CuTabButton *, std::false_type>,
        // method 'RemoveBrowserWindow_'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<CuTabButton *, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Browser_onUrlChanged((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 1: _t->Browser_onTitleChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->Browser_onIconChanged((*reinterpret_cast< std::add_pointer_t<QIcon>>(_a[1]))); break;
        case 3: _t->Browser_onNewWindowCreated((*reinterpret_cast< std::add_pointer_t<CuWebView*>>(_a[1]))); break;
        case 4: _t->Browser_onDownloadRequested((*reinterpret_cast< std::add_pointer_t<QWebEngineDownloadRequest*>>(_a[1]))); break;
        case 5: _t->ChangeTopWindow_((*reinterpret_cast< std::add_pointer_t<CuTabButton*>>(_a[1]))); break;
        case 6: _t->RemoveBrowserWindow_((*reinterpret_cast< std::add_pointer_t<CuTabButton*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CuWebView* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWebEngineDownloadRequest* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CuTabButton* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CuTabButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
