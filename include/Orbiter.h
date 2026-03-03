#ifndef ORBITER_H
#define ORBITER_H

#include <bn_sprite_ptr.h>
#include <bn_fixed_point.h>
#include "Center.h"

class Orbiter
{
    public:
        Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity,
        Center &center);

        void update();

        void reverse();

    private:
        bn::sprite_ptr _sprite;
        bn::fixed_point _velocity;
        Center& _center;
};
#endif