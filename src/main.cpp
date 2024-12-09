#include <bn_core.h>
#include <bn_random.h>
#include <bn_keypad.h>
#include <bn_vector.h>
#include <bn_sprite_ptr.h>
#include "bn_sprite_items_testplayer.h"

int main()
{
    bn::core::init();

    // From: #include <bn_random.h>
    bn::random r;

    // A vector of sprite pointers, maximum size: 1
    // From: #include "bn_vector.h"
    bn::vector<bn::sprite_ptr,10> sprites;

    // Wait for a to be presseed
    while(true){
        
        bn::core::update();

        // if we dont have 10 sprites and a is pressed
        if(bn::keypad::a_pressed() && sprites.size()<10){

            // Figure out a random position
            int randomX = -120+r.get()%240;
            int randomY = -80+r.get()%160;

            // Add to an vector of sprite points
            sprites.push_back(bn::sprite_items::testplayer.create_sprite( randomX, randomY));
        }

        // When b is presssed, and if we have any sprites
        if(bn::keypad::b_pressed() && sprites.size()>0){
            
            // Get a random index to erase
            int eraseIndex = r.get() % sprites.size();

            // Get the iterator for the matching item
            bn::vector<bn::sprite_ptr,1>::iterator it = sprites.begin() + eraseIndex;

            // Remove from the array
            // Since no other references exist, the sprite will be removed here
           sprites.erase(it);
        }

        bn::vector<bn::sprite_ptr,10>::iterator it = sprites.begin();

        while(it<sprites.end())     
        {
            // Get the x position of the sprite
            // Use -> to directly access the sprite data/functions, and not the optional data/functions
            bn::fixed x = it->x();

            x+=bn::fixed(2);

            if(x>160)sprites.erase(it);
            else{

                // Update the position of the sprite
                // Use -> to directly access the sprite data/functions, and not the optional data/functions
                it->set_x(x);

                it++;
            }

        }
        
    }
}