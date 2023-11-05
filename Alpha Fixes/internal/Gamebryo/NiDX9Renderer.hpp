#pragma once

#include "d3d9.h"

class NiDX9Renderer {
public:
	static LPDIRECT3D9 GetD3D9() { return *(LPDIRECT3D9*)0x126F0D8; };
};