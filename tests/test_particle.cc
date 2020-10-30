#include <core/particle.h>

#include <catch2/catch.hpp>

using namespace idealgas;

TEST_CASE("Constructor", "[Constructor][Get]") {
    SECTION("Test Default Constructor") {
        vec2 pos(1.4, 2);
        vec2 vel(0.4, 2.5);
        Particle p(pos, vel);
        REQUIRE(pos == p.GetPosition());
        REQUIRE(vel == p.GetVelocity());
    }
}

TEST_CASE("Set and get", "[Constructor][Get][Set]") {
    vec2 pos(1.4, 2);
    vec2 vel(0.4, 2.5);
    Particle p(pos, vel);

    SECTION("Set only velocity") {
        vec2 set_vel(0.9, 19.2);
        p.SetVelocity(set_vel);
        REQUIRE(pos == p.GetPosition());
        REQUIRE(set_vel == p.GetVelocity());
    }

    SECTION("Set only position") {
        vec2 set_pos(0.9, 19.2);
        p.SetPosition(set_pos);
        REQUIRE(set_pos == p.GetPosition());
        REQUIRE(vel == p.GetVelocity());
    }

    SECTION("Set both velocity and position") {
        vec2 set_pos(0.9, 19.2);
        vec2 set_vel(-13.6, 4.2);
        p.SetPosition(set_pos);
        p.SetVelocity(set_vel);
        REQUIRE(set_pos == p.GetPosition());
        REQUIRE(set_vel == p.GetVelocity());
    }
}

TEST_CASE("HasCollidedWith", "[HasCollidedWith][GetDistanceTo]") {
    vec2 pos(1.4, 2);
    vec2 vel(0.4, 2.5);
    Particle p(pos, vel);

    SECTION("Check particles at same position") {
        vec2 pos2(1.4, 2);
        vec2 vel2(0.4, 2.5);
        Particle p2(pos2, vel2);
        REQUIRE_FALSE(p.HasCollidedWith(p2, 4));
    }

    SECTION("Check particles with velocities moving toward each other") {
        vec2 pos2(5.2, 3.6);
        vec2 vel2(-0.4, -2.5);
        Particle p2(pos2, vel2);
        REQUIRE(p.HasCollidedWith(p2, 4));
    }

    SECTION("Check particles with velocities moving away from each other") {
        vec2 pos2(5.2, 3.6);
        vec2 vel2(0.4, 2.5);
        Particle p2(pos2, vel2);
        REQUIRE_FALSE(p.HasCollidedWith(p2, 4));
    }

    SECTION("Check with particles that are out of reach") {
        vec2 pos2(7.4, 9);
        vec2 vel2(0.4, 2.5);
        Particle p2(pos2, vel2);
        REQUIRE_FALSE(p.HasCollidedWith(p2, 4));
    }
}

TEST_CASE("ChangePostCollisionVelocity", "[ChangePostCollisionVelocity][Get]") {
    vec2 pos(1, 2);
    vec2 vel(1, 2);
    Particle p(pos, vel);

    SECTION("Check Post Collision Velocity of a collision with particle with all zero values") {
        vec2 pos2(0, 0);
        vec2 vel2(0, 0);
        Particle p2(pos2, vel2);
        p.ChangePostCollisionVelocity(p2);
        vec2 final_vel(0,0);
        REQUIRE(final_vel == p.GetVelocity());
    }

    SECTION("Check Post Collision Velocity of a collision with particle with all same values") {
        Particle p2 = p;
        REQUIRE_THROWS_AS(p.ChangePostCollisionVelocity(p2), std::runtime_error);
    }

    SECTION("Check Post Collision Velocity of a legitimate collision") {
        vec2 pos2(3, 4);
        vec2 vel2(2, 1);
        Particle p2(pos2, vel2);
        vec2 curr_vel = p.GetVelocity();
        p.ChangePostCollisionVelocity(p2);
        REQUIRE(curr_vel == p.GetVelocity());
    }
}