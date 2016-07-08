#pragma once

// stl.
#include <vector>
#include <iostream>
#include <memory>
#include <set>

// Salvus.
#include <Utilities/Types.h>
#include <Eigen/Dense>
#include <Element/Element.h>

class Mesh;
class Model;
class Options;

/**
 * This class is responsible for driving a (general) solve.
 *
 * The problem object defines a timestepper (or, frequency domain solve), and any derived
 * classes should be used to set up specific behavior. For example, for 2nd order Newmark,
 * the initializeGlobalDofs function just inverts a diagonal mass matrix, and applies this
 * matrix to the global degrees of freedom. For an implicit time-stepping scheme, this
 * function can be used to set up the sparsity pattern of the global matrix.
 */
class ProblemNew {

 protected:

  /**
   * Queries the graph closure for the mesh, and gets the field on a given element. Note that this
   * does not perform any parallel scattering.
   * @param [in] name A string specifying the field name.
   * @param [in] num The element number.
   * @param [in] closure A vector of indices specifying the correct locations in the global DOFs.
   * @param [in] PETScDM The PETSc DM object.
   * @param [in] PETScSection the PETSc section object.
   * @param [in/out] fields A map containing references to the global fields.
   * @returns A vector containing the field values on the element.
   */
  static RealVec getFieldOnElement(const std::string &name, const PetscInt num,
                                   const Eigen::Ref<const IntVec> &closure,
                                   DM PETScDM, PetscSection PETScSection,
                                   FieldDict &fields);

  /**
   * Queries the graph closure for the mesh, and sums (assembles) local field contribution
   * on a given element into the correct global DOFs. Note that this does not perform an parallel scattering.
   * @param [in] name A string specifying the field name.
   * @param [in] num The element number.
   * @param [in] closure A vector of indices specifying the correct locations in the global DOFs.
   * @param [in] field A vector containing the values to assemble.
   * @param [in] PETScDM The PETSc DM object.
   * @param [in] PETScSection the PETSc section object.
   * @param [in/out] fields A map containing references to the global fields.
   */
  static void addFieldOnElement(const std::string &name, const PetscInt num,
                                const Eigen::Ref<const IntVec> &closure,
                                const Eigen::Ref<const RealVec> &field,
                                DM PETScDM, PetscSection PETScSection,
                                FieldDict &fields);

  /**
   * Queries the global distributed DOFs for a certain field vector. If the vector exists,
   * it is properly transferred to the local partition (GlobalToLocal). If it does not exist,
   * an assertation error is thrown.
   * @param [in] name A string specifying the field name.
   * @param [in] PETScDM A pointer to the governing PETScDM.
   * @param [in/out] A map containing references to the global fields.
   */
  static void checkOutField(const std::string &name, DM PETScDM, FieldDict &fields);

  /**
   * Queries the global distributed DOfs for a certain field vector. If the vector exists,
   * it is properly transferred to the global partition (LocalToGlobal). If it does not exist,
   * and assertation error is thrown.
   * @param [in] name A string specifying the field name.
   * @param [in] PETScDM A pointer to the governing PETScDM.
   * @param [in/out] A map containing references to the global fields.
   */
  static void checkInField(const std::string &name, DM PETScDM, FieldDict &fields);

  /**
   * Sets a global/local field pair to zero.
   * @param [in] name A string specifying the field name.
   * @param [in/out] A map containing references to the global fields.
   */
  static void zeroField(const std::string &name, FieldDict &fields);

 public:

  /// Empty constructor.
  ProblemNew() {};

  /// Empty destructor.
  virtual ~ProblemNew() {};

  /**
   * Factory function to return an object based on a set of runtime options.
   * @param [in] options A reference to the options class.
   * @returns A pointer to the appropriate problem class.
   */
  static std::unique_ptr<ProblemNew> Factory(std::unique_ptr<Options> const &options);

  /**
   * Given a mesh, model, and options, returns a vector of element mixins.
   * This function has the responsibility of initializing and setting up elements in all
   * different problem classes. In here, material parameters are attached to individual
   * elements, internal DOFs are set up, and sources and receivers are attached.
   * @param [in] mesh A pointer to the mesh wrapper.
   * @param [in] model A pointer to the model wrapper.
   * @param [in] options A reference to the options class.
   * @returns A vector of elements, ready for use.
   */
  static ElemVec initializeElements(std::unique_ptr<Mesh> const &mesh,
                                    std::unique_ptr<ExodusModel> const &model,
                                    std::unique_ptr<Options> const &options);


  /**
   * This function is responsible for computing element-wise forces, and then summing up
   * the accelerations into the global degrees of freedom. See internal for comprehensive documentation.
   * @param [in] elements Vector of all elements.
   * @param [in] FieldDict A map containing references to the global fields.
   * @param [in] PETScDM A pointer to the governing PETSc DM.
   * @param [in] PETScSection A point to the governing PETScSection.
   * @param [in] options A reference to the options class.
   * @returns A dictionary of modified fields.
   */
  static std::tuple<ElemVec, FieldDict> assembleIntoGlobalDof(ElemVec elements, FieldDict fields,
                                                              DM PETScDM, PetscSection PETScSection,
                                                              std::unique_ptr<Options> const &options);

  /**
   * Given a set of elements, initialize the global degrees of freedom in a way appropriate
   * for the problem as hand. I.e. set up a sparsity pattern, or create a global mass vector.
   * @param [in] elements Vector of all elements.
   * @param [in] mesh A pointer to the mesh wrapper.
   * @returns A dictionary of modified fields.
   */
  virtual FieldDict initializeGlobalDofs(ElemVec const &elements, std::unique_ptr<Mesh> &mesh) = 0;

  /**
   * Filter the acceleration through the inverse mass matrix (depending on the method).
   * @param [in] fields A map containing references to the global fields.
   * @returns A dictionary of modified fields.
   */
  virtual FieldDict applyInverseMassMatrix(FieldDict fields) = 0;

  /**
   * Advance all relevant fields in time. Note, this should likely be moved to a method
   * of a certain time-stepping class (i.e. makes no sense in the frequency domain).
   * @param [in] fields A map containing references to the global fields.
   * @returns A dictionary of modified fields.
   */
  virtual FieldDict takeTimeStep(FieldDict fields) = 0;

};

