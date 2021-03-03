#pragma once

#include <string>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <math.h>


class Obstacle {
  private:
    float x;
    float y;
    float z;
    float scaleX;
    float scaleY;
    float scaleZ;
    std::string texture;
    std::string textureTwo;
    bool goDown = false;
    bool goRight = false;


  public:
    Obstacle() {}
    ~Obstacle() {}


    void setCoordinates(float x, float y, float z,
          float scaleX, float scaleY, float scaleZ, std::string texture, std::string textureTwo) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->scaleX = scaleX;
      this->scaleY = scaleY;
      this->scaleZ = scaleZ;
      this->texture = texture;
      this->textureTwo = textureTwo;

    }

    std::string getTexture() {
      return this->texture;
    }

    std::string gettextureTwo() {
      return this->textureTwo;
    }

    bool getGoDown() {
      return this->goDown;
    }

    void setGoDown(bool down) {
      this->goDown = down;
    }

    bool getGoRight() {
      return this->goRight;
    }

    void setGoRight(bool down) {
      this->goRight = down;
    }

    float getScaleX() {
      return this->scaleX;
    }
    float getScaleY() {
      return this->scaleY;
    }
    float getScaleZ() {
      return this->scaleZ;
    }

    float getX() {
      return this->x;
    }

    float getY() {
      return this->y;
    }

    float getZ() {
      return this->z;
    }

    void setScaleX(float scaleX) {
      this->scaleX = scaleX;
    }

    void setScaleY(float scaleY) {
      this->scaleY = scaleY;
    }

    void setScaleZ(float scaleZ) {
      this->scaleZ = scaleZ;
    }


    void setX(float x) {
      this->x = x;
    }

    void setY(float y) {
      this->y = y;
    }

    void setZ(float z) {
      this->z = z;
    }
};

class Element {
  private:
    float x;
    float y;
    float z;
    float scaleX;
    float scaleY;
    float scaleZ;

  public:
    Element() {}
    ~Element() {}


    void setCoordinates(float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->scaleX = scaleX;
      this->scaleY = scaleY;
      this->scaleZ = scaleZ;
    }

    float getScaleX() {
      return this->scaleX;
    }
    float getScaleY() {
      return this->scaleY;
    }
    float getScaleZ() {
      return this->scaleZ;
    }

    float getX() {
      return this->x;
    }

    float getY() {
      return this->y;
    }

    float getZ() {
      return this->z;
    }

    void setScaleX(float scaleX) {
      this->scaleX = scaleX;
    }

    void setScaleY(float scaleY) {
      this->scaleY = scaleY;
    }

    void setScaleZ(float scaleZ) {
      this->scaleZ = scaleZ;
    }


    void setX(float x) {
      this->x = x;
    }

    void setY(float y) {
      this->y = y;
    }

    void setZ(float z) {
      this->z = z;
    }
};


class Platform {
  private:
    float x;
    float y;
    float z;
    bool stillInGame = true;
    float scaleX;
    float scaleY;
    float scaleZ;
    char* color;
  //  bool activeObstacle =  false;
  //  float obstacleX = 0;
  //  float obstacleY = 0;
  //  float obstacleZ = 0;
  //  float obstacleScale = 0;





  public:
    Platform(){}
    ~Platform() {}

  void setCoordinates(float x, float y, float z, char* color, float scaleX, float scaleY, float scaleZ) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->color = color;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
  }





  /*void setObstacle(float x, float y, float z, float scale) {
    this->obstacleX = x;
    this->obstacleY = y;
    this->obstacleZ = z;
    this->obstacleScale = scale;
  }*/


//  void setObstacleX(float x) {
  //  this->obstacleX = x;
  //}

  char* getColor() {
    return this->color;
  }

  /*float getObstacleX() {
    return this->obstacleX;
  }

  float getObstacleY() {
    return this->obstacleY;
  }

  float getObstacleZ() {
    return this->obstacleZ;
  }

  float getObstacleScale() {
    return this->obstacleScale;
  }

  void setActiveObstacle(bool activeObstacle) {
    this->activeObstacle = activeObstacle;
  }

  bool getActiveObstacle() {
    return this->activeObstacle;
  }*/

  void setColor(char* color) {
    this->color = color;
  }

  float getScaleX() {
    return this->scaleX;
  }

  float getScaleY() {
    return this->scaleY;
  }

  float getScaleZ() {
    return this->scaleZ;
  }

  float getX() {
    return this->x;
  }

  float getY() {
    return this->y;
  }

  float getZ() {
    return this->z;
  }

  float getStillInGame() {
    return this->stillInGame;
  }

  void setZ(float z) {
    this->z = z;
  }

  void setStillInGame(bool stillInGame) {
    this->stillInGame = stillInGame;
  }
};

class Decoration {
  private:
    float x;
    float y;
    float z;
    float scaleX;
    float scaleY;
    float scaleZ;
    std::string texture;
    std::string textureTwo;

  public:
    Decoration() {}
    ~Decoration() {}


    void setCoordinates(float x, float y, float z,
          float scaleX, float scaleY, float scaleZ, std::string texture, std::string texture2) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->scaleX = scaleX;
      this->scaleY = scaleY;
      this->scaleZ = scaleZ;
      this->texture = texture;
      this->textureTwo = texture;
    }

    std::string getTexture() {
      return this->texture;
    }

    std::string gettextureTwo() {
      return this->textureTwo;
    }


    float getScaleX() {
      return this->scaleX;
    }
    float getScaleY() {
      return this->scaleY;
    }
    float getScaleZ() {
      return this->scaleZ;
    }

    float getX() {
      return this->x;
    }

    float getY() {
      return this->y;
    }

    float getZ() {
      return this->z;
    }

    void setScaleX(float scaleX) {
      this->scaleX = scaleX;
    }

    void setScaleY(float scaleY) {
      this->scaleY = scaleY;
    }

    void setScaleZ(float scaleZ) {
      this->scaleZ = scaleZ;
    }

    void setX(float x) {
      this->x = x;
    }

    void setY(float y) {
      this->y = y;
    }

    void setZ(float z) {
      this->z = z;
    }
};
