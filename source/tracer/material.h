#ifndef MATERIAL_H
#define MATERIAL_H

#include"../util/color.hpp"

class Material {
public:
	Color ambient;
	Color diffuse;
	Color emision;
	double shininess;
	double specular;
};

#endif // MATERIAL_H
