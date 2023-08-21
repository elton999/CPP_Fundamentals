#ifndef CAMERA_H
#define CAMREA_H
#include "glm/glm.hpp"

class Camera
{
public:
	glm::mat4 GetViewMatrix() const;
	virtual void rotate(float yaw, float pitch){}

protected:
	Camera();

	glm::vec3 mPosition;
	glm::vec3 mTargetPos;
	glm::vec3 mUp;

	float mYaw;
	float mPitch;

};


class OrbitCamera : public Camera
{
public:
	OrbitCamera();

	virtual void rotate(float yaw, float pitch); // in degress

	void setLookAt(const glm::vec3& target);
	void setRadious(float radius);

private:
	void updateCameraVectors();
	float mRadius;
};

#endif

