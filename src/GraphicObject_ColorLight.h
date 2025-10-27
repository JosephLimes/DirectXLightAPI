// GraphicObject_ColorLight
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"

class GraphicObject_ColorLight : public GraphicObject_Base
{
public:
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;					// Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;						// Move constructor
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) & = default;	// Copy assignment operator
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) & = default;		// Move assignment operator
	~GraphicObject_ColorLight();		  												// Destructor

	GraphicObject_ColorLight() = delete;

	void SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular);
	void SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod);

private:
	ShaderColorLight*				pShader;
	Matrix							World;
	ShaderColorLight::Material*		MeshMaterials;

};

#endif _GraphicObject_ColorLight
