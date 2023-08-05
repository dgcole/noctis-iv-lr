#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>

class Space : public godot::Node {
    GDCLASS(Space, godot::Node)

  public:
    Space();
    ~Space();

    void _process(double delta) override;

  protected:
    static void _bind_methods();
};