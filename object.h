#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <string_view>

struct Vec3 {
  Vec3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }
  Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Vec3(Vec3& otherVec) {
    this->x = otherVec.x;
    this->y = otherVec.y;
    this->z = otherVec.z;
  }
  std::string toString();
  float x, y, z;
};

std::string Vec3::toString() {
  char buf[100];
  std::sprintf(buf, "x %f y %f z %f", this->x, this->y, this->z);

  std::string s = std::string(buf);
  return s;
}

struct Tri {
  Vec3 vert[3];
};

struct ICollide {
  ICollide() : health{0} {}
  virtual void onHit(unsigned char, bool) = 0;
  unsigned char health;
};

struct IUpdate {
  virtual void update() = 0;
};

struct IDrawable {
  virtual void draw() = 0;
};

struct Object {
  Object() : id{TotalObjectCount++} {}
  Vec3 pos;
  unsigned long int id;
  static unsigned long int TotalObjectCount;
};

unsigned long int Object::TotalObjectCount = 0;

struct Hero : Object, IUpdate, IDrawable, ICollide {
  Hero() { this->health = 100; }
  void update() {
    std::printf("hero (id %d) at pos (%s) update method called\n", id,
                pos.toString().c_str());
  }
  void draw() { std::printf("hero draw method called\n"); }
  void onHit(unsigned char force, bool isDamaging) {
    std::printf("hero with health %d hit with force %d and damage flag %d\n",
                health, force, isDamaging);
  }
};

struct Box : Object, IUpdate, IDrawable, ICollide {
  Box() { this->health = 5; }
  void update() {
    std::printf("box (id %d) at pos (%s) update method called\n", id,
                pos.toString().c_str());
  }
  void draw() { std::printf("box draw method called\n"); }
  void onHit(unsigned char force, bool isDamaging) {
    std::printf("box with health %d hit with force %d and damage flag %d\n",
                health, force, isDamaging);
  }
};