#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "Camera.h"
#include "ClassesTema3.h"
#include <Core/Engine.h>
#include "Tema3Transform3D.h"
#include <algorithm>    // std::max
#include <cstdint>
#include <iostream>
#include <vector>
#include <Component/Transform/Transform.h>

class Tema3 : public SimpleScene
{
	public:
		Tema3();
		~Tema3();

		void Init() override;


	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		std::unordered_map<std::string, Texture2D*> mapTextures;
		GLuint randomTextureID;
		glm::mat4 modelMatrix;
		glm::mat4 projectionMatrix;
		Tema::Camera *camera;
		int deltaTimeClouds;
		float plusJump = 0;
		float spotLight = 1.f;

		Element gas;
		Element powerBar;
		Element score_bar;
		float gasTime = 0;
		std::vector<Element> hearts;

		bool specialPower = false;
		float specialPowerTime = 0;
		int numberOfHearts = 3;
		int numberOfPlatforms = 0;
		float platformTime = 0;
		int distanceBetweenSphereAndCamera = 6;

		float power = 1;
		float PI = 3.14;
		int numberOfReds = 0;
		int maxNumberOfReds = 1;
		int score = 0;
		float maxScoreScale = 2.1f;

		bool animals = false;
		int numberOfYellow = 0;
		int maxNumberOfYellow = 1;

		int numberOfOrange = 0;
		int maxNumberOfOrange = 1;
		float timeBadStuff = 0;
		float maxTimeBadStuff = 2;

		// jump / move
		float jumpAngle = 0.f;
		float moveLeftAngle = 0.f;
		float moveRightAngle = 0.f;

		bool moveLeft = false;
		bool moveRight = false;
		bool sphereJump = false;
		float angleNotInGame = 3;

		std::vector<Platform> platforms;
		std::vector<Platform> specialPlatform;
		std::vector<Element> clouds;
		Element sphere;
		float timeGo;

		bool goDown = false;
		bool thirdPerson = true;
		bool fastSpeed = false;
		float timeFastSpeed = 0;
		bool stillInGame = true;
		float stillInGameTime = 0;
		bool inAir = false;
		bool onPlatform = true;
		bool startedFirst = false;
		bool startedThird = false;
		bool moveLeftFirstPerson = false;
		bool moveRightFirstPerson = false;
		std::vector<Element> diamonds;
		std::vector<Obstacle> obstacles;
		std::vector<Obstacle> decorations;
		std::vector<Obstacle> goodObstacles;

		float sizeDiamond = 0.35f;
		glm::vec3 lightPosition;
		glm::vec3 lightPosition2;
		glm::vec3 lightPosition3;
		glm::vec3 lightPosition4;
		glm::vec3 lightPosition5;
		std::vector<glm::vec3> lightPositions;

		bool collisionObstacle = false;
		int collisionNumber = 0;
		glm::vec3 lightDirection;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;

		Texture2D* CreateRandomTexture(unsigned int width, unsigned int height) {
			GLuint textureID = 0;
			unsigned int channels = 3;
			unsigned int size = width * height * channels;
			unsigned char* data = new unsigned char[size];

			for (int i = 0; i < size; ++i) {
					data[i] = rand() % 1000;
				}
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

			glPixelStorei(GL_PACK_ALIGNMENT, 1);
			CheckOpenGLError();

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);

			CheckOpenGLError();
			Texture2D* texture = new Texture2D();
			texture->Init(textureID, width, height, channels);

			SAFE_FREE_ARRAY(data);
			return texture;
		}

		void RenderMeshTexture(Mesh *mesh, Shader *shader, bool rotate, bool mixt,
			const glm::mat4 & modelMatrix, Texture2D* texture1,
			Texture2D* texture2, const glm::vec3 &color) {
			if (!mesh || !shader || !shader->GetProgramID())
				return;

			glUseProgram(shader->program);

			int light_position = glGetUniformLocation(shader->program, "light_position");
			glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

			light_position = glGetUniformLocation(shader->program, "light_position2");
			glUniform3f(light_position, lightPosition2.x, lightPosition2.y, lightPosition2.z);

			light_position = glGetUniformLocation(shader->program, "light_position3");
			glUniform3f(light_position, lightPosition3.x, lightPosition3.y, lightPosition3.z);

			light_position = glGetUniformLocation(shader->program, "light_position4");
			glUniform3f(light_position, lightPosition4.x, lightPosition4.y, lightPosition4.z);

			light_position = glGetUniformLocation(shader->program, "light_position5");
			glUniform3f(light_position, lightPosition5.x, lightPosition5.y, lightPosition5.z);


			int light_direction = glGetUniformLocation(shader->program, "light_direction");
			glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

			glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
			int eye_position = glGetUniformLocation(shader->program, "eye_position");
			glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

			int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
			glUniform1i(material_shininess, materialShininess);

			int material_kd = glGetUniformLocation(shader->program, "material_kd");
			glUniform1f(material_kd, materialKd);

			glm::vec3 color1 = {1,1,1};
			int object_color = glGetUniformLocation(shader->program, "object_color");
			glUniform3f(object_color, color1.r, color1.g, color1.b);

			int material_ks = glGetUniformLocation(shader->program, "material_ks");
			glUniform1f(material_ks, materialKs);

			spotLight = 1.0f;
			int spotLightLocation = glGetUniformLocation(shader->program, "spotLight");
			glUniform1f(spotLightLocation, spotLight);

			float cutOffAngle = 10.f;
			int angleLocation = glGetUniformLocation(shader->program, "angle");
			glUniform1f(angleLocation, cutOffAngle);



			GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
			glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
			int loc_view_matrix = glGetUniformLocation(shader->program, "View");
			glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

			glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
			int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
			glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


			if (texture1) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
				glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
			}

			if (texture2) {
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
				glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
			}

			if (rotate) {
				int time = glGetUniformLocation(shader->GetProgramID(), "time");
				glUniform1f(time, Engine::GetElapsedTime());
			} else {
				int time = glGetUniformLocation(shader->GetProgramID(), "time");
				glUniform1f(time, -1);
			}

			if (mixt) {
				glUniform1f(glGetUniformLocation(shader->GetProgramID(), "mixt"), 1.0);
			} else {
				glUniform1f(glGetUniformLocation(shader->GetProgramID(), "mixt"), 0.0);
			}

			glBindVertexArray(mesh->GetBuffers()->VAO);
			glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
		}

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, float deformation, int mode)
		{
			if (!mesh || !shader || !shader->program)
				return;

			shader->Use();

			int model = glGetUniformLocation(shader->program, "Model");
			glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			if (mode == 1) {
				int view = glGetUniformLocation(shader->program, "View");
				glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
			} else {
				glm::mat4 viewMatrix = glm::mat4(1);
				int loc_view_matrix = glGetUniformLocation(shader->program, "View");
				glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

			}


			int light_position = glGetUniformLocation(shader->program, "light_position");
			glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

			light_position = glGetUniformLocation(shader->program, "light_position2");
			glUniform3f(light_position, lightPosition2.x, lightPosition2.y, lightPosition2.z);

			light_position = glGetUniformLocation(shader->program, "light_position3");
			glUniform3f(light_position, lightPosition3.x, lightPosition3.y, lightPosition3.z);

			light_position = glGetUniformLocation(shader->program, "light_position4");
			glUniform3f(light_position, lightPosition4.x, lightPosition4.y, lightPosition4.z);

			light_position = glGetUniformLocation(shader->program, "light_position5");
			glUniform3f(light_position, lightPosition5.x, lightPosition5.y, lightPosition5.z);


			int light_direction = glGetUniformLocation(shader->program, "light_direction");
			glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

			glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
			int eye_position = glGetUniformLocation(shader->program, "eye_position");
			glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

			int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
			glUniform1i(material_shininess, materialShininess);

			int material_kd = glGetUniformLocation(shader->program, "material_kd");
			glUniform1f(material_kd, materialKd);

			glm::vec3 color1 = {1,1,1};
			int object_color = glGetUniformLocation(shader->program, "object_color");
			glUniform3f(object_color, color1.r, color1.g, color1.b);

			int material_ks = glGetUniformLocation(shader->program, "material_ks");
			glUniform1f(material_ks, materialKs);


			int projection = glGetUniformLocation(shader->program, "Projection");
			glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

			int deform = glGetUniformLocation(shader->GetProgramID(), "Deformation");
			glUniform1f(deform, deformation);

			int time = glGetUniformLocation(shader->GetProgramID(), "Time");
			glUniform1f(time, Engine::GetElapsedTime());

			mesh->Render();
		}



		void RenderMySimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix,  Texture2D* texture1, bool inPlace) {
			if (!mesh || !shader || !shader->program)
				return;

			shader->Use();

			int model = glGetUniformLocation(shader->program, "Model");
			glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			if (inPlace) {
				glm::mat4 viewMatrix = glm::mat4(1);
				int loc_view_matrix = glGetUniformLocation(shader->program, "View");
				glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			} else {
				int view = glGetUniformLocation(shader->program, "View");
				glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
			}

			int projection = glGetUniformLocation(shader->program, "Projection");
			glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


			if (texture1) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
				glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
			}


			glBindVertexArray(mesh->GetBuffers()->VAO);
			glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
		}


		// pozitionarea platformelor initiale
		void initPlatforms(std::vector<Platform>& platforms) {
			Platform newPlatform;

			newPlatform.setCoordinates(2.f, 0.f, 0.f, (char*)"blue", 1.f, 0.2f, 7.f);
			platforms.push_back(newPlatform);

			newPlatform.setCoordinates(4.f, 0.f, -5.f, (char*)"blue", 1.f, 0.2, 5.f);
			platforms.push_back(newPlatform);

			newPlatform.setCoordinates(2.f, 0.f, -5.5f, (char*)"blue", 1.f, 0.2, 6.f);
			platforms.push_back(newPlatform);

			newPlatform.setCoordinates(6.f, 0.f, -1.f, (char*)"blue", 1.f, 0.2, 1.f);
			platforms.push_back(newPlatform);
		}

		// setul de funcții folosite pentru mișcarea sferei
		// atât în first person, cât și în third
		void doJumpThirdPerson(glm::mat4& modelMatrix, float& jump, bool& boxJump,
												Element& sphere, float deltaTimeSeconds, bool thirdPerson,
												bool& startedThird) {

			float mij = (sphere.getZ() + sphere.getZ() - 1) * 0.5;
			modelMatrix *= Tema3Transform3D::Translate(0, 0, -1);
			modelMatrix *= Tema3Transform3D::RotateOX(jump);
			modelMatrix *= Tema3Transform3D::Translate(0, 0,  sphere.getZ() - mij + 0.5);
			modelMatrix *= Tema3Transform3D::RotateOX(-jump);

			if (jump <= -PI / 2) {
				plusJump -= 4 * deltaTimeSeconds;
			} else {
				plusJump +=  4 * deltaTimeSeconds;
			}

			jump -= 4 * deltaTimeSeconds;
			camera->TranslateForward(2.5 * deltaTimeSeconds);
			lightPosition.z -= 2.5 * deltaTimeSeconds;


			if (jump <= -PI) {
				sphere.setZ(sphere.getZ() - 2);
				sphereJump = false;
				startedThird = false;
				jump = 0.f;
			}
		}

		void doJumpFirstPerson(Element& sphere, float deltaTimeSeconds,
												bool& startedFirst, bool& inAir) {
			if (sphere.getY() < 1.5 && !inAir) {
				sphere.setY(sphere.getY() + 4 * deltaTimeSeconds);
				sphere.setZ(sphere.getZ() - 2 * deltaTimeSeconds);

				camera->TranslateForward(2 *deltaTimeSeconds);
				camera->TranslateUpword(4 * deltaTimeSeconds);
				lightPosition.z -= 2 * deltaTimeSeconds;


			} else {
				inAir = true;
				if (inAir && sphere.getY() > 0.5) {
					sphere.setY(sphere.getY() - 4 * deltaTimeSeconds);
					sphere.setZ(sphere.getZ() - 2 * deltaTimeSeconds);
					camera->TranslateForward(2 *deltaTimeSeconds);
					lightPosition.z -= 2 * deltaTimeSeconds;
					camera->TranslateUpword(-4 * deltaTimeSeconds);

				} else {
					sphereJump = false;
					inAir = false;
					startedFirst = false;
				}
			}
		}

		void doMoveLeft(glm::mat4& modelMatrix, float& jump, bool& moveLeft,
												Element& sphere, float deltaTimeSeconds, bool thirdPerson) {

			float mij = (sphere.getX() + (sphere.getX() - 2)) * 0.5;
			modelMatrix *= Tema3Transform3D::Translate(-1, 0, 0);
			modelMatrix *= Tema3Transform3D::RotateOZ(-jump);
			modelMatrix *= Tema3Transform3D::Translate(sphere.getX() - mij, 0, 0);
			modelMatrix *= Tema3Transform3D::RotateOZ(+jump);


			if (!thirdPerson) {
				if (jump >= -PI / 2) {
						camera->TranslateUpword(1.5 * deltaTimeSeconds);
				} else {
						camera->TranslateUpword(-1.5 * deltaTimeSeconds);
				}
				camera->TranslateRight(-2.5 * deltaTimeSeconds);
			}

			jump -= 4 * deltaTimeSeconds;
			if (jump <= -PI) {
				sphere.setX(sphere.getX() - 2);
				sphere.setY(0.5);
				moveLeft = false;
				jump = 0.f;
			}
		}

		void doMoveRight(glm::mat4& modelMatrix, float& jump, bool& moveRight,
												Element& sphere, float deltaTimeSeconds, bool thirdPerson) {

			float mij = (sphere.getX() + (sphere.getX() + 2)) * 0.5;
			modelMatrix *= Tema3Transform3D::Translate(1, 0, 0);
			modelMatrix *= Tema3Transform3D::RotateOZ(+jump);
			modelMatrix *= Tema3Transform3D::Translate(sphere.getX() - mij, 0, 0);
			modelMatrix *= Tema3Transform3D::RotateOZ(-jump);

			jump -= 4 * deltaTimeSeconds;

			if (!thirdPerson) {
				if (jump >= -PI / 2) {
						camera->TranslateUpword(1.5 * deltaTimeSeconds);
				} else {
						camera->TranslateUpword(-1.5 * deltaTimeSeconds);
				}
				camera->TranslateRight(+2.5 * deltaTimeSeconds);
			}

			if (jump <= -PI){
				sphere.setX(sphere.getX() + 2);
				sphere.setY(0.5);
				moveRight = false;
				jump = 0.f;
			}
		}

		// funcție de ștergere a platformelor ce ies din raza vizuală a camerei
		void deletePlatforms(std::vector<Platform>& platforms, int& numberOfPlatforms, Element sphere) {
			int i = 1;
			while (i < numberOfPlatforms) {
				if (platforms[i].getZ() > sphere.getZ() + distanceBetweenSphereAndCamera) {
						platforms.erase(platforms.begin() + i);
						numberOfPlatforms--;
				} else {
					i++;
				}
			}
		}

		void deleteObstacles(std::vector<Obstacle>& obstacles, int& numberOfObstacles, Element sphere) {
			int i = 1;
			while (i < numberOfObstacles) {
				if (obstacles[i].getZ() > sphere.getZ() + distanceBetweenSphereAndCamera) {
						obstacles.erase(obstacles.begin() + i);
						numberOfObstacles--;
				} else {
					i++;
				}
			}
		}

		// coliziunea dintre sfera si platforme
		bool collision(std::vector<Platform>& platforms, int i, Element sphere) {

			float x = std::max(platforms[i].getX(), std::min(sphere.getX(), platforms[i].getX() + 1));
			float y = std::max(platforms[i].getY(), std::min(sphere.getY(), platforms[i].getY() + 0.2f));
			float z = std::max(platforms[i].getZ(), std::min(sphere.getZ(), platforms[i].getZ()
																														+ platforms[i].getScaleZ()));

			float distance = sqrt((x - sphere.getX()) * (x - sphere.getX()) +
														(y - sphere.getY()) * (y - sphere.getY()) +
														(z - sphere.getZ()) * (z - sphere.getZ()));

			if (distance < 0.35) {
					return true;
			} else {
				return false;
			}
		}


		// coliziunea sfera-obsatcole
		bool collisionWithObstacles(std::vector<Obstacle>& obstacles, int i, Element sphere) {

			float x = std::max(obstacles[i].getX(),
				std::min(sphere.getX(), obstacles[i].getX() + obstacles[i].getScaleX()));
			float y = std::max(obstacles[i].getY(),
						std::min(sphere.getY() + plusJump, obstacles[i].getY() +  obstacles[i].getScaleY()));
			float z = std::max(obstacles[i].getZ(),
						std::min(sphere.getZ(), obstacles[i].getZ() + obstacles[i].getScaleZ()));

			float distance = sqrt((x - sphere.getX()) * (x - sphere.getX()) +
														(y - sphere.getY() - plusJump) * (y - sphere.getY() - sphereJump) +
														(z - sphere.getZ()) * (z - sphere.getZ()));
			if (distance < 0.3) {
				return true;
			} else {
				return false;
			}
		}

		// coliziunea sfera-diamante
		bool collisionWithDiamonds(std::vector<Obstacle>& diamonds, int i, Element sphere) {


			float x = std::max(diamonds[i].getX() - sizeDiamond,
						std::min(sphere.getX(), diamonds[i].getX() + sizeDiamond));
			float y = std::max(diamonds[i].getY(),
					std::min(sphere.getY() + plusJump, diamonds[i].getY() + 1.5f * sizeDiamond));
			float z = std::max(diamonds[i].getZ() - sizeDiamond, std::min(sphere.getZ(), diamonds[i].getZ()));

			float distance = sqrt((x - sphere.getX()) * (x - sphere.getX()) +
														(y - sphere.getY() - plusJump) * (y - sphere.getY() - sphereJump) +
														(z - sphere.getZ()) * (z - sphere.getZ()));


			if (distance < 0.35) {
					return true;
			} else {
				return false;
			}
		}


	 	// imi creez o noua platforma cu pozitia si scalabilitatea pe Z, dar si culoarea random
		// aici imi adaug noi decoratiuni, diamante si obstacole
		// ce au aparitia, textura, dimensiunea pe Z si scalabilitatea random
		void createPlatform(Platform& newPlatform, std::vector<Platform>& platforms, int position, int& numberOfReds,
															int& numberOfOrange, int& numberOfYellow) {
			float scaleZ = rand() % 5 + 3;
			float scaleX = 1;
			float z = platforms[position].getZ() - 1 - scaleZ;
			if (platforms[position].getColor() == "none") {
				z += 2;
			}
			float x = platforms[position].getX();
			float y = platforms[position].getY();
			int color = rand() % 6;

			if (numberOfReds == maxNumberOfReds && color == 2) {
					color = 0;
			}
			if (numberOfOrange == maxNumberOfOrange && color == 3) {
				color = 0;
			}
			if (numberOfYellow == maxNumberOfYellow && color == 4) {
				color = 0;
			}


			switch (color) {
				case 0:
					newPlatform.setCoordinates(x, y, z, (char*) "blue", scaleX, 0.2f, scaleZ);
					break;
				case 1:
					newPlatform.setCoordinates(x, y, z, (char*) "green", scaleX, 0.2f, scaleZ);
					break;
				case 2:
					newPlatform.setCoordinates(x, y, z, (char*) "red", scaleX, 0.2f, scaleZ);
					numberOfReds++;
					break;
				case 3:
					newPlatform.setCoordinates(x, y, z, (char*) "orange", scaleX, 0.2f, scaleZ);
					numberOfOrange++;
					break;
				case 4:
					newPlatform.setCoordinates(x, y, z, (char*) "yellow", scaleX, 0.2f, scaleZ);
					numberOfYellow++;
					break;
				case 5:
					newPlatform.setCoordinates(x, y, z, (char*) "none", scaleX, 0.2f, scaleZ);
					break;
			}

				Obstacle newDiamond;
				std::string textureDiamond;
				int isHere = rand() % 4;

				if (isHere == 0) {
					int type = rand() % 2;

					switch(type) {
						case 0:
							textureDiamond = "diamond";
							break;
						case 1:
							textureDiamond = "diamond2";
							break;
					}


					float obstacleX = x + 0.5;
					float obstacleY = 0.5f;
					float obstacleZ = rand() % int(scaleZ) + z;
					newDiamond.setCoordinates(obstacleX, obstacleY,
										obstacleZ, 1, 1, 1, textureDiamond, "");
					goodObstacles.push_back(newDiamond);
				}


				std::string texture;
				std::string textureCube;
				int decoration = rand() % 5;
				float decorationX;
				if (decoration == 0) {
					int part = rand() % 2;
					if (part == 0) {
						decorationX = 8.5;
					} else {
						decorationX = -3.5;

					}


					int textureDecor = rand() % 3;

					switch(textureDecor) {
						case 0:
							texture = "green";
							break;
						case 1:
							texture = "green1";
							break;
						case 2:
							texture = "green2";
							break;
					}

					textureDecor = rand() % 2;

					switch(textureDecor) {
						case 0:
							textureCube = "brown1";
							break;
						case 1:
							textureCube = "brown2";
							break;
					}

					float decorationZ = rand() % int(scaleZ) + z - 10;
					float decorationY = 0;
					Obstacle decor;
					decor.setCoordinates(decorationX, decorationY,
										decorationZ, 1, 1, 1, texture, textureCube);
					decorations.push_back(decor);
			}

			int active = rand() % 5;
			if (color != 5) {
				if (active == 0) {
					//	newPlatform.setActiveObstacle(true);
						Obstacle newObstacle;

						float obstacleY = 0.2f;
						float obstacleZ = rand() % int(scaleZ) + z;
						int scale = rand() % 3;
						float obstacleX = x;
						float obstacleScale;
						switch (scale) {
							case 0:
								obstacleScale = 0.5;
								obstacleX += 0.275;
								break;
							case 1:
								obstacleScale = 0.75;
								obstacleX += 0.15;

								break;
							case 2:
								obstacleScale = 0.25;
								obstacleX += 0.4;

								break;
						}

						int textureType = rand() % 4;
						std::string obstacleTexture;
						switch (textureType) {
							case 0:
								obstacleTexture = "pig";
								break;
							case 1:
								obstacleTexture = "cow";
								break;
							case 2:
								obstacleTexture = "chicken";
								break;
							case 3:
								obstacleTexture = "sheep";
								break;
						}

						newObstacle.setCoordinates(obstacleX, obstacleY, obstacleZ,
							obstacleScale, obstacleScale, obstacleScale, obstacleTexture, "");
						obstacles.push_back(newObstacle);
				}
			}
		}

		// imi creez 3 platforme odata pe linie
		// asigurandu-ma ca nu ma aflu in cazul in care toate nu exista
		void newPlatforms(std::vector<Platform>& platforms, int& numberOfReds,
							int& numberOfOrange, int& numberOfYellow) {

			Platform platformLeft;
			createPlatform(platformLeft, platforms, platforms.size() - 3, numberOfReds,
									numberOfOrange, numberOfYellow);
			Platform platformMiddle;
			createPlatform(platformMiddle, platforms, platforms.size() - 2, numberOfReds,
									numberOfOrange, numberOfYellow);
			Platform platformRight;
			createPlatform(platformRight, platforms, platforms.size() - 1, numberOfReds,
									numberOfOrange, numberOfYellow);


			if (platformLeft.getColor() == "none" && platformMiddle.getColor() == "none"
													&& platformRight.getColor() == "none") {
				while (platformLeft.getColor() == "none") {
					createPlatform(platformLeft, platforms, platforms.size() - 3, numberOfReds,
									numberOfOrange, numberOfYellow);
				}
				while (platformMiddle.getColor() == "none") {
					createPlatform(platformMiddle, platforms, platforms.size() - 2, numberOfReds,
									numberOfOrange, numberOfYellow);
				}
				createPlatform(platformRight, platforms, platforms.size() - 1, numberOfReds,
									numberOfOrange, numberOfYellow);
			}


			platforms.push_back(platformLeft);
			platforms.push_back(platformMiddle);
			platforms.push_back(platformRight);
		}


		// creare matrice pentru fiecare componenta in parte
		void createSphereWhenSpecialPowerMatrix(glm::mat4& modelMatrix) {
			modelMatrix *= Tema3Transform3D::RotateOX(0.1);
			modelMatrix *= Tema3Transform3D::Scale(0.015f, 0.015f, 0.015f);
		}

		void createSphereWhenNormalMatrix(glm::mat4& modelMatrix, Element sphere) {
			modelMatrix *= Tema3Transform3D::Scale(sphere.getScaleX(),
																					sphere.getScaleY(), sphere.getScaleZ());
		}

		void createPowerBarFrontPartMatrix(Element& powerBar, glm::mat4& modelMatrix) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Tema3Transform3D::Translate(powerBar.getX(),
																							powerBar.getY(), powerBar.getZ());
			modelMatrix *= Tema3Transform3D::Scale(powerBar.getScaleX(),
																			powerBar.getScaleY(), powerBar.getScaleZ());
		}

		void createPowerBarBackPartMatrix(Element& powerBar, glm::mat4& modelMatrix) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Tema3Transform3D::Translate(powerBar.getX(),
																								powerBar.getY(), powerBar.getZ());
			modelMatrix *= Tema3Transform3D::Scale(0.65f, 0.65f, 0.f);
		}

		void createFrontPartMatrix(Element& element, glm::mat4& modelMatrix) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Tema3Transform3D::Translate(element.getX() + 0.05,
																											element.getY() + 0.05, element.getZ());
			modelMatrix *= Tema3Transform3D::Scale(element.getScaleX(), element.getScaleY(),
																																element.getScaleZ());
		}

		void createBackPartMatrix(Element& element, glm::mat4& modelMatrix) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Tema3Transform3D::Translate(element.getX(), element.getY(), element.getZ());
				modelMatrix *= Tema3Transform3D::Scale(2.6f, 0.5f, 0.f);
		}

		void createPlatformMatrix(std::vector<Platform> platforms, int i, glm::mat4& modelMatrix) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Tema3Transform3D::Translate(platforms[i].getX(),
																								platforms[i].getY(), platforms[i].getZ());
			modelMatrix *= Tema3Transform3D::Scale(platforms[i].getScaleX(),
																						platforms[i].getScaleY(), platforms[i].getScaleZ());
		}

		void createBackgroundFastMatrix(glm::mat4& modelMatrix) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Tema3Transform3D::Translate(+2, 0, camera->position.z - 6);
			modelMatrix *= Tema3Transform3D::Scale(0.7f, 0.7f, 0.7f);
		}


		// aplicarea efectelor platformelor pe care aterizeaza sfera asupra sa
		void platformPower(std::vector<Platform>& platforms, int i, bool& oneCollision,
											bool& onPlatform, Element& gas, bool& fastSpeed, float& timeFastSpeed) {

			if (platforms[i].getColor() != "none") {
				oneCollision = true;
				onPlatform = true;

				if (platforms[i].getColor() == "red") {
					std::cout << "The red platform killed you! Game over!" << std::endl;
				//	std::exit(1);
				}

				if (platforms[i].getColor() == "yellow") {
					std::cout << "You lost some gas because of the yellow platform." << std::endl;
					if (gas.getScaleX() > 0.1) {
						gas.setScaleX(gas.getScaleX() - 0.1);
					}
					if (gas.getScaleX() <= 0.1) {
						std::cout << "Insufficient gas! Game over!" << std::endl;
						exit(1);
					}
				}
				if (platforms[i].getColor() == "orange") {
					std::cout << "Fast speed!" << std::endl;
					fastSpeed = true;
					timeFastSpeed = 0;
				}

				if (platforms[i].getColor() == "green") {
					std::cout << "You got some gas because of the green platform." << std::endl;

					if (gas.getScaleX() < 2.5) {
						gas.setScaleX(gas.getScaleX() + 0.1);
					}
					specialPower = true;
				}
				platforms[i].setColor((char*) "purple");
			}
		}

		// verifica daca jocul se termina
		// in cazul in care sfera pica de pe platforma
		void checkEndGame(bool oneCollision, Element& sphere, bool& onPlatform,
										bool& stillInGame, float& stillInGameTime,
										float deltaTimeSeconds) {
			if (!oneCollision && !sphereJump && !moveLeft && !moveRight) {
				onPlatform = false;
				stillInGame = false;
			}

			if (!stillInGame) {
				stillInGameTime += deltaTimeSeconds;
				sphere.setScaleY(sphere.getScaleY() - 0.25 * deltaTimeSeconds);
				sphere.setY(sphere.getY() - 3 * deltaTimeSeconds);
				camera->TranslateUpword(-3 * deltaTimeSeconds);
				if (stillInGameTime > 1.5) {
					std::cout << "You fell. Game over!" << std::endl;
					std::exit(1);
				}
			}
		}

		// modifica viteza cu care se misca sfera si camera
		// existand cele doua metode:
		// 			- viteza aleasa de jucator
		//      - viteza impusa de platforma portocalie ce dureaza aproximativ 2 secunde
		void speed(bool& fastSpeed, Element& sphere, bool stillInGame,
											float& timeFastSpeed, bool& specialPower, float power,
											float deltaTimeSeconds) {

			if (fastSpeed == false && stillInGame) {
					sphere.setZ(sphere.getZ() - power * deltaTimeSeconds);
					camera->TranslateForward(power * deltaTimeSeconds);
					lightPosition.z -= power * deltaTimeSeconds;

			}
			if (fastSpeed == true && stillInGame) {
				sphere.setZ(sphere.getZ() - 16 * deltaTimeSeconds);
				camera->TranslateForward(16 * deltaTimeSeconds);
				lightPosition.z -= 16 * deltaTimeSeconds;
				timeFastSpeed += deltaTimeSeconds;

				if (timeFastSpeed > 2) {
					std::cout << "Normal speed!" << std::endl;
					fastSpeed = false;
					timeFastSpeed = 0;
					specialPower = false;
				}
			}
		}


		void initTexture() {
			const std::string textureLoc = "Source/Laboratoare/Tema3/Textures/";

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "moon.jpg").c_str(), GL_REPEAT);
				mapTextures["moon"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "gold.jpg").c_str(), GL_REPEAT);
				mapTextures["diamond"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "diamond2.jpg").c_str(), GL_REPEAT);
				mapTextures["diamond2"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "sheep.jpg").c_str(), GL_REPEAT);
				mapTextures["sheep"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "chicken.png").c_str(), GL_REPEAT);
				mapTextures["chicken"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "cow.jpg").c_str(), GL_REPEAT);
				mapTextures["cow"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "pig.png").c_str(), GL_REPEAT);
				mapTextures["pig"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "light.jpg").c_str(), GL_REPEAT);
				mapTextures["light"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "cube.png").c_str(), GL_REPEAT);
				mapTextures["cube"] = texture;
			}
			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "red.jpeg").c_str(), GL_REPEAT);
				mapTextures["red"] = texture;
			}
			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "blue.jpg").c_str(), GL_REPEAT);
				mapTextures["blue"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "heart.png").c_str(), GL_REPEAT);
				mapTextures["heart"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "yellow.jpg").c_str(), GL_REPEAT);
				mapTextures["yellow"] = texture;
			}
			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "orange.jpg").c_str(), GL_REPEAT);
				mapTextures["orange"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "green.jpg").c_str(), GL_REPEAT);
				mapTextures["green"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "purple.jpeg").c_str(), GL_REPEAT);
				mapTextures["purple"] = texture;
			}
			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "stick.jpg").c_str(), GL_REPEAT);
				mapTextures["stick"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "pyramide.png").c_str(), GL_REPEAT);
				mapTextures["pyra"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "green1.jpg").c_str(), GL_REPEAT);
				mapTextures["green1"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "yellow.jpeg").c_str(), GL_REPEAT);
				mapTextures["yellow1"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "purple1.jpeg").c_str(), GL_REPEAT);
				mapTextures["purple1"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "brown.jpg").c_str(), GL_REPEAT);
				mapTextures["brown1"] = texture;
			}
			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "brown.jpeg").c_str(), GL_REPEAT);
				mapTextures["brown2"] = texture;
			}
			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "green2.jpg").c_str(), GL_REPEAT);
				mapTextures["green2"] = texture;
			}

			{
				Texture2D* texture = new Texture2D();
				texture->Load2D((textureLoc + "white.png").c_str(), GL_REPEAT);
				mapTextures["white"] = texture;
			}
			{

				Texture2D* texture = new Texture2D();
				texture->Load2D("Resources/Models/Vegetation/Bamboo/bamboo.png", GL_REPEAT);
				mapTextures["bamboo"] = texture;

			}
		}
};
