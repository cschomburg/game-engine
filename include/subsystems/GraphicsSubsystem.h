#include <memory>
#include <set>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Color.h"
#include "Font.h"
#include "GameEngine.h"
#include "Subsystem.h"
#include "components/Renderable.h"
#include "interfaces/IPositionable.h"

class GraphicsSubsystem : public Subsystem {
public:
	GraphicsSubsystem(GameEngine *engine);
	virtual ~GraphicsSubsystem();

	bool init();
	void update();

	void registerRenderable(Renderable::Ptr renderable);
	void unregisterRenderable(Renderable::Ptr renderable);
	IPositionable::Ptr camera();
	void setCamera(IPositionable::Ptr positionable);

	void setColor(const Color &color);

private:
	void render(Renderable::Ptr renderable);

private:
	std::vector<Renderable::Ptr> m_renderables;
	IPositionable::Ptr m_camera;
	Font::Ptr m_font16;
	Font::Ptr m_font32;
	Font::Ptr m_font48;

	int m_frameCount;
	int m_lastSecond;
	int m_fps;
};
