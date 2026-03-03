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

//Speed multiplier for the orbiters every 5 seconds, that lasts five seconds, ( 5 on, 5 off, and so on)
int boost_timer = 0;
bool boost_active = false;
static constexpr int BOOST_DURATION = 300;
static constexpr int BOOST_INTERVAL = 300;
int frame_count = 0;



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
                orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center));

                if (boost_active) 
                {
                    orbiters.back().set_speed_multiplier(2);
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

        // Speed boost logic
        frame_count++;

        //Start boost every boost_interval frames
        if (!boost_active && frame_count >= BOOST_INTERVAL)
        {
            boost_active = true;
            boost_timer = BOOST_DURATION;
            frame_count = 0;

            for(Orbiter &orbiter : orbiters) 
            {
                orbiter.set_speed_multiplier(bn::fixed(2));
            }
        }

        if (boost_active)
        {
            boost_timer--;
            
            if(boost_timer <= 0)
            {
                boost_active = false;

                for (Orbiter &orbiter : orbiters) 
                {
                    orbiter.set_speed_multiplier(bn::fixed(1));
                    orbiter.reset_velocity();
                }
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