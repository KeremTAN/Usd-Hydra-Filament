#include <iostream>
#include <pxr/pxr.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/imaging/hd/engine.h>
#include <pxr/imaging/hd/tokens.h>

PXR_NAMESPACE_USING_DIRECTIVE

int main(int argc, char** argv) {
    UsdStageRefPtr stage = UsdStage::CreateNew("test_sphere.usda");

    UsdGeomSphere sphere = UsdGeomSphere::Define(stage, SdfPath("/TestSphere"));
    sphere.GetRadiusAttr().Set(2.0);

    stage->Save();
    std::cout << "Test Sphere is created\n";

    return 0;
}