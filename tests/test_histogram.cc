#include <visualizer/histogram.h>

#include <catch2/catch.hpp>

using namespace idealgas;
using namespace idealgas::visualizer;
using glm::vec2;

TEST_CASE("Overloaded Constructor"){
    Histogram h(vec2(0,0), 40, ci::Color("red"), 0.2);
    vec2 c(0,0);
    REQUIRE(c == h.GetBottomLeftCorner());
    REQUIRE(40 == h.GetHistogramSize());
    REQUIRE(ci::Color("red") == h.GetColor());
    REQUIRE(0.2 == h.GetRoundingFactor());
}

TEST_CASE("Set and Get Particle Vector") {
    Histogram h(vec2(0,0), 40, ci::Color("red"), 0.2);
    Particle p(vec2(0,0), vec2(0,0));
    vector<Particle> particle_list;
    particle_list.push_back(p);
    h.SetParticleVector(particle_list);
    vector<Particle> compare_vec = h.GetParticleVector();
    REQUIRE(compare_vec.size() == 1);
    REQUIRE(compare_vec[0].GetVelocity() == vec2(0,0));
    REQUIRE(compare_vec[0].GetPosition() == vec2(0,0));
}

TEST_CASE("UpdateFrequencyMap") {
    SECTION("Frequency Map Update for a single particle") {
        Histogram h(vec2(0,0), 40, ci::Color("red"), 0.1);
        Particle p(vec2(0,0), vec2(1,2));
        vector<Particle> particle_list;
        particle_list.push_back(p);
        h.SetParticleVector(particle_list);
        h.UpdateFrequencyMap();
        map<double, size_t> freq_map = h.GetFrequencyMap();
        REQUIRE(freq_map.size() == 1);
        REQUIRE(freq_map[2.2] == 1);
    }

    SECTION("Frequency Map Update for multiple particles with same speed") {
        Histogram h(vec2(0,0), 40, ci::Color("red"), 0.1);
        Particle p(vec2(0,0), vec2(1,2));
        Particle p2(vec2(0,0), vec2(2,1));
        Particle p3(vec2(0,0), vec2(0,2.2));
        Particle p4(vec2(0,0), vec2(2.2,0));
        vector<Particle> particle_list;
        particle_list.push_back(p);
        particle_list.push_back(p2);
        particle_list.push_back(p3);
        particle_list.push_back(p4);
        h.SetParticleVector(particle_list);
        h.UpdateFrequencyMap();
        map<double, size_t> freq_map = h.GetFrequencyMap();
        REQUIRE(freq_map.size() == 1);
        REQUIRE(freq_map[2.2] == 4);
    }

    SECTION("Frequency Map Update for multiple particles with different speeds") {
        Histogram h(vec2(0,0), 40, ci::Color("red"), 0.1);
        Particle p(vec2(0,0), vec2(1,2));
        Particle p2(vec2(0,0), vec2(0,1));
        Particle p3(vec2(0,0), vec2(2,2));
        Particle p4(vec2(0,0), vec2(4,3));
        vector<Particle> particle_list;
        particle_list.push_back(p);
        particle_list.push_back(p2);
        particle_list.push_back(p3);
        particle_list.push_back(p4);
        h.SetParticleVector(particle_list);
        h.UpdateFrequencyMap();
        map<double, size_t> freq_map = h.GetFrequencyMap();
        REQUIRE(freq_map.size() == 4);
        REQUIRE(freq_map[2.2] == 1);
        REQUIRE(freq_map[1.0] == 1);
        REQUIRE(freq_map[2.8] == 1);
        REQUIRE(freq_map[5.0] == 1);
    }
}
