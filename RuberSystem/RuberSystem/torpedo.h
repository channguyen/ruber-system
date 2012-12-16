#ifndef TORPEDO_H
#define TORPEDO_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <random>

#include "opengl_macro.h"
#include "drawable_interface.h"
#include "movable_interface.h"
#include "object3d.h"
#include "test_vector3.h"
#include "colors.h"

using namespace std;
using namespace util;
using namespace colors;

struct torpedo_type  {
	enum type  {
		AGM_84_HARPOON = 0,
		AIM_4_FALCON = 1
	};

	torpedo_type(type t) : t(t) {
	}

	torpedo_type() {
		t = AIM_4_FALCON;
	}

	operator type() const { 
		return t;
	}

	type t;
private:
	// prevent automatic conversion for any other 
	// built-in types such as bool, int, etc
	template<typename T>
	operator T () const;
};

class torpedo:
	public object3d,
	public drawable_interface, 
	public movable_interface {

public:
	torpedo(): 
		counter(0),
		radius(50),
		alive(false) {
		
		collidable = true;
		explosion_radius = 1000;
		bounding_sphere_radius = radius + 10;
		lives = 1000;
	}

	torpedo(const string& name, const vector3<float> &position, const vector3<float> &target, int lives):
		object3d(name, 0, true, position, vector3<float>(0, 1, 0)) {
		initialize(10, target, colors::red, torpedo_type::AGM_84_HARPOON, lives);
	}

	torpedo(const string &name, const vector3<float> &position, const vector3<float> &target, const color_name &color, const torpedo_type &type, float speed, int lives):
		object3d(name, 0, true, position, vector3<float>(0, 1, 0)) {
		initialize(speed, target, color, type, lives);
	}

	void initialize(float speed, const vector3<float> &target, const color_name &color, const torpedo_type &type, int lives) {
		radius = 50;
		alive = true;
		counter = 0;
		explosion_radius = 1000;
		collidable = true;
		gravity_on = false;
	
		this->speed  = speed;
		this->target = target;
		this->color = color;
		this->mtype = type;
		this->lives = lives;
	}

	void draw_explosion() {
		if (explosion_radius > 0) {
			gl_color_3fv(get_color(colors::green));
			glut_solid_sphere(explosion_radius, 40, 20);
			explosion_radius -= 50;
		}
	}

	void draw() {
		gl_push_matrix(); {
			// update
			gl_mult_matrix_f(OM);
			// actual rendering
			if (alive) {
				// draw_vector(get_forward(), colors::cyan);
				// draw_vector((target - position).normal(), colors::yellow);
				draw_itself(mtype);
				draw_vector(target - get_position(), colors::yellow);
			} else {
				draw_explosion();
			}
			// draw axes or bounding sphere
			object3d::draw();
		} gl_pop_matrix();
	}

	void draw_itself(const torpedo_type &type) {
		gl_color_3fv(get_color(color));
		switch (type) {
			case torpedo_type::AGM_84_HARPOON:
				glut_solid_sphere(50, 40, 20);
				break;

			case torpedo_type::AIM_4_FALCON:
				glut_solid_sphere(50, 40, 20);
				break;
		}
	}

	void move() {
		vector3<float> to_target = target - get_position();
		to_target.normalize();
		position += (get_forward() * speed);
	}

	void update() {
		counter++;
		if (alive) {
			if (counter <= lives) {
				turn_toward();
			} else {
				alive = false;
			}
		}
	}

	double get_rotation_angle(vector3<float> u, vector3<float> v) const {
		u.normalize();
		v.normalize();
		double cosine_theta = u.dot(v);
		// domain of arccosine is [-1, 1]
		if (cosine_theta > 1) {
			cosine_theta = 1;
		}
		if (cosine_theta < -1) {
			cosine_theta = -1;
		}
		return math3d::to_degree(acos(cosine_theta));
	}

	vector3<float> get_rotation_axis(vector3<float> u, vector3<float> v) const {
		u.normalize();
		v.normalize();
		// fix linear case
		if (u == v || u == -v) {
			v[0] += 0.05;
			v[1] += 0.0;
			v[2] += 0.05;
			v.normalize();
		}
		return u.cross(v).normal();
	}

	void turn_toward() {
		vector3<float> to_target = (target - position);
		gl_matrix_mode(GL_MODELVIEW);
		gl_push_matrix(); {
			gl_load_identity();
			gl_translate_f(position.get_x(), position.get_y(), position.get_z());
			gl_rotate_f(1.0f, 0, 1, 0);
			gl_get_float_v(GL_MODELVIEW_MATRIX, OM);
		} gl_pop_matrix();
		if (gravity_on) {
			if (gravity_vector.length() != 0) {
				position += (to_target.normal() + gravity_vector.normal()) * speed;
			}
		} else {
			position += (to_target.normal() * speed);
		}
	}

	void turn_to_face() {
		vector3<float> to_target = (target - position);
		vector3<float> axis = get_rotation_axis(to_target, get_forward());
		double angle = get_rotation_angle(get_forward(), to_target);
		if (axis.get_x() + axis.get_y() + axis.get_z() >= 0) {
			angle = 180 - angle;
		} else {
			angle = -angle;
		}
		gl_matrix_mode(GL_MODELVIEW);
			gl_push_matrix(); {
			gl_load_identity();
			gl_translate_f(position.get_x(), position.get_y(), position.get_z());
			gl_rotate_f(angle, axis.get_x(), axis.get_y(), axis.get_z());
			gl_get_float_v(GL_MODELVIEW_MATRIX, OM);
		} gl_pop_matrix();
		move();
	}

	void draw_vector(vector3<float> v, color_name c) {
		gl_color_3fv(get_color(c));
		v *= 9999999;
		gl_begin(GL_LINES); {
			gl_vertex_3f(0.0f, 0.0f, 0.0f);
			gl_vertex_3f(v[0], v[1], v[2]);
		} gl_end();
	}

	void destroy() {
		alive = false;
		counter = 0;
	}

	void reborn() {
		alive = true;
		counter = 0;
	}

	void apply_gravity(const vector3<float> &gravity) {
		gravity_on = true;
		gravity_vector = gravity;
	}

	void set_gravity(bool mode) {
		gravity_on = mode;
	}

	void track(const vector3<float> &t) {
		target = t;
	}

public:
	bool is_alive() const {
		return alive;
	}

	int get_current_frame() const {
		return counter;
	}

	int get_lives() const {
		return lives;
	}

	void set_lives(int l) {
		lives = l;
	}

	void set_new_position(const vector3<float> &p) {
		set_position(p);
	}

	void set_new_target(const vector3<float> t) {
		target = t;
	}

private:
	bool gravity_on;
	vector3<float> gravity_vector;
	float radius;
	bool alive;
	int lives;
	int speed;
	int counter;
	int explosion_radius;
	color_name color;
	torpedo_type mtype;
	vector3<float> target;
};

#endif
