extends CharacterBody2D

class_name Base_Agent

# constsant to be used in case of checking the current state
const idle = 'i'
const enroute = 'e'

var speed := 50
var state := idle # i for idle, e for enroute
var target_position := Vector2i()

# basic function for movement
func move_to(target: Vector2i):
	target_position = target
	state = enroute
	
# basic means of sprite movement towards target location
func _physics_process(delta: float) -> void:
	if state == enroute:
		var direction = (target_position - snapped(global_position, 1))
		velocity = direction * speed # uses a built in velocity variable
		move_and_slide() # built in movement method
	
	# once the agent has reached within a certain range of the target posi
	if global_position.distance_to(target_position) < 4:
		state = idle
		velocity = Vector2i.ZERO
	pass
