#ifndef MATERIAL_H
#define MATERIAL_H

#include"../util/color.hpp"

class Material {
public:
	Color ambient;
	Color diffuse;
	Color specular;
	Color emision;
	double shininess;
};

#endif // MATERIAL_H
