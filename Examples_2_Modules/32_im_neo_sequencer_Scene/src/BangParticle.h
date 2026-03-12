#pragma once

#include "ofMain.h"

class BangParticle {
public:
  BangParticle() = default;

  BangParticle(const ofVec2f& position, const ofFloatColor& color, float radius = 64.0f, float lifeSeconds = 1.0f)
  {
    reset(position, color, radius, lifeSeconds);
  }

  void reset(const ofVec2f& position, const ofFloatColor& color, float radius = 64.0f, float lifeSeconds = 1.0f)
  {
    position_ = position;
    color_ = color;
    startRadius_ = std::max(1.0f, radius);
    radius_ = startRadius_;
    lifeSeconds_ = std::max(0.01f, lifeSeconds);
    ageSeconds_ = 0.0f;
    alive_ = true;
  }

  void update(float deltaSeconds)
  {
    if (!alive_) return;

    ageSeconds_ += std::max(0.0f, deltaSeconds);
    const float t = ofClamp(ageSeconds_ / lifeSeconds_, 0.0f, 1.0f);

    radius_ = ofLerp(startRadius_, 0.0f, t);
    color_.a = 1.0f - t;
    alive_ = (ageSeconds_ < lifeSeconds_) && (radius_ > 0.25f);
  }

  void draw() const
  {
    if (!alive_) return;

    ofSetColor(color_);
    ofDrawCircle(position_, radius_);
  }

  bool isAlive() const
  {
    return alive_;
  }

private:
  ofVec2f position_{ 0.0f, 0.0f };
  ofFloatColor color_{ 1.0f, 1.0f, 1.0f, 1.0f };
  float startRadius_ = 32.0f;
  float radius_ = 32.0f;
  float lifeSeconds_ = 1.0f;
  float ageSeconds_ = 0.0f;
  bool alive_ = false;
};
