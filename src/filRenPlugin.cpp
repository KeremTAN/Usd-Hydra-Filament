#include <pxr/pxr.h>
#include "filRenPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType) {
    HdRendererPluginRegistry::Define<FilRenPlugin>();
    printf("[ o Filamanet Plugin ] is loaded\n");
}

FilRenPlugin::FilRenPlugin() = default;
FilRenPlugin::~FilRenPlugin() = default;

HdRenderDelegate* FilRenPlugin::CreateRenderDelegate() {
    return new FilRenDelegate();
}

HdRenderDelegate* FilRenPlugin::CreateRenderDelegate(const HdRenderSettingsMap& settingsMap) {
    return new FilRenDelegate();
}

void FilRenPlugin::DeleteRenderDelegate(HdRenderDelegate* renderDelegate) {
    delete renderDelegate;
}

// you can think that like a private access modifier
namespace {
static bool isGpuSupported() {
    using filament::Engine;
    using B = Engine::Backend;
    static const bool isSupported = []{

        Engine* e = Engine::create(B::METAL);
        if (!e) {
            e = Engine::create(B::OPENGL);
        }
        if (e) {
            Engine::destroy(&e); 
            return true; 
        }
        return false;
    }();

    return isSupported;
}
} // end of namespace

bool FilRenPlugin::IsSupported(bool gpuEnabled) const {
    return gpuEnabled && isGpuSupported();
}

PXR_NAMESPACE_CLOSE_SCOPE




