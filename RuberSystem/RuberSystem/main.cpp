/** 
 * Wanted features:
 *	DONE	1) Load model 3d
 *			2) Reflection - mirror
 *			3) Flocking behavior
 *			4) Shading 
 *			5) Ray tracer
 *			6) Sub division object
 *			7) AI for spaceship
 *			8) Sound effect
 *			9) Explosion effect
 *			10) Gameplay: story, level, starcraft character
 *			11) Robot moving in space
 * DONE		12) Draw a better spaceship
 *			13) Advanced lighting effect
 *			14) Advanced bounding sphere (moving through torus)
 * DONE		15) Texture mapping for the whole scene	
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <GL/glut.h>

#include "driver.h"
#include "triangle_loader.h"

using namespace std;

double get_rotation_angle(vector3<float> u, vector3<float> v) {
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
	double angle = acos(cosine_theta);
	return angle;
}

vector3<float> get_rotation_axis(vector3<float> u, vector3<float> v) {
	u.normalize();
	v.normalize();
	// fix linear case
	if (u == v || u == -v) {
		v[0] += 0.1;
		v[1] += 0.0;
		v[2] += 0.1;
		v.normalize();
	}
	return u.cross(v);
}

void test_cross_product() {
	vector3<float> u(1, 0, 0);
	vector3<float> v(-1, 0, 0);
	cout << get_rotation_axis(u, v) << endl;
}

int main(int argc, char **argv) {
	// util::triangle_loader::run();
	driver::run(argc, argv);
	// test_cross_product();
	return 0;
}