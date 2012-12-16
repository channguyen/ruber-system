#ifndef MOON_H
#define MOON_H

#include "object3d.h"
#include "opengl_macro.h"
#include "colors.h"
#include "movable_interface.h"
#include "drawable_interface.h"
#include "missile.h"
#include "spaceship.h"
#include <iostream>

using namespace colors;

class moon:		
	public object3d,
	public movable_interface,
	public drawable_interface {

public:
	virtual ~moon() {
	}

	moon(const string &name = "moon", float radius = 1.0f, float degree = 1.0f, float p[3] = NULL, const color_name &c = red)
		:object3d(name, radius, false, vector3<float>(p[0], p[1], p[2]), vector3<float>(0, 1, 0)), 
		radius(radius), degree(degree), color(c), angle(0.0f) {
		collidable = true;
		rotate_about = true;
		bounding_sphere_radius = radius + 10;
	}

public:
	virtual void draw() {
		gl_push_matrix(); {
			// update itself
			gl_mult_matrix_f(OM);
			// actual rendering
			draw_itself();
			// draw axes or bounding sphere
			object3d::draw();
		} gl_pop_matrix();
	}

	void draw_itself() {
		gl_color_3fv(get_color(color));
		if (is_solid()) {
			glut_solid_sphere(radius, 40, 20);
		} else {
			glut_wire_sphere(radius, 40, 20);
		}
	}

	virtual void update() {
		yaw += degree;
		if (yaw >= 360.f) {
			yaw = 0.0f;
		}
		object3d::update_internal();
	}

	void set_parent_position(const vector3<float> &pos) {
		parent_position = pos;
	}

	vector3<float> get_parent_position() {
		return parent_position;
	}

	bool collide_with(const object3d *other) const {
		if (util::math3d::distance(parent_position + get_position(), other->get_position()) <= (get_bounding_sphere_radius() + other->get_bounding_sphere_radius())) {
			return true;	
		}
		return false;
	}

protected:
	float radius;
	float angle;
	float degree;
	color_name color;
	vector3<float> parent_position;
};

#endif