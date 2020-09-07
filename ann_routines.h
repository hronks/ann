#ifndef ANN_ROUTINES_H
#define ANN_ROUTINES_H

#include "ann.h"

struct Layer {


};


struct ANN {

    std::vector <Layer *> l;

    ANN(int length) {
      l.resize(length + 2);
    }

    void link() {

      l[0]->raw_input = &in;
      l[l.size()-1]->raw_output = & y;
    }

};



#endif
