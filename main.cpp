#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "object.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
  Hero h{};
  Box box{};
  Box box2{};
  Vec3 v{2, 4, 6};
  Vec3 v2{1, 2, 3};
  box.pos = v;
  h.pos = v2;

  {
    using std::vector;
    vector<Object*> ent{};
    ent.push_back(&h);
    ent.push_back(&box);
    ent.push_back(&box2);

    vector<IDrawable*> stuff_to_draw{};
    stuff_to_draw.push_back(&h);
    stuff_to_draw.push_back(&box);
    stuff_to_draw.push_back(&box2);

    vector<IUpdate*> stuff_to_update{};
    stuff_to_update.push_back(&h);
    stuff_to_update.push_back(&box);
    stuff_to_update.push_back(&box2);

    vector<ICollide*> stuff_to_collide{};
    stuff_to_collide.push_back(&h);
    stuff_to_collide.push_back(&box);
    stuff_to_collide.push_back(&box2);

    for (const auto& i : stuff_to_draw) {
      i->draw();
    }

    for (const auto& i : stuff_to_update) {
      i->update();
    }

    for (const auto& i : stuff_to_collide) {
      i->onHit(3, true);
    }
  }
}
