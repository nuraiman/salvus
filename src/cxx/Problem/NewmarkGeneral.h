//
// Created by Michael Afanasiev on 2016-03-14.
//

#ifndef SALVUS_NEWMARKGENERAL_H
#define SALVUS_NEWMARKGENERAL_H

#include "Problem.h"

class NewmarkGeneral: public Problem {

private:

    Mesh *mMesh;
    Quad *mReferenceQuad;
    std::vector<Quad *> mElements;

public:

    virtual void solve(Options options);
    virtual void initialize(Mesh *mesh, ExodusModel *model, Quad *quad, Options options);

};


#endif //SALVUS_NEWMARKGENERAL_H