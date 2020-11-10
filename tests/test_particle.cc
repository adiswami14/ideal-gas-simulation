#include <core/particle.h>

#include <catch2/catch.hpp>
#include <core/red_particle.h>
#include <core/blue_particle.h>
#include <core/white_particle.h>

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
    SECTION("RedParticle") {
        vec2 pos(1.4, 2);
        vec2 vel(0.4, 2.5);
        RedParticle p(pos, vel);

        SECTION("Check particles at same position") {
            vec2 pos2(1.4, 2);
            vec2 vel2(0.4, 2.5);
            RedParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }

        SECTION("Check particles with velocities moving toward each other") {
            vec2 pos2(1.6, 3.6);
            vec2 vel2(-0.4, -2.5);
            RedParticle p2(pos2, vel2);
            REQUIRE(p.HasCollidedWith(p2));
        }

        SECTION("Check particles with velocities moving away from each other") {
            vec2 pos2(1.6, 3.6);
            vec2 vel2(0.4, 2.5);
            RedParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }

        SECTION("Check with particles that are out of reach") {
            vec2 pos2(7.4, 9);
            vec2 vel2(0.4, 2.5);
            RedParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }
    }

    SECTION("BlueParticle") {
        vec2 pos(1.4, 2);
        vec2 vel(0.4, 2.5);
        BlueParticle p(pos, vel);

        SECTION("Check particles at same position") {
            vec2 pos2(1.4, 2);
            vec2 vel2(0.4, 2.5);
            BlueParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }

        SECTION("Check particles with velocities moving toward each other") {
            vec2 pos2(5.2, 3.6);
            vec2 vel2(-0.4, -2.5);
            BlueParticle p2(pos2, vel2);
            REQUIRE(p.HasCollidedWith(p2));
        }

        SECTION("Check particles with velocities moving away from each other") {
            vec2 pos2(5.2, 3.6);
            vec2 vel2(0.4, 2.5);
            BlueParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }

        SECTION("Check with particles that are out of reach") {
            vec2 pos2(7.4, 9);
            vec2 vel2(0.4, 2.5);
            BlueParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }
    }

    SECTION("WhiteParticle") {
        vec2 pos(1.4, 2);
        vec2 vel(0.4, 2.5);
        WhiteParticle p(pos, vel);

        SECTION("Check particles at same position") {
            vec2 pos2(1.4, 2);
            vec2 vel2(0.4, 2.5);
            WhiteParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }

        SECTION("Check particles with velocities moving toward each other") {
            vec2 pos2(6.2, 3.6);
            vec2 vel2(-0.4, -2.5);
            WhiteParticle p2(pos2, vel2);
            REQUIRE(p.HasCollidedWith(p2));
        }

        SECTION("Check particles with velocities moving away from each other") {
            vec2 pos2(6.2, 3.6);
            vec2 vel2(0.4, 2.5);
            WhiteParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }

        SECTION("Check with particles that are out of reach") {
            vec2 pos2(10.2, 9);
            vec2 vel2(0.4, 2.5);
            WhiteParticle p2(pos2, vel2);
            REQUIRE_FALSE(p.HasCollidedWith(p2));
        }
    }
}

TEST_CASE("ChangePostCollisionVelocity", "[ChangePostCollisionVelocity][Get]") {
    SECTION("RedParticle") {
        vec2 pos(1, 2);
        vec2 vel(1, 2);
        RedParticle p(pos, vel);

        SECTION("Check Post Collision Velocity of a collision with particle with all zero values") {
            vec2 pos2(0, 0);
            vec2 vel2(0, 0);
            RedParticle p2(pos2, vel2);
            p.ChangePostCollisionVelocity(p2);
            vec2 final_vel(0, 0);
            REQUIRE(final_vel == p.GetVelocity());
        }

        SECTION("Check Post Collision Velocity of a collision with particle with all same values") {
            RedParticle p2 = p;
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(vel == p.GetVelocity());
            REQUIRE(vel == p2.GetVelocity());
        }

        SECTION("Check Post Collision Velocity of a collision with red particle") {
            vec2 pos2(2, 3);
            vec2 vel2(2, 1);
            RedParticle p2(pos2, vel2);
            vec2 curr_vel(1,2);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }

        SECTION("Check Post Collision Velocity of a collision with blue particle") {
            vec2 pos2(6, 5);
            vec2 vel2(2, 1);
            BlueParticle p2(pos2, vel2);
            vec2 curr_vel(1.42,2.252);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }

        SECTION("Check Post Collision Velocity of a collision with white particle") {
            vec2 pos2(6, 5);
            vec2 vel2(2, 1);
            WhiteParticle p2(pos2, vel2);
            vec2 curr_vel(1.49,2.294);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }
    }

    SECTION("BlueParticle") {
        vec2 pos(1, 2);
        vec2 vel(1, 2);
        BlueParticle p(pos, vel);

        SECTION("Check Post Collision Velocity of a collision with particle with all zero values") {
            vec2 pos2(0, 0);
            vec2 vel2(0, 0);
            BlueParticle p2(pos2, vel2);
            p.ChangePostCollisionVelocity(p2);
            vec2 final_vel(0, 0);
            REQUIRE(final_vel == p.GetVelocity());
        }

        SECTION("Check Post Collision Velocity of a collision with particle with all same values") {
            BlueParticle p2 = p;
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(vel == p.GetVelocity());
            REQUIRE(vel == p2.GetVelocity());
        }

        SECTION("Check Post Collision Velocity of a collision with red particle") {
            vec2 pos2(2, 3);
            vec2 vel2(2, 1);
            RedParticle p2(pos2, vel2);
            vec2 curr_vel(1,2);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }

        SECTION("Check Post Collision Velocity of a collision with blue particle") {
            vec2 pos2(6, 5);
            vec2 vel2(2, 1);
            BlueParticle p2(pos2, vel2);
            vec2 curr_vel(1.294,2.176);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }

        SECTION("Check Post Collision Velocity of a collision with white particle") {
            vec2 pos2(6, 5);
            vec2 vel2(2, 1);
            WhiteParticle p2(pos2, vel2);
            vec2 curr_vel(1.392,2.235);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }
    }

    SECTION("WhiteParticle") {
        vec2 pos(1, 2);
        vec2 vel(1, 2);
        WhiteParticle p(pos, vel);

        SECTION("Check Post Collision Velocity of a collision with particle with all zero values") {
            vec2 pos2(0, 0);
            vec2 vel2(0, 0);
            WhiteParticle p2(pos2, vel2);
            p.ChangePostCollisionVelocity(p2);
            vec2 final_vel(0, 0);
            REQUIRE(final_vel == p.GetVelocity());
        }

        SECTION("Check Post Collision Velocity of a collision with particle with all same values") {
            WhiteParticle p2 = p;
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(vel == p.GetVelocity());
            REQUIRE(vel == p2.GetVelocity());
        }

        SECTION("Check Post Collision Velocity of a collision with red particle") {
            vec2 pos2(2, 3);
            vec2 vel2(2, 1);
            RedParticle p2(pos2, vel2);
            vec2 curr_vel(1,2);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }

        SECTION("Check Post Collision Velocity of a collision with blue particle") {
            vec2 pos2(6, 5);
            vec2 vel2(2, 1);
            BlueParticle p2(pos2, vel2);
            vec2 curr_vel(1.196,2.118);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }

        SECTION("Check Post Collision Velocity of a collision with white particle") {
            vec2 pos2(6, 5);
            vec2 vel2(2, 1);
            WhiteParticle p2(pos2, vel2);
            vec2 curr_vel(1.294,2.176);
            p.ChangePostCollisionVelocity(p2);
            REQUIRE(curr_vel.x == Approx(p.GetVelocity().x).epsilon(0.01));
            REQUIRE(curr_vel.y == Approx(p.GetVelocity().y).epsilon(0.01));
        }
    }
}