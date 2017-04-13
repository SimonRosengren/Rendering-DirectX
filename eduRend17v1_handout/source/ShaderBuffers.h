
#pragma once
#ifndef MATRIXBUFFERS_H
#define MATRIXBUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct MatrixBuffer_t
{
	mat4f ModelToWorldMatrix;
	mat4f WorldToViewMatrix;
	mat4f ProjectionMatrix;
};
struct LightBuffer_t
{
	float4 LightColor;
	float4 LightDir;
	float4 CameraDir;
};
struct PhongBuffer_t
{
	float4 SpecularPower;
	float4 SpecularColor;
	float4 AmbientColor;
	float4 DiffuseColor;
	float isSkybox;
	float3 padding;
};


#endif