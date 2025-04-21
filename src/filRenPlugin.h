#pragma once

#include <pxr/pxr.h>
#include <pxr/imaging/hd/rendererPlugin.h>
#include <pxr/imaging/hd/rendererPluginRegistry.h>
#include "filRenDelegate.h"

PXR_NAMESPACE_OPEN_SCOPE

class FilRenPlugin final : public HdRendererPlugin {
public:
    
    FilRenPlugin()  = default;
    ~FilRenPlugin()  = default;
       
    HdRenderDelegate* CreateRenderDelegate() override;
    // virtual HdRenderDelegate* CreateRenderDelegate(const HdRenderSettingsMap& settingsMap) override;
    void DeleteRenderDelegate(HdRenderDelegate *renderDelegate) override;
    bool IsSupported(bool gpuEnabled = true) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE
