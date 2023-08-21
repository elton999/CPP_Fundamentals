#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

Camera::Camera()
	:mPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	mTargetPos(glm::vec3(0.0f, 0.0f, 0.0f)),
	mUp(glm::vec3(0.0f, 0.1f, 0.0f)),
	mYaw(0),
	mPitch(0)
{

}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(mPosition, mTargetPos, mUp);
}

// OrbitCamera

OrbitCamera::OrbitCamera():mRadius(10.0f){}

void OrbitCamera::setLookAt(const glm::vec3& target)
{
	mTargetPos = target;
}

void OrbitCamera::setRadious(float radius)
{
	mRadius = glm::clamp(radius, 2.0f, 80.0f);
}

void OrbitCamera::rotate(float yaw, float pitch)
{
	mYaw = glm::radians(yaw);
	mPitch = glm::radians(pitch);

	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f );

	updateCameraVectors();
}

void OrbitCamera::updateCameraVectors()
{
	mPosition.x = mTargetPos.x + mRadius * cosf(mPitch) * sinf(mYaw);
	mPosition.y = mTargetPos.y + mRadius * sinf(mPitch);
	mPosition.z = mTargetPos.z + mRadius * cosf(mPitch) * cosf(mYaw);
}