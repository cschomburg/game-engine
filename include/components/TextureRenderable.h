#ifndef TEXTURERENDERABLE_H
#define TEXTURERENDERABLE_H

#include <string>

#include "components/Renderable.h"

class Texture;

class TextureRenderable : public Renderable {
public:
	typedef std::shared_ptr<TextureRenderable> Ptr;

	TextureRenderable();
	virtual ~TextureRenderable();

	std::shared_ptr<Texture> texture() const;
	void setTexture(const std::string &texturePath);

	void render();

private:
	std::shared_ptr<Texture> m_texture;
};

#endif /* end of include guard: TEXTURERENDERABLE_H */
