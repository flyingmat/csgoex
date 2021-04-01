#pragma once

class IVRenderView {
public:
	/*   4 */ void SetBlend(float blend) {
		GetVirtualFunction<void(__thiscall*)(IVRenderView*, float)>(this, 4)(this, blend);
	}

	/*   6 */ void SetColorModulation(float* const blend) {
		GetVirtualFunction<void(__thiscall*)(IVRenderView*, float* const)>(this, 6)(this, blend);
	}

	/*  44 */ void Push3DView(void* pRenderContext, const CViewSetup& view, int nFlags, void* pRenderTarget, void* frustumPlanes) {
		GetVirtualFunction<void(__thiscall*)(IVRenderView*, void*, const CViewSetup&, int, void*, void*)>(this, 44)(this, pRenderContext, view, nFlags, pRenderTarget, frustumPlanes);
	}

	/*  46 */ void PopView(void* pRenderContext, void* frustumPlanes) {
		GetVirtualFunction<void(__thiscall*)(IVRenderView*, void*, void*)>(this, 46)(this, pRenderContext, frustumPlanes);
	}
};
