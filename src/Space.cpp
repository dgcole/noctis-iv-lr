#include "Space.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/sprite3d.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include "noctis-0.h"
#include "noctis-d.h"
#include "noctis.h"

Space::Space() {}

Space::~Space() {}

void Space::_bind_methods() {}

void Space::_process(double delta) {
    if (godot::Engine::get_singleton()->is_editor_hint()) {
        return;
    }

    static bool initialized                                  = false;
    static godot::Ref<godot::ShaderMaterial> shader_material = nullptr;
    static godot::MeshInstance3D *mesh_instance              = get_node<godot::MeshInstance3D>("../MeshInstance3D");
    if (!initialized) {
        if (!init()) {
            assert(false);
        }

        immediate_mesh = memnew(godot::ImmediateMesh);
        mesh_instance->set_mesh(immediate_mesh);

        shader_material = godot::ResourceLoader::get_singleton()->load("poly3d.material");

        initialized = true;
    }

    immediate_mesh->clear_surfaces();
    loop();

    // Render out old video buffer to texture for reference
    auto img = godot::Image::create(adapted_width, adapted_height, false, godot::Image::FORMAT_RGB8);
    for (int x = 0; x < adapted_width; x++) {
        for (int y = 0; y < adapted_height; y++) {
            uint8_t color_index = adapted[adapted_width * y + x];
            uint32_t color_r    = currpal[color_index * 3] * 4;
            uint32_t color_g    = currpal[color_index * 3 + 1] * 4;
            uint32_t color_b    = currpal[color_index * 3 + 2] * 4;

            img->set_pixel(x, y,
                           godot::Color((float) color_r / 255.0, (float) color_g / 255.0, (float) color_b / 255.0));
        }
    }
    auto texture = godot::ImageTexture::create_from_image(img);

    godot::Sprite3D *sprite = get_node<godot::Sprite3D>("../Sprite3D");
    sprite->set_texture(texture);

    mesh_instance->set_material_override(shader_material);
}