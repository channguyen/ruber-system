#ifndef EXPLODABLE_INTERFACE_H
#define EXPLODABLE_INTERFACE_H

class explodable_interface {
public:
	virtual void draw_explosion() = 0;
	virtual ~explodable_interface() {}
};

#endif