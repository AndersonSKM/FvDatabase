/****************************************************************************
** Meta object code from reading C++ file 'laycaneditorplugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../laycaneditorplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'laycaneditorplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LaycanEditor__Internal__LaycanEditorPlugin_t {
    QByteArrayData data[3];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LaycanEditor__Internal__LaycanEditorPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LaycanEditor__Internal__LaycanEditorPlugin_t qt_meta_stringdata_LaycanEditor__Internal__LaycanEditorPlugin = {
    {
QT_MOC_LITERAL(0, 0, 42), // "LaycanEditor::Internal::Layca..."
QT_MOC_LITERAL(1, 43, 13), // "triggerAction"
QT_MOC_LITERAL(2, 57, 0) // ""

    },
    "LaycanEditor::Internal::LaycanEditorPlugin\0"
    "triggerAction\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LaycanEditor__Internal__LaycanEditorPlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void LaycanEditor::Internal::LaycanEditorPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LaycanEditorPlugin *_t = static_cast<LaycanEditorPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->triggerAction(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject LaycanEditor::Internal::LaycanEditorPlugin::staticMetaObject = {
    { &ExtensionSystem::IPlugin::staticMetaObject, qt_meta_stringdata_LaycanEditor__Internal__LaycanEditorPlugin.data,
      qt_meta_data_LaycanEditor__Internal__LaycanEditorPlugin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LaycanEditor::Internal::LaycanEditorPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LaycanEditor::Internal::LaycanEditorPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LaycanEditor__Internal__LaycanEditorPlugin.stringdata0))
        return static_cast<void*>(const_cast< LaycanEditorPlugin*>(this));
    return ExtensionSystem::IPlugin::qt_metacast(_clname);
}

int LaycanEditor::Internal::LaycanEditorPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ExtensionSystem::IPlugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    '4',  0x02, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    ' ',  0x02, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '!',  0x00, 'o',  'r',  'g',  '.',  'q',  't', 
    '-',  'p',  'r',  'o',  'j',  'e',  'c',  't', 
    '.',  'Q',  't',  '.',  'Q',  't',  'C',  'r', 
    'e',  'a',  't',  'o',  'r',  'P',  'l',  'u', 
    'g',  'i',  'n',  0x00, 0x9b, 0x09, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x12, 0x00, 'L',  'a', 
    'y',  'c',  'a',  'n',  'E',  'd',  'i',  't', 
    'o',  'r',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x1a, 0xa0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x11, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0x94, 0x01, 0x00, 0x00,
    0x13, 0x00, 0x00, 0x00, 'p',  0x01, 0x00, 0x00,
    0x1b, 0x03, 0x00, 0x00, 0x04, 0x00, 'N',  'a', 
    'm',  'e',  0x00, 0x00, 0x0c, 0x00, 'L',  'a', 
    'y',  'c',  'a',  'n',  'E',  'd',  'i',  't', 
    'o',  'r',  0x00, 0x00, 0x1b, 0x07, 0x00, 0x00,
    0x07, 0x00, 'V',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x05, 0x00, '0',  '.', 
    '0',  '.',  '1',  0x00, 0x9b, 0x0a, 0x00, 0x00,
    0x0d, 0x00, 'C',  'o',  'm',  'p',  'a',  't', 
    'V',  'e',  'r',  's',  'i',  'o',  'n',  0x00,
    0x05, 0x00, '0',  '.',  '0',  '.',  '1',  0x00,
    0x1b, 0x0d, 0x00, 0x00, 0x06, 0x00, 'V',  'e', 
    'n',  'd',  'o',  'r',  0x06, 0x00, 'L',  'a', 
    'y',  'c',  'a',  'n',  0x1b, 0x10, 0x00, 0x00,
    0x09, 0x00, 'C',  'o',  'p',  'y',  'r',  'i', 
    'g',  'h',  't',  0x00, 0x0a, 0x00, '(',  'C', 
    ')',  ' ',  'L',  'a',  'y',  'c',  'a',  'n', 
    0x9b, 0x13, 0x00, 0x00, 0x07, 0x00, 'L',  'i', 
    'c',  'e',  'n',  's',  'e',  0x00, 0x00, 0x00,
    0x03, 0x00, 'G',  'P',  'L',  0x00, 0x00, 0x00,
    0x1b, 0x17, 0x00, 0x00, 0x0b, 0x00, 'D',  'e', 
    's',  'c',  'r',  'i',  'p',  't',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x1d, 0x00, 'M',  'a', 
    'n',  'a',  'g',  'e',  ' ',  'y',  'o',  'u', 
    'r',  ' ',  'l',  'a',  'y',  'c',  'a',  'n', 
    ' ',  'm',  'i',  'g',  'r',  'a',  't',  'i', 
    'o',  'n',  's',  0x00, 0x9b, 0x1c, 0x00, 0x00,
    0x03, 0x00, 'U',  'r',  'l',  0x00, 0x00, 0x00,
    '%',  0x00, 'h',  't',  't',  'p',  's',  ':', 
    '/',  '/',  'g',  'i',  't',  'h',  'u',  'b', 
    '.',  'c',  'o',  'm',  '/',  'A',  'n',  'd', 
    'e',  'r',  's',  'o',  'n',  'S',  'K',  'M', 
    '/',  'L',  'a',  'y',  'c',  'a',  'n',  0x00,
    0x14, '$',  0x00, 0x00, 0x0c, 0x00, 'D',  'e', 
    'p',  'e',  'n',  'd',  'e',  'n',  'c',  'i', 
    'e',  's',  0x00, 0x00, 'P',  0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    '8',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x04, 0x00, 'C',  'o',  'r',  'e',  0x00, 0x00,
    0x1b, 0x06, 0x00, 0x00, 0x07, 0x00, 'V',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x06, 0x00, '4',  '.',  '0',  '.',  '8',  '2', 
    0x0c, 0x00, 0x00, 0x00, ' ',  0x00, 0x00, 0x00,
    0x85, 0x01, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x0c, 0x01, 0x00, 0x00,
    0xa4, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0xd8, 0x00, 0x00, 0x00,
    '\\', 0x00, 0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '|',  0x00, 0x00, 0x00,
    '<',  0x00, 0x00, 0x00, 'p',  0x00, 0x00, 0x00,
    '`',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    '4',  0x02, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    ' ',  0x02, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '!',  0x00, 'o',  'r',  'g',  '.',  'q',  't', 
    '-',  'p',  'r',  'o',  'j',  'e',  'c',  't', 
    '.',  'Q',  't',  '.',  'Q',  't',  'C',  'r', 
    'e',  'a',  't',  'o',  'r',  'P',  'l',  'u', 
    'g',  'i',  'n',  0x00, 0x95, 0x09, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 0x94, 0x01, 0x00, 0x00,
    0x13, 0x00, 0x00, 0x00, 'p',  0x01, 0x00, 0x00,
    0x1b, 0x03, 0x00, 0x00, 0x04, 0x00, 'N',  'a', 
    'm',  'e',  0x00, 0x00, 0x0c, 0x00, 'L',  'a', 
    'y',  'c',  'a',  'n',  'E',  'd',  'i',  't', 
    'o',  'r',  0x00, 0x00, 0x1b, 0x07, 0x00, 0x00,
    0x07, 0x00, 'V',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x05, 0x00, '0',  '.', 
    '0',  '.',  '1',  0x00, 0x9b, 0x0a, 0x00, 0x00,
    0x0d, 0x00, 'C',  'o',  'm',  'p',  'a',  't', 
    'V',  'e',  'r',  's',  'i',  'o',  'n',  0x00,
    0x05, 0x00, '0',  '.',  '0',  '.',  '1',  0x00,
    0x1b, 0x0d, 0x00, 0x00, 0x06, 0x00, 'V',  'e', 
    'n',  'd',  'o',  'r',  0x06, 0x00, 'L',  'a', 
    'y',  'c',  'a',  'n',  0x1b, 0x10, 0x00, 0x00,
    0x09, 0x00, 'C',  'o',  'p',  'y',  'r',  'i', 
    'g',  'h',  't',  0x00, 0x0a, 0x00, '(',  'C', 
    ')',  ' ',  'L',  'a',  'y',  'c',  'a',  'n', 
    0x9b, 0x13, 0x00, 0x00, 0x07, 0x00, 'L',  'i', 
    'c',  'e',  'n',  's',  'e',  0x00, 0x00, 0x00,
    0x03, 0x00, 'G',  'P',  'L',  0x00, 0x00, 0x00,
    0x1b, 0x17, 0x00, 0x00, 0x0b, 0x00, 'D',  'e', 
    's',  'c',  'r',  'i',  'p',  't',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x1d, 0x00, 'M',  'a', 
    'n',  'a',  'g',  'e',  ' ',  'y',  'o',  'u', 
    'r',  ' ',  'l',  'a',  'y',  'c',  'a',  'n', 
    ' ',  'm',  'i',  'g',  'r',  'a',  't',  'i', 
    'o',  'n',  's',  0x00, 0x9b, 0x1c, 0x00, 0x00,
    0x03, 0x00, 'U',  'r',  'l',  0x00, 0x00, 0x00,
    '%',  0x00, 'h',  't',  't',  'p',  's',  ':', 
    '/',  '/',  'g',  'i',  't',  'h',  'u',  'b', 
    '.',  'c',  'o',  'm',  '/',  'A',  'n',  'd', 
    'e',  'r',  's',  'o',  'n',  'S',  'K',  'M', 
    '/',  'L',  'a',  'y',  'c',  'a',  'n',  0x00,
    0x14, '$',  0x00, 0x00, 0x0c, 0x00, 'D',  'e', 
    'p',  'e',  'n',  'd',  'e',  'n',  'c',  'i', 
    'e',  's',  0x00, 0x00, 'P',  0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 'L',  0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
    '8',  0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x04, 0x00, 'N',  'a',  'm',  'e',  0x00, 0x00,
    0x04, 0x00, 'C',  'o',  'r',  'e',  0x00, 0x00,
    0x1b, 0x06, 0x00, 0x00, 0x07, 0x00, 'V',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x06, 0x00, '4',  '.',  '0',  '.',  '8',  '2', 
    0x0c, 0x00, 0x00, 0x00, ' ',  0x00, 0x00, 0x00,
    0x85, 0x01, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x0c, 0x01, 0x00, 0x00,
    0xa4, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0xd8, 0x00, 0x00, 0x00,
    '\\', 0x00, 0x00, 0x00, '(',  0x00, 0x00, 0x00,
    0x1b, '>',  0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x12, 0x00, 'L',  'a',  'y',  'c',  'a',  'n', 
    'E',  'd',  'i',  't',  'o',  'r',  'P',  'l', 
    'u',  'g',  'i',  'n',  '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x1a, 0xa0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '<',  0x00, 0x00, 0x00,
    0xe0, 0x01, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00,
    0x10, 0x02, 0x00, 0x00
};
#endif // QT_NO_DEBUG

using namespace LaycanEditor;
using namespace LaycanEditor::Internal;
QT_MOC_EXPORT_PLUGIN(LaycanEditor::Internal::LaycanEditorPlugin, LaycanEditorPlugin)

QT_END_MOC_NAMESPACE
