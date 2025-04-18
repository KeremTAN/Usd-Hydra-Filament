#include <pxr/imaging/hd/renderPass.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilamentRenderPass final : public HdRenderPass {
public:
    FilamentRenderPass(HdRenderIndex* index, HdRprimCollection const& collection) : 
        HdRenderPass(index, collection) 
    {}

    ~FilamentRenderPass() = default;

    bool IsConverged() const override;

    void _Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) override;

    void _MarkCollectionDirty() override;

    void _Sync() override;
};

PXR_NAMESPACE_CLOSE_SCOPE