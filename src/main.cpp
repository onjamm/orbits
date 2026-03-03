#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"
#include "movement.h"
#include "Center.h"
#include "Orbiter.h"

// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 30;

// Default starting posiiton and velocity for Orbiter
static constexpr bn::fixed_point ORBITER_START_POSIITON = {0, 0};
static constexpr bn::fixed_point ORBITER_START_VELOCITY = {0, 5};

//Reverse 
bool reversed = false;



int main()
{
    bn::core::init();

    Center center = Center({30, 40}, .05, 2);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};

    while (true)
    {
        // Add an orbiter when A is pressed if there's room
        if (bn::keypad::a_pressed())
        {
            if (orbiters.size() < MAX_ORBITERS)
            {
                if (reversed)
                {
                    orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY * -1, center));
                } else {
                    orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center));
                }
                


            }
            
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed())
        {
            if (orbiters.size() > 0)
            {
                orbiters.pop_back();
            }
        }

        // If you click a and b at the same time the orbiters will reverse direction
        if (bn::keypad::a_pressed() && bn::keypad::b_pressed())
        {
            reversed = !reversed;
            for (Orbiter& orbiter : orbiters)
            {
                orbiter.reverse();
            }
        }

        center.update();
        for (Orbiter &orbiter : orbiters)
        {
            orbiter.update();
        }

        bn::core::update();
    }
}