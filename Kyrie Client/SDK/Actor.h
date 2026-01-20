#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Utils/Utils.h"

#include "../Memory/Memory.h"
#include "../Utils/Math.h"
#include "Components/RenderPositionComponent.h"
#include "Level.h"
#include "GameMode.h"
#include "EntityContext/EntityContext.h"
#include "Components/StateVectorComponent.h"

class EntityRotation {
public:
	Vec2<float> rotPrev;
	Vec2<float> rot;
};

enum ActorFlags;
class Mob;
class Player;
class HashedString;
class ActorDamageSource;
class Packet;
enum InputMode;
enum NewInteractionModel;
enum UIProfanityContext;
enum MaterialType;
class IConstBlockSource;
class ActorDamageCause;
class ActorUniqueID;
class Block;
class ActorEvent;
class ItemStack;
enum ArmorSlot;
enum EquipmentSlot;
class CompoundTag;
class DataLoadHelper;
class ActorLink;
class ChangeDimensionPacket;
class Attribute;
class MobEffectInstance;
enum ItemUseMethod;
class ItemStackBase;
class ActorInteraction;
class Options;
class EquipmentTableDefinition;
enum HandSlot;
class RenderParams;
class AnimationComponent;
enum AnimationComponentGroupType;

class Actor {
public:
	BUILD_ACCESS(this, Level*, level, 0X1D8);
	BUILD_ACCESS(this, EntityRotation*, rotation, 0x2A0);
	BUILD_ACCESS(this, GameMode*, gameMode, 0xA88
	);
public:
	EntityContext* getEntityContext()
	{
		uintptr_t address = reinterpret_cast<uintptr_t>(this);
		return reinterpret_cast<EntityContext*>((uintptr_t)this + 0x8);
	}

	RenderPositionComponent* getRenderPositionComponent() {
		return getEntityContext()->tryGetComponent<RenderPositionComponent>();
	}

	StateVectorComponent* getStateVectorComponent() {
		return getEntityContext()->tryGetComponent<StateVectorComponent>();
	}
public:
	virtual __int64 getStatusFlag(ActorFlags);
	virtual void setStatusFlag(ActorFlags, bool);
};