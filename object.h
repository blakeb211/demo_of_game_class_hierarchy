#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <string>

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

// Triangle struct
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

// @TODO: may decide to focus on simplicity and avoid encapsulation by making
// TotalObjectCount a public variable. Otherwise, I should just make 'id' field
// private and add getters + setters
struct Object {
  enum class TYPE { UNSPECIALIZED_OBJECT, HERO, BOX };

  Object() : id{TotalObjectCount++}, otype{0} {}
  TYPE otype;
  Vec3 pos;
  unsigned long int id;
  unsigned int long getTotalObjCount() { return TotalObjectCount; }
  void decreaseTotalObjCount() { TotalObjectCount--; }

 private:
  static unsigned long int TotalObjectCount;
};

// must define static member variable outside of class
unsigned long int Object::TotalObjectCount = 0;

auto magic(Object::TYPE e) noexcept {
  // constexpr
  const std::map<Object::TYPE, const char*> MyEnumStrings{
      {Object::TYPE::UNSPECIALIZED_OBJECT,
       "Object::TYPE::UNSPECIALIZED_OBJECT"},
      {Object::TYPE::HERO, "Object::TYPE::HERO"},
      {Object::TYPE::BOX, "Object::TYPE::BOX"}};
  auto it = MyEnumStrings.find(e);
  return it == MyEnumStrings.end() ? "Value not part of Object::TYPE"
                                   : it->second;
}

// @DESIGN: prefer multiple inheritance of interfaces (abstract clases of pure
// virtuals) and only single level basic inheritance
struct Hero : Object, IUpdate, IDrawable, ICollide {
  Hero() {
    this->health = 100;
    this->otype = Object::TYPE::HERO;
  }
  void IUpdate::update() {
    std::printf("hero (id %d) at pos (%s) update method called\n", id,
                pos.toString().c_str());
  }
  void IDrawable::draw() { std::printf("hero draw method called\n"); }
  void ICollide::onHit(unsigned char force, bool isDamaging) {
    std::printf("hero with health %d hit with force %d and damage flag %d\n",
                health, force, isDamaging);
  }
};

struct Box : Object, IUpdate, IDrawable, ICollide {
  Box() {
    this->health = 5;
    this->otype = Object::TYPE::BOX;
  }
  void IUpdate::update() {
    std::printf("box (id %d) at pos (%s) update method called\n", id,
                pos.toString().c_str());
  }
  void IDrawable::draw() { std::printf("box draw method called\n"); }
  void ICollide::onHit(unsigned char force, bool isDamaging) {
    std::printf("box with health %d hit with force %d and damage flag %d\n",
                health, force, isDamaging);
  }
};