#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "Geometry.h"
#include "stdafx.h"
#include <vector>
#include "vec\vec.h"
#include "vec\mat.h"
#include "ShaderBuffers.h"
#include "drawcall.h"
#include "mesh.h"

using namespace linalg;

class Cube : public Geometry_t
{
	std::vector<vertex_t> vertices;	
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;

public:
	Cube(ID3D11Device* dx3ddevice, ID3D11DeviceContext* dx3ddevice_context);
	void compute_tangentSpace(vertex_t& v0, vertex_t& v1, vertex_t& v2, vertex_t& v3);
	virtual void render() const;
	~Cube();
};
#endif

