#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <string>

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
  float pos;
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
  void IUpdate::update() override final {
    std::printf("hero (id %d) at pos (%f) update method called\n", id, pos);
  }
  void IDrawable::draw() override final { std::printf("hero draw method called\n"); }
  void ICollide::onHit(unsigned char force, bool isDamaging) override final {
    std::printf("hero with health %d hit with force %d and damage flag %d\n",
                health, force, isDamaging);
  }
};

struct Box : Object, IUpdate, IDrawable, ICollide {
  Box() {
    this->health = 5;
    this->otype = Object::TYPE::BOX;
  }
  void IUpdate::update() override final {
    std::printf("box (id %d) at pos (%f) update method called\n", id,
                pos);
  }
  void IDrawable::draw() override final { std::printf("box draw method called\n"); }
  void ICollide::onHit(unsigned char force, bool isDamaging) override final {
    std::printf("box with health %d hit with force %d and damage flag %d\n",
                health, force, isDamaging);
  }
};
