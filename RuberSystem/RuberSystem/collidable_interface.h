#ifndef COLLIDABLE_INTERFACE_H
#define COLLIDABLE_INTERFACE_H

class collidable_interface {
	virtual bool collide_with(const object3d *rhs) const = 0;
};

#endif