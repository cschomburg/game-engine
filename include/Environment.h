#pragma once

class Environment()
{
public:
	static Environment * instance();

	Environment();
	virtual ~Environment();

	bool init(Game *game, int screenWidth, int screenHeight, bool fullscreen,
			  const char *windowTitle);
	void destroy();

	void startMainLoop();
	void stopMainLoop();
	void isRunning();

	float time();
	int maxFrameRate();
	void setMaxFrameRate(int fps);

private:
	static Environment g_instance;

	Game * m_game;

	GlInterface * m_interface;

};
