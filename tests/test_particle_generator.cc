#include <core/particle_generator.h>

#include <catch2/catch.hpp>

using namespace idealgas;

TEST_CASE("GenerateParticle", "[GenerateParticle][GetParticleList]") {
    ParticleGenerator pg;
    vec2 pos(0, 0);
    vec2 vel(0,0);

    SECTION("Generate a red particle") {
        pg.GenerateParticle(pos, vel, "red");
        Particle p = pg.GetParticleList()[0];
        REQUIRE(pg.GetParticleList().size() == 1);
        REQUIRE(p.mass_ == 2);
        REQUIRE(p.radius_ == 2);
        REQUIRE(pos == p.GetPosition());
        REQUIRE(vel == p.GetVelocity());
    }

    SECTION("Generate a blue particle") {
        pg.GenerateParticle(pos, vel, "blue");
        Particle p = pg.GetParticleList()[0];
        REQUIRE(pg.GetParticleList().size() == 1);
        REQUIRE(p.mass_ == 5);
        REQUIRE(p.radius_ == 4);
        REQUIRE(pos == p.GetPosition());
        REQUIRE(vel == p.GetVelocity());
    }

    SECTION("Generate a white particle") {
        pg.GenerateParticle(pos, vel, "white");
        Particle p = pg.GetParticleList()[0];
        REQUIRE(pg.GetParticleList().size() == 1);
        REQUIRE(p.mass_ == 10);
        REQUIRE(p.radius_ == 7);
        REQUIRE(pos == p.GetPosition());
        REQUIRE(vel == p.GetVelocity());
    }

    SECTION("Generate multiple particles") {
        pg.GenerateParticle(pos, vel, "red");
        vec2 pos2(4, 2);
        vec2 vel2(-13.2, 5);
        pg.GenerateParticle(pos2, vel2, "blue");
        vec2 pos3(52.1, 341);
        vec2 vel3(-3.2, 1.2);
        pg.GenerateParticle(pos3, vel3, "white");
        REQUIRE(pg.GetParticleList().size() == 3);
        REQUIRE(pos == pg.GetParticleList()[0].GetPosition());
        REQUIRE(vel == pg.GetParticleList()[0].GetVelocity());
        REQUIRE(pos2 == pg.GetParticleList()[1].GetPosition());
        REQUIRE(vel2 == pg.GetParticleList()[1].GetVelocity());
        REQUIRE(pos3 == pg.GetParticleList()[2].GetPosition());
        REQUIRE(vel3 == pg.GetParticleList()[2].GetVelocity());
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
        pg.GenerateParticle(pos, vel, "red");
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
    }

    SECTION("Update Particle after horizontal wall collision") {
        vec2 pos(50, 2);
        vec2 vel(1, 2);
        vec2 new_vel(-1, 2);
        vec2 curr_pos = pos+new_vel;
        pg.GenerateParticle(pos, vel, "red");
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == new_vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
    }

    SECTION("Update Particle after vertical wall collision") {
        vec2 pos(1, 50);
        vec2 vel(1, 2);
        vec2 new_vel(1, -2);
        vec2 curr_pos = pos+new_vel;
        pg.GenerateParticle(pos, vel, "red");
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == new_vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
    }

    SECTION("Update Multiple Particles after no collision has occurred") {
        vec2 pos(1, 2);
        vec2 vel(1, 2);
        vec2 pos2(3, 4);
        vec2 vel2(2, 1);
        vec2 pos3(14,5);
        vec2 vel3(5,4);
        vec2 curr_pos = pos + vel;
        vec2 p2_pos = pos2 + vel2;
        vec2 p3_pos = pos3+vel3;
        pg.GenerateParticle(pos, vel, "red");
        pg.GenerateParticle(pos2, vel2, "blue");
        pg.GenerateParticle(pos3, vel3, "white");
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
        REQUIRE(pg.GetParticleList()[1].GetVelocity() == vel2);
        REQUIRE(pg.GetParticleList()[1].GetPosition() == p2_pos);
        REQUIRE(pg.GetParticleList()[2].GetVelocity() == vel3);
        REQUIRE(pg.GetParticleList()[2].GetPosition() == p3_pos);
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
        pg.GenerateParticle(pos, vel, "red");
        pg.GenerateParticle(pos2, vel2, "red");
        pg.UpdateParticles();
        REQUIRE(pg.GetParticleList()[0].GetVelocity() == new_vel);
        REQUIRE(pg.GetParticleList()[0].GetPosition() == curr_pos);
        REQUIRE(pg.GetParticleList()[1].GetVelocity() == new_vel2);
        REQUIRE(pg.GetParticleList()[1].GetPosition() == p2_pos);
    }
}

