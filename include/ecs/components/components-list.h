#ifndef __ecs_components_components_list_h__
#define __ecs_components_components_list_h__

#include "ecs/components/sprite.h"
#include "ecs/components/physics.h"

enum {
	COMPONENT_NONE,
	COMPONENT_SPRITE, // merge
	COMPONENT_SPRITE_SHEET, // merge
	COMPONENT__NUM
};

#endif
