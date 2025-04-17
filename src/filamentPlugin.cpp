#include <pxr/pxr.h>
#include "filamentPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType) {
    HdRendererPluginRegistry::Define<FilamentPlugin>();
}

HdRenderDelegate* FilamentPlugin::CreateRenderDelegate() {
    return new FilamentRenderDelegate();
}

// HdRenderDelegate* FilamentPlugin::CreateRenderDelegate(const HdRenderSettingsMap& settingsMap) {
//     return new FilamentRenderDelegate(settingsMap);
// }

void FilamentPlugin::DeleteRenderDelegate(HdRenderDelegate* renderDelegate) {
    delete renderDelegate;
}

/**
 * TODO: it will be updated when FilamentRenderDelegate::IsSupported() impl. figure out
 */
bool FilamentPlugin::IsSupported(bool gpuEnabled) const {
    const bool support = gpuEnabled /* && FilamentRenderDelegate::IsSupported() */;
    if (!support) {
        TF_DEBUG(HD_RENDERER_PLUGIN).Msg(
            "hdFilament renderer plugin unsupported: %s\n",
            gpuEnabled ? "filament engine unsupported" : "no gpu");
    }
    return support;
}

PXR_NAMESPACE_CLOSE_SCOPE




