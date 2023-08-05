#pragma once

#include <godot_cpp/classes/immediate_mesh.hpp>

#include "noctis-d.h"

extern godot::ImmediateMesh *immediate_mesh;

// Definitions for noctis.cpp
bool init();
void loop();