//
// Created by Michael Afanasiev on 2016-01-27.
//

#ifndef SALVUS_MESH_H
#define SALVUS_MESH_H

#include <map>
#include <iosfwd>
#include <string>
#include <vector>

#include <mpi.h>
#include <assert.h>

#include <petscdm.h>
#include <petscvec.h>
#include <petscdmplex.h>
#include <petscdmtypes.h>
#include <petscistypes.h>
#include <petscviewerhdf5.h>

#include <Eigen/Dense>

#include "../Utilities/Options.h"
#include "../Utilities/Utilities.h"

/**
 * Struct holding the vectors representing the global DOFs.
 * The global PETSc vector is defined across processors,
 * and knows which of its entries are on processor boundaries. The local PETSc vector exists only on the
 * current processor.
 */
struct vec_struct {
    std::string name;   /** < Field name (i.e. displacement_x) */
    Vec glb;            /** < Global PETSc vector */
    Vec loc;            /** < Local PETSc vector */
};

class Mesh {

    int mNumberElementsLocal;       /** < Number of elements on this processor. */
    int mNumberDimensions;          /** < Number of dimensions of the mesh. */
    int mTime;                      /** < Time step number. Could probably be handled in a smarter way */

    std::string mExodusFileName;    /** < Exodus file from which this mesh (skeleton) was defined. */

    DM mDistributedMesh;            /** < PETSc distributed mesh defining parallel element layout. */
    PetscSection mMeshSection;      /** < Mesh section describing location of the integration points. In the future we
                                        * may have many of these per mesh. */

protected:

    std::map<std::string, vec_struct> mFields;  /** < Dictionary holding the fields on the global dof. */
    PetscViewer mViewer;                        /** < Holds information used to dump field values to disk. */

public:

    /**
     * Factory which returns a `Mesh` based on user defined options.
     * The `Mesh` is really a collection of the global dofs, and the fields defined on these dofs will depend on both
     * the physics of the system under consideration, and the method of time-stepping chosen.
     * @return Some derived mesh class.
     */
    static Mesh *factory(Options options);

    /**
     * Reads an exodus mesh from a file defined in options.
     * By the time this method is finished, the mesh has been
     * read, and parallelized across processors (via a call to Chaco).
     * @param [in] options The master options struct. TODO: Move the gobbling of options to the constructor.
     */
    void read(Options options);

    /**
     * Sets up the dofs across elements and processor boundaries.
     * Specifcally, this function defines a `DMPlex section` spread across all elements. It is this section that
     * defines the integration points, and carries information about which of these points are shared across processor
     * boundries.
     * @param [in] number_dof_vertex Number of dofs per 0-d mesh component (vertex). 1 for the standard GLL basis.
     * @param [in] number_dof_edge Number of dofs per 1-d mesh component (edge). order-1 for the standard GLL basis.
     * @param [in] number_dof_face Number of dofs per 2-d mesh component (face). (order-1)^2 for the standard GLL basis.
     * @param [in] number_dof_volume Number of dofs per 3-d mesh component (volume). Something something for the
     * standard GLL basis.
     */
    void setupGlobalDof(PetscInt number_dof_vertex, PetscInt number_dof_edge,
                        PetscInt number_dof_face, PetscInt number_dof_volume,
                        PetscInt number_dimensions);

    /**
     * Registers both the global (across parallel partition) and local (on a single parallel partition) vectors for a
     * given name. Vector information is stored in an `std::map` under mFields, with `name` as the key.
     * @param name Name of field to register.
     */
    void registerFieldVectors(const std::string &name);

    /**
     * Begins (and ends) the gloabl -> local MPI sends for a given field name. By the time this function returns, you
     * can be confident that the MPI sends have been completed (i.e. it is blocking), and will be available to each
     * element.
     * @param name Name of field to checkout.
     */
    void checkOutField(const std::string &name);

    /**
     * Does the local -> global MPI sends for a given field name. The
     * send is performed with an sum, i.e.  the value of field on
     * coincident GLL points are properly summed together. 
     * @param name Name of field to assemble on global dofs.
     */
    void assembleLocalFieldToGlobal(const std::string &name);

    /**
     * Begins the local -> global MPI sends for a given field name. The
     * send is performed with an sum, i.e.  the value of field on
     * coincident GLL points are properly summed together. Note that
     * this function is non-blocking!! This MUST be paired with an
     * equivalent call to `assembleLocalFieldToGlobalEnd`.
     * @param name Name of field to assemble on global dofs.
     */
    void assembleLocalFieldToGlobalBegin(const std::string &name);

    /**
     * Makes a processor local array "global". As a "set", does not incurr any communication.
     * @param name Name of field to assemble on global dofs.
     */
    void setLocalFieldToGlobal(const std::string &name);
    
    /**
     * Finishes the local -> global MPI sends for a given field name. The
     * send is performed with an sum, i.e.  the value of field on
     * coincident GLL points are properly summed together. This MUST be paired with an
     * equivalent call to `assembleLocalFieldToGlobalBegin`.
     * @param name Name of field to assemble on global dofs.
     */
    void assembleLocalFieldToGlobalEnd(const std::string &name);
        
    /**
     * Begins the local -> global MPI sends for a given field name. The send is performed with an implied sum, i.e.
     * the value of field on coincident GLL points are properly summed together. Note that this function is
     * non-blocking!! This MUST be paired with an equivalent call to checkInFieldEnd.
     * @param name Name of field to checkin.
     */
    void checkInFieldBegin(const std::string &name);

    /**
     * Ends the local -> global MPI send for a given field name. This function should come after an equivalent
     * checkInFieldBegin. This method is blocking, so you can be confident that when it returns the desired field has
     * been scattered and summed into the global (parallel) degrees of freedom.
     * @param name Name of field to checkin.
     */
    void checkInFieldEnd(const std::string &name);

    /**
     * Returns an ordered vector of a field (i.e. x-displacement) on an element, via a call to DMPlexVecGetClosure.
     * Note that a vector containing the closure mapping must also be passed in -- this should change in the future.
     * @param [in] name Name of field.
     * @param [in] element_number Element number (on the local processor) for which the field is requested.
     * @param [in] closure A vector of size mNumberIntegrationPoints, which specifies the mapping from the Plex element
     * closure to the desired gll point ordering.
     * @ return The ordered field on an element.
     */
    Eigen::VectorXd getFieldOnElement(const std::string &name, const int &element_number,
                                      const Eigen::VectorXi &closure);

    /**
     * Sums a field on an element into the degrees of freedom owned by the local processor, via a call to
     * DMPlexVecSetClosure.
     * @param [in] field_name Name of field.
     * @param [in] element_number Element number (on the local processor) for which the field is requested.
     * @param [in] closure A vector of size mNumberIntegrationPoints, which specifies the mapping from the Plex element
     * closure to the desired gll point ordering.
     * @param [in] field The element-ordered field (i.e. x-displacement) to sum into the mesh.
     */
    void setFieldOnElement(const std::string &name, const int &element_number,
                           const Eigen::VectorXi &closure, const Eigen::VectorXd &field);


    /**
     * Sets a field from an element into the degrees of freedom owned by the local processor, via a call to
     * DMPlexVecSetClosure. Shared DOF should be identical, and are thus set from an arbitrary element.
     * @param [in] field_name Name of field.
     * @param [in] element_number Element number (on the local processor) for which the field is requested.
     * @param [in] closure A vector of size mNumberIntegrationPoints, which specifies the mapping from the Plex element
     * closure to the desired gll point ordering.
     * @param [in] field The element-ordered field (i.e. x-displacement) to sum into the mesh.
     */
    void setFieldFromElement(const std::string &name, const int element_number,
                             const Eigen::VectorXi &closure, const Eigen::VectorXd &field);
    
    /**
     * Sums a field from an element into the degrees of freedom owned by the local processor, via a call to
     * DMPlexVecSetClosure. Shared DOF are summed (i.e., assembled).
     * @param [in] field_name Name of field.
     * @param [in] element_number Element number (on the local processor) for which the field is requested.
     * @param [in] closure A vector of size mNumberIntegrationPoints, which specifies the mapping from the Plex element
     * closure to the desired gll point ordering.
     * @param [in] field The element-ordered field (i.e. x-displacement) to sum into the mesh.
     */
    void addFieldFromElement(const std::string &name, const int element_number,
                           const Eigen::VectorXi &closure, const Eigen::VectorXd &field);
    
    /**
     * Number of elements owned by the current processors.
     * @ return Number of Elements.
     */
    inline PetscInt NumberElementsLocal() { return mNumberElementsLocal; }

    /**
     * Defines the field to visualize, and the name of the file to dump to.
     * @param [in] movie_filename Where to save the file.
     * TODO: Should add field name here, and interval? Do we need to support other dump options than HDF5?
     */
    void setUpMovie(const std::string &movie_filename);

    /**
     * Commits a movie frame to disk, using the interface defined in setUpMovie.
     */
    void saveFrame(std::string name);

    /**
     * Needs to be called at the end of a time loop if a movie is desired.
     * Cleans up the open HDF5 file, and safely shuts down the output stream.
     */
    void finalizeMovie();

    /**
     * Set a desired vec_struct to zero. Usefull for those terms which we sum into (i.e. element forcing).
     */
    void zeroFields(const std::string &name);

    /**
     * Virtual function which implements the time stepping.
     * This will change based on physics, time stepping routine, and dimension.
     */
    virtual void advanceField() = 0;

    /**
     * Virtual function to register the fields on the global dofs.
     * This will change based on physics, time stepping routine, and dimension. See some of the example classes
     * below for how this function is to be used. In a nutshell though, you will create a vec_struct, saved in the
     * dictionary mFields, which contains a reference to both a local and global PETSc vector.
     */
    virtual void registerFields() = 0;

    /**
     * Virtual function to apply the inverse of a mass matrix.
     * This is usually called at the beginning of a time loop. Again, it will depend on the specific physics and
     * time scheme used. When this function is complete, the global fields should be ready to take a time-step (at
     * least that's the case for explicit schemes).
     */
    virtual void applyInverseMassMatrix() = 0;

    /**
     * Distributed mesh getattr.
     * TODO: I don't think we actually need these anymore.
     */
    inline DM &DistributedMesh() { return mDistributedMesh; }
    inline PetscSection &MeshSection() { return mMeshSection; }

};

#endif //SALVUS_MESH_H