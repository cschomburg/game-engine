#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera : public GameObject {
public:
	Camera();
	virtual ~Camera();

	void onUpdate();
	void onRender();

	void track(GameObject * object);
	float zoomLevel() const;
	void setZoomLevel(float zoomLevel);

private:
	float m_zoomLevel;
	GameObject * m_tracked;
};

#endif /* end of include guard: CAMERA_H */
