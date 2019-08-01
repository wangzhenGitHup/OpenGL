#ifndef __CAMERA__H__
#define __CAMERA__H__

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <vector>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = YAW, 
		float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
		MovementSpeed(SPEED), 
		MouseSensitivity(SENSITIVITY), 
		Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : 
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
		MovementSpeed(SPEED), 
		MouseSensitivity(SENSITIVITY), 
		Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
	
	glm::vec3 getPosition(){ return Position; }

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yOffset);
	float getZoom(){ return Zoom; }
	glm::vec3 getFront(){ return Front; }

private:
	void updateCameraVectors();

private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
};


#endif