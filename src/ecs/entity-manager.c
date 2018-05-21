#include "ecs/entity-manager.h"

#include "lib/stretchy-buf.h"
#include "lib/bit-array.h"

#include "ecs/components/physics.h"

// behind the scenes use stretchy buffers
typedef struct {
	BitArray* mask;
	PhysicsComponent* physics;
} EntityManager;

void entity_manager_create(EntityManager* entity_manager)
{
	BitArray bit_array;
	bit_array_create(&bit_array);

	PhysicsComponent physics_component;
	physics_component_create(&physics_component);

	entity_manager->mask = bit_array;
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
