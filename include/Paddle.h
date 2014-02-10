#ifndef PADDLE_H
#define PADDLE_H

#include <Fission/Core/Component.h>

class Paddle : public fsn::Component
{
    FISSION_COMPONENT

    public:
        Paddle(int deflectDir = 1);
        ~Paddle();

        int deflectDir;

    private:
};

#endif // PADDLE_H
