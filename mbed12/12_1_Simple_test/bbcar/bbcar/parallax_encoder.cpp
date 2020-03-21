#include "parallax_encoder.h"

std::vector<parallax_encoder*> parallax_encoder::encoder_list;

parallax_encoder::parallax_encoder ( DigitalIn& input ) {
    din = &input;
    steps = 0;
    last = 0;
    encoder_list.push_back(this);
}

void parallax_encoder::proc(){
    int value = din->read();
    if(!last && value) steps++;
    last = value;
}

void parallax_encoder::encoder_control(){
    int i;
    for( i=0; i<encoder_list.size(); i++ ){
        (encoder_list[i])->proc();
    }
}
