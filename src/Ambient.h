#ifndef AMBIENT_H
#define AMBIENT_H

#pragma once

#include <Arduino.h>
#include "messaging.pb.h"

class Ambient {
    private:


    public: 
        Ambient();

        void loop();

        void sendProtobuf();


};

extern Ambient *ambient;

#endif