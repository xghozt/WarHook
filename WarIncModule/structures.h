// Generated using ReClass 2015

#pragma once
#pragma pack(1)

#include <stdint.h>
#include <Windows.h>
#include <string>
#include "stdafx.h"
#include "Vec3.h"

enum {
	SLOT_PRIMARY = 0,
	SLOT_SECONDARY,
	SLOT_THIRD,
	SLOT_FOUR,
	SLOT_FIVE,
	SLOT_SIX,
	SLOT_SEVEN,
	SLOT_MAX
};

enum {
	OBJECT_DEBUGTEXTURE = 0,
	OBJECT_BUILDING,
	OBJECT_LAKE,
	OBJECT_LIGHTHELPER,
	OBJECT_LIGHTMESH,
	OBJECT_TREE,
	OBJECT_WATERPLANE,
	OBJECT_PARTICLESYSTEM,
	OBJECT_BULLET,
	OBJECT_DROPPEDLOOTBOX,
	OBJECT_DROPPEDMEDKIT,
	OBJECT_DROPPEDMOTIONSENSOR,
	OBJECT_DROPPEDRESPAWNBEACON,
	OBJECT_DROPPEDWEAPON,
	OBJECT_GRENADE,
	OBJECT_MINE,
	OBJECT_AUTOTURRET,
	OBJECT_RIOTSHIELD,
	OBJECT_ROCKET,
	OBJECT_ROCKETGRENADE,
	OBJECT_LOCALCOLORCORRECTION,
	OBJECT_ROAD,
	OBJECT_TERRAIN,
	OBJECT_DEPOT,
	OBJECT_ENVMAPPROBE,
	OBJECT_AI_PLAYER,
	OBJECT_AMBIENTSOUND,
	OBJECT_MAPBORDER,
	OBJECT_BOMBPLACMENT,
	OBJECT_CONTROLPOINT,
	OBJECT_DAMAGEAREA,
	OBJECT_DROPPEDBOMB,
	OBJECT_PERMWEAPONDROP,
	OBJECT_SIEGEOBJECTIVE,
	OBJECT_SUPPLYCRATE,
	OBJECT_BLACKOPSCRATE,
	OBJECT_UAV,
	OBJECT_REVERBZONE,
	OBJECT_UIWEAPON_MODEL,
	OBJECT_DBF_MASTERCONTROL,
	OBJECT_AIRSTRIKE,
	OBJECT_VEHICLESPAWN,
	OBJECT_REVERBZONEBOX,
	OBJECT_GAMEOBJECT,
	OBJECT_MESHGAMEOBJECT,
	OBJECT_DUMMYOBJECT,
	OBJECT_SPRITE
};

typedef Vec3 Vector3;

typedef union
{
	float val_float;
	uint32_t val_int;
} conversion_type;

#define OFFSET_WEAPONCONFIGTABLE		0xD398E4 //CWeaponConfig*		(size:0x134)
#define OFFSET_AMMOCONFIGTABLE			0xD39860 //CAmmoConfig*			(size:0x38)
#define OFFSET_GEARCONFIGTABLE			0xD3A8EC //CGearConfig*			(size:0x50)
#define OFFSET_ITEMCONFIGTABLE			0xD3B8F0 //CItemsConfig*		(size:0x28)
#define OFFSET_ATTACHMENTCONFIGTABLE	0xD3A0E8 //CAttachmentConfig*	(size:0x6C)
#define OFFSET_PACKAGECONFIGTABLE		0xD3D8F4 //CPackageConfig*		(size:0x60)

class CSkeleton;
class CBipedData;
class CBone;
class CGameObject;
class CPlayer;
class R3DNetwork;
class CPlayerPhyisics;
class Weapon;
class CWeaponInfo;
class CWeaponConfig;
class CGearConfig;
class CItemConfig;
class CAttachmentConfig;
class R3DRenderer;
class CPackageConfig;
class CObjectManager;
class ObjectInfo_t;
class CDroppedWeapon;
class DroppedWeaponPhysUnk;
class CDeployedMine;
class SceneBox;
class N000020D7;
class N00002100;
class N0000397C;

class CSkeleton
{
public:
	char pad_0x0000[0x28]; //0x0000
	CBipedData* m_biped; //0x0028 
	char pad_0x002C[0x2050]; //0x002C
	uint32_t N0000251E; //0x207C 
	char pad_0x2080[0x8]; //0x2080
	uint32_t N00002521; //0x2088 
	uint32_t N00002522; //0x208C 
	char pad_0x2090[0x20]; //0x2090
	uint32_t N0000252E; //0x20B0 
	char pad_0x20B4[0x48]; //0x20B4

};//Size=0x20FC

class CBipedData
{
public:
	char pad_0x0000[0x18]; //0x0000
	uint32_t m_bonecount; //0x0018 
	CBone* m_bones; //0x001C 

};//Size=0x0020

class CBone
{
public:
	char* m_name; //0x0000 
	char pad_0x0004[0x88]; //0x0004
	D3DXMATRIX m_bonematrix; //0x008C 
	D3DXMATRIX N00000748; //0x00CC 

};//Size=0x010C

class CGameObject
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void SetFlag(int flag); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void SetVelocity(Vec3 velocity); //
	virtual Vec3 GetPosition(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual Vec3 GetVelocity(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Draw(); //
	virtual void Function22(); //
	virtual void Function23(); //
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27(); //
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //

	uint32_t m_objectmeta; //0x0004 
	char pad_0x0008[0x4]; //0x0008
	Vec3 m_spawnpos; //0x000C 
	Vec3 m_position; //0x0018 
	Vec3 N0000000A; //0x0024 
	float N0000000D; //0x0030 
	char pad_0x0034[0x8]; //0x0034
	float m_vectorunk_01; //0x003C 
	char pad_0x0040[0x4]; //0x0040
	float N00002144; //0x0044 
	char pad_0x0048[0xC]; //0x0048
	uint32_t m_pNextObj; //0x0054 
	char pad_0x0058[0x4]; //0x0058
	uint32_t N0000001A; //0x005C 
	Vec3 N0000001B; //0x0060 
	Vec3 N0000001E; //0x006C 
	Vec3 N00000021; //0x0078 
	Vec3 N00000024; //0x0084 
	char pad_0x0090[0x174]; //0x0090
	uint32_t m_id; //0x0204 
	char pad_0x0208[0x8]; //0x0208
	uint32_t m_objFlags; //0x0210 
	char pad_0x0214[0x4]; //0x0214
	char* m_class; //0x0218 
	char pad_0x021C[0x8]; //0x021C
	char* m_path; //0x0224 
	char pad_0x0228[0x74]; //0x0228
	float N00001748; //0x029C 
	char pad_0x02A0[0x5C]; //0x02A0

	ObjectInfo_t* GetObjectInfo()
	{
		return (ObjectInfo_t*)(this->m_objectmeta ^ 0x33F9FCE8);
	}
	CGameObject* GetNext()
	{
		return (CGameObject*)(this->m_pNextObj ^ 0xDACE913A);
	}
};//Size=0x02FC

class CPlayer : public CGameObject
{
public:
	char pad_0x02FC[0x108]; //0x02FC
	uint32_t m_bMarked; //0x0404 
	char pad_0x0408[0x20]; //0x0408
	char m_name_xor[64]; //0x0428 
	uint32_t m_name_length; //0x0468 
	char pad_0x046C[0xF0]; //0x046C
	unsigned char N000004A0; //0x055C 
	uint32_t m_team; //0x055D 
	char pad_0x0561[0x15F]; //0x0561
	CPlayerPhyisics* m_physics; //0x06C0 
	char pad_0x06C4[0x8]; //0x06C4
	CSkeleton* m_skeleton; //0x06CC 
	char pad_0x06D0[0xC]; //0x06D0
	Weapon* m_weaponSlots[7]; //0x06DC 
	uint32_t m_selectedWeapon; //0x06F8 
	uint32_t m_previousWeapon; //0x06FC 
	char pad_0x0700[0x7C]; //0x0700
	uint32_t m_spine1_id; //0x077C 
	uint32_t m_spine2_id; //0x0780 
	uint32_t m_neck_id; //0x0784 
	uint32_t m_left_upperarm_id; //0x0788 
	uint32_t m_right_upperarm_id; //0x078C 
	uint32_t m_head_id; //0x0790 
	uint32_t m_health; //0x0794 XOR'd
	uint32_t m_right_hand_id; //0x0798 
	uint32_t m_left_hand_id; //0x079C 
	char pad_0x07A0[0x10]; //0x07A0
	Vec3 m_velocity; //0x07B0 
	char pad_0x07BC[0x44]; //0x07BC
	uint32_t m_bIsDead; //0x0800 
	char pad_0x0804[0x20]; //0x0804
	float m_jumpVelocity; //0x0824 
	Vec3 N00000797; //0x0828 
	char pad_0x0834[0x28]; //0x0834
	float m_yaw; //0x085C 
	float m_pitch; //0x0860 
	char pad_0x0864[0x10]; //0x0864
	float N000007AC; //0x0874 
	float N000007AD; //0x0878 
	float N000007AE; //0x087C 
	char pad_0x0880[0x4]; //0x0880
	float N000007B0; //0x0884 
	float N000007B1; //0x0888 
	char pad_0x088C[0x4]; //0x088C
	float N00000803; //0x0890 
	char pad_0x0894[0x4]; //0x0894
	float N00000805; //0x0898 
	char pad_0x089C[0x3C]; //0x089C
	D3DXMATRIX m_bonetranslation; //0x08D8 
	char pad_0x0918[0x40]; //0x0918
	float N00000835; //0x0958 
	float N00000836; //0x095C 
	char pad_0x0960[0x4F0]; //0x0960

	float GetHealth()
	{
		conversion_type h;
		h.val_int = this->m_health ^ 0x1515CD3A;
		return h.val_float;
	}

	int GetTeam()
	{
		return this->m_team ^ 0x21C3DFCA;
	}

	std::string GetName()
	{
		int len = this->m_name_length;

		char temp[64];
		memset(temp, 0, sizeof(temp));
		memcpy(temp, this->m_name_xor, len);

		for (int i = 0; i < len; i++)
			temp[i] ^= i - 9;

		return temp;
	}
	bool GetBoneOrigin(int bone_id, Vec3 &pOut)
	{
		if (!this->m_skeleton || !this->m_skeleton->m_biped)
			return false;

		CBipedData* biped = this->m_skeleton->m_biped;

		if (bone_id < 0 || bone_id > biped->m_bonecount)
			return false;

		D3DXMATRIX pRotationMatrix, pBoneMatrixOut;
		D3DXMATRIX BoneMatrix = biped->m_bones[bone_id].m_bonematrix;

		D3DXMatrixRotationYawPitchRoll(&pRotationMatrix, 0.0, 1.5707963, 0.0);

		D3DXMatrixMultiply(&BoneMatrix, &BoneMatrix, &this->m_bonetranslation);
		D3DXMatrixMultiply(&pBoneMatrixOut, &pRotationMatrix, &BoneMatrix);

		pOut.x = pBoneMatrixOut._41;
		pOut.y = pBoneMatrixOut._42;
		pOut.z = pBoneMatrixOut._43;

		return true;
	}
};//Size=0x0E50

class R3DNetwork
{
public:
	virtual void Function0(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //

	char pad_0x0004[0xC]; //0x0004
	uint32_t m_ping; //0x0010 
	char pad_0x0014[0x4]; //0x0014
	uintptr_t m_playerlist[511]; //0x0018 XOR'd
	uint32_t m_player_count; //0x0814 
	uint32_t N00000742; //0x0818 
	uint32_t m_localplayer; //0x081C 
	char pad_0x0820[0x1800]; //0x0820

	static R3DNetwork* Get()
	{
		return (R3DNetwork*)(*(uintptr_t*)(WarHook::ImageBase + 0x74C69C) ^ 0xC7AA2FB5);
	}
	CPlayer* GetLocalPlayer()
	{
		return (CPlayer*)(this->m_localplayer ^ 0xA3BFBAB7);
	}

	CPlayer* GetPlayer(int index)
	{
		return (CPlayer*)((*(uintptr_t*)((uintptr_t)(&m_playerlist) + (index * 0x10))) ^ 0xFA643FB3);
	}
};//Size=0x2020

class CPlayerPhyisics
{
public:
	char pad_0x0000[0x234]; //0x0000

};//Size=0x0234

class Weapon
{
public:
	char pad_0x0000[0xC]; //0x0000
	CWeaponInfo* m_info; //0x000C 
	char pad_0x0010[0x1C]; //0x0010
	CPlayer* m_owner; //0x002C 
	char pad_0x0030[0x10]; //0x0030
	CGameObject* m_physobj; //0x0040 
	char pad_0x0044[0x2A8]; //0x0044
	uint32_t m_firemode; //0x02EC 
	char pad_0x02F0[0x18]; //0x02F0
	uint32_t m_shotconfig; //0x0308 
	char pad_0x030C[0x480]; //0x030C

	CWeaponConfig* GetWeaponConfig() const
	{
		return (CWeaponConfig*)(this->m_shotconfig ^ 0xFCD2829A);
	}
};//Size=0x078C

class CWeaponInfo
{
public:
	char pad_0x0000[0xC4]; //0x0000

};//Size=0x00C4

class CWeaponConfig
{
public:
	char pad_0x0000[0x14]; //0x0000
	uint32_t m_id; //0x0014 
	uint32_t m_category; //0x0018 
	char* m_muzzle_file; //0x001C 
	char* m_description; //0x0020 
	char pad_0x0024[0x4]; //0x0024
	char* m_fileName; //0x0028 
	char* m_icon; //0x002C 
	char* m_name; //0x0030 
	uint32_t m_levelrequired; //0x0034 0xCF5488FD
	char pad_0x0038[0x4]; //0x0038
	uint32_t m_upgrade; //0x003C 
	char* m_file; //0x0040 
	char pad_0x0044[0x4]; //0x0044
	char* m_animationPrefix; //0x0048 
	char* m_bullet; //0x004C 
	float m_mass; //0x0050 
	float m_speed; //0x0054 
	float m_damage; //0x0058 
	float m_decay; //0x005C 
	uint32_t m_area; //0x0060 
	uint32_t m_delay; //0x0064 
	uint32_t m_timeout; //0x0068 
	unsigned char m_immediate; //0x006C 
	uint32_t m_numShells; //0x006D 0xFA43D7CC 
	uint32_t m_clipsize; //0x0071 0xAF8CFA32 
	char pad_0x0075[0x3]; //0x0075
	float m_activeReloadTick; //0x0078 
	uint32_t m_reloadTime; //0x007C 0xAD56D3C1 
	uint32_t m_spread; //0x0080 0xF2454A6C 
	uint32_t m_rateOfFire; //0x0084 0x1327D2F9
	uint32_t m_recoil; //0x0088 0xA246DAFC
	uint32_t m_type; //0x008C assault=0, pistol, grenade, mine, rpg, smg, melee 
	uint32_t m_firemode; //0x0090 
	char* m_scopeType; //0x0094 
	float m_scopeZoom; //0x0098 
	char pad_0x009C[0x10]; //0x009C
	Vec3 m_muzzleOffset; //0x00AC 
	char pad_0x00B8[0xC]; //0x00B8
	uint32_t m_sound_shoot; //0x00C4 
	uint32_t m_sound_shoot_distant; //0x00C8 
	uint32_t m_sound_reload; //0x00CC 
	uint32_t m_sound_shoot_single; //0x00D0 
	uint32_t m_sound_shoot_auto; //0x00D4 
	uint32_t m_sound_shoot_single_player; //0x00D8 
	uint32_t m_sound_shoot_auto_player; //0x00DC 
	char pad_0x00E0[0x8]; //0x00E0
	uint32_t m_bIsFPS; //0x00E8 
	char pad_0x00EC[0x4C]; //0x00EC

	int GetClipSize()
	{
		return m_clipsize ^ 0xAF8CFA32;
	}
	int GetNumShells()
	{
		return m_numShells ^ 0xFA43D7CC;
	}
	float GetSpread()
	{
		conversion_type h;
		h.val_int = m_spread ^ 0xF2454A6C;
		return h.val_float;
	}
	float GetRecoil()
	{
		conversion_type h;
		h.val_int = m_recoil ^ 0xA246DAFC;
		return h.val_float;
	}
	float GetRateOfFire()
	{
		conversion_type h;
		h.val_int = m_rateOfFire ^ 0x1327D2F9;
		return h.val_float;
	}
	float GetReloadTime()
	{
		conversion_type h;
		h.val_int = m_reloadTime ^ 0xAD56D3C1;
		return h.val_float;
	}
	int GetLevel()
	{
		return m_levelrequired ^ 0xCF5488FD;
	}
	void SetSpread(float a)
	{
		m_spread = ((uint32_t)a ^ 0xF2454A6C);
	}
	void SetRecoil(float a)
	{
		m_recoil = ((uint32_t)a ^ 0xA246DAFC);
	}
	void SetRateOfFire(float a)
	{
		m_rateOfFire = ((uint32_t)a ^ 0xA246DAFC);
	}
	void SetReloadTime(float a)
	{
		m_reloadTime = ((uint32_t)a ^ 0xAD56D3C1);
	}
	void SetLevel(int level)
	{
		m_levelrequired = level ^ 0xCF5488FD;
	}
	void SetClipSize(int a) {
		m_clipsize = (a ^ 0xAF8CFA32);
	}
	void SetNumShells(int a) {
		m_numShells = (a ^ 0xFA43D7CC);
	}
	static uint32_t GetCount()
	{
		return *(uint32_t*)(WarHook::ImageBase + (0xD398E4 + 0x800));
	}
	static CWeaponConfig* Get(uint32_t i)
	{
		CWeaponConfig** packages = (CWeaponConfig**)(WarHook::ImageBase + 0xD398E4);

		if (i < 0 || i > CWeaponConfig::GetCount())
			return nullptr;

		return (CWeaponConfig*)packages[i];
	}
};//Size=0x0138

class CGearConfig
{
public:
	char pad_0x0000[0xC]; //0x0000
	uint32_t m_id; //0x000C 
	uint32_t m_category; //0x0010 
	char* m_description; //0x0014 
	char* m_icon; //0x0018 
	char* m_name; //0x001C 
	char pad_0x0020[0x8]; //0x0020
	char* m_file; //0x0028 
	char pad_0x002C[0x4]; //0x002C
	float m_weight; //0x0030 
	uint32_t m_levelrequired; //0x0034 0xCF358FA5 
	float m_damagePerc; //0x0038 
	float m_damageMax; //0x003C 
	float m_bulkiness; //0x0040 
	float m_inaccuracy; //0x0044 
	float m_stealth; //0x0048 
	uint32_t m_protectionLevel; //0x004C 
	char pad_0x0050[0x4]; //0x0050

	int GetLevel()
	{
		return m_levelrequired ^ 0xCF358FA5;
	}
	void SetLevel(int level)
	{
		m_levelrequired = level ^ 0xCF358FA5;
	}
	static uint32_t GetCount()
	{
		return *(uint32_t*)(WarHook::ImageBase + (0xD3A8EC + 0x800));
	}
	static CGearConfig* Get(uint32_t i)
	{
		CGearConfig** packages = (CGearConfig**)(WarHook::ImageBase + 0xD3A8EC);

		if (i < 0 || i > CGearConfig::GetCount())
			return nullptr;

		return (CGearConfig*)packages[i];
	}
};//Size=0x0054

class CItemConfig
{
public:
	char pad_0x0000[0x4]; //0x0000
	uint32_t m_id; //0x0004 
	uint32_t m_category; //0x0008 
	char* m_description; //0x000C 
	char* m_icon; //0x0010 
	char* m_name; //0x0014 
	char pad_0x0018[0x8]; //0x0018
	uint32_t m_levelrequired; //0x0020 0xFA5F4CA5 

	int GetLevel()
	{
		return m_levelrequired ^ 0xFA5F4CA5;
	}
	void SetLevel(int level)
	{
		m_levelrequired = level ^ 0xFA5F4CA5;
	}
	static uint32_t GetCount()
	{
		return *(uint32_t*)(WarHook::ImageBase + (0xD3B8F0 + 0x800));
	}
	static CItemConfig* Get(uint32_t i)
	{
		CItemConfig** packages = (CItemConfig**)(WarHook::ImageBase + 0xD3B8F0);

		if (i < 0 || i > CItemConfig::GetCount())
			return nullptr;

		return (CItemConfig*)packages[i];
	}
};//Size=0x0024

class CAttachmentConfig
{
public:
	char pad_0x0000[0xC]; //0x0000
	uint32_t m_type; //0x000C 
	uint32_t m_spec_id; //0x0010 
	char* m_muzzle_particle; //0x0014 
	char* m_description; //0x0018 
	char pad_0x001C[0x4]; //0x001C
	char* m_icon; //0x0020 
	char* m_name; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	char* m_file; //0x002C 
	char* m_scope_anim; //0x0030 
	uint32_t m_levelrequired; //0x0034 0xFA5F4CBC 
	float m_damage; //0x0038 
	float m_range; //0x003C 
	float m_firerate; //0x0040 
	float m_recoil; //0x0044 
	float m_spread; //0x0048 
	uint32_t m_clipsize; //0x004C 
	char pad_0x0050[0x8]; //0x0050
	float m_scopemag; //0x0058 
	uint32_t m_sound_shoot_single; //0x005C 
	uint32_t m_sound_shoot_auto; //0x0060 
	uint32_t m_sound_shoot_single_player; //0x0064 
	uint32_t m_sound_shoot_auto_player; //0x0068 
	char pad_0x006C[0x4]; //0x006C

	int GetLevel()
	{
		return m_levelrequired ^ 0xFA5F4CBC;
	}
	void SetLevel(int level)
	{
		m_levelrequired = level ^ 0xFA5F4CBC;
	}
	static uint32_t GetCount()
	{
		return *(uint32_t*)(WarHook::ImageBase + (0xD3A0E8 + 0x800));
	}
	static CAttachmentConfig* Get(uint32_t i)
	{
		CAttachmentConfig** packages = (CAttachmentConfig**)(WarHook::ImageBase + 0xD3A0E8);

		if (i < 0 || i > CAttachmentConfig::GetCount())
			return nullptr;

		return (CAttachmentConfig*)packages[i];
	}
};//Size=0x0070

class R3DRenderer
{
public:
	char pad_0x0000[0x18]; //0x0000
	uint32_t m_width; //0x0018 
	uint32_t m_height; //0x001C 
	char pad_0x0020[0x30]; //0x0020
	IDirect3DDevice9* m_pDevice; //0x0050 
	char pad_0x0054[0x13C]; //0x0054
	D3DXMATRIX m_viewMatrix; //0x0190 
	char pad_0x01D0[0x40]; //0x01D0
	D3DXMATRIX m_projectionMatrix; //0x0210 
	char pad_0x0250[0x80]; //0x0250

	static R3DRenderer* Get()
	{
		return *(R3DRenderer**)((WarHook::ImageBase + 0xD37EA4));
	}
};//Size=0x02D0

class CPackageConfig
{
public:
	char pad_0x0000[0x4]; //0x0000
	uint32_t m_id; //0x0004 
	uint32_t m_category; //0x0008 
	char* m_description; //0x000C 
	char* m_icon; //0x0010 
	char* m_name; //0x0014 
	char pad_0x0018[0x8]; //0x0018
	uint32_t m_levelrequired; //0x0020 0xFA5F4CA5
	char pad_0x0024[0x4]; //0x0024
	uint32_t m_gp; //0x0028 
	uint32_t m_sp; //0x002C 
	uint32_t m_item1_id; //0x0030 
	uint32_t m_item1_exp; //0x0034 
	uint32_t m_item2_id; //0x0038 
	uint32_t m_item2_exp; //0x003C 
	uint32_t m_item3_id; //0x0040 
	uint32_t m_item3_exp; //0x0044 
	uint32_t m_item4_id; //0x0048 
	uint32_t m_item4_exp; //0x004C 
	uint32_t m_item5_id; //0x0050 
	uint32_t m_item5_exp; //0x0054 
	uint32_t m_item6_id; //0x0058 
	uint32_t m_item6_exp; //0x005C 
	char pad_0x0060[0x4]; //0x0060

	int GetLevel()
	{
		return m_levelrequired ^ 0xFA5F4CA5;
	}
	void SetLevel(int level)
	{
		m_levelrequired = level ^ 0xFA5F4CA5;
	}
	static uint32_t GetCount()
	{
		return *(uint32_t*)GetModuleHandleA("WarInc.exe") + (0xD3D8F4 + 0x800);
	}
	static CPackageConfig* Get(uint32_t i)
	{
		CPackageConfig* packages = (CPackageConfig*)(WarHook::ImageBase + 0xD3D8F4);

		if (i < 0 || i > CPackageConfig::GetCount())
			return nullptr;

		return (CPackageConfig*)&packages[i];
	}

};//Size=0x0064

class CObjectManager
{
public:
	char pad_0x0000[0x8]; //0x0000
	uint32_t m_frame; //0x0008 
	SceneBox* m_pSceneBox; //0x000C 
	N000020D7* N0000159F; //0x0010 
	char pad_0x0014[0x1C]; //0x0014
	uint32_t m_firstObject; //0x0030 
	uint32_t m_numObjects; //0x0034 1FDC2DE9
	uint32_t m_lastObject; //0x0038 
	uint32_t m_numUnk01; //0x003C F4F1CD3F
	char pad_0x0040[0x4]; //0x0040
	uint32_t N000015AC; //0x0044 
	char pad_0x0048[0x78]; //0x0048

	static CObjectManager* Get()
	{
		return (CObjectManager*)(*(uintptr_t*)(WarHook::ImageBase + 0x74C6B8) ^ 0xFA8DF94A);
	}
	CGameObject* GetFirst()
	{
		return (CGameObject*)(this->m_firstObject ^ 0xF9FD85A);
	}

	CGameObject* GetLast()
	{
		return (CGameObject*)(this->m_lastObject ^ 0xF83A8CD2);
	}

	uint32_t GetObjectCount()
	{
		return (this->m_numObjects ^ 0x1FDC2DE9);
	}
};//Size=0x00C0

class ObjectInfo_t
{
public:
	uint32_t m_id; //0x0000 
	char* m_class; //0x0004 
	char pad_0x0008[0x1C]; //0x0008

	std::string GetClass()
	{
		return std::string(m_class);
	}
};//Size=0x0024

class CDroppedWeapon : public CGameObject
{
public:
	uint32_t m_weapon_id; //0x02FC 
	char pad_0x0300[0x28]; //0x0300
	uint32_t m_flags; //0x0328 
	DroppedWeaponPhysUnk* m_physunk; //0x032C 
	char pad_0x0330[0x4]; //0x0330

	std::string GetName()
	{
		int packageCount = CWeaponConfig::GetCount();

		for (int pkg_id = 0; pkg_id < packageCount; pkg_id++)
		{
			CWeaponConfig* pWeaponInfo = CWeaponConfig::Get(pkg_id);

			if (!pWeaponInfo)
				continue;

			if (pWeaponInfo->m_id == this->m_weapon_id)
				return pWeaponInfo->m_name;
		}

		return "None";
	}
};//Size=0x0334

class DroppedWeaponPhysUnk
{
public:
	char pad_0x0000[0x1014]; //0x0000

};//Size=0x1014

class CDeployedMine : public CGameObject
{
public:
	char* m_bullet; //0x02FC 
	CWeaponConfig* m_info; //0x0300 
	char pad_0x0304[0x58]; //0x0304

};//Size=0x035C

class SceneBox
{
public:
	char pad_0x0000[0x84]; //0x0000

};//Size=0x0084

class N000020D7
{
public:
	char pad_0x0000[0x84]; //0x0000

};//Size=0x0084

class N00002100
{
public:
	char pad_0x0000[0x34]; //0x0000
	Vec3 GetPosition(); //0x0034 
	char pad_0x0038[0xC]; //0x0038

};//Size=0x0044

class N0000397C
{
public:
	char pad_0x0000[0x84]; //0x0000

};//Size=0x0084


