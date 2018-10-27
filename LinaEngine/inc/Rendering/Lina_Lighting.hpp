/*
Author: Inan Evin
www.inanevin.com

MIT License

Lina Engine, Copyright (c) 2018 Inan Evin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

4.0.30319.42000
10/27/2018 8:29:51 PM

*/

#pragma once

#ifndef Lina_Lighting_HPP
#define Lina_Lighting_HPP

#include "Game/Lina_ActorComponent.hpp"
#include "DataStructures/Lina_Color.hpp"
#include "Rendering/Shaders/Lina_Shader.hpp"


/* BASE LIGHT */
class Lina_BaseLight : public Lina_ActorComponent
{

public:

	Color color;
	float intensity;
	inline const Lina_Shader* GetShader() const { return m_Shader; }

protected:

	Lina_BaseLight(Lina_Shader* shader, const Color c, float i) : color(c), intensity(i), m_Shader(shader) {};

private:

	Lina_Shader* m_Shader;

};

/* DIRECTIONAL LIGHT */

class Lina_DirectionalLight : public Lina_BaseLight
{

public:

	Lina_DirectionalLight(const Color c = COLOR_Black, float i = 0, Vector3 dir = Vector3::one()) :
		Lina_BaseLight(Engine()->RenderingEngine()->GetForwardDirectionalShader(), c, i) , direction(dir) {};

	Vector3 direction;

protected:

	void AttachToActor(Lina_Actor&) override;

};

/* ATTENUATION */

struct Lina_Attenuation
{

public:

	friend class Lina_PointLight;
	friend class AttenuationTypes;

	Lina_Attenuation() : constant(0), linear(0), exponent(1.0f) {};
	Lina_Attenuation(float c, float l, float e) : constant(c), linear(l), exponent(e) {};

	float constant;
	float linear;
	float exponent;

	static Lina_Attenuation AT_CONSTANT;
	static Lina_Attenuation AT_CONSTLIN;
	static Lina_Attenuation AT_CONSTQUAD;
	static Lina_Attenuation AT_LINEAR;
	static Lina_Attenuation AT_LINCONST;
	static Lina_Attenuation AT_LINQUAD;
	static Lina_Attenuation AT_QUADRATIC;
	static Lina_Attenuation AT_QUADCONST;
	static Lina_Attenuation AT_QUADLIN;
};

				 
Lina_Attenuation Lina_Attenuation::AT_CONSTANT = Lina_Attenuation(1.0f, 0.0f, 0.0f);
Lina_Attenuation Lina_Attenuation::AT_CONSTLIN = Lina_Attenuation(0.66f, 0.33f, 0.0f);
Lina_Attenuation Lina_Attenuation::AT_CONSTQUAD = Lina_Attenuation(0.66f, 0.0f, 0.33f);
Lina_Attenuation Lina_Attenuation::AT_LINEAR = Lina_Attenuation(0.0f, 1.0f, 0.0f);
Lina_Attenuation Lina_Attenuation::AT_LINCONST = Lina_Attenuation(0.33f, 0.66f, 0.0f);
Lina_Attenuation Lina_Attenuation::AT_LINQUAD = Lina_Attenuation(0.0f, 0.66f, 0.33f);
Lina_Attenuation Lina_Attenuation::AT_QUADRATIC = Lina_Attenuation(0.0f, 0.0f, 1.0f);
Lina_Attenuation Lina_Attenuation::AT_QUADCONST = Lina_Attenuation(0.33f, 0.0f, 0.66f);
Lina_Attenuation Lina_Attenuation::AT_QUADLIN = Lina_Attenuation(0.0f, 0.33f, 0.66f);


/* POINT LIGHT */

class Lina_PointLight : public Lina_BaseLight
{

public:

	Lina_PointLight(Color c = COLOR_Black, float i = 0.0f, float r = 0.0f, Lina_Attenuation at = Lina_Attenuation::AT_QUADRATIC)
		: Lina_BaseLight(Engine()->RenderingEngine()->GetForwardPointShader(), c, i), range(r), attenuation(at) {};

	float range;
	

protected:

	Lina_PointLight(Lina_Shader* s, Color c = COLOR_Black, float i = 0.0f, float r = 0.0f, Lina_Attenuation at = Lina_Attenuation::AT_QUADRATIC)
		: Lina_BaseLight(s, c, i), range(r), attenuation(at) {};

	void AttachToActor(Lina_Actor&) override;

private:

	Lina_Attenuation attenuation;
	friend class Lina_Shader;	// Shader uses position.
	Vector3 position;	// Updated via attached actor transform.
	void Update(float) override;
	void AttachToActor(Lina_Actor&) override;

};


class Lina_SpotLight : public Lina_PointLight
{

public:

	Lina_SpotLight(Color c = COLOR_Black, float i = 0.0f, float r = 0.0f, float co = 0.1f, Vector3 dir = Vector3::one()) :
		Lina_PointLight(Engine()->RenderingEngine()->GetForwardSpotShader(), c, i, r), direction(dir), cutoff(co) {};
	
	float cutoff;
	Vector3 direction;

private:
	void AttachToActor(Lina_Actor&) override;

};



#endif