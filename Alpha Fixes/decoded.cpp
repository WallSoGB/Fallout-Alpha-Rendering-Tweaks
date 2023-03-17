#include <decoded.h>
#include <GameData.h>

const char* BSRenderPass::GetPassName(UInt32 pass) {
	const char* result;
#if _DEBUG
	if (pass != BSRenderPass::GetCurrentPassType()) {
		_ERROR("[BSRenderPass::GetPassName] Passes don't match! Was given %i, while current is %i", pass, BSRenderPass::GetCurrentPassType());
	}
#endif
	if (!pass) {
#if _DEBUG
		_ERROR("[BSRenderPass::GetPassName] Given pass was empty!");
#endif
		pass = BSRenderPass::GetCurrentPassType();
	}

	switch (pass)
	{
	case BSSM_ZONLY:
		result = "BSSM_ZONLY";
		break;
	case BSSM_ZONLY_At:
		result = "BSSM_ZONLY_At";
		break;
	case BSSM_ZONLY_S:
		result = "BSSM_ZONLY_S";
		break;
	case BSSM_ZONLY_TEXEFFECT:
		result = "BSSM_ZONLY_TEXEFFECT";
		break;
	case BSSM_ZONLY_TEXEFFECT_S:
		result = "BSSM_ZONLY_TEXEFFECT_S";
		break;
	case BSSM_CONSTALPHA:
		result = "BSSM_CONSTALPHA";
		break;
	case BSSM_CONSTALPHA_At:
		result = "BSSM_CONSTALPHA_At";
		break;
	case BSSM_CONSTALPHA_S:
		result = "BSSM_CONSTALPHA_S";
		break;
	case BSSM_AMBIENT_OCCLUSION:
		result = "BSSM_AMBIENT_OCCLUSION";
		break;
	case BSSM_3XZONLY:
		result = "BSSM_3XZONLY";
		break;
	case BSSM_3XZONLY_S:
		result = "BSSM_3XZONLY_S";
		break;
	case BSSM_3XZONLY_Vc:
		result = "BSSM_3XZONLY_Vc";
		break;
	case BSSM_3XZONLY_SVc:
		result = "BSSM_3XZONLY_SVc";
		break;
	case BSSM_3XZONLY_TEXEFFECT:
		result = "BSSM_3XZONLY_TEXEFFECT";
		break;
	case BSSM_3XZONLY_TEXEFFECT_S:
		result = "BSSM_3XZONLY_TEXEFFECT_S";
		break;
	case BSSM_DEPTHMAP:
		result = "BSSM_DEPTHMAP";
		break;
	case BSSM_DEPTHMAP_At:
		result = "BSSM_DEPTHMAP_At";
		break;
	case BSSM_DEPTHMAP_S:
		result = "BSSM_DEPTHMAP_S";
		break;
	case BSSM_DEPTHMAP_SAt:
		result = "BSSM_DEPTHMAP_SAt";
		break;
	case BSSM_SELFILLUMALPHABLOCK:
		result = "BSSM_SELFILLUMALPHABLOCK";
		break;
	case BSSM_SELFILLUMALPHABLOCK_S:
		result = "BSSM_SELFILLUMALPHABLOCK_S";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LF:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LF";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LV:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LV";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFS:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFS";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVS:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVS";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFP:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFP";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVP:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVP";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFSP:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFSP";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVSP:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVSP";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFSShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFSShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVSShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVSShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFPShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFPShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVPShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVPShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFSPShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFSPShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LVSPShp:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LVSPShp";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFB:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFB";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFSB:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFSB";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFPB:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFPB";
		break;
	case BSSM_GRASS_NOALPHA_DIRONLY_LFSPB:
		result = "BSSM_GRASS_NOALPHA_DIRONLY_LFSPB";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LF:
		result = "BSSM_GRASS_NOALPHA_1POINT_LF";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LV:
		result = "BSSM_GRASS_NOALPHA_1POINT_LV";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFS:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFS";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVS:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVS";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFP:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFP";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVP:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVP";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFSP:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFSP";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVSP:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVSP";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFSShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFSShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVSShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVSShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFPShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFPShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVPShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVPShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFSPShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFSPShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LVSPShp:
		result = "BSSM_GRASS_NOALPHA_1POINT_LVSPShp";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFB:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFB";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFSB:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFSB";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFPB:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFPB";
		break;
	case BSSM_GRASS_NOALPHA_1POINT_LFSPB:
		result = "BSSM_GRASS_NOALPHA_1POINT_LFSPB";
		break;
	case BSSM_LEAVES_AD:
		result = "BSSM_LEAVES_AD";
		break;
	case BSSM_LEAVES_ADPt:
		result = "BSSM_LEAVES_ADPt";
		break;
	case BSSM_FRONDS:
		result = "BSSM_FRONDS";
		break;
	case BSSM_PARTICLE_PREPASS:
		result = "BSSM_PARTICLE_PREPASS";
		break;
	case BSSM_NOLIGHTING:
		result = "BSSM_NOLIGHTING";
		break;
	case BSSM_NOLIGHTING_VC:
		result = "BSSM_NOLIGHTING_VC";
		break;
	case BSSM_NOLIGHTING_TexVC:
		result = "BSSM_NOLIGHTING_TexVC";
		break;
	case BSSM_NOLIGHTING_MAT:
		result = "BSSM_NOLIGHTING_MAT";
		break;
	case BSSM_NOLIGHTING_S:
		result = "BSSM_NOLIGHTING_S";
		break;
	case BSSM_NOLIGHTING_VC_S:
		result = "BSSM_NOLIGHTING_VC_S";
		break;
	case BSSM_NOLIGHTING_TexVC_S:
		result = "BSSM_NOLIGHTING_TexVC_S";
		break;
	case BSSM_NOLIGHTING_MAT_S:
		result = "BSSM_NOLIGHTING_MAT_S";
		break;
	case BSSM_NOLIGHTING_FALLOFF:
		result = "BSSM_NOLIGHTING_FALLOFF";
		break;
	case BSSM_NOLIGHTING_VC_FALLOFF:
		result = "BSSM_NOLIGHTING_VC_FALLOFF";
		break;
	case BSSM_NOLIGHTING_TexVC_FALLOFF:
		result = "BSSM_NOLIGHTING_TexVC_FALLOFF";
		break;
	case BSSM_NOLIGHTING_MAT_FALLOFF:
		result = "BSSM_NOLIGHTING_MAT_FALLOFF";
		break;
	case BSSM_NOLIGHTING_FALLOFF_S:
		result = "BSSM_NOLIGHTING_FALLOFF_S";
		break;
	case BSSM_NOLIGHTING_VC_FALLOFF_S:
		result = "BSSM_NOLIGHTING_VC_FALLOFF_S";
		break;
	case BSSM_NOLIGHTING_TexVC_FALLOFF_S:
		result = "BSSM_NOLIGHTING_TexVC_FALLOFF_S";
		break;
	case BSSM_NOLIGHTING_MAT_FALLOFF_S:
		result = "BSSM_NOLIGHTING_MAT_FALLOFF_S";
		break;
	case BSSM_NOLIGHTING_PSYS:
		result = "BSSM_NOLIGHTING_PSYS";
		break;
	case BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET:
		result = "BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET";
		break;
	case BSSM_NOLIGHTING_PSYS_PREMULT_ALPHA:
		result = "BSSM_NOLIGHTING_PSYS_PREMULT_ALPHA";
		break;
	case BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET_PREMULT_ALPHA:
		result = "BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET_PREMULT_ALPHA";
		break;
	case BSSM_NOLIGHTING_STRIP_PSYS:
		result = "BSSM_NOLIGHTING_STRIP_PSYS";
		break;
	case BSSM_NOLIGHTING_STRIP_PSYS_SUBTEX:
		result = "BSSM_NOLIGHTING_STRIP_PSYS_SUBTEX";
		break;
	case BSSM_AMBIENT:
		result = "BSSM_AMBIENT";
		break;
	case BSSM_AMBIENT_G:
		result = "BSSM_AMBIENT_G";
		break;
	case BSSM_AMBIENT_At:
		result = "BSSM_AMBIENT_At";
		break;
	case BSSM_AMBIENT_GAt:
		result = "BSSM_AMBIENT_GAt";
		break;
	case BSSM_AMBIENT_S:
		result = "BSSM_AMBIENT_S";
		break;
	case BSSM_AMBIENT_SG:
		result = "BSSM_AMBIENT_SG";
		break;
	case BSSM_AMBIENT_SAt:
		result = "BSSM_AMBIENT_SAt";
		break;
	case BSSM_AMBIENT_SGAt:
		result = "BSSM_AMBIENT_SGAt";
		break;
	case BSSM_AMBIENT_Sb:
		result = "BSSM_AMBIENT_Sb";
		break;
	case BSSM_AMBIENT_Mn:
		result = "BSSM_AMBIENT_Mn";
		break;
	case BSSM_AMBIENT_F:
		result = "BSSM_AMBIENT_F";
		break;
	case BSSM_AMBIENT_FAt:
		result = "BSSM_AMBIENT_FAt";
		break;
	case BSSM_AMBDIFFTEX:
		result = "BSSM_AMBDIFFTEX";
		break;
	case BSSM_AMBDIFFTEX_Vc:
		result = "BSSM_AMBDIFFTEX_Vc";
		break;
	case BSSM_AMBDIFFTEX_G:
		result = "BSSM_AMBDIFFTEX_G";
		break;
	case BSSM_AMBDIFFTEX_GVc:
		result = "BSSM_AMBDIFFTEX_GVc";
		break;
	case BSSM_AMBDIFFTEX_Fg:
		result = "BSSM_AMBDIFFTEX_Fg";
		break;
	case BSSM_AMBDIFFTEX_A:
		result = "BSSM_AMBDIFFTEX_A";
		break;
	case BSSM_AMBDIFFTEX_AVc:
		result = "BSSM_AMBDIFFTEX_AVc";
		break;
	case BSSM_AMBDIFFTEX_GA:
		result = "BSSM_AMBDIFFTEX_GA";
		break;
	case BSSM_AMBDIFFTEX_GAVc:
		result = "BSSM_AMBDIFFTEX_GAVc";
		break;
	case BSSM_AMBDIFFTEX_FgA:
		result = "BSSM_AMBDIFFTEX_FgA";
		break;
	case BSSM_AMBDIFFTEX_GFgA:
		result = "BSSM_AMBDIFFTEX_GFgA";
		break;
	case BSSM_AMBDIFFTEX_S:
		result = "BSSM_AMBDIFFTEX_S";
		break;
	case BSSM_AMBDIFFTEX_SVc:
		result = "BSSM_AMBDIFFTEX_SVc";
		break;
	case BSSM_AMBDIFFTEX_SG:
		result = "BSSM_AMBDIFFTEX_SG";
		break;
	case BSSM_AMBDIFFTEX_SGVc:
		result = "BSSM_AMBDIFFTEX_SGVc";
		break;
	case BSSM_AMBDIFFTEX_SFg:
		result = "BSSM_AMBDIFFTEX_SFg";
		break;
	case BSSM_AMBDIFFTEX_SA:
		result = "BSSM_AMBDIFFTEX_SA";
		break;
	case BSSM_AMBDIFFTEX_SAVc:
		result = "BSSM_AMBDIFFTEX_SAVc";
		break;
	case BSSM_AMBDIFFTEX_SGA:
		result = "BSSM_AMBDIFFTEX_SGA";
		break;
	case BSSM_AMBDIFFTEX_SGAVc:
		result = "BSSM_AMBDIFFTEX_SGAVc";
		break;
	case BSSM_AMBDIFFTEX_SFgA:
		result = "BSSM_AMBDIFFTEX_SFgA";
		break;
	case BSSM_AMBDIFFTEX_SGFgA:
		result = "BSSM_AMBDIFFTEX_SGFgA";
		break;
	case BSSM_AMBDIFFTEX_Sb:
		result = "BSSM_AMBDIFFTEX_Sb";
		break;
	case BSSM_AMBDIFFTEX_SbF:
		result = "BSSM_AMBDIFFTEX_SbF";
		break;
	case BSSM_AMBDIFFDIRANDPT:
		result = "BSSM_AMBDIFFDIRANDPT";
		break;
	case BSSM_AMBDIFFDIRANDPT_S:
		result = "BSSM_AMBDIFFDIRANDPT_S";
		break;
	case BSSM_AMBDIFFDIRANDPT_Sb:
		result = "BSSM_AMBDIFFDIRANDPT_Sb";
		break;
	case BSSM_AMBDIFFTEX_F:
		result = "BSSM_AMBDIFFTEX_F";
		break;
	case BSSM_AMBDIFFTEX_FVc:
		result = "BSSM_AMBDIFFTEX_FVc";
		break;
	case BSSM_AMBDIFFTEX_FG:
		result = "BSSM_AMBDIFFTEX_FG";
		break;
	case BSSM_AMBDIFFTEX_FGVc:
		result = "BSSM_AMBDIFFTEX_FGVc";
		break;
	case BSSM_AMBDIFFTEX_FA:
		result = "BSSM_AMBDIFFTEX_FA";
		break;
	case BSSM_AMBDIFFTEX_FAVc:
		result = "BSSM_AMBDIFFTEX_FAVc";
		break;
	case BSSM_AMBDIFFTEX_FFg:
		result = "BSSM_AMBDIFFTEX_FFg";
		break;
	case BSSM_AMBDIFFTEX_FGA:
		result = "BSSM_AMBDIFFTEX_FGA";
		break;
	case BSSM_AMBDIFFTEX_FGAVc:
		result = "BSSM_AMBDIFFTEX_FGAVc";
		break;
	case BSSM_AMBDIFFTEX_FGFgA:
		result = "BSSM_AMBDIFFTEX_FGFgA";
		break;
	case BSSM_AMBDIFFTEX_SF:
		result = "BSSM_AMBDIFFTEX_SF";
		break;
	case BSSM_AMBDIFFTEX_SFVc:
		result = "BSSM_AMBDIFFTEX_SFVc";
		break;
	case BSSM_AMBDIFFTEX_SFG:
		result = "BSSM_AMBDIFFTEX_SFG";
		break;
	case BSSM_AMBDIFFTEX_SFGVc:
		result = "BSSM_AMBDIFFTEX_SFGVc";
		break;
	case BSSM_AMBDIFFTEX_SFA:
		result = "BSSM_AMBDIFFTEX_SFA";
		break;
	case BSSM_AMBDIFFTEX_SFAVc:
		result = "BSSM_AMBDIFFTEX_SFAVc";
		break;
	case BSSM_AMBDIFFTEX_SFFg:
		result = "BSSM_AMBDIFFTEX_SFFg";
		break;
	case BSSM_AMBDIFFTEX_SFGA:
		result = "BSSM_AMBDIFFTEX_SFGA";
		break;
	case BSSM_AMBDIFFTEX_SFGAVc:
		result = "BSSM_AMBDIFFTEX_SFGAVc";
		break;
	case BSSM_AMBDIFFTEX_SFGFgA:
		result = "BSSM_AMBDIFFTEX_SFGFgA";
		break;
	case BSSM_LANDAD:
		result = "BSSM_LANDAD";
		break;
	case BSSM_LANDAD_Shp:
		result = "BSSM_LANDAD_Shp";
		break;
	case BSSM_ADTS:
		result = "BSSM_ADTS";
		break;
	case BSSM_ADTS_G:
		result = "BSSM_ADTS_G";
		break;
	case BSSM_ADTS_H:
		result = "BSSM_ADTS_H";
		break;
	case BSSM_ADTS_Fg:
		result = "BSSM_ADTS_Fg";
		break;
	case BSSM_ADTS_Px:
		result = "BSSM_ADTS_Px";
		break;
	case BSSM_ADTS_GPx:
		result = "BSSM_ADTS_GPx";
		break;
	case BSSM_ADTS_S:
		result = "BSSM_ADTS_S";
		break;
	case BSSM_ADTS_SG:
		result = "BSSM_ADTS_SG";
		break;
	case BSSM_ADTS_SH:
		result = "BSSM_ADTS_SH";
		break;
	case BSSM_ADTS_SFg:
		result = "BSSM_ADTS_SFg";
		break;
	case BSSM_ADTS_Sb:
		result = "BSSM_ADTS_Sb";
		break;
	case BSSM_ADTS_Shp:
		result = "BSSM_ADTS_Shp";
		break;
	case BSSM_ADTS_GShp:
		result = "BSSM_ADTS_GShp";
		break;
	case BSSM_ADTS_HShp:
		result = "BSSM_ADTS_HShp";
		break;
	case BSSM_ADTS_FgShp:
		result = "BSSM_ADTS_FgShp";
		break;
	case BSSM_ADTS_PxShp:
		result = "BSSM_ADTS_PxShp";
		break;
	case BSSM_ADTS_GPxShp:
		result = "BSSM_ADTS_GPxShp";
		break;
	case BSSM_ADTS_SShp:
		result = "BSSM_ADTS_SShp";
		break;
	case BSSM_ADTS_SGShp:
		result = "BSSM_ADTS_SGShp";
		break;
	case BSSM_ADTS_SHShp:
		result = "BSSM_ADTS_SHShp";
		break;
	case BSSM_ADTS_SFgShp:
		result = "BSSM_ADTS_SFgShp";
		break;
	case BSSM_ADTS_SbShp:
		result = "BSSM_ADTS_SbShp";
		break;
	case BSSM_ADTS2:
		result = "BSSM_ADTS2";
		break;
	case BSSM_ADTS2_G:
		result = "BSSM_ADTS2_G";
		break;
	case BSSM_ADTS2_H:
		result = "BSSM_ADTS2_H";
		break;
	case BSSM_ADTS2_Fg:
		result = "BSSM_ADTS2_Fg";
		break;
	case BSSM_ADTS2_Px:
		result = "BSSM_ADTS2_Px";
		break;
	case BSSM_ADTS2_GPx:
		result = "BSSM_ADTS2_GPx";
		break;
	case BSSM_ADTS2_S:
		result = "BSSM_ADTS2_S";
		break;
	case BSSM_ADTS2_SG:
		result = "BSSM_ADTS2_SG";
		break;
	case BSSM_ADTS2_SH:
		result = "BSSM_ADTS2_SH";
		break;
	case BSSM_ADTS2_SFg:
		result = "BSSM_ADTS2_SFg";
		break;
	case BSSM_ADTS2_Sb:
		result = "BSSM_ADTS2_Sb";
		break;
	case BSSM_ADTS2_Shp:
		result = "BSSM_ADTS2_Shp";
		break;
	case BSSM_ADTS2_GShp:
		result = "BSSM_ADTS2_GShp";
		break;
	case BSSM_ADTS2_HShp:
		result = "BSSM_ADTS2_HShp";
		break;
	case BSSM_ADTS2_FgShp:
		result = "BSSM_ADTS2_FgShp";
		break;
	case BSSM_ADTS2_PxShp:
		result = "BSSM_ADTS2_PxShp";
		break;
	case BSSM_ADTS2_GPxShp:
		result = "BSSM_ADTS2_GPxShp";
		break;
	case BSSM_ADTS2_SShp:
		result = "BSSM_ADTS2_SShp";
		break;
	case BSSM_ADTS2_SGShp:
		result = "BSSM_ADTS2_SGShp";
		break;
	case BSSM_ADTS2_SHShp:
		result = "BSSM_ADTS2_SHShp";
		break;
	case BSSM_ADTS2_SFgShp:
		result = "BSSM_ADTS2_SFgShp";
		break;
	case BSSM_ADTS2_SbShp:
		result = "BSSM_ADTS2_SbShp";
		break;
	case BSSM_ADTS_ONELIGHT:
		result = "BSSM_ADTS_ONELIGHT";
		break;
	case BSSM_ADTS_DIRANDPT:
		result = "BSSM_ADTS_DIRANDPT";
		break;
	case BSSM_ADT10:
		result = "BSSM_ADT10";
		break;
	case BSSM_ADT10_G:
		result = "BSSM_ADT10_G";
		break;
	case BSSM_ADT10_Fg:
		result = "BSSM_ADT10_Fg";
		break;
	case BSSM_ADT10_S:
		result = "BSSM_ADT10_S";
		break;
	case BSSM_ADT10_SG:
		result = "BSSM_ADT10_SG";
		break;
	case BSSM_ADT10_SFg:
		result = "BSSM_ADT10_SFg";
		break;
	case BSSM_ADT4:
		result = "BSSM_ADT4";
		break;
	case BSSM_ADT4_Opt:
		result = "BSSM_ADT4_Opt";
		break;
	case BSSM_ADT4_G:
		result = "BSSM_ADT4_G";
		break;
	case BSSM_ADT4_Fg:
		result = "BSSM_ADT4_Fg";
		break;
	case BSSM_ADT4_S:
		result = "BSSM_ADT4_S";
		break;
	case BSSM_ADT4_SG:
		result = "BSSM_ADT4_SG";
		break;
	case BSSM_ADT4_SFg:
		result = "BSSM_ADT4_SFg";
		break;
	case BSSM_ADTS10:
		result = "BSSM_ADTS10";
		break;
	case BSSM_ADTS10_Opt:
		result = "BSSM_ADTS10_Opt";
		break;
	case BSSM_ADTS10_G:
		result = "BSSM_ADTS10_G";
		break;
	case BSSM_ADTS10_Fg:
		result = "BSSM_ADTS10_Fg";
		break;
	case BSSM_ADTS10_S:
		result = "BSSM_ADTS10_S";
		break;
	case BSSM_ADTS10_SG:
		result = "BSSM_ADTS10_SG";
		break;
	case BSSM_ADTS10_SFg:
		result = "BSSM_ADTS10_SFg";
		break;
	case BSSM_AD2:
		result = "BSSM_AD2";
		break;
	case BSSM_AD2_G:
		result = "BSSM_AD2_G";
		break;
	case BSSM_AD2_Px:
		result = "BSSM_AD2_Px";
		break;
	case BSSM_AD2_GPx:
		result = "BSSM_AD2_GPx";
		break;
	case BSSM_AD2_Fg:
		result = "BSSM_AD2_Fg";
		break;
	case BSSM_AD2_S:
		result = "BSSM_AD2_S";
		break;
	case BSSM_AD2_SG:
		result = "BSSM_AD2_SG";
		break;
	case BSSM_AD2_SFg:
		result = "BSSM_AD2_SFg";
		break;
	case BSSM_AD2_Sb:
		result = "BSSM_AD2_Sb";
		break;
	case BSSM_AD2_Shp:
		result = "BSSM_AD2_Shp";
		break;
	case BSSM_AD2_GShp:
		result = "BSSM_AD2_GShp";
		break;
	case BSSM_AD2_PxShp:
		result = "BSSM_AD2_PxShp";
		break;
	case BSSM_AD2_GPxShp:
		result = "BSSM_AD2_GPxShp";
		break;
	case BSSM_AD2_FgShp:
		result = "BSSM_AD2_FgShp";
		break;
	case BSSM_AD2_SShp:
		result = "BSSM_AD2_SShp";
		break;
	case BSSM_AD2_SGShp:
		result = "BSSM_AD2_SGShp";
		break;
	case BSSM_AD2_SFgShp:
		result = "BSSM_AD2_SFgShp";
		break;
	case BSSM_AD2_SbShp:
		result = "BSSM_AD2_SbShp";
		break;
	case BSSM_AD3:
		result = "BSSM_AD3";
		break;
	case BSSM_AD3_G:
		result = "BSSM_AD3_G";
		break;
	case BSSM_AD3_Px:
		result = "BSSM_AD3_Px";
		break;
	case BSSM_AD3_GPx:
		result = "BSSM_AD3_GPx";
		break;
	case BSSM_AD3_Fg:
		result = "BSSM_AD3_Fg";
		break;
	case BSSM_AD3_S:
		result = "BSSM_AD3_S";
		break;
	case BSSM_AD3_SG:
		result = "BSSM_AD3_SG";
		break;
	case BSSM_AD3_SFg:
		result = "BSSM_AD3_SFg";
		break;
	case BSSM_AD3_Sb:
		result = "BSSM_AD3_Sb";
		break;
	case BSSM_AD3_Shp:
		result = "BSSM_AD3_Shp";
		break;
	case BSSM_AD3_GShp:
		result = "BSSM_AD3_GShp";
		break;
	case BSSM_AD3_PxShp:
		result = "BSSM_AD3_PxShp";
		break;
	case BSSM_AD3_GPxShp:
		result = "BSSM_AD3_GPxShp";
		break;
	case BSSM_AD3_FgShp:
		result = "BSSM_AD3_FgShp";
		break;
	case BSSM_AD3_SShp:
		result = "BSSM_AD3_SShp";
		break;
	case BSSM_AD3_SGShp:
		result = "BSSM_AD3_SGShp";
		break;
	case BSSM_AD3_SFgShp:
		result = "BSSM_AD3_SFgShp";
		break;
	case BSSM_AD3_SbShp:
		result = "BSSM_AD3_SbShp";
		break;
	case BSSM_ADT:
		result = "BSSM_ADT";
		break;
	case BSSM_ADT_Opt:
		result = "BSSM_ADT_Opt";
		break;
	case BSSM_ADT_OptLOD:
		result = "BSSM_ADT_OptLOD";
		break;
	case BSSM_ADT_Mn:
		result = "BSSM_ADT_Mn";
		break;
	case BSSM_ADT_G:
		result = "BSSM_ADT_G";
		break;
	case BSSM_ADT_Fg:
		result = "BSSM_ADT_Fg";
		break;
	case BSSM_ADT_Px:
		result = "BSSM_ADT_Px";
		break;
	case BSSM_ADT_PxOpt:
		result = "BSSM_ADT_PxOpt";
		break;
	case BSSM_ADT_GPx:
		result = "BSSM_ADT_GPx";
		break;
	case BSSM_ADT_H:
		result = "BSSM_ADT_H";
		break;
	case BSSM_ADT_S:
		result = "BSSM_ADT_S";
		break;
	case BSSM_ADT_SG:
		result = "BSSM_ADT_SG";
		break;
	case BSSM_ADT_SFg:
		result = "BSSM_ADT_SFg";
		break;
	case BSSM_ADT_Sb:
		result = "BSSM_ADT_Sb";
		break;
	case BSSM_ADT_SH:
		result = "BSSM_ADT_SH";
		break;
	case BSSM_ADT_Shp:
		result = "BSSM_ADT_Shp";
		break;
	case BSSM_ADT_MnShp:
		result = "BSSM_ADT_MnShp";
		break;
	case BSSM_ADT_GShp:
		result = "BSSM_ADT_GShp";
		break;
	case BSSM_ADT_FgShp:
		result = "BSSM_ADT_FgShp";
		break;
	case BSSM_ADT_PxShp:
		result = "BSSM_ADT_PxShp";
		break;
	case BSSM_ADT_GPxShp:
		result = "BSSM_ADT_GPxShp";
		break;
	case BSSM_ADT_HShp:
		result = "BSSM_ADT_HShp";
		break;
	case BSSM_ADT_SShp:
		result = "BSSM_ADT_SShp";
		break;
	case BSSM_ADT_SGShp:
		result = "BSSM_ADT_SGShp";
		break;
	case BSSM_ADT_SFgShp:
		result = "BSSM_ADT_SFgShp";
		break;
	case BSSM_ADT_SbShp:
		result = "BSSM_ADT_SbShp";
		break;
	case BSSM_ADT_SHShp:
		result = "BSSM_ADT_SHShp";
		break;
	case BSSM_ADT2:
		result = "BSSM_ADT2";
		break;
	case BSSM_ADT2_G:
		result = "BSSM_ADT2_G";
		break;
	case BSSM_ADT2_Fg:
		result = "BSSM_ADT2_Fg";
		break;
	case BSSM_ADT2_Px:
		result = "BSSM_ADT2_Px";
		break;
	case BSSM_ADT2_GPx:
		result = "BSSM_ADT2_GPx";
		break;
	case BSSM_ADT2_H:
		result = "BSSM_ADT2_H";
		break;
	case BSSM_ADT2_S:
		result = "BSSM_ADT2_S";
		break;
	case BSSM_ADT2_SG:
		result = "BSSM_ADT2_SG";
		break;
	case BSSM_ADT2_SFg:
		result = "BSSM_ADT2_SFg";
		break;
	case BSSM_ADT2_Sb:
		result = "BSSM_ADT2_Sb";
		break;
	case BSSM_ADT2_SH:
		result = "BSSM_ADT2_SH";
		break;
	case BSSM_ADT2_Shp:
		result = "BSSM_ADT2_Shp";
		break;
	case BSSM_ADT2_GShp:
		result = "BSSM_ADT2_GShp";
		break;
	case BSSM_ADT2_FgShp:
		result = "BSSM_ADT2_FgShp";
		break;
	case BSSM_ADT2_PxShp:
		result = "BSSM_ADT2_PxShp";
		break;
	case BSSM_ADT2_GPxShp:
		result = "BSSM_ADT2_GPxShp";
		break;
	case BSSM_ADT2_HShp:
		result = "BSSM_ADT2_HShp";
		break;
	case BSSM_ADT2_SShp:
		result = "BSSM_ADT2_SShp";
		break;
	case BSSM_ADT2_SGShp:
		result = "BSSM_ADT2_SGShp";
		break;
	case BSSM_ADT2_SFgShp:
		result = "BSSM_ADT2_SFgShp";
		break;
	case BSSM_ADT2_SbShp:
		result = "BSSM_ADT2_SbShp";
		break;
	case BSSM_ADT2_SHShp:
		result = "BSSM_ADT2_SHShp";
		break;
	case BSSM_DIFFUSEDIR:
		result = "BSSM_DIFFUSEDIR";
		break;
	case BSSM_DIFFUSEPT:
		result = "BSSM_DIFFUSEPT";
		break;
	case BSSM_DIFFUSEDIR_S:
		result = "BSSM_DIFFUSEDIR_S";
		break;
	case BSSM_DIFFUSEPT_S:
		result = "BSSM_DIFFUSEPT_S";
		break;
	case BSSM_DIFFUSEDIR_Sb:
		result = "BSSM_DIFFUSEDIR_Sb";
		break;
	case BSSM_DIFFUSEPT_Sb:
		result = "BSSM_DIFFUSEPT_Sb";
		break;
	case BSSM_DIFFUSEPT2:
		result = "BSSM_DIFFUSEPT2";
		break;
	case BSSM_DIFFUSEPT2_Fg:
		result = "BSSM_DIFFUSEPT2_Fg";
		break;
	case BSSM_DIFFUSEPT2_Px:
		result = "BSSM_DIFFUSEPT2_Px";
		break;
	case BSSM_DIFFUSEPT2_S:
		result = "BSSM_DIFFUSEPT2_S";
		break;
	case BSSM_DIFFUSEPT2_SFg:
		result = "BSSM_DIFFUSEPT2_SFg";
		break;
	case BSSM_DIFFUSEPT2_Sb:
		result = "BSSM_DIFFUSEPT2_Sb";
		break;
	case BSSM_DIFFUSEPT2_Shp:
		result = "BSSM_DIFFUSEPT2_Shp";
		break;
	case BSSM_DIFFUSEPT2_FgShp:
		result = "BSSM_DIFFUSEPT2_FgShp";
		break;
	case BSSM_DIFFUSEPT2_PxShp:
		result = "BSSM_DIFFUSEPT2_PxShp";
		break;
	case BSSM_DIFFUSEPT2_SShp:
		result = "BSSM_DIFFUSEPT2_SShp";
		break;
	case BSSM_DIFFUSEPT2_SFgShp:
		result = "BSSM_DIFFUSEPT2_SFgShp";
		break;
	case BSSM_DIFFUSEPT2_SbShp:
		result = "BSSM_DIFFUSEPT2_SbShp";
		break;
	case BSSM_DIFFUSEPT3:
		result = "BSSM_DIFFUSEPT3";
		break;
	case BSSM_DIFFUSEPT3_Fg:
		result = "BSSM_DIFFUSEPT3_Fg";
		break;
	case BSSM_DIFFUSEPT3_Px:
		result = "BSSM_DIFFUSEPT3_Px";
		break;
	case BSSM_DIFFUSEPT3_S:
		result = "BSSM_DIFFUSEPT3_S";
		break;
	case BSSM_DIFFUSEPT3_SFg:
		result = "BSSM_DIFFUSEPT3_SFg";
		break;
	case BSSM_DIFFUSEPT3_Sb:
		result = "BSSM_DIFFUSEPT3_Sb";
		break;
	case BSSM_DIFFUSEPT3_Shp:
		result = "BSSM_DIFFUSEPT3_Shp";
		break;
	case BSSM_DIFFUSEPT3_FgShp:
		result = "BSSM_DIFFUSEPT3_FgShp";
		break;
	case BSSM_DIFFUSEPT3_PxShp:
		result = "BSSM_DIFFUSEPT3_PxShp";
		break;
	case BSSM_DIFFUSEPT3_SShp:
		result = "BSSM_DIFFUSEPT3_SShp";
		break;
	case BSSM_DIFFUSEPT3_SFgShp:
		result = "BSSM_DIFFUSEPT3_SFgShp";
		break;
	case BSSM_DIFFUSEPT3_SbShp:
		result = "BSSM_DIFFUSEPT3_SbShp";
		break;
	case BSSM_TEXTURE:
		result = "BSSM_TEXTURE";
		break;
	case BSSM_TEXTURE_Fg:
		result = "BSSM_TEXTURE_Fg";
		break;
	case BSSM_TEXTURE_H:
		result = "BSSM_TEXTURE_H";
		break;
	case BSSM_TEXTURE_S:
		result = "BSSM_TEXTURE_S";
		break;
	case BSSM_TEXTURE_Vc:
		result = "BSSM_TEXTURE_Vc";
		break;
	case BSSM_TEXTURE_SVc:
		result = "BSSM_TEXTURE_SVc";
		break;
	case BSSM_TEXTURE_SFg:
		result = "BSSM_TEXTURE_SFg";
		break;
	case BSSM_TEXTURE_Sb:
		result = "BSSM_TEXTURE_Sb";
		break;
	case BSSM_TEXTURE_SH:
		result = "BSSM_TEXTURE_SH";
		break;
	case BSSM_TEXTURE_Px:
		result = "BSSM_TEXTURE_Px";
		break;
	case BSSM_SPECULARDIR:
		result = "BSSM_SPECULARDIR";
		break;
	case BSSM_SPECULARPT:
		result = "BSSM_SPECULARPT";
		break;
	case BSSM_SPECULARDIR_S:
		result = "BSSM_SPECULARDIR_S";
		break;
	case BSSM_SPECULARPT_S:
		result = "BSSM_SPECULARPT_S";
		break;
	case BSSM_2x_SPECULARDIR:
		result = "BSSM_2x_SPECULARDIR";
		break;
	case BSSM_2x_SPECULARDIR_H:
		result = "BSSM_2x_SPECULARDIR_H";
		break;
	case BSSM_2x_SPECULARDIR_Px:
		result = "BSSM_2x_SPECULARDIR_Px";
		break;
	case BSSM_2x_SPECULARDIR_S:
		result = "BSSM_2x_SPECULARDIR_S";
		break;
	case BSSM_2x_SPECULARDIR_SH:
		result = "BSSM_2x_SPECULARDIR_SH";
		break;
	case BSSM_2x_SPECULARDIR_Sb:
		result = "BSSM_2x_SPECULARDIR_Sb";
		break;
	case BSSM_2x_SPECULARDIR_Shp:
		result = "BSSM_2x_SPECULARDIR_Shp";
		break;
	case BSSM_2x_SPECULARDIR_HShp:
		result = "BSSM_2x_SPECULARDIR_HShp";
		break;
	case BSSM_2x_SPECULARDIR_PxShp:
		result = "BSSM_2x_SPECULARDIR_PxShp";
		break;
	case BSSM_2x_SPECULARDIR_SShp:
		result = "BSSM_2x_SPECULARDIR_SShp";
		break;
	case BSSM_2x_SPECULARDIR_SHShp:
		result = "BSSM_2x_SPECULARDIR_SHShp";
		break;
	case BSSM_2x_SPECULARDIR_SbShp:
		result = "BSSM_2x_SPECULARDIR_SbShp";
		break;
	case BSSM_2x_SPECULARPT:
		result = "BSSM_2x_SPECULARPT";
		break;
	case BSSM_2x_SPECULARPT_H:
		result = "BSSM_2x_SPECULARPT_H";
		break;
	case BSSM_2x_SPECULARPT_Px:
		result = "BSSM_2x_SPECULARPT_Px";
		break;
	case BSSM_2x_SPECULARPT_S:
		result = "BSSM_2x_SPECULARPT_S";
		break;
	case BSSM_2x_SPECULARPT_SH:
		result = "BSSM_2x_SPECULARPT_SH";
		break;
	case BSSM_2x_SPECULARPT_Sb:
		result = "BSSM_2x_SPECULARPT_Sb";
		break;
	case BSSM_2x_SPECULARPT2:
		result = "BSSM_2x_SPECULARPT2";
		break;
	case BSSM_2x_SPECULARPT2_H:
		result = "BSSM_2x_SPECULARPT2_H";
		break;
	case BSSM_2x_SPECULARPT2_Px:
		result = "BSSM_2x_SPECULARPT2_Px";
		break;
	case BSSM_2x_SPECULARPT2_S:
		result = "BSSM_2x_SPECULARPT2_S";
		break;
	case BSSM_2x_SPECULARPT2_SH:
		result = "BSSM_2x_SPECULARPT2_SH";
		break;
	case BSSM_2x_SPECULARPT2_Sb:
		result = "BSSM_2x_SPECULARPT2_Sb";
		break;
	case BSSM_2x_SPECULARPT3:
		result = "BSSM_2x_SPECULARPT3";
		break;
	case BSSM_2x_SPECULARPT3_H:
		result = "BSSM_2x_SPECULARPT3_H";
		break;
	case BSSM_2x_SPECULARPT3_Px:
		result = "BSSM_2x_SPECULARPT3_Px";
		break;
	case BSSM_2x_SPECULARPT3_S:
		result = "BSSM_2x_SPECULARPT3_S";
		break;
	case BSSM_2x_SPECULARPT3_SH:
		result = "BSSM_2x_SPECULARPT3_SH";
		break;
	case BSSM_2x_SPECULARPT3_Sb:
		result = "BSSM_2x_SPECULARPT3_Sb";
		break;
	case BSSM_3XOCCLUSION:
		result = "BSSM_3XOCCLUSION";
		break;
	case BSSM_3XLIGHTING:
		result = "BSSM_3XLIGHTING";
		break;
	case BSSM_3XLIGHTING_S:
		result = "BSSM_3XLIGHTING_S";
		break;
	case BSSM_3XLIGHTING_H:
		result = "BSSM_3XLIGHTING_H";
		break;
	case BSSM_3XLIGHTING_Px:
		result = "BSSM_3XLIGHTING_Px";
		break;
	case BSSM_3XLIGHTING_Pxo:
		result = "BSSM_3XLIGHTING_Pxo";
		break;
	case BSSM_3XLIGHTING_Fg:
		result = "BSSM_3XLIGHTING_Fg";
		break;
	case BSSM_3XLIGHTING_SFg:
		result = "BSSM_3XLIGHTING_SFg";
		break;
	case BSSM_3XLIGHTING_G:
		result = "BSSM_3XLIGHTING_G";
		break;
	case BSSM_3XLIGHTING_SG:
		result = "BSSM_3XLIGHTING_SG";
		break;
	case BSSM_3XLIGHTING_Vc:
		result = "BSSM_3XLIGHTING_Vc";
		break;
	case BSSM_3XLIGHTING_VcS:
		result = "BSSM_3XLIGHTING_VcS";
		break;
	case BSSM_3XLIGHTING_VcPx:
		result = "BSSM_3XLIGHTING_VcPx";
		break;
	case BSSM_3XLIGHTING_VcPxo:
		result = "BSSM_3XLIGHTING_VcPxo";
		break;
	case BSSM_3XLIGHTING_VcG:
		result = "BSSM_3XLIGHTING_VcG";
		break;
	case BSSM_3XLIGHTING_VcSG:
		result = "BSSM_3XLIGHTING_VcSG";
		break;
	case BSSM_3XLIGHTING_Spc:
		result = "BSSM_3XLIGHTING_Spc";
		break;
	case BSSM_3XLIGHTING_SSpc:
		result = "BSSM_3XLIGHTING_SSpc";
		break;
	case BSSM_3XLIGHTING_HSpc:
		result = "BSSM_3XLIGHTING_HSpc";
		break;
	case BSSM_3XLIGHTING_PxSpc:
		result = "BSSM_3XLIGHTING_PxSpc";
		break;
	case BSSM_3XLIGHTING_PxoSpc:
		result = "BSSM_3XLIGHTING_PxoSpc";
		break;
	case BSSM_3XLIGHTING_FgSpc:
		result = "BSSM_3XLIGHTING_FgSpc";
		break;
	case BSSM_3XLIGHTING_SFgSpc:
		result = "BSSM_3XLIGHTING_SFgSpc";
		break;
	case BSSM_3XLIGHTING_GSpc:
		result = "BSSM_3XLIGHTING_GSpc";
		break;
	case BSSM_3XLIGHTING_SGSpc:
		result = "BSSM_3XLIGHTING_SGSpc";
		break;
	case BSSM_3XLIGHTING_VcSpc:
		result = "BSSM_3XLIGHTING_VcSpc";
		break;
	case BSSM_3XLIGHTING_VcSSpc:
		result = "BSSM_3XLIGHTING_VcSSpc";
		break;
	case BSSM_3XLIGHTING_VcPxSpc:
		result = "BSSM_3XLIGHTING_VcPxSpc";
		break;
	case BSSM_3XLIGHTING_VcPxoSpc:
		result = "BSSM_3XLIGHTING_VcPxoSpc";
		break;
	case BSSM_3XLIGHTING_VcGSpc:
		result = "BSSM_3XLIGHTING_VcGSpc";
		break;
	case BSSM_3XLIGHTING_VcSGSpc:
		result = "BSSM_3XLIGHTING_VcSGSpc";
		break;
	case BSSM_3XLIGHTING_Shp:
		result = "BSSM_3XLIGHTING_Shp";
		break;
	case BSSM_3XLIGHTING_SShp:
		result = "BSSM_3XLIGHTING_SShp";
		break;
	case BSSM_3XLIGHTING_HShp:
		result = "BSSM_3XLIGHTING_HShp";
		break;
	case BSSM_3XLIGHTING_PxShp:
		result = "BSSM_3XLIGHTING_PxShp";
		break;
	case BSSM_3XLIGHTING_PxoShp:
		result = "BSSM_3XLIGHTING_PxoShp";
		break;
	case BSSM_3XLIGHTING_FgShp:
		result = "BSSM_3XLIGHTING_FgShp";
		break;
	case BSSM_3XLIGHTING_SFgShp:
		result = "BSSM_3XLIGHTING_SFgShp";
		break;
	case BSSM_3XLIGHTING_GShp:
		result = "BSSM_3XLIGHTING_GShp";
		break;
	case BSSM_3XLIGHTING_SGShp:
		result = "BSSM_3XLIGHTING_SGShp";
		break;
	case BSSM_3XLIGHTING_VcShp:
		result = "BSSM_3XLIGHTING_VcShp";
		break;
	case BSSM_3XLIGHTING_VcSShp:
		result = "BSSM_3XLIGHTING_VcSShp";
		break;
	case BSSM_3XLIGHTING_VcPxShp:
		result = "BSSM_3XLIGHTING_VcPxShp";
		break;
	case BSSM_3XLIGHTING_VcPxoShp:
		result = "BSSM_3XLIGHTING_VcPxoShp";
		break;
	case BSSM_3XLIGHTING_VcGShp:
		result = "BSSM_3XLIGHTING_VcGShp";
		break;
	case BSSM_3XLIGHTING_VcSGShp:
		result = "BSSM_3XLIGHTING_VcSGShp";
		break;
	case BSSM_3XLIGHTING_ShpSpc:
		result = "BSSM_3XLIGHTING_ShpSpc";
		break;
	case BSSM_3XLIGHTING_SShpSpc:
		result = "BSSM_3XLIGHTING_SShpSpc";
		break;
	case BSSM_3XLIGHTING_HShpSpc:
		result = "BSSM_3XLIGHTING_HShpSpc";
		break;
	case BSSM_3XLIGHTING_PxShpSpc:
		result = "BSSM_3XLIGHTING_PxShpSpc";
		break;
	case BSSM_3XLIGHTING_PxoShpSpc:
		result = "BSSM_3XLIGHTING_PxoShpSpc";
		break;
	case BSSM_3XLIGHTING_FgShpSpc:
		result = "BSSM_3XLIGHTING_FgShpSpc";
		break;
	case BSSM_3XLIGHTING_SFgShpSpc:
		result = "BSSM_3XLIGHTING_SFgShpSpc";
		break;
	case BSSM_3XLIGHTING_GShpSpc:
		result = "BSSM_3XLIGHTING_GShpSpc";
		break;
	case BSSM_3XLIGHTING_SGShpSpc:
		result = "BSSM_3XLIGHTING_SGShpSpc";
		break;
	case BSSM_3XLIGHTING_VcShpSpc:
		result = "BSSM_3XLIGHTING_VcShpSpc";
		break;
	case BSSM_3XLIGHTING_VcSShpSpc:
		result = "BSSM_3XLIGHTING_VcSShpSpc";
		break;
	case BSSM_3XLIGHTING_VcPxShpSpc:
		result = "BSSM_3XLIGHTING_VcPxShpSpc";
		break;
	case BSSM_3XLIGHTING_VcPxoShpSpc:
		result = "BSSM_3XLIGHTING_VcPxoShpSpc";
		break;
	case BSSM_3XLIGHTING_VcGShpSpc:
		result = "BSSM_3XLIGHTING_VcGShpSpc";
		break;
	case BSSM_3XLIGHTING_VcSGShpSpc:
		result = "BSSM_3XLIGHTING_VcSGShpSpc";
		break;
	case BSSM_3XSILHOUETTE:
		result = "BSSM_3XSILHOUETTE";
		break;
	case BSSM_3XSILHOUETTE_Vc:
		result = "BSSM_3XSILHOUETTE_Vc";
		break;
	case BSSM_3XENVMAP:
		result = "BSSM_3XENVMAP";
		break;
	case BSSM_3XENVMAP_W:
		result = "BSSM_3XENVMAP_W";
		break;
	case BSSM_3XENVMAP_Vc:
		result = "BSSM_3XENVMAP_Vc";
		break;
	case BSSM_3XENVMAP_WVc:
		result = "BSSM_3XENVMAP_WVc";
		break;
	case BSSM_3XENVMAP_S:
		result = "BSSM_3XENVMAP_S";
		break;
	case BSSM_3XENVMAP_SVc:
		result = "BSSM_3XENVMAP_SVc";
		break;
	case BSSM_3XENVMAP_EYE:
		result = "BSSM_3XENVMAP_EYE";
		break;
	case BSSM_3XLIGHTING_SIMPLESHADOW:
		result = "BSSM_3XLIGHTING_SIMPLESHADOW";
		break;
	case BSSM_3XLIGHTING_SIMPLESHADOW_Vc:
		result = "BSSM_3XLIGHTING_SIMPLESHADOW_Vc";
		break;
	case BSSM_3XLIGHTING_SIMPLESHADOW_S:
		result = "BSSM_3XLIGHTING_SIMPLESHADOW_S";
		break;
	case BSSM_3XLIGHTING_SIMPLESHADOW_VcS:
		result = "BSSM_3XLIGHTING_SIMPLESHADOW_VcS";
		break;
	case BSSM_3XDEPTHMAP:
		result = "BSSM_3XDEPTHMAP";
		break;
	case BSSM_3XDEPTHMAP_Vc:
		result = "BSSM_3XDEPTHMAP_Vc";
		break;
	case BSSM_3XDEPTHMAP_S:
		result = "BSSM_3XDEPTHMAP_S";
		break;
	case BSSM_3XDEPTHMAP_VcS:
		result = "BSSM_3XDEPTHMAP_VcS";
		break;
	case BSSM_3XRENDERNORMALS:
		result = "BSSM_3XRENDERNORMALS";
		break;
	case BSSM_3XRENDERNORMALS_Vc:
		result = "BSSM_3XRENDERNORMALS_Vc";
		break;
	case BSSM_3XRENDERNORMALS_S:
		result = "BSSM_3XRENDERNORMALS_S";
		break;
	case BSSM_3XRENDERNORMALS_VcS:
		result = "BSSM_3XRENDERNORMALS_VcS";
		break;
	case BSSM_3XRENDERNORMALS_FIRE:
		result = "BSSM_3XRENDERNORMALS_FIRE";
		break;
	case BSSM_3XRENDERNORMALS_CLEAR:
		result = "BSSM_3XRENDERNORMALS_CLEAR";
		break;
	case BSSM_3XRENDERNORMALS_CLEAR_S:
		result = "BSSM_3XRENDERNORMALS_CLEAR_S";
		break;
	case BSSM_3XCONSTALPHA:
		result = "BSSM_3XCONSTALPHA";
		break;
	case BSSM_3XCONSTALPHA_Vc:
		result = "BSSM_3XCONSTALPHA_Vc";
		break;
	case BSSM_3XCONSTALPHA_S:
		result = "BSSM_3XCONSTALPHA_S";
		break;
	case BSSM_3XCONSTALPHA_SVc:
		result = "BSSM_3XCONSTALPHA_SVc";
		break;
	case BSSM_3XDEPTH:
		result = "BSSM_3XDEPTH";
		break;
	case BSSM_3XDEPTH_Vc:
		result = "BSSM_3XDEPTH_Vc";
		break;
	case BSSM_3XDEPTH_S:
		result = "BSSM_3XDEPTH_S";
		break;
	case BSSM_3XDEPTH_SVc:
		result = "BSSM_3XDEPTH_SVc";
		break;
	case BSSM_3XVELOCITY:
		result = "BSSM_3XVELOCITY";
		break;
	case BSSM_3XVELOCITY_S:
		result = "BSSM_3XVELOCITY_S";
		break;
	case BSSM_3XLOCALMAP:
		result = "BSSM_3XLOCALMAP";
		break;
	case BSSM_3XLOCALMAP_S:
		result = "BSSM_3XLOCALMAP_S";
		break;
	case BSSM_3XLOCALMAP_CLEAR:
		result = "BSSM_3XLOCALMAP_CLEAR";
		break;
	case BSSM_3XTEXEFFECT:
		result = "BSSM_3XTEXEFFECT";
		break;
	case BSSM_3XTEXEFFECT_S:
		result = "BSSM_3XTEXEFFECT_S";
		break;
	case BSSM_RENDERNORMALS:
		result = "BSSM_RENDERNORMALS";
		break;
	case BSSM_RENDERNORMALS_S:
		result = "BSSM_RENDERNORMALS_S";
		break;
	case BSSM_RENDERNORMALS_FIRE:
		result = "BSSM_RENDERNORMALS_FIRE";
		break;
	case BSSM_RENDERNORMALS_CLEAR:
		result = "BSSM_RENDERNORMALS_CLEAR";
		break;
	case BSSM_RENDERNORMALS_CLEAR_S:
		result = "BSSM_RENDERNORMALS_CLEAR_S";
		break;
	case BSSM_DEPTH:
		result = "BSSM_DEPTH";
		break;
	case BSSM_DEPTH_S:
		result = "BSSM_DEPTH_S";
		break;
	case BSSM_DEPTH_Mn:
		result = "BSSM_DEPTH_Mn";
		break;
	case BSSM_VELOCITY:
		result = "BSSM_VELOCITY";
		break;
	case BSSM_VELOCITY_S:
		result = "BSSM_VELOCITY_S";
		break;
	case BSSM_LOCALMAP:
		result = "BSSM_LOCALMAP";
		break;
	case BSSM_LOCALMAP_S:
		result = "BSSM_LOCALMAP_S";
		break;
	case BSSM_LOCALMAP_CLEAR:
		result = "BSSM_LOCALMAP_CLEAR";
		break;
	case BSSM_LANDDIFF:
		result = "BSSM_LANDDIFF";
		break;
	case BSSM_LAND2xDIFF:
		result = "BSSM_LAND2xDIFF";
		break;
	case BSSM_LAND_G:
		result = "BSSM_LAND_G";
		break;
	case BSSM_LANDAD_A:
		result = "BSSM_LANDAD_A";
		break;
	case BSSM_LANDAD_AShp:
		result = "BSSM_LANDAD_AShp";
		break;
	case BSSM_LAND_GA:
		result = "BSSM_LAND_GA";
		break;
	case BSSM_LANDDIFF_A:
		result = "BSSM_LANDDIFF_A";
		break;
	case BSSM_LAND2xDIFF_A:
		result = "BSSM_LAND2xDIFF_A";
		break;
	case BSSM_LAND1O:
		result = "BSSM_LAND1O";
		break;
	case BSSM_LAND1O_Shp:
		result = "BSSM_LAND1O_Shp";
		break;
	case BSSM_LAND1O_Simple:
		result = "BSSM_LAND1O_Simple";
		break;
	case BSSM_LAND1O_SimpleShp:
		result = "BSSM_LAND1O_SimpleShp";
		break;
	case BSSM_LAND1O4:
		result = "BSSM_LAND1O4";
		break;
	case BSSM_LAND1O4_Shp:
		result = "BSSM_LAND1O4_Shp";
		break;
	case BSSM_LAND1O4_Simple:
		result = "BSSM_LAND1O4_Simple";
		break;
	case BSSM_LAND1O4_SimpleShp:
		result = "BSSM_LAND1O4_SimpleShp";
		break;
	case BSSM_LAND2O:
		result = "BSSM_LAND2O";
		break;
	case BSSM_LAND2O_Shp:
		result = "BSSM_LAND2O_Shp";
		break;
	case BSSM_LAND2O_Simple:
		result = "BSSM_LAND2O_Simple";
		break;
	case BSSM_LAND2O_SimpleShp:
		result = "BSSM_LAND2O_SimpleShp";
		break;
	case BSSM_LAND2O4:
		result = "BSSM_LAND2O4";
		break;
	case BSSM_LAND2O4_Shp:
		result = "BSSM_LAND2O4_Shp";
		break;
	case BSSM_LAND2O4_Simple:
		result = "BSSM_LAND2O4_Simple";
		break;
	case BSSM_LAND2O4_SimpleShp:
		result = "BSSM_LAND2O4_SimpleShp";
		break;
	case BSSM_LAND3O:
		result = "BSSM_LAND3O";
		break;
	case BSSM_LAND3O_Shp:
		result = "BSSM_LAND3O_Shp";
		break;
	case BSSM_LAND3O_Simple:
		result = "BSSM_LAND3O_Simple";
		break;
	case BSSM_LAND3O_SimpleShp:
		result = "BSSM_LAND3O_SimpleShp";
		break;
	case BSSM_LAND3O4:
		result = "BSSM_LAND3O4";
		break;
	case BSSM_LAND3O4_Shp:
		result = "BSSM_LAND3O4_Shp";
		break;
	case BSSM_LAND3O4_Simple:
		result = "BSSM_LAND3O4_Simple";
		break;
	case BSSM_LAND3O4_SimpleShp:
		result = "BSSM_LAND3O4_SimpleShp";
		break;
	case BSSM_LAND4O:
		result = "BSSM_LAND4O";
		break;
	case BSSM_LAND4O_Shp:
		result = "BSSM_LAND4O_Shp";
		break;
	case BSSM_LAND4O_Simple:
		result = "BSSM_LAND4O_Simple";
		break;
	case BSSM_LAND4O_SimpleShp:
		result = "BSSM_LAND4O_SimpleShp";
		break;
	case BSSM_LAND4O4:
		result = "BSSM_LAND4O4";
		break;
	case BSSM_LAND4O4_Shp:
		result = "BSSM_LAND4O4_Shp";
		break;
	case BSSM_LAND4O4_Simple:
		result = "BSSM_LAND4O4_Simple";
		break;
	case BSSM_LAND4O4_SimpleShp:
		result = "BSSM_LAND4O4_SimpleShp";
		break;
	case BSSM_LAND5O:
		result = "BSSM_LAND5O";
		break;
	case BSSM_LAND5O_Shp:
		result = "BSSM_LAND5O_Shp";
		break;
	case BSSM_LAND5O_Simple:
		result = "BSSM_LAND5O_Simple";
		break;
	case BSSM_LAND5O_SimpleShp:
		result = "BSSM_LAND5O_SimpleShp";
		break;
	case BSSM_LAND5O4:
		result = "BSSM_LAND5O4";
		break;
	case BSSM_LAND5O4_Shp:
		result = "BSSM_LAND5O4_Shp";
		break;
	case BSSM_LAND5O4_Simple:
		result = "BSSM_LAND5O4_Simple";
		break;
	case BSSM_LAND5O4_SimpleShp:
		result = "BSSM_LAND5O4_SimpleShp";
		break;
	case BSSM_LAND6O:
		result = "BSSM_LAND6O";
		break;
	case BSSM_LAND6O_Shp:
		result = "BSSM_LAND6O_Shp";
		break;
	case BSSM_LAND6O_Simple:
		result = "BSSM_LAND6O_Simple";
		break;
	case BSSM_LAND6O_SimpleShp:
		result = "BSSM_LAND6O_SimpleShp";
		break;
	case BSSM_LAND6O4:
		result = "BSSM_LAND6O4";
		break;
	case BSSM_LAND6O4_Shp:
		result = "BSSM_LAND6O4_Shp";
		break;
	case BSSM_LAND6O4_Simple:
		result = "BSSM_LAND6O4_Simple";
		break;
	case BSSM_LAND6O4_SimpleShp:
		result = "BSSM_LAND6O4_SimpleShp";
		break;
	case BSSM_LAND7O:
		result = "BSSM_LAND7O";
		break;
	case BSSM_LAND7O_Shp:
		result = "BSSM_LAND7O_Shp";
		break;
	case BSSM_LAND7O_Simple:
		result = "BSSM_LAND7O_Simple";
		break;
	case BSSM_LAND7O_SimpleShp:
		result = "BSSM_LAND7O_SimpleShp";
		break;
	case BSSM_LAND7O4:
		result = "BSSM_LAND7O4";
		break;
	case BSSM_LAND7O4_Shp:
		result = "BSSM_LAND7O4_Shp";
		break;
	case BSSM_LAND7O4_Simple:
		result = "BSSM_LAND7O4_Simple";
		break;
	case BSSM_LAND7O4_SimpleShp:
		result = "BSSM_LAND7O4_SimpleShp";
		break;
	case BSSM_LANDO_Am:
		result = "BSSM_LANDO_Am";
		break;
	case BSSM_LANDLO_A:
		result = "BSSM_LANDLO_A";
		break;
	case BSSM_2x_SIMPLESHADOW:
		result = "BSSM_2x_SIMPLESHADOW";
		break;
	case BSSM_2x_SIMPLESHADOW_S:
		result = "BSSM_2x_SIMPLESHADOW_S";
		break;
	case BSSM_2x_SIMPLESHADOW_LAND:
		result = "BSSM_2x_SIMPLESHADOW_LAND";
		break;
	case BSSM_2x_SIMPLESHADOW_Sb:
		result = "BSSM_2x_SIMPLESHADOW_Sb";
		break;
	case BSSM_ADT_Sbb:
		result = "BSSM_ADT_Sbb";
		break;
	case BSSM_DISTANT_TREE_BASE:
		result = "BSSM_DISTANT_TREE_BASE";
		break;
	case BSSM_SKYBASEPRE:
		result = "BSSM_SKYBASEPRE";
		break;
	case BSSM_SKY:
		result = "BSSM_SKY";
		break;
	case BSSM_SKY_MOON_STARS_MASK:
		result = "BSSM_SKY_MOON_STARS_MASK";
		break;
	case BSSM_SKY_STARS:
		result = "BSSM_SKY_STARS";
		break;
	case BSSM_SKY_TEXTURE:
		result = "BSSM_SKY_TEXTURE";
		break;
	case BSSM_SKY_CLOUDS:
		result = "BSSM_SKY_CLOUDS";
		break;
	case BSSM_SKY_CLOUDS_UNDERWATER:
		result = "BSSM_SKY_CLOUDS_UNDERWATER";
		break;
	case BSSM_WATER_LOD:
		result = "BSSM_WATER_LOD";
		break;
	case BSSM_WATER_LOD_NO_REFLECTIONS:
		result = "BSSM_WATER_LOD_NO_REFLECTIONS";
		break;
	case BSSM_PARTICLE:
		result = "BSSM_PARTICLE";
		break;
	case BSSM_BOLT:
		result = "BSSM_BOLT";
		break;
	case BSSM_BEAM:
		result = "BSSM_BEAM";
		break;
	case BSSM_ENVMAP:
		result = "BSSM_ENVMAP";
		break;
	case BSSM_ENVMAP_Vc:
		result = "BSSM_ENVMAP_Vc";
		break;
	case BSSM_ENVMAP_S:
		result = "BSSM_ENVMAP_S";
		break;
	case BSSM_ENVMAP_SVc:
		result = "BSSM_ENVMAP_SVc";
		break;
	case BSSM_2x_ENVMAP:
		result = "BSSM_2x_ENVMAP";
		break;
	case BSSM_2x_ENVMAP_S:
		result = "BSSM_2x_ENVMAP_S";
		break;
	case BSSM_2x_ENVMAP_W:
		result = "BSSM_2x_ENVMAP_W";
		break;
	case BSSM_2x_ENVMAP_EYE:
		result = "BSSM_2x_ENVMAP_EYE";
		break;
	case BSSM_GEOMDECAL:
		result = "BSSM_GEOMDECAL";
		break;
	case BSSM_GEOMDECAL_S:
		result = "BSSM_GEOMDECAL_S";
		break;
	case BSSM_TEXEFFECT:
		result = "BSSM_TEXEFFECT";
		break;
	case BSSM_TEXEFFECT_S:
		result = "BSSM_TEXEFFECT_S";
		break;
	case BSSM_2x_TEXEFFECT:
		result = "BSSM_2x_TEXEFFECT";
		break;
	case BSSM_2x_TEXEFFECT_S:
		result = "BSSM_2x_TEXEFFECT_S";
		break;
	case BSSM_FOG:
		result = "BSSM_FOG";
		break;
	case BSSM_FOG_A:
		result = "BSSM_FOG_A";
		break;
	case BSSM_FOG_S:
		result = "BSSM_FOG_S";
		break;
	case BSSM_FOG_SA:
		result = "BSSM_FOG_SA";
		break;
	case BSSM_FOG_Sb:
		result = "BSSM_FOG_Sb";
		break;
	case BSSM_GRASS_DIRONLY_LF:
		result = "BSSM_GRASS_DIRONLY_LF";
		break;
	case BSSM_GRASS_DIRONLY_LV:
		result = "BSSM_GRASS_DIRONLY_LV";
		break;
	case BSSM_GRASS_DIRONLY_LFS:
		result = "BSSM_GRASS_DIRONLY_LFS";
		break;
	case BSSM_GRASS_DIRONLY_LVS:
		result = "BSSM_GRASS_DIRONLY_LVS";
		break;
	case BSSM_GRASS_DIRONLY_LFP:
		result = "BSSM_GRASS_DIRONLY_LFP";
		break;
	case BSSM_GRASS_DIRONLY_LVP:
		result = "BSSM_GRASS_DIRONLY_LVP";
		break;
	case BSSM_GRASS_DIRONLY_LFSP:
		result = "BSSM_GRASS_DIRONLY_LFSP";
		break;
	case BSSM_GRASS_DIRONLY_LVSP:
		result = "BSSM_GRASS_DIRONLY_LVSP";
		break;
	case BSSM_GRASS_DIRONLY_LFShp:
		result = "BSSM_GRASS_DIRONLY_LFShp";
		break;
	case BSSM_GRASS_DIRONLY_LVShp:
		result = "BSSM_GRASS_DIRONLY_LVShp";
		break;
	case BSSM_GRASS_DIRONLY_LFSShp:
		result = "BSSM_GRASS_DIRONLY_LFSShp";
		break;
	case BSSM_GRASS_DIRONLY_LVSShp:
		result = "BSSM_GRASS_DIRONLY_LVSShp";
		break;
	case BSSM_GRASS_DIRONLY_LFPShp:
		result = "BSSM_GRASS_DIRONLY_LFPShp";
		break;
	case BSSM_GRASS_DIRONLY_LVPShp:
		result = "BSSM_GRASS_DIRONLY_LVPShp";
		break;
	case BSSM_GRASS_DIRONLY_LFSPShp:
		result = "BSSM_GRASS_DIRONLY_LFSPShp";
		break;
	case BSSM_GRASS_DIRONLY_LVSPShp:
		result = "BSSM_GRASS_DIRONLY_LVSPShp";
		break;
	case BSSM_GRASS_DIRONLY_LFB:
		result = "BSSM_GRASS_DIRONLY_LFB";
		break;
	case BSSM_GRASS_DIRONLY_LFSB:
		result = "BSSM_GRASS_DIRONLY_LFSB";
		break;
	case BSSM_GRASS_DIRONLY_LFPB:
		result = "BSSM_GRASS_DIRONLY_LFPB";
		break;
	case BSSM_GRASS_DIRONLY_LFSPB:
		result = "BSSM_GRASS_DIRONLY_LFSPB";
		break;
	case BSSM_GRASS_1POINT_LF:
		result = "BSSM_GRASS_1POINT_LF";
		break;
	case BSSM_GRASS_1POINT_LV:
		result = "BSSM_GRASS_1POINT_LV";
		break;
	case BSSM_GRASS_1POINT_LFS:
		result = "BSSM_GRASS_1POINT_LFS";
		break;
	case BSSM_GRASS_1POINT_LVS:
		result = "BSSM_GRASS_1POINT_LVS";
		break;
	case BSSM_GRASS_1POINT_LFP:
		result = "BSSM_GRASS_1POINT_LFP";
		break;
	case BSSM_GRASS_1POINT_LVP:
		result = "BSSM_GRASS_1POINT_LVP";
		break;
	case BSSM_GRASS_1POINT_LFSP:
		result = "BSSM_GRASS_1POINT_LFSP";
		break;
	case BSSM_GRASS_1POINT_LVSP:
		result = "BSSM_GRASS_1POINT_LVSP";
		break;
	case BSSM_GRASS_1POINT_LFShp:
		result = "BSSM_GRASS_1POINT_LFShp";
		break;
	case BSSM_GRASS_1POINT_LVShp:
		result = "BSSM_GRASS_1POINT_LVShp";
		break;
	case BSSM_GRASS_1POINT_LFSShp:
		result = "BSSM_GRASS_1POINT_LFSShp";
		break;
	case BSSM_GRASS_1POINT_LVSShp:
		result = "BSSM_GRASS_1POINT_LVSShp";
		break;
	case BSSM_GRASS_1POINT_LFPShp:
		result = "BSSM_GRASS_1POINT_LFPShp";
		break;
	case BSSM_GRASS_1POINT_LVPShp:
		result = "BSSM_GRASS_1POINT_LVPShp";
		break;
	case BSSM_GRASS_1POINT_LFSPShp:
		result = "BSSM_GRASS_1POINT_LFSPShp";
		break;
	case BSSM_GRASS_1POINT_LVSPShp:
		result = "BSSM_GRASS_1POINT_LVSPShp";
		break;
	case BSSM_GRASS_1POINT_LFB:
		result = "BSSM_GRASS_1POINT_LFB";
		break;
	case BSSM_GRASS_1POINT_LFSB:
		result = "BSSM_GRASS_1POINT_LFSB";
		break;
	case BSSM_GRASS_1POINT_LFPB:
		result = "BSSM_GRASS_1POINT_LFPB";
		break;
	case BSSM_GRASS_1POINT_LFSPB:
		result = "BSSM_GRASS_1POINT_LFSPB";
		break;
	case BSSM_GRASS_SHADOW_L:
		result = "BSSM_GRASS_SHADOW_L";
		break;
	case BSSM_GRASS_SHADOW_LS:
		result = "BSSM_GRASS_SHADOW_LS";
		break;
	case BSSM_GRASS_SHADOW_LB:
		result = "BSSM_GRASS_SHADOW_LB";
		break;
	case BSSM_GRASS_SHADOW_LSB:
		result = "BSSM_GRASS_SHADOW_LSB";
		break;
	case BSSM_WATER_STENCIL:
		result = "BSSM_WATER_STENCIL";
		break;
	case BSSM_WATER_STENCIL_Vc:
		result = "BSSM_WATER_STENCIL_Vc";
		break;
	case BSSM_WATER_WADING:
		result = "BSSM_WATER_WADING";
		break;
	case BSSM_WATER_WADING_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_WADING_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_WADING_NO_REFRACTIONS:
		result = "BSSM_WATER_WADING_NO_REFRACTIONS";
		break;
	case BSSM_WATER_WADING_NO_REFLECTIONS:
		result = "BSSM_WATER_WADING_NO_REFLECTIONS";
		break;
	case BSSM_WATER_WADING_NO_DEPTH:
		result = "BSSM_WATER_WADING_NO_DEPTH";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_NO_REFRACTIONS:
		result = "BSSM_WATER_WADING_NO_DEPTH_NO_REFRACTIONS";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS:
		result = "BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS";
		break;
	case BSSM_WATER_INTERIOR_WADING:
		result = "BSSM_WATER_INTERIOR_WADING";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_WADING_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS:
		result = "BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS";
		break;
	case BSSM_WATER_WADING_SPECULAR_LIGHTING:
		result = "BSSM_WATER_WADING_SPECULAR_LIGHTING";
		break;
	case BSSM_WATER_WADING_Vc:
		result = "BSSM_WATER_WADING_Vc";
		break;
	case BSSM_WATER_WADING_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_WADING_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_WADING_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_WADING_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_WADING_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_WADING_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_Vc:
		result = "BSSM_WATER_WADING_NO_DEPTH_Vc";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_WADING_NO_DEPTH_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_WADING_SPECULAR_LIGHTING_Vc:
		result = "BSSM_WATER_WADING_SPECULAR_LIGHTING_Vc";
		break;
	case BSSM_WATER:
		result = "BSSM_WATER";
		break;
	case BSSM_WATER_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_NO_REFRACTIONS:
		result = "BSSM_WATER_NO_REFRACTIONS";
		break;
	case BSSM_WATER_NO_REFLECTIONS:
		result = "BSSM_WATER_NO_REFLECTIONS";
		break;
	case BSSM_WATER_INTERIOR:
		result = "BSSM_WATER_INTERIOR";
		break;
	case BSSM_WATER_INTERIOR_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_NO_REFLECTIONS:
		result = "BSSM_WATER_INTERIOR_NO_REFLECTIONS";
		break;
	case BSSM_WATER_NODEPTH:
		result = "BSSM_WATER_NODEPTH";
		break;
	case BSSM_WATER_NODEPTH_NO_REFLECTIONS:
		result = "BSSM_WATER_NODEPTH_NO_REFLECTIONS";
		break;
	case BSSM_WATER_NODEPTH_NO_REFRACTIONS:
		result = "BSSM_WATER_NODEPTH_NO_REFRACTIONS";
		break;
	case BSSM_WATER_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH:
		result = "BSSM_WATER_INTERIOR_NODEPTH";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_NO_REFRACTIONS:
		result = "BSSM_WATER_INTERIOR_NODEPTH_NO_REFRACTIONS";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS:
		result = "BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS";
		break;
	case BSSM_WATER_SPECULAR_LIGHTING:
		result = "BSSM_WATER_SPECULAR_LIGHTING";
		break;
	case BSSM_WATER_UNDERWATER:
		result = "BSSM_WATER_UNDERWATER";
		break;
	case BSSM_WATER_Vc:
		result = "BSSM_WATER_Vc";
		break;
	case BSSM_WATER_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_Vc:
		result = "BSSM_WATER_INTERIOR_Vc";
		break;
	case BSSM_WATER_INTERIOR_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_NODEPTH_Vc:
		result = "BSSM_WATER_NODEPTH_Vc";
		break;
	case BSSM_WATER_NODEPTH_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_NODEPTH_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_NODEPTH_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_NODEPTH_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_Vc:
		result = "BSSM_WATER_INTERIOR_NODEPTH_Vc";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_NO_REFRACTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_NODEPTH_NO_REFRACTIONS_Vc";
		break;
	case BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_Vc:
		result = "BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_Vc";
		break;
	case BSSM_WATER_SPECULAR_LIGHTING_Vc:
		result = "BSSM_WATER_SPECULAR_LIGHTING_Vc";
		break;
	case BSSM_PRECIPITATION_RAIN:
		result = "BSSM_PRECIPITATION_RAIN";
		break;
	case BSSM_SKYBASEPOST:
		result = "BSSM_SKYBASEPOST";
		break;
	case BSSM_SELFILLUM_SKY:
		result = "BSSM_SELFILLUM_SKY";
		break;
	case BSSM_SKY_SUNGLARE:
		result = "BSSM_SKY_SUNGLARE";
		break;
	case BSSM_SELFILLUM_SKY_SUN:
		result = "BSSM_SELFILLUM_SKY_SUN";
		break;
	case BSSM_SELFILLUM_SKY_CLOUDS:
		result = "BSSM_SELFILLUM_SKY_CLOUDS";
		break;
	case BSSM_SELFILLUM_SKY_SKY_QUAD:
		result = "BSSM_SELFILLUM_SKY_SKY_QUAD";
		break;
	case BSSM_SELFILLUMALPHA:
		result = "BSSM_SELFILLUMALPHA";
		break;
	case BSSM_SELFILLUMALPHA_S:
		result = "BSSM_SELFILLUMALPHA_S";
		break;
	case BSSM_WATER_DEPTH:
		result = "BSSM_WATER_DEPTH";
		break;
	case BSSM_WATER_DEPTH_S:
		result = "BSSM_WATER_DEPTH_S";
		break;
	case BSSM_3XWATER_DEPTH:
		result = "BSSM_3XWATER_DEPTH";
		break;
	case BSSM_3XWATER_DEPTH_S:
		result = "BSSM_3XWATER_DEPTH_S";
		break;
	case BSSM_NLWATER_DEPTH:
		result = "BSSM_NLWATER_DEPTH";
		break;
	case BSSM_NLWATER_DEPTH_S:
		result = "BSSM_NLWATER_DEPTH_S";
		break;
	case BSSM_WATER_DEPTH_At:
		result = "BSSM_WATER_DEPTH_At";
		break;
	case BSSM_WATER_DEPTH_SAt:
		result = "BSSM_WATER_DEPTH_SAt";
		break;
	case BSSM_3XWATER_DEPTH_At:
		result = "BSSM_3XWATER_DEPTH_At";
		break;
	case BSSM_3XWATER_DEPTH_SAt:
		result = "BSSM_3XWATER_DEPTH_SAt";
		break;
	case BSSM_NLWATER_DEPTH_At:
		result = "BSSM_NLWATER_DEPTH_At";
		break;
	case BSSM_NLWATER_DEPTH_At_S:
		result = "BSSM_NLWATER_DEPTH_At_S";
		break;
	case BSSM_WATER_DEPTH_Vc:
		result = "BSSM_WATER_DEPTH_Vc";
		break;
	case BSSM_WATER_DEPTH_SVc:
		result = "BSSM_WATER_DEPTH_SVc";
		break;
	case BSSM_3XWATER_DEPTH_Vc:
		result = "BSSM_3XWATER_DEPTH_Vc";
		break;
	case BSSM_3XWATER_DEPTH_SVc:
		result = "BSSM_3XWATER_DEPTH_SVc";
		break;
	case BSSM_NLWATER_DEPTH_Vc:
		result = "BSSM_NLWATER_DEPTH_Vc";
		break;
	case BSSM_NLWATER_DEPTH_Vc_S:
		result = "BSSM_NLWATER_DEPTH_Vc_S";
		break;
	case BSSM_WATER_DEPTH_AtVc:
		result = "BSSM_WATER_DEPTH_AtVc";
		break;
	case BSSM_WATER_DEPTH_SAtVc:
		result = "BSSM_WATER_DEPTH_SAtVc";
		break;
	case BSSM_3XWATER_DEPTH_AtVc:
		result = "BSSM_3XWATER_DEPTH_AtVc";
		break;
	case BSSM_3XWATER_DEPTH_SAtVc:
		result = "BSSM_3XWATER_DEPTH_SAtVc";
		break;
	case BSSM_NLWATER_DEPTH_AtVc:
		result = "BSSM_NLWATER_DEPTH_AtVc";
		break;
	case BSSM_NLWATER_DEPTH_AtVc_S:
		result = "BSSM_NLWATER_DEPTH_AtVc_S";
		break;
	case BSSM_BLOOD_SPLATTER_FLARE:
		result = "BSSM_BLOOD_SPLATTER_FLARE";
		break;
	case BSSM_BLOOD_SPLATTER:
		result = "BSSM_BLOOD_SPLATTER";
		break;
	case BSSM_SHADOWVOLUME_BACK:
		result = "BSSM_SHADOWVOLUME_BACK";
		break;
	case BSSM_SHADOWVOLUME_FRONT:
		result = "BSSM_SHADOWVOLUME_FRONT";
		break;
	case BSSM_SHADOWVOLUME_WIRE:
		result = "BSSM_SHADOWVOLUME_WIRE";
		break;
	case BSSM_TILE:
		result = "BSSM_TILE";
		break;
	case BSSM_IMAGESPACE:
		result = "BSSM_IMAGESPACE";
		break;
	default:
		result = "Unknown pass!";
		break;
	}
	return result;
}

const char* BSRenderPass::GetPassName() {
	if (this->bEnabled)
		return BSRenderPass::GetPassName(this->usPassEnum);
	else
		return "Pass not initialized";
}

const char* BSRenderPass::GetCurrentPassName() {
	BSRenderPass* pCurrPass = BSRenderPass::GetCurrentPass();
	if (pCurrPass && pCurrPass->bEnabled)
		return pCurrPass->GetPassName(pCurrPass->usPassEnum);
	else
		return "Pass not initialized";
}

const char* BSRenderPass::GetCurrentPassShaderType() {
	UInt32 eType = 0;
	BSRenderPass* pCurrPass = BSRenderPass::GetCurrentPass();
	if (pCurrPass && pCurrPass->bEnabled) {
		if (pCurrPass->usPassEnum > 0 && pCurrPass->usPassEnum < BSSM_IMAGESPACE) {
			if (pCurrPass->pGeometry) {
				NiGeometry* pGeo = pCurrPass->pGeometry->IsGeometry();
				if (pGeo) {
					BSShaderProperty* pShaderProp = ((BSShaderProperty*)pGeo->shaderProperties.m_shadeProperty);
					if (pShaderProp) {
						eType = ((BSShaderProperty*)pGeo->shaderProperties.m_shadeProperty)->m_eShaderType;
					}
					else {
#if _DEBUG
						_ERROR("[BSRenderPass::GetCurrentPassShaderType] No shader property!");
#endif
						return "No shader property!";
					}
				}
				else {
					return "Geometry not initialized!";
				}
			}
			else {
#if _DEBUG
				_ERROR("[BSRenderPass::GetCurrentPassShaderType] Geometry not initialized!");
#endif
				return "Geometry not initialized!";
			}
		}
		else {
			return "ImageSpace";
		}
	}
	return NiShadeProperty::GetShaderType(eType);
}

const char* NiShadeProperty::GetShaderType(UInt32 eType) {
	const char* result;
	switch (eType) {
	case NiShadeProperty::kType_Lighting:
		result = "Lighting";
		break;
	case NiShadeProperty::kType_DistantLOD:
		result = "Distant LOD";
		break;
	case NiShadeProperty::kType_GeometryDecal:
		result = "Geo Decal";
		break;
	case NiShadeProperty::kType_TallGrass:
		result = "Tall Grass";
		break;
	case NiShadeProperty::kType_SpeedTreeLeaf:
		result = "SpeedTree Leaf";
		break;
	case NiShadeProperty::kType_PPLighting:
		result = "Per Pixel Lighting";
		break;
	case NiShadeProperty::kType_Hair:
		result = "Hair";
		break;
	case NiShadeProperty::kType_SpeedTreeBranch:
		result = "SpeedTree Branch";
		break;
	case NiShadeProperty::kType_SpeedTreeBillboard:
		result = "SpeedTree Billboard";
		break;
	case NiShadeProperty::kType_Lighting30:
		result = "Lighting 3.0";
		break;
	case NiShadeProperty::kType_Sky:
		result = "Sky";
		break;
	case NiShadeProperty::kType_Water:
		result = "Water";
		break;
	case NiShadeProperty::kType_Bolt:
		result = "Bolt";
		break;
	case NiShadeProperty::kType_Particle:
		result = "Particle";
		break;
	case NiShadeProperty::kType_Precipitation:
		result = "Precipitation";
		break;
	case NiShadeProperty::kType_Tile:
		result = "Tile";
		break;
	case NiShadeProperty::kType_NoLighting:
		result = "No Lighting";
		break;
	case NiShadeProperty::kType_VolumetricFog:
		result = "Volumetric Fog";
		break;
	case NiShadeProperty::kType_BloodSplatter:
		result = "Blood Splatter";
		break;
	case NiShadeProperty::kType_DistantTree:
		result = "Distant Tree";
		break;
	default:
		result = "Unknown";
		break;
	}
	return result;
}

NiProperty* NiAVObject::GetProperty(UInt32 propID)
{
	if (!this)
		return nullptr;
	NiProperty* v4 = nullptr;
	if (propID >= 7)
	{
		return nullptr;
	}
	DListNode<NiPropertyPtr>* v3 = m_propertyList.Head();
	if (!v3)
	{
		return nullptr;
	}
	while (1)
	{
		NiProperty* v4 = v3->data->m_pObject;
		v3 = v3->next;
		if (v4)
		{
			if (v4->Type() == propID)
			{
				break;
			}
		}
		if (!v3)
		{
			return nullptr;
		}
	}
	return v4;
}