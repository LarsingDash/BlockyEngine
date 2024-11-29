//
// Created by hmkam on 29/11/2024.
//

#ifndef TYPE_HPP
#define TYPE_HPP

enum PhysicsType {
	COLLIDER,
	RIGIDBODY
};

class Type {
public:
	Type(bool isTrigger, bool isStatic);
	virtual ~Type();

	virtual PhysicsType GetType() = 0;
};

#endif //TYPE_HPP
