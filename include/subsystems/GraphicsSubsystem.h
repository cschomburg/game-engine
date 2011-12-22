#include <memory>
#include <set>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Color.h"
#include "Subsystem.h"

class Font;
class Object;
class Renderable;

class GraphicsSubsystem : public Subsystem {
public:
	GraphicsSubsystem(GameEngine *engine);
	virtual ~GraphicsSubsystem();

	bool init();
	void update();

	void registerObject(Object *object);
	void unregisterObject(Object *object);
	void setCamera(Object *object);

	void setColor(const Color &color);
	void render(const Renderable &renderable);

private:
	std::vector<Renderable *> m_renderables;
	Object *m_camera;
	std::shared_ptr<Font> m_font16;
	std::shared_ptr<Font> m_font32;
	std::shared_ptr<Font> m_font48;

	int m_frameCount;
	int m_lastSecond;
	int m_fps;
};
