#ifndef TEST_VECTOR3_H
#define TEST_VECTOR3_H

#include <iostream>
#include "vector3.h"

using namespace std;
using namespace util;

namespace unit_test {
	void test_constructor() {
		vector3<float> v(1.0, 2.0f, 3.0f);		
		cout << v << endl;
	}
}

#endif