#include "Element.h"

#include <Eigen/Dense>

#include "Element/HyperCube/Quad/Acoustic.h"
#include "Element/HyperCube/Quad/Elastic.h"

#include "Element/Simplex/Triangle/AcousticTri.h"

// Default implementation
void Element::setupTest(Mesh* mesh, Options options) {
    printf("ERROR: No test implemented\n");
    MPI::COMM_WORLD.Abort(-1);
}

double Element::checkTest(Mesh* mesh, Options options, const Eigen::MatrixXd &displacement, double time) {
    printf("ERROR: No test implemented\n");
    MPI::COMM_WORLD.Abort(-1);
    return -1;
}

Element *Element::factory(Options options) {

    std::string physics(options.PhysicsSystem());
    
    try {
        if(options.ElementShape() == "quad") {
            if (physics == "acoustic") {
                return new AcousticQuad(options);
            } else if (physics == "elastic") {
                return new Elastic(options);
            }
        }
        else if(options.ElementShape() == "triangle") {
            if (physics == "acoustic") {
                return new AcousticTri(options);
            }
        } else {
            throw std::runtime_error("Runtime Error: Element physics " + physics + " not supported");
        }
    } catch (std::exception &e) {
        PRINT_ROOT() << e.what();
        MPI::COMM_WORLD.Abort(-1);
    }
    // Should never get here.
    return nullptr;
}

void Element::setBoundaryConditions(Mesh *mesh) {

    mBndElm = false;
    for(auto& keys : mesh->BoundaryElementFaces()) {
        auto boundary_name = keys.first;
        auto elements_in_boundary = keys.second;
        if(elements_in_boundary.find(mElmNum) != elements_in_boundary.end()) {
            // found this element on some boundary            
            mBndElm = true;
            // assign boundary_name -> {face_ids}
            mBnd[boundary_name] = elements_in_boundary[mElmNum];
        }
    }
}

void Element::applyBoundaryConditions(Mesh *mesh,
                                   Options &options,
                                   std::string fieldname) {

    if(!mBndElm) return;
    
    // dirichlet boundaries
    double value = 0; // value to set
    auto dirichlet_boundary_names = options.DirichletBoundaries();
    for(auto& bndry : dirichlet_boundary_names) {
        auto faceids = mBnd[bndry];
        for(auto& faceid : faceids) {
            auto field = mesh->getFieldOnFace(fieldname,faceid);
            // apply dirichlet condition
            field = 0*field.array() + value;
            mesh->setFieldFromFace(fieldname,faceid,field);
        }
    }
}

