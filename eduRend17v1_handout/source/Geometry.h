//
//  Geometry.h
//
//  (c) CJG 2016, cjgribel@gmail.com
//

#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "stdafx.h"
#include <vector>
#include "vec\vec.h"
#include "vec\mat.h"
#include "ShaderBuffers.h"
#include "drawcall.h"
#include "mesh.h"

using namespace linalg;

class Geometry_t
{
protected:
	// Pointers to the current device and device context
	ID3D11Device* const			dxdevice;
	ID3D11DeviceContext* const	dxdevice_context;

	// Pointers to the class' vertex & index arrays
	ID3D11Buffer* vertex_buffer = nullptr;
	ID3D11Buffer* index_buffer = nullptr;

	//ID3D11ShaderResourceView* m_texture = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;




public:

	//For normal mapping
	vec3f D, E;
	vec2f F, G;
	float R;
	vec3f T, B;

	Geometry_t(
		ID3D11Device* dxdevice, 
		ID3D11DeviceContext* dxdevice_context) 
		:	dxdevice(dxdevice),
			dxdevice_context(dxdevice_context)
	{
		//Create sampler
		HRESULT hr;
		D3D11_SAMPLER_DESC sd =
		{
			D3D11_FILTER_ANISOTROPIC,
			D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_TEXTURE_ADDRESS_WRAP,
			0.0f,
			4,
			D3D11_COMPARISON_NEVER,
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			-FLT_MAX,
			FLT_MAX,
		};


		ASSERT(hr = dxdevice->CreateSamplerState(&sd, &m_sampleState));
	}

	//
	// Map and update the matrix buffer
	//
	virtual void MapMatrixBuffers(
		ID3D11Buffer* matrix_buffer,
		mat4f ModelToWorldMatrix,
		mat4f WorldToViewMatrix,
		mat4f ProjectionMatrix);
	virtual void MapLightBuffer(ID3D11Buffer* light_buffer, float4 LightColor, float4 LightDir, float4 CameraDir);
	virtual void MapPhongBuffer(ID3D11Buffer* light_buffer, float4 SpecularPower, float4 SpecularColor, float4 AmbientColor, float4 DiffuseColor, float isSkybox);
	void compute_tangentSpace(vertex_t& v0, vertex_t& v1, vertex_t& v2);

	//
	// Abstract render method: must be implemented by derived classes
	//
	virtual void render() const = 0;

	//
	// Destructor
	//
	virtual ~Geometry_t()
	{ 
		SAFE_RELEASE(vertex_buffer);
		SAFE_RELEASE(index_buffer);
	}
};

class Quad_t : public Geometry_t
{
	// our local vertex and index arrays
	std::vector<vertex_t> vertices;
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;

public:

	Quad_t(
		ID3D11Device* dx3ddevice,
		ID3D11DeviceContext* dx3ddevice_context);

	virtual void render() const;

	~Quad_t() { }
};

class OBJModel_t : public Geometry_t
{
	// index ranges, representing drawcalls, within an index array
	struct index_range_t
	{
		size_t start;
		size_t size;
		unsigned ofs;
		int mtl_index;
	};

	std::vector<index_range_t> index_ranges;
	std::vector<material_t> materials;

	void append_materials(const std::vector<material_t>& mtl_vec)
	{
		materials.insert(materials.end(), mtl_vec.begin(), mtl_vec.end());
	}

public:

	OBJModel_t(
		const std::string& objfile,
		ID3D11Device* dxdevice,
		ID3D11DeviceContext* dxdevice_context);

	virtual void render() const;

	~OBJModel_t() { }
};

#endif