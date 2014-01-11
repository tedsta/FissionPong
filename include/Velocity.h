#ifndef VELOCITY_H
#define VELOCITY_H

#include <Fission/Core/Component.h>

class Velocity : public fsn::Component
{
    FISSION_COMPONENT

    public:
        Velocity(int x = 0, int y = 0);
        ~Velocity();

        int mX;
        int mY;
};

#endif // VELOCITY_H
