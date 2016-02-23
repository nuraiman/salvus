/**
 * A class to oversee the setup and solution of our problem. Created by Michael Afanasiev on 2016-01-27.
 * The `Problem` class is responsible for directing the majority of the work done in the program. It should be
 * inherited from for each conceivable combination of parameters (i.e. there should be a separate derived class for
 * the scalar wave equation solved on 2-D quads, and the elastic wave equation solved on 2-D quads). What is key, is
 * that in each derived class, the important variable pointers (mesh, reference element, model) are defined as whatever
 * type they are required to be for that specific probelm. For instance, in acoustic case, the reference element should
 * currently be defined as `Acoustic *mReferenceElement`. If this is properly done, an abstract interface can be kept,
 * which takes a general element and mesh object, with the assumption that within each derived function these objects
 * will be downcasted (via a <dynamic_cast>).
 */


#ifndef SALVUS_SOLVER_H
#define SALVUS_SOLVER_H


#include <ostream>
#include <iostream>
#include <openmpi/ompi/mpi/cxx/mpicxx.h>
#include <iosfwd>
#include <string>
#include "Utilities.h"
#include "Element/HyperCube/Quad.h"
#include "Mesh.h"
#include "Element/HyperCube/Quad/Elastic.h"
#include "Source.h"
#include "Element/HyperCube/Quad/Acoustic.h"

class Problem {

public:

    static Problem *factory(std::string solver_type);

    virtual void solve() = 0;
    virtual void initialize(Mesh *mesh, ExodusModel *model, Quad *quad, Options options) = 0;


};

class TimeDomainScalar2d : public Problem {

private:

    ScalarNewmark2D *mMesh;
    Acoustic *mReferenceQuad;
    std::vector<Acoustic *> mElements;

    double mSimulationDuration;
    double mTimeStep;


public:


    virtual void solve();
    virtual void initialize(Mesh *mesh, ExodusModel *model, Quad *quad, Options options);

};

class TimeDomainElastic2d: public Problem {

private:

    ElasticNewmark2D *mMesh;
    Elastic *mReferenceQuad;
    std::vector<Elastic *> mElements;

    double mSimulationDuration;
    double mTimeStep;

public:

    virtual void solve();
    virtual void initialize(Mesh *mesh, ExodusModel *model, Quad *quad, Options options);


};


#endif //SALVUS_SOLVE
