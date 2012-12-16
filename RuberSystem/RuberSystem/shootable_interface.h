#ifndef SHOOTABLE_INTERFACE
#define SHOOTABLE_INTERFACE

#include <vector>

#include "vector3.h"
#include "test_vector3.h"
#include "object3d.h"
#include "math3d.h"
#include "missile.h"
#include "torpedo.h"

using namespace std;

class shootable_interface {
public:
	virtual torpedo *shoot_target(const vector3<float> &target) = 0;
	virtual bool scan_target(const object3d *obj) = 0;

public:
	virtual ~shootable_interface() {}
};

#endif