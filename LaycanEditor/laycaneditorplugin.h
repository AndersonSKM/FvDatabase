#ifndef LAYCANEDITOR_H
#define LAYCANEDITOR_H

#include "laycaneditor_global.h"

#include <extensionsystem/iplugin.h>

namespace LaycanEditor {
namespace Internal {

class LaycanEditorPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "LaycanEditor.json")

public:
    LaycanEditorPlugin();
    ~LaycanEditorPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
};

} // namespace Internal
} // namespace LaycanEditor



#endif // LAYCANEDITOR_H

