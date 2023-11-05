#pragma once

#include "NiAVObject.hpp"
#include "NiPropertyState.hpp"

class NiRenderer;
class BSShader;
class NiAlphaProperty;
class NiStencilProperty;
class NiShadeProperty;
class NiMaterialProperty;

NiSmartPointer(NiGeometryData);
NiSmartPointer(NiSkinInstance);
NiSmartPointer(NiGeometry);

class NiGeometry : public NiAVObject {
public:
	NiGeometry();
	virtual ~NiGeometry();

	virtual void	RenderImmediate(NiRenderer* pkRenderer);
	virtual void	RenderImmediateAlt(NiRenderer* pkRenderer);
	virtual void	SetModelData(NiGeometryData* pkModelData);
	virtual void	CalculateNormals();
	virtual void	CalculateConsistency(bool bTool);

	struct RendererData
	{
	};

	NiPropertyState		m_kProperties;
	NiGeometryDataPtr	m_spModelData;
	NiSkinInstancePtr	m_spSkinInstance;
	BSShader*			m_pShader;
	__forceinline NiAlphaProperty* GetAlphaProperty() const { return m_kProperties.GetAlphaProperty(); };
	
	template <class T>
	T* GetShadeProperty() const { return static_cast<T*>(m_kProperties.GetShadeProperty<T>()); };

	__forceinline NiStencilProperty* GetStencilProperty() const { return m_kProperties.GetStencilProperty(); };

};

ASSERT_SIZE(NiGeometry, 0xC4);