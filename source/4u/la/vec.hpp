#ifndef VEC_HPP
#define VEC_HPP

#include"vecn.hpp"
#include"vec2.hpp"
#include"vec3.hpp"
#include"vec4.hpp"

typedef tvecn<double,2>     vec2;
typedef tvecn<int,2>		ivec2;
typedef tvecn<double,3>     vec3;
typedef tvecn<int,3>		ivec3;
typedef tvecn<double,4>     vec4;
typedef tvecn<int,4>		ivec4;

const vec2 nullvec2(0.0,0.0);
const ivec2 nullivec2(0,0);
const vec3 nullvec3(0.0,0.0,0.0);
const ivec3 nullivec3(0,0,0);
const vec4 nullvec4(0.0,0.0,0.0,0.0);
const ivec4 nullivec4(0,0,0,0);

#endif // VEC_HPP
