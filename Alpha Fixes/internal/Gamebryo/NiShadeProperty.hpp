#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiShadeProperty);

class NiShadeProperty : public NiProperty {
public:
	NiShadeProperty();
	virtual ~NiShadeProperty();

	enum ShaderPropType : UInt32 {
		PROP_Lighting = 0x1,
		PROP_DistantLOD = 0x2,
		PROP_GeometryDecal = 0x3,
		PROP_TallGrass = 0x4,
		PROP_SpeedTreeLeaf = 0x6,
		PROP_PPLighting = 0x8,
		PROP_Hair = 0x9,
		PROP_SpeedTreeBranch = 0xA,
		PROP_SpeedTreeBillboard = 0xB,
		PROP_Lighting30 = 0xC,
		PROP_Sky = 0xD,
		PROP_Water = 0xE,
		PROP_Bolt = 0xF,
		PROP_Particle = 0x11,
		PROP_Precipitation = 0x12,
		PROP_Tile = 0x13,
		PROP_NoLighting = 0x15,
		PROP_VolumetricFog = 0x16,
		PROP_BloodSplatter = 0x17,
		PROP_DistantTree = 0x18,
	};

	UInt16			m_usFlags;
	ShaderPropType	m_eShaderType;

	CREATE_OBJECT(NiShadeProperty, 0xA814E0);
};

ASSERT_SIZE(NiShadeProperty, 0x20);