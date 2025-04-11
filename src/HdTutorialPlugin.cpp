#include <pxr/imaging/hd/rendererPlugin.h>
#include <pxr/imaging/hd/rendererPluginRegistry.h>
#include "HdTutorialRenderDelegate.h"

PXR_NAMESPACE_OPEN_SCOPE;

class HdTutorialPlugin : public HdRendererPlugin {
public:
    HdTutorialPlugin()  = default;
    virtual ~HdTutorialPlugin()  = default;

    // RenderDelegate oluşturma
    virtual HdRenderDelegate *CreateRenderDelegate() override {
        printf("[Tutorial Plugin] RenderDelegate created!\n");
        return new HdTutorialRenderDelegate();
    }

    // DeleteRenderDelegate implementation (required pure virtual method)
    virtual void DeleteRenderDelegate(HdRenderDelegate *renderDelegate) override {
        delete renderDelegate;
    }

    // Plugin destek kontrolü - corrected signature to match base class
    virtual bool IsSupported(bool gpuEnabled = true) const override { 
        return true; 
    }
};

TF_REGISTRY_FUNCTION(TfType) {
    HdRendererPluginRegistry::Define<HdTutorialPlugin>();
  }

PXR_NAMESPACE_CLOSE_SCOPE


