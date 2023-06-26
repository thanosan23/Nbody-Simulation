#include <iostream>
#include <vector>
#include <fstream>

#include "vec3.hpp"
#include "entity.hpp"

#include "../include/toml.hpp"

using namespace std;

const double GRAVITATIONAL_CONSTANT = 6.67e-11;
const double SECONDS_IN_DAY = 86400;

const string SETTINGS = "configuration.toml";

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    // read config file
    cout << "Reading data from " + SETTINGS + "..." << '\n';
    auto config = toml::parse_file(SETTINGS);
    double increment = config["simulation"]["increment"].value_or(SECONDS_IN_DAY);
    double time = config["simulation"]["time"].value_or(SECONDS_IN_DAY * 365); // default = 1 year
    string showLabels = config["simulation"]["showLabels"].value_or("false");

    double bodies = config["simulation"]["celestialBodies"].value_or(0);

    // instantiate the celestial bodies
    vector<Entity> celestialBodies;
    vector<string> names;

    for(int i = 0; i < bodies; i++) {
        auto current = config["body"+to_string(i+1)];
        names.push_back(current["name"].value_or(""));

        Entity body = Entity(
            current["x"].value_or(0.0),
            current["y"].value_or(0.0),
            current["z"].value_or(0.0),
            current["xVel"].value_or(0.0),
            current["yVel"].value_or(0.0),
            current["zVel"].value_or(0.0),
            current["mass"].value_or(0.0)
        );
        celestialBodies.push_back(body);
    }

    // start the simulation
    double t = 0; // time is measured in the seconds
    double end = time;
    // output config data into file
    ofstream file;
    file.open(argv[1]);
    file << celestialBodies.size() << '\n' << end/increment << '\n' << showLabels << '\n';
    for(string &name : names) file << name << '\n';

    vec3 minPos, maxPos;

    while(t < end) {
        for(int i = 0; i < celestialBodies.size(); i++) {
            // https://www.cs.princeton.edu/courses/archive/spr01/cs126/assignments/nbody.html
            // total force acting on body is the accumulation of this celestial body and other bodies
            vec3 F;
            for(int j = 0; j < celestialBodies.size(); j++) {
                if(i == j) continue; // skip if both bodies are the same
                // calculate the distance
                vec3 r = celestialBodies[i].pos - celestialBodies[j].pos;

                // get the unit vector to represent direction
                vec3 rUnit = r.unit();

                // calculate attraction force using gravitational acceleration formula
                double accel = -GRAVITATIONAL_CONSTANT * ((celestialBodies[j].mass) / pow(r.mag(), 2.0));
                vec3 gravitationalAcceleration = vec3(accel);
                gravitationalAcceleration *= rUnit; // add direction to acceleration

                // accumulate the acceleration values for each body
                F += gravitationalAcceleration;
            }
            // calculate and update the velocity of the body using the acceleration force
            celestialBodies[i].vel += F * increment;
        }
        // calculate the new positions of the body
        for (int i = 0; i < celestialBodies.size(); i++) {
            celestialBodies[i].pos += celestialBodies[i].vel * increment;
            minPos.x = min(celestialBodies[i].pos.x, minPos.x);
            minPos.y = min(celestialBodies[i].pos.y, minPos.y);
            minPos.z = min(celestialBodies[i].pos.z, minPos.z);

            maxPos.x = max(celestialBodies[i].pos.x, maxPos.x);
            maxPos.y = max(celestialBodies[i].pos.y, maxPos.y);
            maxPos.z = max(celestialBodies[i].pos.z, maxPos.z);

        }
        // output the positions into file to allow for visualization
        for (int i = 0; i < celestialBodies.size(); i++) {
            file << celestialBodies[i].pos.x << ' ' << celestialBodies[i].pos.y << ' ' << celestialBodies[i].pos.z << '\n';
        }
        t += increment;
    }
    // output min and max values to allow for good visualization
    file << minPos.x << ' ' << minPos.y << ' ' << minPos.z << '\n';
    file << maxPos.x << ' ' << maxPos.y << ' ' << maxPos.z;
    // close file
    file.close();
}
