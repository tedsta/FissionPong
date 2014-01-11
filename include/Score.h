#ifndef SCORE_H
#define SCORE_H

#include <Fission/Core/Component.h>

class Score : public fsn::Component
{
    FISSION_COMPONENT

    public:
        Score();
        ~Score();

        int mScore;
};

#endif // SCORE_H
