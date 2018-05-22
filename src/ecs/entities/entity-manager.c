#include "ecs/entity-manager.h"

#include "lib/data-structures/stretchy-buf.h"
#include "lib/data-structures/bit-array.h"

#include "ecs/components/components-list.h"

typedef struct {
	BitArray** mask;
	PhysicsComponent* physics;
} EntityManager;

void entity_manager_create(EntityManager* entity_manager, size_t max_component_types)
{
	BitArray bit_array = bit_array_create(max_component_types);
	STRETCHY_BUF_PUSH(entity_manager->mask, bit_array);

	PhysicsComponent physics_component;
	physics_component_create(&physics_component);

	// ...
}	

void entity_manager_destroy(EntityManager* entity_manager)
{
	// mask
	STRETCHY_BUF_DESTROY(entity_manager->mask);

	// components
	free(entity_manager->physics);

	// manager
	free(entity_manager);
}	
