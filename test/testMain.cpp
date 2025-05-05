#include <iostream>
#include <pxr/pxr.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/imaging/hd/rendererPlugin.h>
#include <pxr/imaging/hd/rendererPluginRegistry.h>
#include <pxr/imaging/hd/engine.h>
#include <pxr/imaging/hd/tokens.h>
#include <pxr/imaging/hd/renderPass.h>
#include <pxr/imaging/hd/rprimCollection.h>
#include <pxr/imaging/hd/driver.h>
#include <pxr/imaging/hd/task.h>
#include <pxr/imaging/hdx/taskController.h>
#include <pxr/imaging/hdx/renderTask.h>
#include <pxr/imaging/hdx/renderSetupTask.h>
#include <pxr/imaging/hdx/selectionTask.h>

#include "../src/filRenDelegate.h"

PXR_NAMESPACE_USING_DIRECTIVE

int main(int argc, char** argv) {

    UsdStageRefPtr stage = UsdStage::Open("../examples/usd_examples/test_sphere.usda");
    if (!stage) {
        std::cerr << "[X] USD stage could not be opened\n";
        return 1;
    }

    // Take Plugin
    TfToken pluginId("FilRenPlugin");
    HdRendererPlugin* plugin = HdRendererPluginRegistry::GetInstance().GetRendererPlugin(pluginId);
    if (!plugin || !plugin->IsSupported()) {
        std::cerr << "[X] Plugin could not be found or be supported: " << pluginId << '\n';
        return 1;
    }

    // Create Delegate
    HdRenderDelegate* renderDelegate = plugin->CreateRenderDelegate();
    
    // create RenderIndex
    HdRenderIndex* renderIndex = HdRenderIndex::New(renderDelegate, {});
    if (!renderIndex) {
        std::cerr << "[X] RenderIndex could not be created.\n";
        return 1;
    }

    delete renderIndex;
    return 0;
}