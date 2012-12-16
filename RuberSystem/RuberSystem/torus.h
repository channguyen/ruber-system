#ifndef TORUS_H
#define TORUS_H

#include <vector>
#include <string>
#include <algorithm>

#include "object3d.h"
#include "opengl_macro.h"
#include "colors.h"
#include "movable_interface.h"
#include "collidable_interface.h"
#include "math3d.h"
#include "vector3.h"

using namespace std;
using namespace colors;
using namespace util;

class torus:	
	public object3d, 
	public movable_interface,
	public drawable_interface {

public:
	static const int OFFSET = 1000;

public:
	torus(const string &name = "torus", float radius = 1.0f, float degree = 1.0f, float p[3] = NULL, const color_name& c = green): 
		object3d(name, radius, false, vector3<float>(p[0], p[1], p[2]), vector3<float>(0, 1, 0)),  
		radius(radius), 
		degree(degree),  
		color(c) {
		for (int i = 0; i < 3; ++i) {
			position[i] = p[i];
		}
		bounding_sphere_radius = radius + 10;
	}

	~torus() {
	}

	void draw_bounding_sphere() {
		double center = OFFSET + radius;
		double diamater = (OFFSET + radius)*2;
		int no_sphere = (diamater/radius) * 4;	
		double angle = 0.0;
		for (int i = 0; i < no_sphere; ++i) {
			gl_push_matrix(); {
				gl_color_3fv(get_color(colors::white));
				gl_translate_f(center*cos(angle), center*sin(angle), 0);
				glut_wire_sphere(bounding_sphere_radius, 40, 20);
			} gl_pop_matrix();
			angle += (2 * util::constants::PI) / no_sphere;
		}
	}

	bool collide_with(const object3d *other) const {
		double outer_radius = OFFSET + radius;
		double diamater = (OFFSET + radius)*2;
		int no_sphere = (diamater/radius) * 4;	
		double angle = 0.0;
		vector3<float> center;
		for (int i = 0; i < no_sphere; ++i) {
			center = get_position() + vector3<float>(outer_radius*cos(angle), outer_radius*sin(angle), 0.0f);
			if (math3d::distance(center, other->get_position()) < (bounding_sphere_radius + other->get_bounding_sphere_radius())) {
				return true;
			}
			angle += (2 * util::constants::PI) / no_sphere;
		}
		return false;
	}

	void draw() {
		gl_push_matrix(); {
			// update
			gl_mult_matrix_f(OM);
			// actual rendering	
			draw_itself();
			// draw bounding sphere
			if (bounding_sphere) {
				draw_bounding_sphere();
			}
			// draw axis or bounding sphere
			object3d::draw();
		} gl_pop_matrix();
	}

	void draw_itself() {
		gl_color_3fv(get_color(color));
		if (is_solid()) {
			glut_solid_sphere(100, 40, 20);
			glut_solid_torus(radius, radius + OFFSET, 40, 20);
		} else {
			glut_wire_sphere(100, 40, 20);
			glut_wire_torus(radius, radius + OFFSET, 40, 20);
		}
	}

	void update() {
		object3d::update_internal();
	}

private:
	float radius;
	float degree;
	color_name color;
};

#endif