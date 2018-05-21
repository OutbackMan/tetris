#include "ecs/components.h"

// entity-manager.c
#include "ecs/components/component.h"

// entities
	// single
	#include "ecs/components/component.h"
	create_entity_component()
	// compositions
	#include "ecs/entities/single/component.h"
	create_entity_component1()
	create_entity_component2()

// components
typedef struct {} Component;
create_component()

// systems
	// single

	// compositions

void g_component_create_render(EntityManager* entity_manager)
{
	entity_manager		
}

void g_entity_manager_create_index(EntityManager* entity_manager)
{
	for (int i = 0; i < ENTITY_CAPACITY; ++i) {
		if (entity_manager.component_mask[i] == COMPONENT_NONE) {
			return i;	
		}		
	}	

	// increase entity capacity
}

void g_entity_manager__create_entity_render(EntityManager* entity_manager, int entity_index)
{
	RenderComponent render_component;
	g_component_create_render(&render_component, "graphic.bmp");
	entity_manager.component_render[entity_index] = render_component;
}

void g_entity_manager_create_entity_object(EntityManager* entity_manager)
{
	int entity_index = g_entity_manager__create_index(entity_manager);	
		
	g_entity_manager_create_entity_render(entity_manager, entity_index);	
	g_entity_manager_create_entity_physics(entity_manager, entity_index);	

}
