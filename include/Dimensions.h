#ifndef Dimensions_H
#define Dimensions_H

#include <Fission/Core/Component.h>

class Dimensions : public fsn::Component
{
    FISSION_COMPONENT
    public:
        Dimensions(int x = 0, int y = 0);
        ~Dimensions();

        int x; // Width
        int y; // Height

    private:
};

#endif // Dimensions_H
