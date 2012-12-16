#ifndef SUN_H
#define SUN_H

#include "object3d.h"
#include "drawable_interface.h"
#include "opengl_macro.h"
#include "colors.h"
#include "image.h"
#include "torpedo.h"
#include "spaceship.h"

using namespace std;

class sun :
	public object3d,
	public drawable_interface {

public:
	sun() 
		:MAX_LENGTH(200.0), MAX_FORCE(18.0) {
	}

	sun(const string &name, float radius, unsigned tid):
		object3d(name), 
		texture_on(true),
		radius(radius),
		MAX_LENGTH(200.0),
		MAX_FORCE(18.0) {

		angle = 0.0f;
		bounding_sphere = false;
		collidable = true;
		bounding_sphere_radius = radius + 100;
		gravity_on = false;

		texture_id = tid;
		sphere = glu_new_quadric();
		glu_quadric_draw_style(sphere, GLU_FILL);
		glu_quadric_texture(sphere, GL_TRUE);
		glu_quadric_normals(sphere, GLU_SMOOTH);

		yaw = angle;
		rotate_about = false;
	}

	void add_affected_objects(torpedo **tp) {
		affected_objects.push_back(tp);
	}

	void add_spaceship(spaceship **sp) {
		this->sp = *sp;
	}

	void apply_texture() {
		gl_color_3fv(get_color(colors::yellow));
		if (texture_on) {
			gl_enable(GL_TEXTURE_2D);
			gl_bind_texture(GL_TEXTURE_2D, texture_id);
			gl_tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			gl_tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else {
			gl_disable(GL_TEXTURE_2D);
		}
	}

	void draw() {
		gl_push_matrix(); {
			// set texture
			apply_texture();
			// update
			gl_mult_matrix_f(OM);
			// draw it
			glu_sphere(sphere, 2000.0, 200, 40);
			// bounding sphere
			object3d::draw();
			// draw gravity
			if (gravity_on) {
				for_each(affected_objects.begin(), affected_objects.end(), [&](torpedo **tp) {
					if ((*tp)->is_alive()) {
						// draw_force_vector((*tp)->get_position());
					}
				});
				if (sp->is_alive()) {
					// draw_force_vector(sp->get_position());
				}
			}
		} gl_pop_matrix();
	}

	/** 
	 * TODO: scale it for proper look
	 */
	void draw_force_vector(vector3<float> &p) {
		cout << p << endl;
		// distance to (0, 0, 0) so it's equal the length of vector f	
		double d = p.length();
		// gravity force force 
		double force = (90000000.0)/(d * d);
		// length to draw
		double length = (MAX_LENGTH * force)/MAX_FORCE;
		double alpha = 1.0 - length/d;
		gl_line_width(2.0f);
		gl_color_3fv(get_color(colors::color_name::green));
		gl_begin(GL_LINES); {
			gl_vertex_3f(p[0], p[1], p[2]);
			gl_vertex_3f(p[0]/alpha, p[1]/alpha, p[2]/alpha);
		} gl_end();
		gl_line_width(1.0f);
	}

	void update() {
		yaw += 0.0f;
		if (yaw >= 360.0f) {
			yaw = 0.0f;
		}
		object3d::update_internal();
	}

	void toggle_texture_mode() {
		texture_on = !texture_on;
	}

	void set_gravity_on(bool flag) {
		gravity_on = flag;
	}

private:
	const double MAX_LENGTH;
	const double MAX_FORCE;
	bool texture_on;
	bool gravity_on;
	float radius;
	GLUquadricObj *sphere;
	image *img;
	unsigned texture_id;
	float angle;
	vector<torpedo**> affected_objects;
	spaceship *sp;
};

#endif