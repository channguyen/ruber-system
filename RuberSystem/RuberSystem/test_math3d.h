#ifndef TEST_MATH3D_H
#define TEST_MATH3D_H

#include <iostream>
#include "vector3.h"
#include "math3d.h"

using namespace std;
using namespace util;

namespace unit_test {
	void test_all() {
		double angle = 90;
		cout << math3d::degree_to_radian(degree) << endl;
		double radian = 3.14;
		cout << math3d::radian_to_degree(radian) << endl;
	}
}

#endif