#include <vector>
#include <iostream>

void createCube(std::vector<glm::vec3>& vertices,
	std::vector<glm::vec3>& normals,
	std::vector<glm::vec2>& textureCoords,
	std::vector<unsigned short>& indices, bool animals) {
	// PYRAMIDE

	float size = 1;
	vertices = {
		glm::vec3(0.f, 0.f, 0.f),	// 0
		glm::vec3(0.f, 0.f, size), // 1
		glm::vec3(size, 0, size), // 2
		glm::vec3(size, 0.f, 0.f), // 3

		glm::vec3(0.f, 0.f, 0.f), // 4
		glm::vec3(0.f, 0.f, size), // 5
		glm::vec3(0.f, size, 0), // 6
		glm::vec3(0.f, size, size), // 7

		glm::vec3(0.f, 0.f, 0.f), // 8
		glm::vec3(0.f, size, 0.f), // 9
		glm::vec3(size, size, 0.f), // 10
		glm::vec3(size, 0.f, 0.f), // 11

		glm::vec3(size, 0.f, 0.f), // 12
		glm::vec3(size, size, 0.f), // 13
		glm::vec3(size, size, size), // 14
		glm::vec3(size, 0.f, size), // 15

		glm::vec3(0.f, 0.f, size), // 16
		glm::vec3(size, 0.f, size), // 17
		glm::vec3(size, size, size), // 18
		glm::vec3(0.f, size, size), // 19


		glm::vec3(0.f, size, 0.f), // 20
		glm::vec3(0.f, size, size), // 21
		glm::vec3(size, size, size), // 22
		glm::vec3(size, size, 0), // 23
	};


	normals =
	{
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),

		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),

	};

	if (!animals) {
		textureCoords = {
			glm::vec2(1.0f, 1.0f), // 0
			glm::vec2(1.0f, 0.0f), // 1
			glm::vec2(0.0f, 0.0f), // 2
			glm::vec2(0.0f, 1.0f), // 3

			glm::vec2(1.0f, 1.0f), // 4
			glm::vec2(1.0f, 0.0f), // 5
			glm::vec2(0.0f, 1.0f), // 6
			glm::vec2(0.0f, 0.0f), // 7

			glm::vec2(1.0f, 1.0f), // 8
			glm::vec2(0.0f, 1.0f), // 9
			glm::vec2(0.0f, 0.0f), // 10
			glm::vec2(1.0f, 0.0f), // 11

			glm::vec2(1.0f, 1.0f), // 12
			glm::vec2(0.0f, 1.0f), // 13
			glm::vec2(0.0f, 0.0f), // 14
			glm::vec2(1.0f, 0.0f), // 15

			glm::vec2(0.0f, 0.0f), // 16
			glm::vec2(1.0f, 0.0f), // 17
			glm::vec2(1.0f, 1.0f), // 18
			glm::vec2(0.0f, 1.0f), // 19

			glm::vec2(0.0f, 1.0f), // 20
			glm::vec2(0.0f, 0.0f), // 21
			glm::vec2(1.0f, 0.0f), // 22
			glm::vec2(1.0f, 1.0f) // 23
		};
	 } else {
		textureCoords = {
			glm::vec2(0.0f, 0.0f), // 0
			glm::vec2(0.0f, 0.0f), // 1
			glm::vec2(0.0f, 0.0f), // 2
			glm::vec2(0.0f, 0.0f), // 3

			glm::vec2(0.0f, 0.0f), // 4
			glm::vec2(0.0f, 0.0f), // 5
			glm::vec2(0.0f, 0.0f), // 6
			glm::vec2(0.0f, 0.0f), // 7

			glm::vec2(0.0f, 0.0f), // 8
			glm::vec2(0.0f, 0.0f), // 9
			glm::vec2(0.0f, 0.0f), // 10
			glm::vec2(0.0f, 0.0f), // 11

			glm::vec2(0.0f, 0.0f), // 12
			glm::vec2(0.0f, 0.0f), // 13
			glm::vec2(0.0f, 0.0f), // 14
			glm::vec2(0.0f, 0.0f), // 15

			glm::vec2(0.0f, 1.0f), // 16
			glm::vec2(1.0f, 1.0f), // 17
			glm::vec2(1.0f, 0.0f), // 18
			glm::vec2(0.0f, 0.0f), // 19

			glm::vec2(0.0f, 0.0f), // 20
			glm::vec2(0.0f, 0.0f), // 21
			glm::vec2(0.0f, 0.0f), // 22
			glm::vec2(0.0f, 0.0f) // 23
		};
	}


	indices = {
		1,0,3,
		3,2,1,
		4,5,6,
		5,7,6,
		8,9,11,
		9,10,11,
		12,13,14,
		12,15,14,
		16,17,18,
		18,19,16,
		20,21,23,
		21,22,23,
	};
}

void createPyramide(std::vector<glm::vec3>& vertices,
	std::vector<glm::vec3>& normals,
	std::vector<glm::vec2>& textureCoords,
	std::vector<unsigned short>& indices) {
	// PYRAMIDE

	float size = 1.f;
	vertices = {
				glm::vec3(0.f, 0.f, 0.f),	// 0
				glm::vec3(0.f, 0.f,  -size), // 1
				glm::vec3(4 * size, 0.f,  -size), // 2
				glm::vec3(4 * size, 0.f,  0.f), // 3

				glm::vec3(0.f, 0.f, 0.f),	// 4
				glm::vec3(2 * size, 5 * size, - size / 2), // 5
				glm::vec3(4 * size, 0.f,  0.f), // 6

				glm::vec3(0.f, 0.f, 0.f),	// 7
				glm::vec3(0.f, 0.f,  -size), // 8
				glm::vec3(2 * size, 5 * size, - size / 2), // 9


				glm::vec3(0.f, 0.f,  -size), // 10
				glm::vec3(4 * size, 0.f,  -size), // 11
				glm::vec3(2 * size, 5 * size, - size / 2), // 12

				glm::vec3(4 * size, 0.f,  0.f), // 13
				glm::vec3(4 * size, 0.f,  -size), // 14
				glm::vec3(2 * size, 5 * size, - size / 2), // 15

	};


	normals = {

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 0, 0),

		glm::vec3(0, 1, 0), // 10
		glm::vec3(1, 0, 0), // 11
		glm::vec3(1, 0, -1), // 12

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0),

	};

	textureCoords = {
		glm::vec2(0.0f, 0.0f), // 0
		glm::vec2(0.0f, 1.0f), // 1
		glm::vec2(1.0f, 1.0f), // 2
		glm::vec2(1.0f, 0.0f), // 3

		glm::vec2(0.0f, 0.0f), // 4
		glm::vec2(0.5f, 1.0f), // 5
		glm::vec2(1.0f, 0.0f), // 6

		glm::vec2(0.0f, 0.0f), // 7
		glm::vec2(1.0f, 0.0f), // 8
		glm::vec2(0.5f, 1.0f), // 9

		glm::vec2(0.0f, 0.0f), // 10
		glm::vec2(1.0f, 0.0f), // 11
		glm::vec2(0.5f, 1.0f), // 12

		glm::vec2(0.0f, 0.0f), // 13
		glm::vec2(1.0f, 0.0f), // 14
		glm::vec2(0.5f, 1.0f), // 15

	};

	indices = {
		0,1,2,
		1,2,3,
		4,5,6,
		7,8,9,
		10,11,12,
		13,14,15,
	};
}



void createDiamond(std::vector<glm::vec3>& vertices,
	std::vector<glm::vec3>& normals,
	std::vector<glm::vec2>& textureCoords,
	std::vector<unsigned short>& indices) {

	float size =  0.35f;
	vertices = {
		glm::vec3(0.f, 0.f, -size / 2),	// 0
		glm::vec3(-size, size,  0), // 1
		glm::vec3(size, size, 0), // 2

		glm::vec3(0.f, 0.f, - size / 2),	// 3
		glm::vec3(size, size, 0), // 4
		glm::vec3(size, size, - size), // 5

		glm::vec3(0.f, 0.f, -size / 2),	// 6
		glm::vec3(size, size, - size), // 7
		glm::vec3(-size, size,  -size), // 8

		glm::vec3(-size, size,  -size), // 9
		glm::vec3(-size, size,  0), // 10
		glm::vec3(0.f, 0.f, - size / 2),	// 11

		glm::vec3(-size, size,  0), // 12
		glm::vec3(size, size, 0), // 13
		glm::vec3(0,  1.5 * size, -size / 2), // 14

		glm::vec3(size, size, 0), // 15
		glm::vec3(size, size, - size), // 16
		glm::vec3(0,  1.5 * size, -size / 2), // 17

		glm::vec3(size, size, - size), // 18
		glm::vec3(-size, size,  -size), // 19
		glm::vec3(0,  1.5 * size, -size / 2), // 20

		glm::vec3(-size, size,  -size), // 21
		glm::vec3(-size, size,  0), // 22
		glm::vec3(0,  1.5 * size, -size / 2), // 23

	};


	normals = {
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
	};

	textureCoords = {
		glm::vec2(0.5f, 0.0f), // 0
		glm::vec2(0.0f, 1.0f), // 1
		glm::vec2(1.0f, 1.0f), // 2

		glm::vec2(0.5f, 0.0f), // 3
		glm::vec2(0.0f, 1.0f), // 4
    glm::vec2(1.0f, 1.0f), // 5

		glm::vec2(0.5f, 0.0f), // 6
		glm::vec2(1.0f, 1.0f), // 7
    glm::vec2(0.0f, 1.0f), // 8

		glm::vec2(1.0f, 1.0f), // 9
		glm::vec2(0.0f, 1.0f), // 10
    glm::vec2(0.5f, 0.0f) ,// 11

		glm::vec2(0.0f, 0.0f), // 12
		glm::vec2(1.0f, 0.0f), // 13
    glm::vec2(0.5f, 1.0f), // 14

		glm::vec2(0.0f, 0.0f), // 15
		glm::vec2(1.0f, 0.0f), // 16
    glm::vec2(0.5f, 1.0f), // 17

		glm::vec2(1.0f, 0.0f), // 18
		glm::vec2(0.0f, 0.0f), // 19
    glm::vec2(0.5f, 1.0f), // 20

		glm::vec2(0.0f, 0.0f), // 21
		glm::vec2(1.0f, 0.0f), // 22
		glm::vec2(0.5f, 1.0f), // 23

	};

	indices = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
    18, 19, 20,
    21, 22, 23,
	};
};
