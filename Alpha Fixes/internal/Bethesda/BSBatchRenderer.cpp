#include "BSBatchRenderer.hpp"

// 0xB99A90
void BSBatchRenderer::AccumStruct4::AddHead(UInt32 auiList, BSShaderProperty::RenderPass* apRenderPass) {
	ThisStdCall(0xB99A90, this, auiList, apRenderPass);
}

// 0xB99B00
void BSBatchRenderer::AccumStruct4::AddTail(UInt32 auiList, BSShaderProperty::RenderPass* apRenderPass) {
	ThisStdCall(0xB99B00, this, auiList, apRenderPass);
}
