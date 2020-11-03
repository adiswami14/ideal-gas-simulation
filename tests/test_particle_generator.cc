#include <core/particle_generator.h>

#include <catch2/catch.hpp>

using namespace idealgas;

TEST_CASE("GenerateParticle", "[GenerateParticle][GetParticleList]") {
    ParticleGenerator pg;
    vec2 pos(0, 0);
    vec2 vel(0,0);

    SECTION("Generate a single particle") {
        pg.GenerateParticle(pos, vel, false);
        REQUIRE(pg.GetParticleList().size() == 1);
        REQUIRE(pos == pg.GetParticleList()[0].GetPosition());
        REQUIRE(vel == pg.GetParticleList()[0].GetVelocity());
    }

    SECTION("Generate multiple particles") {
        pg.GenerateParticle(pos, vel, false);
        vec2 pos2(4, 2);
        vec2 vel2(-13.2, 5);
        pg.GenerateParticle(pos2, vel2, false);
        REQUIRE(pg.GetParticleList().size() == 2);
        REQUIRE(pos == pg.GetParticleList()[0].GetPosition());
        REQUIRE(vel == pg.GetParticleList()[0].GetVelocity());
        REQUIRE(pos2 == pg.GetParticleList()[1].GetPosition());
        REQUIRE(vel2 == pg.GetParticleList()[1].GetVelocity());
    }
}

TEST_CASE("SetBox", "[SetBox]") {
    ParticleGenerator pg;
    Box box(vec2(0,0), 1);
    pg.SetBox(box);
    REQUIRE(box.GetBoxSize() == 1);
    vec2 check(0,0);
    REQUIRE(box.GetTopLeftCorner() == check);
}

TEST_CASE("UpdateParticles", "[UpdateParticles][SetBox][GenerateParticle][GetParticleList]") {
    ParticleGenerator pg;
    Box box(vec2(0,0), 50);
    pg.SetBox(box);

    SECTION("Update Single Particle") {
        vec2 pos(1, 2);
        vec2 vel(1, 2);
        vec2 curr_pos = pos+vel;
        pg.GenerateParticle(pos, vel, false);
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
    }

    SECTION("Update Particle after horizontal wall collision") {
        vec2 pos(50, 2);
        vec2 vel(1, 2);
        vec2 new_vel(-1, 2);
        vec2 curr_pos = pos+new_vel;
        pg.GenerateParticle(pos, vel, false);
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == new_vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
    }

    SECTION("Update Particle after vertical wall collision") {
        vec2 pos(1, 50);
        vec2 vel(1, 2);
        vec2 new_vel(1, -2);
        vec2 curr_pos = pos+new_vel;
        pg.GenerateParticle(pos, vel, false);
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == new_vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
    }

    SECTION("Update Multiple Particles after no collision has occurred") {
        vec2 pos(1, 2);
        vec2 vel(1, 2);
        vec2 pos2(3, 4);
        vec2 vel2(2, 1);
        vec2 curr_pos = pos + vel;
        vec2 p2_pos = pos2 + vel2;
        pg.GenerateParticle(pos, vel, false);
        pg.GenerateParticle(pos2, vel2, false);
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
        REQUIRE(pg.GetParticleList()[1].GetVelocity() == vel2);
        REQUIRE(pg.GetParticleList()[1].GetPosition() == p2_pos);
    }

    SECTION("Update multiple particles after collision has occurred") {
        vec2 pos(10, 10);
        vec2 vel(1, 2);
        vec2 pos2(11, 11);
        vec2 vel2(-2, -1);
        vec2 new_vel(-2, -1);
        vec2 curr_pos = pos + new_vel;
        vec2 new_vel2 (1, 2);
        vec2 p2_pos = pos2 + new_vel2;
        pg.GenerateParticle(pos, vel, false);
        pg.GenerateParticle(pos2, vel2, false);
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == new_vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
        REQUIRE(pg.GetParticleList()[1].GetVelocity() == new_vel2);
        REQUIRE(pg.GetParticleList()[1].GetPosition() == p2_pos);
    }
}

