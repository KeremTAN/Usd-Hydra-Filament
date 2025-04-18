#include <pxr/imaging/hd/renderPass.h>

PXR_NAMESPACE_OPEN_SCOPE

class FilRenPass final : public HdRenderPass {
public:
    FilRenPass(HdRenderIndex* index, HdRprimCollection const& collection) : 
        HdRenderPass(index, collection) 
    {}

    ~FilRenPass() = default;

    bool IsConverged() const override;

    void _Execute(HdRenderPassStateSharedPtr const& renderPassState, TfTokenVector const& renderTags) override;

    void _MarkCollectionDirty() override;

    void _Sync() override;
};

PXR_NAMESPACE_CLOSE_SCOPE