#include <iostream>
#include "../include/Animal.h"
#include "pxr/pxr.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/sphere.h"
#include "pxr/imaging/hd/engine.h"
#include "pxr/imaging/hd/tokens.h"

// Filament için gerekli minimum header'lar
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

PXR_NAMESPACE_USING_DIRECTIVE

int main() {
    std::cout << "USD, Hydra ve Filament Test Başlıyor...\n";
    creatures::Animal a{};
    a.attack("a bug");
    
    // 1. USD kısmını test et
    try {
        // Yeni bir USD dosyası oluştur
        UsdStageRefPtr stage = UsdStage::CreateNew("test_scene.usda");
        
        // Basit bir küre ekle
        UsdGeomSphere sphere = UsdGeomSphere::Define(stage, SdfPath("/TestSphere"));
        sphere.GetRadiusAttr().Set(2.0);
        
        // Dosyayı kaydet
        stage->Save();
        std::cout << "USD test başarılı: test_scene.usda oluşturuldu.\n";
    } catch (const std::exception& e) {
        std::cerr << "USD test başarısız: " << e.what() << "\n";
        return 1;
    }
    
    // 2. Hydra kısmını test et
    try {
        // Hydra engine'i başlat
        HdEngine engine;
        std::cout << "Hydra test başarılı: Engine oluşturuldu.\n";
        
        // Hydra render token kontrolü - renderTags (s ile) kullanılıyor
        std::cout << "Hydra temel render tokenleri kontrol ediliyor... \n";
        if (HdTokens->renderTags == TfToken("renderTagsValue")) { 
            std::cout << "Hydra render tags bulundu: " << HdTokens->renderTags.GetString() << "\n";
        } else {
            std::cout << "Hydra render tags bulunamadı\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Hydra test başarısız: " << e.what() << "\n";
        return 1;
    }
    
    // 3. Filament kısmını test et
    try {
        // Filament engine'i başlat
        filament::Engine* engine = filament::Engine::create();
        
        if (engine) {
            // Filament'in temel bileşenlerini oluştur
            filament::Renderer* renderer = engine->createRenderer();
            filament::Scene* scene = engine->createScene();
            
            // Temizle
            engine->destroy(scene);
            engine->destroy(renderer);
            filament::Engine::destroy(&engine);
            
            std::cout << "Filament test başarılı: Engine, Renderer ve Scene oluşturuldu ve silindi.\n";
        } else {
            std::cerr << "Filament test başarısız: Engine oluşturulamadı.\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Filament test başarısız: " << e.what() << "\n";
        return 1;
    }
    
    std::cout << "Tüm testler başarılı! Kütüphaneler doğru şekilde kurulmuş.\n";
    return 0;
}