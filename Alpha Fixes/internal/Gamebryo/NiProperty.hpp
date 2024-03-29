#pragma once

#include "NiObjectNET.hpp"

class NiUpdateData;

NiSmartPointer(NiProperty);
NiRTTIAddress(NiProperty, 0x11F4420);

class NiProperty : public NiObjectNET {
public:
	NiProperty();
	virtual ~NiProperty();

	virtual UInt32	Type();
	virtual void	Update(NiUpdateData* pUpdateData);

	enum PropertyType {
		ALPHA,
		CULLING,
		MATERIAL,
		SHADE,
		STENCIL,
		TEXTURING,
		MAX_TYPES
	};
};

ASSERT_SIZE(NiProperty, 0x18);