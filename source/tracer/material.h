#ifndef MATERIAL_H
#define MATERIAL_H

#include"../util/color.hpp"

class Material {
public:
	Color ambient;
	Color diffuse;
	Color emision;
	double specular;
	Material(const Color &a, double sp = 0.2, const Color &e = Color(0,0,0), const Color &d = Color(1,1,1)) :
		ambient(a), specular(sp), emision(e), diffuse(d)
	{

	}
};

#endif // MATERIAL_H
