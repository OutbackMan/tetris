#ifndef __ecs_components_physics_component_h__
#define __ecs_components_physics_component_h__

typedef struct {
	float vx;
	float vy;
	float ax;
	float ay;
	float collision_radius;
	float friction;
	bool is_stable;
	int bounce_before_death;
	bool is_dead;
	bool is_on_ground; // to introduce drag
} G_ComponentPhysics;

void ecs_component_create_physics(
	G_ComponentPhysics* physics_component,
	float x_velocity,
	float y_velocity,
	float x_acceleration,
	float y_acceleration,
	float friction,
	int bounce_count_till_death,
	bool is_stable,
	bool is_dead
);

void ecs_component_create_physics(
	G_ComponentPhysics* physics_component,
	float x_velocity,
	float y_velocity,
	float x_acceleration,
	float y_acceleration,
	float friction,
	int bounce_count_till_death,
	bool is_stable,
	bool is_dead
)
{
	physics_component->x_velocity = x_velocity;	
	physics_component->x_acceleration = x_acceleration;	
	physics_component->y_velocity = y_velocity;	
	physics_component->y_acceleration = y_acceleration;	
	physics_component->friction = friction;	
	physics_component->bounce_count_till_death = bounce_count_till_death;	
	physics_component->is_stable = is_stable;	
	physics_component->is_dead = is_dead;	
	
}


#endif
