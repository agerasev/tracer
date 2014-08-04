#ifndef MAT_HPP
#define MAT_HPP

#include"matnm.hpp"
#include"matn.hpp"

typedef tmatnm<double,2,2>     mat2;
typedef tmatnm<int,2,2>        imat2;
typedef tmatnm<double,3,3>     mat3;
typedef tmatnm<int,3,3>        imat3;
typedef tmatnm<double,4,4>     mat4;
typedef tmatnm<int,4,4>        imat4;

const mat2 nullmat2 = {0.0,0.0,0.0,0.0};
const imat2 nullimat2 = {0,0,0,0};
const mat3 nullmat3 = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
const imat3 nullimat3 = {0,0,0,0,0,0,0,0,0};
const mat4 nullmat4 = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
const imat4 nullimat4 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

const mat2 unimat2 = {1.0,0.0,0.0,1.0};
const imat2 uniimat2 = {1,0,0,1};
const mat3 unimat3 = {1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0};
const imat3 uniimat3 = {1,0,0,0,1,0,0,0,1};
const mat4 unimat4 = {1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0};
const imat4 uniimat4 = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

#endif // MAT_HPP
