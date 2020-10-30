#include <core/box.h>

#include <catch2/catch.hpp>

using namespace idealgas;

TEST_CASE("Overloaded Constructor and Getters", "[Constructor][GetTopLeftCorner][GetBoxSize][GetParticleRadius]") {
    SECTION("Test Overloaded Constructor") {
        vec2 v(0,0);
        Box box(v, 2, 2);
        REQUIRE(v == box.GetTopLeftCorner());
        REQUIRE(2 == box.GetBoxSize());
        REQUIRE(2 == box.GetParticleRadius());
    }
}

TEST_CASE("IsAtXBoundary", "[IsAtXBoundary][Constructor]") {
    vec2 v(50,50);
    Box box(v, 500, 4);

    SECTION("Is within box") {
        vec2 pos(100, 100);
        vec2 vel(2, 2);
        Particle p(pos, vel);
        REQUIRE(!box.IsAtXBoundary(p));
    }

    SECTION("Is at left edge of box") {
        vec2 pos(52, 100);
        vec2 vel(-2, 2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtXBoundary(p));
    }

    SECTION("Is at right edge of box") {
        vec2 pos(548, 100);
        vec2 vel(2, 2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtXBoundary(p));
    }

    SECTION("Is over left edge of box") {
        vec2 pos(40, 100);
        vec2 vel(-2, 2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtXBoundary(p));
    }

    SECTION("Is over right edge of box") {
        vec2 pos(552, 100);
        vec2 vel(2, 2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtXBoundary(p));
    }
}

TEST_CASE("IsAtYBoundary") {
    vec2 v(50,50);
    Box box(v, 500, 4);

    SECTION("Is within box") {
        vec2 pos(100, 100);
        vec2 vel(2, 2);
        Particle p(pos, vel);
        REQUIRE(!box.IsAtYBoundary(p));
    }

    SECTION("Is at top edge of box") {
        vec2 pos(100, 52);
        vec2 vel(2, -2);
        Particle p(pos, vel);
        bool x = box.IsAtYBoundary(p);
        x = false;
        //REQUIRE(box.IsAtYBoundary(p));
    }

    SECTION("Is at bottom edge of box") {
        vec2 pos(100, 548);
        vec2 vel(2, 2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtYBoundary(p));
    }

    SECTION("Is over top edge of box") {
        vec2 pos(100, 49);
        vec2 vel(2, -2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtYBoundary(p));
    }

    SECTION("Is over bottom edge of box") {
        vec2 pos(100, 576);
        vec2 vel(2, 2);
        Particle p(pos, vel);
        REQUIRE(box.IsAtYBoundary(p));
    }
}