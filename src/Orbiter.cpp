#include "Orbiter.h"
#include "Center.h"
#include "bn_sprite_items_dot.h"

static constexpr bn::fixed FORCE_SCALE = 10;

Orbiter::Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity,
                   Center &center) : _sprite(bn::sprite_items::dot.create_sprite(starting_location)),
                                     _velocity(starting_velocity),
                                     _center(center)
{

}

void Orbiter::update()
{
    bn::fixed_point delta = _center.position() - _sprite.position();

    bn::fixed_point force = delta * _center.mass();
    force /= FORCE_SCALE;

    _velocity += force;

    _sprite.set_position(_sprite.position() + _velocity);
}
