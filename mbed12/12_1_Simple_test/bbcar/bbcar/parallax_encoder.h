#ifndef PARALLAX_ENCODER_H
#define PARALLAX_ENCODER_H

#include "mbed.h"
#include <vector>

class parallax_encoder {
    public:
        static std::vector<parallax_encoder*> encoder_list;

        parallax_encoder( DigitalIn& input );

        void proc();
        void encoder_control();
        int get_steps(){ return steps; }
        float get_cm(){ return steps*6.5*3.14/32; }
        void reset(){ steps = 0; }
        operator int(){ return steps; }
        
    private:
        int steps;
        int last;
        DigitalIn *din;
};

#endif
