#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Tema3Transform3D.h"
#include "ClassesTema3.h"
#include <vector>
#include <include/glm.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Objects.h"

using namespace std;

Tema3::Tema3() {}

Tema3::~Tema3() {}

void Tema3::Init() {

	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> textureCoords;
	std::vector<unsigned short> indices;

	lightPosition = glm::vec3(12.3, 8, -10);
	lightPosition2 = glm::vec3(3, 1, -5);
	lightPosition3 = glm::vec3(5.9, 1, -5);
	lightPosition4 = glm::vec3(3, 1, -10);
	lightPosition5 = glm::vec3(5.9, 1, -10);

	lightPositions.push_back(lightPosition2);
	lightPositions.push_back(lightPosition3);
	lightPositions.push_back(lightPosition4);
	lightPositions.push_back(lightPosition5);
	lightDirection = glm::vec3(0, -1, 0);
	materialShininess = 30;
	materialKd = 0.5;
	materialKs = 0.5;

	// introducere texturi
	initTexture();
	camera = new Tema::Camera();

	{
		createCube(vertices, normals, textureCoords, indices, false);
		Mesh* mesh = new Mesh("cube");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		createCube(vertices, normals, textureCoords, indices, true);
		Mesh* mesh = new Mesh("animals");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		createPyramide(vertices, normals, textureCoords, indices);
		Mesh* mesh = new Mesh("pira");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		createDiamond(vertices, normals, textureCoords, indices);
		Mesh* mesh = new Mesh("diamond");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// SFERA
	Mesh* mesh = new Mesh("sphere");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[mesh->GetMeshID()] = mesh;

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// inițializări
	gas.setCoordinates(-3.7f, 1.95f, -5.f, 2.5f, 0.4f, 0.f);
	powerBar.setCoordinates(-2.6f, 1.3f, -3.f, 0.1f, 0.1f, 0.f);
	sphere.setCoordinates(2.5f, 0.5f, -3.f, 0.7f, 0.7f, 0.7f);
	score_bar.setCoordinates(+4.2f, -0.5f, -5.f, 0.5f, 0.1f, 0.f);
	initPlatforms(platforms);
	numberOfPlatforms = 3;

	Element heart;
	heart.setCoordinates(+4.7f, -1.f, -5.f, 0.35f, 0.35f, 0.01f);
	hearts.push_back(heart);
	heart.setCoordinates(+4.3f, -1.f, -5.f, 0.35f, 0.35f, 0.01f);
	hearts.push_back(heart);
	heart.setCoordinates(+3.9f, -1.f, -5.f, 0.35f, 0.35f, 0.01f);
	hearts.push_back(heart);



	{
		Shader *shader = new Shader("ShaderTema3");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}


	{
		Shader *shader = new Shader("ShaderTema3Texture");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader2.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader2.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("ShaderTema3Light");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderLight.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderLight.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}


void Tema3::FrameStart() {
}

void Tema3::Update(float deltaTimeSeconds) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema3Transform3D::Translate(sphere.getX(), sphere.getY(), sphere.getZ());

	// folosita atunci cand se trece in timpul sariturii intre perspective
	if (thirdPerson && startedFirst && stillInGame) {
		doJumpFirstPerson(sphere, deltaTimeSeconds, startedFirst, inAir);
		camera->TranslateUpword(2 * deltaTimeSeconds);
	}

	if (!thirdPerson && startedThird && stillInGame) {
		doJumpThirdPerson(modelMatrix, jumpAngle, sphereJump, sphere, deltaTimeSeconds, thirdPerson, startedThird);
		camera->TranslateForward(4.5 * deltaTimeSeconds);
	}

	// muta sfera in directia corespunzatoare
	if (stillInGame) {
		if (thirdPerson) {
			if (sphereJump && !startedFirst) {
				startedThird = true;
				doJumpThirdPerson(modelMatrix, jumpAngle, sphereJump, sphere, deltaTimeSeconds, thirdPerson, startedThird);
			}
		} else {
			if (sphereJump && !startedThird) {
				startedFirst = true;
				doJumpFirstPerson(sphere, deltaTimeSeconds, startedThird, inAir);
			}
		}

		if (moveLeft) {
			doMoveLeft(modelMatrix, moveLeftAngle, moveLeft, sphere, deltaTimeSeconds, thirdPerson);
		}
		if (moveRight) {
			doMoveRight(modelMatrix, moveRightAngle, moveRight, sphere, deltaTimeSeconds,thirdPerson);
		}
	}

	// roteste sfera atunci cand cade
	if (!stillInGame) {
		specialPower = false;
		modelMatrix *= Tema3Transform3D::RotateOY(angleNotInGame);
		angleNotInGame += 2 * deltaTimeSeconds;
	}

	// se afiseaza sfera
	if (specialPower == true) {
		createSphereWhenSpecialPowerMatrix(modelMatrix);
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema3"], modelMatrix, 1.f, 1);
	} else {
		createSphereWhenNormalMatrix(modelMatrix, sphere);
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema3"], modelMatrix, 0.f, 1);
	}

	// se afiseaza sfera pentru viteza folosita de utilizator
	createPowerBarFrontPartMatrix(powerBar, modelMatrix);
	RenderMySimpleMesh(meshes["sphere"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["purple1"], true);

	createPowerBarBackPartMatrix(powerBar, modelMatrix);
	RenderMySimpleMesh(meshes["sphere"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["purple"], true);

	// se afiseaza bara de combustibil
	createFrontPartMatrix(gas, modelMatrix);
	RenderMySimpleMesh(meshes["cube"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["purple1"], true);

	createBackPartMatrix(gas, modelMatrix);
	RenderMySimpleMesh(meshes["cube"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["red"], true);


	// se afiseaza bara de scor
	createFrontPartMatrix(score_bar, modelMatrix);
	RenderMySimpleMesh(meshes["cube"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["purple1"], true);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema3Transform3D::Translate(score_bar.getX(), score_bar.getY(), score_bar.getZ());
	modelMatrix *= Tema3Transform3D::Scale(0.6f, 2.2f, 0.f);
	RenderMySimpleMesh(meshes["cube"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["yellow1"], true);

	// se afiseaza vietile
	for (int i = 0; i < numberOfHearts; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema3Transform3D::Translate(hearts[i].getX(), hearts[i].getY(), hearts[i].getZ());
		modelMatrix *= Tema3Transform3D::Scale(hearts[i].getScaleX(), hearts[i].getScaleY(), hearts[i].getScaleZ());
		RenderMySimpleMesh(meshes["animals"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["heart"], true);
	}

	// imi afisez platformele
	for (int i = 1; i < platforms.size(); i++) {
		createPlatformMatrix(platforms, i, modelMatrix);
		if (platforms[i].getColor() != "none") {
			RenderMeshTexture(meshes["cube"], shaders["ShaderTema3Texture"], false,
			false, modelMatrix, mapTextures[platforms[i].getColor()], NULL, glm::vec3(1,0,0));
		}

	}

	platformTime += deltaTimeSeconds;
	// numarul maxim de platforme din scena sunt 27
	// acestea le includ si pe cele ce se afla in spatele camerei
	// nesterse inca din vectorul de platforme
	while (numberOfPlatforms < 27) {
		newPlatforms(platforms, numberOfReds, numberOfOrange, numberOfYellow);
		numberOfPlatforms += 3;
	}

	timeBadStuff += deltaTimeSeconds;

	if (gas.getScaleX() < 1.5) {
		maxTimeBadStuff = 4;
	} else {
		maxTimeBadStuff = 2;
	}
	if (timeBadStuff > maxTimeBadStuff) {
		// adauga o noua posibilitate de a avea o noua
		// platforma cu caracter negativ in scena
		maxNumberOfReds += 1;
		maxNumberOfYellow += 1;
		maxNumberOfOrange += 1;
		timeBadStuff = 0;
	}

	if (specialPower == true) {
		specialPowerTime += deltaTimeSeconds;
		// puterea speciala de deformare ramane valabila un timp mic
		// (mai putin de o secunda aproximativ)
		if (specialPowerTime > 0.75) {
			specialPower = false;
			specialPowerTime = 0;
		}
	}
	gasTime += deltaTimeSeconds;
	// dupa 3 secunde aproximativ va scadea cantitatea de combustibil
	if (gasTime > 3.f) {
		gasTime = 0;
		std::cout << "You lost some gas because of the time." << std::endl;

		if (gas.getScaleX() > 0.2) {
 				gas.setScaleX(gas.getScaleX() - 0.1);
		}	else {
				cout << "Insufficient gas! Game over!" << endl;
				exit(1);
		}
	}

	// sterge platformele nevizibile in scena
	deletePlatforms(platforms, numberOfPlatforms, sphere);

	// misca camera si sfera

	speed(fastSpeed, sphere, stillInGame, timeFastSpeed, specialPower, power, deltaTimeSeconds);

	// coliziune
	bool oneCollision = false;
	for (int i = 0; i < platforms.size(); i++) {
	 	if (collision(platforms, i, sphere) && moveLeft == false &&
															moveRight == false && sphereJump == false) {
			platformPower(platforms, i, oneCollision, onPlatform, gas, fastSpeed, timeFastSpeed);
		}
	}


	// verifica daca bila a cazut de pe platforma
	//checkEndGame(oneCollision, sphere,onPlatform, stillInGame, stillInGameTime, deltaTimeSeconds);


	// afișare elemente decorative
	for (int i = 0; i < decorations.size(); i++) {
		modelMatrix =  glm::mat4(1);
		modelMatrix *= Tema3Transform3D::Translate(decorations[i].getX(), decorations[i].getY(), decorations[i].getZ());

		RenderMeshTexture(meshes["pira"], shaders["ShaderTema3Texture"], false, false,
			modelMatrix, mapTextures[decorations[i].getTexture()], NULL, glm::vec3(1,1,0));

		if (decorations[i].getX() < 0) {
			modelMatrix *= Tema3Transform3D::Translate(1.5, -1, -1);
		} else {
			modelMatrix *= Tema3Transform3D::Translate(1.5, -1, -1);
		}
		RenderMeshTexture(meshes["cube"], shaders["ShaderTema3Texture"], false,
		false, modelMatrix, mapTextures[decorations[i].gettextureTwo()], NULL, glm::vec3(1,0,1));
	}

	int numberOfDecorations = decorations.size();
	deleteObstacles(decorations, numberOfDecorations, sphere);



	// coliziunea cu diamantele
	int diamonds = goodObstacles.size();
	for (int i = 0; i < diamonds; i++) {
			if (collisionWithDiamonds(goodObstacles, i, sphere)) {
				if (score_bar.getScaleY() < maxScoreScale) {
					score_bar.setScaleY(score_bar.getScaleY() + 0.5);
				}

				if (score_bar.getScaleY() >= maxScoreScale) {
					numberOfHearts++;
					score_bar.setScaleY(0.1);
				}

				goodObstacles.erase(goodObstacles.begin() + i);
				i--;
				diamonds--;
			}
	}

	// miscarea fiecarui tip de diamant
	for (int i = 0; i < goodObstacles.size(); i++) {
		if (goodObstacles[i].getTexture().compare("diamond") == 0) {


			if (!goodObstacles[i].getGoDown()) {
				goodObstacles[i].setY(goodObstacles[i].getY() + deltaTimeSeconds);
			} else {
				goodObstacles[i].setY(goodObstacles[i].getY() - deltaTimeSeconds);
			}

			if (goodObstacles[i].getY() > 1.2f) {
				goodObstacles[i].setGoDown(true);
			}

			if (goodObstacles[i].getY() < 0.2f) {
				goodObstacles[i].setGoDown(false);

			}
		} else {

			if (goodObstacles[i].getX() == 6.5) {
				goodObstacles[i].setGoRight(true);
			}

			if (goodObstacles[i].getX() == 2.5) {
				goodObstacles[i].setGoRight(false);
			}

			if (!goodObstacles[i].getGoRight() && timeGo > 3) {
				goodObstacles[i].setX(goodObstacles[i].getX() + 2);
				timeGo = 0;
			} else if (goodObstacles[i].getGoRight() && timeGo > 3) {
				goodObstacles[i].setX(goodObstacles[i].getX() - 2);
				timeGo = 0;
			}
			timeGo += deltaTimeSeconds;

		}
	}


	// afișarea diamantelor
	for (int i = 0; i < goodObstacles.size(); i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema3Transform3D::Translate(goodObstacles[i].getX(), goodObstacles[i].getY(), goodObstacles[i].getZ());
		RenderMeshTexture(meshes["diamond"], shaders["ShaderTema3Texture"],
		false, false, modelMatrix, mapTextures[goodObstacles[i].getTexture()], NULL, glm::vec3(1,0,1));
	}

	// ștergerea diamantelor ce ies din scenă
	int numberOfDiamonds = goodObstacles.size();
	deleteObstacles(goodObstacles, numberOfDiamonds, sphere);

	// coliziune și afișare obstacole
	collisionNumber = 0;
	for (int i = 0; i < obstacles.size(); i++) {
		if (collisionWithObstacles(obstacles, i, sphere)) {

			if (!collisionObstacle) {
				if (numberOfHearts > 0) {
					numberOfHearts--;
				}
				if (numberOfHearts == 0) {
					cout << "Game over! You lost your hearts!" << endl;
					exit(1);
				}
			}

			collisionNumber++;
			collisionObstacle = true;
		}

		modelMatrix =  glm::mat4(1);
		modelMatrix *= Tema3Transform3D::Translate(obstacles[i].getX(), obstacles[i].getY(), obstacles[i].getZ());
		modelMatrix *= Tema3Transform3D::Scale(obstacles[i].getScaleX(), obstacles[i].getScaleY(), obstacles[i].getScaleZ());
		RenderMeshTexture(meshes["animals"], shaders["ShaderTema3Texture"],
		false, false, modelMatrix, mapTextures[obstacles[i].getTexture()], NULL, glm::vec3(1, 0, 0));
	}

	if (collisionNumber == 0) {
		collisionObstacle = false;
	}

	// ștergere obstacole ce ies din scenă
	int numberOfObstacles = obstacles.size();
	deleteObstacles(obstacles, numberOfObstacles, sphere);

	// afișare lună
	modelMatrix = glm::mat4(1);
	modelMatrix *= Tema3Transform3D::Translate(lightPosition.x, lightPosition.y, lightPosition.z);
	modelMatrix *= Tema3Transform3D::Scale(1.5f, 1.5f, 1.5f);
	RenderMySimpleMesh(meshes["sphere"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["moon"], false);

	// afișare felinare
	for (int i = 0; i < lightPositions.size(); i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema3Transform3D::Translate(lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);
		modelMatrix *= Tema3Transform3D::Scale(0.5f, 0.5f, 0.5f);
		RenderMySimpleMesh(meshes["sphere"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["light"], false);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema3Transform3D::Translate(lightPositions[i].x, lightPositions[i].y - 1.2, lightPositions[i].z);
		modelMatrix *= Tema3Transform3D::Scale(0.1f, 1.f, 0.1f);
		RenderMySimpleMesh(meshes["cube"], shaders["ShaderTema3Light"], modelMatrix, mapTextures["stick"], false);
	}

	// modificare poziții felinare, dacă ies din scenă
	if (lightPositions[3].z > sphere.getZ() + distanceBetweenSphereAndCamera) {
		lightPositions[0].z = decorations[decorations.size() - 1].getZ();
		lightPositions[1].z = decorations[decorations.size() - 1].getZ();
		lightPositions[2].z = decorations[decorations.size() - 1].getZ() - 5;
		lightPositions[3].z = decorations[decorations.size() - 1].getZ() - 5;

		lightPosition2.z = decorations[decorations.size() - 1].getZ();
		lightPosition3.z = decorations[decorations.size() - 1].getZ();
		lightPosition4.z = decorations[decorations.size() - 1].getZ() - 5;
		lightPosition5.z = decorations[decorations.size() - 1].getZ() - 5;
	}

}

void Tema3::FrameEnd() {}

void Tema3::OnInputUpdate(float deltaTime, int mods) {
	if (window->KeyHold(GLFW_KEY_A)) {
		if (onPlatform) {
			moveLeft = true;
			onPlatform = false;
		}
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		if (onPlatform) {
			moveRight = true;
			onPlatform = false;
		}
	}

	if (window->KeyHold(GLFW_KEY_SPACE)) {
		if (onPlatform || moveRight || moveLeft) {
			sphereJump = true;
			onPlatform = false;
		}
	}

}

void Tema3::OnKeyPress(int key, int mods) {

	if (window->KeyHold(GLFW_KEY_C)) {
		if (thirdPerson) {
			camera->setPosition(glm::vec3(sphere.getX(), sphere.getY() + 0.25, sphere.getZ() - 0.35));
			thirdPerson = false;
		} else {
			if (stillInGame) {
				camera->setPosition(glm::vec3(4.5f, 1.35f, sphere.getZ() + distanceBetweenSphereAndCamera));
			} else {
				camera->setPosition(glm::vec3(4.5f, sphere.getY() + 0.25, sphere.getZ() + distanceBetweenSphereAndCamera));
			}
			thirdPerson = true;

		}
	}

	if (window->KeyHold(GLFW_KEY_W)) {
		if (fastSpeed) {
			cout << "You can't change the speed in Fast Mode!" << endl;
		} else {
			if (powerBar.getScaleX() < 0.6) {
				powerBar.setScaleX(powerBar.getScaleX() + 0.1);
				powerBar.setScaleY(powerBar.getScaleY() + 0.1);
				power += 0.75;
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (fastSpeed) {
			cout << "You can't change the speed in Fast Mode!" << endl;
		} else {
			if (powerBar.getScaleX() > 0.2) {
				powerBar.setScaleX(powerBar.getScaleX() - 0.1);
				powerBar.setScaleY(powerBar.getScaleY() - 0.1);
				power -= 0.75;
			}
		}
	}
}

void Tema3::OnKeyRelease(int key, int mods) {}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema3::OnWindowResize(int width, int height) {}
