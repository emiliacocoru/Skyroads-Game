#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Tema{
	class Camera {
		public:
			Camera() {
				position = glm::vec3(4.5f, 1.5f, 3.f);
				forward = glm::vec3(0, 0, -0.5);
				up		= glm::vec3(0, 0.5, 0);
				right	= glm::vec3(1, 0, 0);
				distanceToTarget = 1;
			}

			~Camera(){}

			void setPosition(const glm::vec3 &position) {
				this->position = position;
			}

			glm::vec3 getForward() {
				return this->forward;
			}

			void MoveForward(float distance) {
				glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			}

			void TranslateForward(float distance) {
				position += glm::normalize(forward)* distance;
			}

			void TranslateUpword(float distance) {
				position += glm::normalize(up) * distance;
			}

			void TranslateRight(float distance) {
				position += glm::normalize(right) * distance;
			}

			glm::mat4 GetViewMatrix() {
				return glm::lookAt(position, position + forward, up);
			}

			glm::vec3 GetTargetPosition() {
				return position + forward * distanceToTarget;
			}

		public:
			float distanceToTarget;
			glm::vec3 position;
			glm::vec3 forward;
			glm::vec3 right;
			glm::vec3 up;
		};
}
