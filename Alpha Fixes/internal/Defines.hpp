#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

#include <NiUpdateData.hpp>

class NiDX9Renderer;

typedef NiDX9Renderer NiD3DRenderer;

typedef struct _D3DVECTOR4 {
	float x;
	float y;
	float z;
	float w;
} D3DVECTOR4;
#define D3DVECTOR4_DEFINED

// Align D3DXMATRIX
typedef __declspec(align(16)) D3DXMATRIX    D3DXALIGNEDMATRIX;

static NiUpdateData g_defaultUpdateData = NiUpdateData();

#define STACK_ALLOCATE(class_name, pointer_name) \
    char pointer_name[sizeof(class_name)]; \
    class_name* p##pointer_name = (class_name*)pointer_name;