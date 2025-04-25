#pragma once

#include <pxr/pxr.h>
#include <pxr/imaging/hd/rendererPlugin.h>
#include <pxr/imaging/hd/rendererPluginRegistry.h>
#include "filRenDelegate.h"

PXR_NAMESPACE_OPEN_SCOPE

class __attribute__((visibility("default"))) FilRenPlugin final : public HdRendererPlugin {
public:
    
    FilRenPlugin();
    ~FilRenPlugin() override;
       
    HdRenderDelegate* CreateRenderDelegate() override;
    HdRenderDelegate* CreateRenderDelegate(const HdRenderSettingsMap& settingsMap) override;
    void DeleteRenderDelegate(HdRenderDelegate *renderDelegate) override;
    bool IsSupported(bool gpuEnabled = true) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE
