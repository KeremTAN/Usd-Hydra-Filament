#include <pxr/pxr.h>
#include "filRenPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType) {
    HdRendererPluginRegistry::Define<FilRenPlugin>();
}

HdRenderDelegate* FilRenPlugin::CreateRenderDelegate() {
    return new FilRenDelegate();
}

// HdRenderDelegate* FilRenPlugin::CreateRenderDelegate(const HdRenderSettingsMap& settingsMap) {
//     return new FilRenDelegate(settingsMap);
// }

void FilRenPlugin::DeleteRenderDelegate(HdRenderDelegate* renderDelegate) {
    delete renderDelegate;
}

/**
 * TODO: it will be updated when FilRenDelegate::IsSupported() impl. figure out
 */
bool FilRenPlugin::IsSupported(bool gpuEnabled) const {
    const bool support = gpuEnabled /* && FilRenDelegate::IsSupported() */;
    if (!support) {
        TF_DEBUG(HD_RENDERER_PLUGIN).Msg(
            "hdFilament renderer plugin unsupported: %s\n",
            gpuEnabled ? "filament engine unsupported" : "no gpu");
    }
    return support;
}

PXR_NAMESPACE_CLOSE_SCOPE




