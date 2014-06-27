/*
 * Copyright 2011-2012 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Based on:
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/
// Code: Cyril Meynier
//
// Copyright (c) 1999-2000 ARKANE Studios SA. All rights reserved

#ifndef ARX_GAME_PLAYER_H
#define ARX_GAME_PLAYER_H

#include <string>
#include <vector>

#include "game/Entity.h"
#include "game/Spells.h"
#include "game/GameTypes.h"
#include "math/Types.h"
#include "platform/Flags.h"

struct EERIE_3DOBJ;
class TextureContainer;

#define MAX_EQUIPED 12

struct ARX_NECKLACE {
	EERIE_3DOBJ * lacet;
	EERIE_3DOBJ * runes[RUNE_COUNT];
	TextureContainer * pTexTab[RUNE_COUNT];
};

struct ARX_INTERFACE_MEMORIZE_SPELL {
	bool bSpell;
	unsigned long lTimeCreation;
	unsigned long lDuration;
	Rune iSpellSymbols[6];
	float fPosX;
	float fPosY;
};

enum PlayerMovementFlag {
	PLAYER_MOVE_WALK_FORWARD  = (1<<0),
	PLAYER_MOVE_WALK_BACKWARD = (1<<1),
	PLAYER_MOVE_STRAFE_LEFT   = (1<<2),
	PLAYER_MOVE_STRAFE_RIGHT  = (1<<3),
	PLAYER_MOVE_JUMP          = (1<<4),
	PLAYER_MOVE_STEALTH       = (1<<5),
	PLAYER_ROTATE             = (1<<6),
	PLAYER_CROUCH             = (1<<7),
	PLAYER_LEAN_LEFT          = (1<<8),
	PLAYER_LEAN_RIGHT         = (1<<9)
};
DECLARE_FLAGS(PlayerMovementFlag, PlayerMovement)
DECLARE_FLAGS_OPERATORS(PlayerMovement)

enum PlayerFlag {
	PLAYERFLAGS_NO_MANA_DRAIN   = (1<<0),
	PLAYERFLAGS_INVULNERABILITY = (1<<1)
};
DECLARE_FLAGS(PlayerFlag, PlayerFlags)
DECLARE_FLAGS_OPERATORS(PlayerFlags)

enum RuneFlag {
	FLAG_AAM         = (1<<(RUNE_AAM)),
	FLAG_CETRIUS     = (1<<(RUNE_CETRIUS)),
	FLAG_COMUNICATUM = (1<<(RUNE_COMUNICATUM)),
	FLAG_COSUM       = (1<<(RUNE_COSUM)),
	FLAG_FOLGORA     = (1<<(RUNE_FOLGORA)),
	FLAG_FRIDD       = (1<<(RUNE_FRIDD)),
	FLAG_KAOM        = (1<<(RUNE_KAOM)),
	FLAG_MEGA        = (1<<(RUNE_MEGA)),
	FLAG_MORTE       = (1<<(RUNE_MORTE)),
	FLAG_MOVIS       = (1<<(RUNE_MOVIS)),
	FLAG_NHI         = (1<<(RUNE_NHI)),
	FLAG_RHAA        = (1<<(RUNE_RHAA)),
	FLAG_SPACIUM     = (1<<(RUNE_SPACIUM)),
	FLAG_STREGUM     = (1<<(RUNE_STREGUM)),
	FLAG_TAAR        = (1<<(RUNE_TAAR)),
	FLAG_TEMPUS      = (1<<(RUNE_TEMPUS)),
	FLAG_TERA        = (1<<(RUNE_TERA)),
	FLAG_VISTA       = (1<<(RUNE_VISTA)),
	FLAG_VITAE       = (1<<(RUNE_VITAE)),
	FLAG_YOK         = (1<<(RUNE_YOK))
};
DECLARE_FLAGS(RuneFlag, RuneFlags)
DECLARE_FLAGS_OPERATORS(RuneFlags)

enum JumpPhase {
	NotJumping = 0,
	JumpStart = 1,
	JumpAscending = 2,
	JumpDescending = 4,
	JumpEnd = 5
};

struct ARXCHARACTER {
	
	Vec3f pos;
	Anglef angle;
	IO_PHYSICS physics;
	
	ANIM_USE bookAnimation[MAX_ANIM_LAYERS];

	// Jump Sub-data
	unsigned long jumpstarttime;
	float jumplastposition;
	JumpPhase jumpphase;
	
	bool climbing;
	bool levitate;
	
	Anglef desiredangle;
	Vec3f size;
	ARX_PATH * inzone;
	
	bool falling;
	short doingmagic;
	short Interface;
	
	PlayerMovement Current_Movement;
	PlayerMovement Last_Movement;
	bool onfirmground;
	
	Entity * rightIO;
	Entity * leftIO;
	Entity * equipsecondaryIO;
	Entity * equipshieldIO;
	Entity * torch;
	
	EntityHandle equiped[MAX_EQUIPED]; 
	
	struct PlayerAttribute {
		float strength;
		float dexterity;
		float constitution;
		float mind;
		
		PlayerAttribute()
			: strength(0)
			, dexterity(0)
			, constitution(0)
			, mind(0)
		{}
		
		void add(const PlayerAttribute & other) {
			strength += other.strength;
			dexterity += other.dexterity;
			constitution += other.constitution;
			mind += other.mind;
		}
	};
	
	struct PlayerSkill {
		float stealth;
		float mecanism;
		float intuition;
		
		float etheralLink;
		float objectKnowledge;
		float casting;
		
		float projectile;
		float closeCombat;
		float defense;
		
		PlayerSkill()
			: stealth(0)
			, mecanism(0)
			, intuition(0)
			, etheralLink(0)
			, objectKnowledge(0)
			, casting(0)
			, projectile(0)
			, closeCombat(0)
			, defense(0)
		{}
		
		void add(const PlayerSkill & other) {
			stealth += other.stealth;
			mecanism += other.mecanism;
			intuition += other.intuition;
			
			etheralLink += other.etheralLink;
			objectKnowledge += other.objectKnowledge;
			casting += other.casting;
			
			projectile += other.projectile;
			closeCombat += other.closeCombat;
			defense += other.defense;
		}
	};
	
	struct PlayerMisc {
		float armorClass;
		float resistMagic;
		float resistPoison;
		float criticalHit;
		float damages;
		
		PlayerMisc()
			: armorClass(0)
			, resistMagic(0)
			, resistPoison(0)
			, criticalHit(0)
			, damages(0)
		{}
		
		void add(const PlayerMisc & other) {
			armorClass += other.armorClass;
			resistMagic += other.resistMagic;
			resistPoison += other.resistPoison;
			criticalHit += other.criticalHit;
			damages += other.damages;
		}
	};
	
	// Modifier Values (Items, curses, etc...)
	PlayerAttribute m_attributeMod;
	PlayerSkill m_skillMod;
	PlayerMisc m_miscMod;
	
	// Full Frame values (including items)
	PlayerAttribute m_attributeFull;
	PlayerSkill m_skillFull;
	PlayerMisc m_miscFull;
	
	long Full_AimTime;
	float Full_life;
	float Full_maxlife;
	float Full_maxmana;
	
	// true (naked) Player Values
	PlayerAttribute m_attribute;
	PlayerSkill m_skill;
	PlayerMisc m_misc;
	
	long AimTime;
	
	ResourcePool lifePool;
	ResourcePool manaPool;
	
	// Player Old Values
	PlayerSkill m_skillOld;
	
	unsigned char Attribute_Redistribute;
	unsigned char Skill_Redistribute;
	
	unsigned char level;
	
	long xp;
	char skin;
	
	RuneFlags rune_flags;
	TextureContainer * heads[5];
	float poison;
	float hunger;
	PlayerFlags playerflags;
	long gold;
	short bag;
	ARX_INTERFACE_MEMORIZE_SPELL SpellToMemorize;

	float TRAP_DETECT;
	float TRAP_SECRET;
	
	static float baseRadius() { return 52.f; }
	static float baseHeight() { return -170.f; }
	static float crouchHeight() { return -120.f; }
	static float levitateHeight() { return -220.f; }
	
	static Vec3f baseOffset() { return Vec3f(0.f, baseHeight(), 0.f); }
	
	Vec3f basePosition() {
		return Vec3f(pos.x, pos.y - baseHeight(), pos.z);
	}
	
	Cylinder baseCylinder() {
		Cylinder c;
		c.height = baseHeight();
		c.radius = baseRadius();
		c.origin = basePosition();
		return c;
	}
	
};

struct KEYRING_SLOT {
	char slot[64];
};


// Quests Management (QuestLogBook)

struct STRUCT_QUEST {
	std::string ident;
};

extern ARXCHARACTER player;
extern ARX_NECKLACE necklace;
extern EERIE_3DOBJ * hero;
extern ANIM_HANDLE * herowaitbook;
extern ANIM_HANDLE * herowait_2h;
extern std::vector<STRUCT_QUEST> PlayerQuest;
extern std::vector<KEYRING_SLOT> Keyring;

extern bool BLOCK_PLAYER_CONTROLS;
extern bool USE_PLAYERCOLLISIONS;
extern bool WILLRETURNTOCOMBATMODE;

void ARX_PLAYER_MakeSpHero();
void ARX_PLAYER_LoadHeroAnimsAndMesh();
void ARX_PLAYER_InitPlayer();
void ARX_PLAYER_BecomesDead();
void ARX_PLAYER_ClickedOnTorch(Entity * io);
void ARX_PLAYER_RectifyPosition();
void ARX_PLAYER_Frame_Update();
void ARX_PLAYER_Manage_Movement();
void ARX_PLAYER_Manage_Death();
void ARX_PLAYER_Quest_Add(const std::string & quest, bool _bLoad = false);
void ARX_PLAYER_Quest_Init();
void ARX_PLAYER_FrontPos(Vec3f * pos);
void ARX_PLAYER_ComputePlayerFullStats();
void ARX_PLAYER_MakeFreshHero();
void ARX_PLAYER_QuickGeneration();
void ARX_PLAYER_MakeAverageHero();
void ARX_PLAYER_Modify_XP(long val);
void ARX_PLAYER_FrameCheck(float Framedelay);
void ARX_PLAYER_Poison(float val);
void ARX_PLAYER_Manage_Visual();
void ARX_PLAYER_Remove_Invisibility();
void ARX_Player_Rune_Add(RuneFlag rune);
void ARX_Player_Rune_Remove(RuneFlag rune);
void ARX_PLAYER_AddGold(long value);
void ARX_PLAYER_AddGold(Entity * gold);
void ARX_PLAYER_AddBag();
bool ARX_PLAYER_CanStealItem(Entity * item);

void ARX_KEYRING_Init();
void ARX_KEYRING_Add(const std::string & key);
void ARX_KEYRING_Combine(Entity * io);

void ARX_PLAYER_Reset_Fall();
void ARX_PLAYER_KillTorch();
void ARX_PLAYER_PutPlayerInNormalStance(long val);
void ARX_PLAYER_Start_New_Quest();
void ARX_PLAYER_Rune_Add_All();
 
void ARX_PLAYER_Restore_Skin();
float GetPlayerStealth();

void ARX_GAME_Reset(long type = 0);
long GetXPforLevel(long level);
bool ARX_PLAYER_IsInFightMode();
void ARX_PLAYER_Invulnerability(long flag);

void ForcePlayerLookAtIO(Entity * io);

#endif // ARX_GAME_PLAYER_H
