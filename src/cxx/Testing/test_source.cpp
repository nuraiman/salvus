#include <petsc.h>
#include <Eigen/Dense>
#include <Utilities/Options.h>
#include <Source/Source.h>
#include <Mesh/Mesh.h>
#include <Model/ExodusModel.h>
#include <Problem/Problem.h>
#include <Element/HyperCube/TensorQuad.h>
#include <Element/HyperCube/QuadP1.h>
#include <Physics/Scalar.h>
#include "hdf5.h"
#include "hdf5_hl.h"
#include <exception>
#include "catch.h"

using namespace std;

double true_ricker(const PetscReal time, const PetscReal freq,
                   const PetscReal delay, const PetscReal amp) {
  double factor = M_PI * M_PI * freq * freq * (time - delay) * (time - delay);
  return amp * ((1 - 2 * factor) * exp(-1 * factor));
}

/* Test plugins. */
template <typename Element>
class QuadTestPlugin: public Element {
 public:
  QuadTestPlugin<Element>(unique_ptr<Options> const &options): Element(options) {};
};

typedef class Scalar<TensorQuad<QuadP1>> quadtest_p1;


TEST_CASE("Test source functionality", "[source]") {

  SECTION("unit") {

    SECTION("ricker source from hdf5") {

      // write hdf5 source file
      std::string source_file("source.h5");
      PetscInt rank; MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
      std::vector<double> loc1{50000, 50000, 50000};
      std::vector<double> loc2{50000, 90000, 90000};

      vector<PetscReal> x{50000, 50000};
      vector<PetscReal> y{50000, 90000};
      vector<PetscReal> z{50000, 90000};

      /* True options. */
      vector<int> source_components{1,2};
      vector<double> ricker_amp{10.0, 20.0};
      vector<double> ricker_time{0.1, 0.01};
      vector<double> ricker_freq{50.0, 60.0};
      vector<double> ricker_dir{0.0, 1.0};

      if ( !rank ) {
        hid_t           file;
        hid_t           group;
        herr_t          status;
      
        file =  H5Fcreate(source_file.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        group = H5Gcreate2(file, "/source1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Gclose (group);
        group = H5Gcreate2(file, "/source2", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Gclose (group);
        std::string source_type("ricker");

        H5LTset_attribute_string(file, "/", "type", source_type.c_str());

        H5LTset_attribute_double(file, "/source1", "location", loc1.data(), 3);
        H5LTset_attribute_int(file, "/source1", "num-components", &(source_components[0]), 1);
        H5LTset_attribute_double(file, "/source1", "ricker-amplitude", &(ricker_amp[0]), 1);
        H5LTset_attribute_double(file, "/source1", "ricker-center-freq", &(ricker_freq[0]), 1);
        H5LTset_attribute_double(file, "/source1", "ricker-time-delay", &(ricker_time[0]), 1);

        H5LTset_attribute_double(file, "/source2", "location", loc2.data(), 3);
        H5LTset_attribute_int(file, "/source2", "num-components", &(source_components[1]), 1);
        H5LTset_attribute_double(file, "/source2", "ricker-amplitude", &(ricker_amp[1]), 1);
        H5LTset_attribute_double(file, "/source2", "ricker-center-freq", &(ricker_freq[1]), 1);
        H5LTset_attribute_double(file, "/source2", "ricker-time-delay", &(ricker_time[1]), 1);
        H5LTset_attribute_double(file, "/source2", "ricker-direction", ricker_dir.data(), 2);

        status = H5Fclose (file);
        MPI_Barrier(PETSC_COMM_WORLD);
      }

      PetscOptionsClear(NULL);
      const char *arg[] =
      {"salvus_test", "--testing", "true", "--source-file-name", source_file.c_str(), NULL};

      char **argv = const_cast<char **> (arg);
      int argc = sizeof(arg) / sizeof(const char *) - 1;
      PetscOptionsInsert(NULL, &argc, &argv, NULL);

      /* Need something to complete the source, so we choose ricker. */
      std::unique_ptr<Options> options(new Options);
      options->SetDimension(3);
      options->setOptions();
      auto sources = Source::Factory(options);

      /* Require that naming worked correctly. */
      REQUIRE(Source::NumSources() == 2);

      for (PetscInt i = 0; i < Source::NumSources(); i++) {
        REQUIRE(sources[i]->LocX() == x[i]);
        REQUIRE(sources[i]->LocY() == y[i]);
        REQUIRE(sources[i]->LocZ() == z[i]);
      }

      /* Require ricker source fires properly. */
      for (PetscInt i = 0; i < Source::NumSources(); i++) {
        REQUIRE(sources[i]->Num() == i);
        for (PetscInt j = 0; j < 1000; j++) {
          PetscReal time = j * 1e-3;
          Eigen::VectorXd sim_ricker(sources[i]->fire(time, j));
          REQUIRE( sim_ricker.sum()
                      == Approx(true_ricker(time, ricker_freq[i], ricker_time[i], ricker_amp[i])));
        }
      }

    }

    SECTION("source from hdf5") {

      // write hdf5 source file
      std::string source_file("source.h5");
      std::vector<double> loc1{50000, 50000, 50000};
      std::vector<double> loc2{50000, 90000, 90000};

      vector<PetscReal> x{50000, 50000};
      vector<PetscReal> y{50000, 90000};
      vector<PetscReal> z{50000, 90000};

      /* True options. */
      vector<int> source_components{1,2};
      vector<double> ricker_amp{10.0, 20.0};
      vector<double> ricker_time{0.1, 0.01};
      vector<double> ricker_freq{50.0, 60.0};

      const hsize_t nTimeSteps = 1000;

      PetscInt rank; MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
      if ( !rank ) {
        hid_t           file;
        hid_t           group;
        herr_t          status;
      
        file =  H5Fcreate(source_file.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        group = H5Gcreate2(file, "/source1", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        group = H5Gcreate2(file, "/source2", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        std::string source_type("file");

        H5LTset_attribute_string(file, "/", "type", source_type.c_str());
        H5LTset_attribute_double(file, "/source1", "location", loc1.data(), 3);
        H5LTset_attribute_int(file, "/source1", "num-components", &(source_components[0]), 1);

        H5LTset_attribute_double(file, "/source2", "location", loc2.data(), 3);
        H5LTset_attribute_int(file, "/source2", "num-components", &(source_components[1]), 1);

        std::vector<PetscReal> source_time_function(nTimeSteps);
        for (PetscInt j = 0; j < nTimeSteps; j++) {
          PetscReal time = j * 1e-3;
          source_time_function[j] = true_ricker(time, ricker_freq[0], ricker_time[0], ricker_amp[0]);
        }
        
        H5LTmake_dataset_double (file, "/source1/data", 1, &nTimeSteps, source_time_function.data());
        
        Eigen::MatrixXd source_time_function2;
        source_time_function2.setZero(nTimeSteps,2);
        for (PetscInt j = 0; j < nTimeSteps; j++) {
          PetscReal time = j * 1e-3;
          source_time_function2(j,0) = true_ricker(time, ricker_freq[1], ricker_time[1], ricker_amp[1]);
          source_time_function2(j,1) = true_ricker(time, ricker_freq[1], ricker_time[1], ricker_amp[1]);
        }
        const hsize_t nTimeSteps2[2] = {2, 1000};
        H5LTmake_dataset_double (file, "/source2/data", 2, nTimeSteps2, source_time_function2.data());

        status = H5Fclose (file);
      }
      PetscOptionsClear(NULL);
      const char *arg[] =
      {"salvus_test", "--testing", "true", "--duration", "1",
       "--time-step", "1e-3", "--source-file-name", source_file.c_str(), NULL};

      char **argv = const_cast<char **> (arg);
      int argc = sizeof(arg) / sizeof(const char *) - 1;
      PetscOptionsInsert(NULL, &argc, &argv, NULL);

      /* Need something to complete the source, so we choose ricker. */
      std::unique_ptr<Options> options(new Options);
      options->SetDimension(3);
      options->setOptions();
      auto sources = Source::Factory(options);

      /* Require that naming worked correctly. */
      REQUIRE(Source::NumSources() == 2);

      for (PetscInt i = 0; i < Source::NumSources(); i++) {
        REQUIRE(sources[i]->LocX() == x[i]);
        REQUIRE(sources[i]->LocY() == y[i]);
        REQUIRE(sources[i]->LocZ() == z[i]);
      }

      /* Require ricker source fires properly. */
      for (PetscInt i = 0; i < Source::NumSources(); i++) {
        REQUIRE(sources[i]->Num() == i);
        sources[i]->loadData();
        for (PetscInt j = 0; j < nTimeSteps; j++) {
          PetscReal time = j * 1e-3;
          Eigen::VectorXd sim_ricker(sources[i]->fire(time, j));
          REQUIRE( sim_ricker.sum()
                      == Approx((i+1.0) * true_ricker(time, ricker_freq[i], ricker_time[i], ricker_amp[i])));
        }
      }
    }


    PetscOptionsClear(NULL);
    const char *arg[] =
        {"salvus_test", "--testing", "true", "--number-of-sources", "2", "--source-type", "ricker",
         "--source-location-x", "50000,50000", "--source-location-y", "50000,90000", "--source-location-z", "50000,90000",
         "--ricker-amplitude", "10,20", "--ricker-time-delay", "0.1,0.01",
         "--ricker-center-freq", "50,60", NULL};

    char **argv = const_cast<char **> (arg);
    int argc = sizeof(arg) / sizeof(const char *) - 1;
    PetscOptionsInsert(NULL, &argc, &argv, NULL);

    SECTION("general") {

      vector<PetscReal> x{50000, 50000};
      vector<PetscReal> y{50000, 90000};
      vector<PetscReal> z{50000, 90000};

      /* Need something to complete the source, so we choose ricker. */
      PetscOptionsSetValue(NULL, "--ricker-amplitude", "10,20");
      PetscOptionsSetValue(NULL, "--ricker-time-delay", "0.1,0.01");
      PetscOptionsSetValue(NULL, "--ricker-center-freq", "50,60");
      PetscOptionsSetValue(NULL, "--source-num-components", "1,1");
      std::unique_ptr<Options> options(new Options);
      options->SetDimension(3);
      options->setOptions();
      auto sources = Source::Factory(options);

      /* Require that naming worked correctly. */
      REQUIRE(Source::NumSources() == 2);

      for (PetscInt i = 0; i < Source::NumSources(); i++) {
        REQUIRE(sources[i]->LocX() == x[i]);
        REQUIRE(sources[i]->LocY() == y[i]);
        REQUIRE(sources[i]->LocZ() == z[i]);
      }

      /* Require deletion works properly. */
      sources.back().reset();
      REQUIRE(Source::NumSources() == 1);
      sources[0].reset();
      REQUIRE(Source::NumSources() == 0);

    }

    SECTION("ricker") {

      /* Options for ricker. */
      PetscOptionsSetValue(NULL, "--ricker-amplitude", "10,20");
      PetscOptionsSetValue(NULL, "--ricker-time-delay", "0.1,0.01");
      PetscOptionsSetValue(NULL, "--ricker-center-freq", "50,60");
      PetscOptionsSetValue(NULL, "--source-num-components", "1,1");
      std::unique_ptr<Options> options(new Options);
      options->setOptions();

      /* True options. */
      vector<PetscReal> ricker_amp{10, 20};
      vector<PetscReal> ricker_time{0.1, 0.01};
      vector<PetscReal> ricker_freq{50, 60};

      auto sources = Source::Factory(options);

      /* Require ricker source fires properly. */
      for (PetscInt i = 0; i < Source::NumSources(); i++) {
        REQUIRE(sources[i]->Num() == i);
        for (PetscInt j = 0; j < 1000; j++) {
          PetscReal time = j * 1e-3;
          Eigen::VectorXd sim_ricker(sources[i]->fire(time, j));
          REQUIRE( sim_ricker(0) 
                      == true_ricker(time, ricker_freq[i], ricker_time[i], ricker_amp[i]));
        }
      }

    }

    SECTION("integration_3d") {

      string e_file = "small_hex_mesh_to_test_sources.e";
      PetscOptionsSetValue(NULL, "--mesh-file", e_file.c_str());
      PetscOptionsSetValue(NULL, "--model-file", e_file.c_str());
      PetscOptionsSetValue(NULL, "--polynomial-order", "3");
      PetscOptionsSetValue(NULL, "--source-num-components", "1,1");
      std::unique_ptr<Options> options(new Options);
      options->SetDimension(3);
      options->setOptions();

      unique_ptr<ExodusModel> model(new ExodusModel(options));
      model->read();

      unique_ptr<Mesh> mesh(new Mesh(options));
      mesh->read();
      mesh->setupTopology(model, options);
      auto problem = Problem::Factory(options);
      auto elements = problem->initializeElements(mesh, model, options);
      mesh->setupGlobalDof(elements[0], options);

      /* True values. */
      std::vector<PetscInt> locations {1, 0, 0, 0, 0, 0, 1, 0};
      vector<PetscReal> ricker_amp{10, 20};
      vector<PetscReal> ricker_time{0.1, 0.01};

      SECTION("quad") {
        for (auto &e: elements) {
          if (e->Num() == 0) {
            REQUIRE(e->computeSourceTerm(ricker_time[0],0).sum() == Approx(ricker_amp[0]));
          }
          else if (e->Num() == 6) {
            REQUIRE(e->computeSourceTerm(ricker_time[1],0).sum() == Approx(ricker_amp[1]));
          }
          else {
            REQUIRE(e->computeSourceTerm(ricker_time[0],0).sum() == Approx(0.0));
            REQUIRE(e->computeSourceTerm(ricker_time[1],0).sum() == Approx(0.0));
          }
        }
      }
    }

    SECTION("integration_2d") {

      string e_file = "fluid_layer_over_elastic_cartesian_2D_50s.e";
      PetscOptionsSetValue(NULL, "--mesh-file", e_file.c_str());
      PetscOptionsSetValue(NULL, "--model-file", e_file.c_str());
      PetscOptionsSetValue(NULL, "--polynomial-order", "9");
      PetscOptionsSetValue(NULL, "--source-num-components", "2,1");
      std::unique_ptr<Options> options(new Options);
      options->SetDimension(2);
      options->setOptions();

      unique_ptr<ExodusModel> model(new ExodusModel(options));
      model->read();

      unique_ptr<Mesh> mesh(new Mesh(options));
      mesh->read();
      mesh->setupTopology(model, options);
      auto problem = Problem::Factory(options);
      auto elements = problem->initializeElements(mesh, model, options);
      mesh->setupGlobalDof(elements[0], options);

      /* True values. */
      vector<PetscReal> ricker_amp{10, 20};
      vector<PetscReal> ricker_time{0.1, 0.01};

      SECTION("quad") {
        for (auto &e: elements) {
          if (e->Num() == 0) {
            REQUIRE(e->computeSourceTerm(ricker_time[0],0).sum() == Approx(ricker_amp[0]));
          }
          else if (e->Num() == 2) {
            REQUIRE(e->computeSourceTerm(ricker_time[1],0).sum() == Approx(ricker_amp[1]));
          }
          else {
            REQUIRE(e->computeSourceTerm(ricker_time[0],0).sum() == Approx(0.0));
            REQUIRE(e->computeSourceTerm(ricker_time[1],0).sum() == Approx(0.0));
          }
        }
      }
    }

    SECTION("exceptions") {

      PetscOptionsSetValue(NULL, "--source-type", "ricke");
      PetscOptionsSetValue(NULL, "--source-num-components", "1,1");
      std:unique_ptr<Options> options(new Options);
      options->setOptions();

      /* If we put a bad source time in. */
      REQUIRE_THROWS_AS(Source::Factory(options), std::runtime_error);

    }

    SECTION("exceptions source file") {

      PetscOptionsSetValue(NULL, "--source-file-name", "no_source.h5");
      std::unique_ptr<Options> options(new Options);
        
      /* If we put a bad source file in. */
      REQUIRE_THROWS_AS(options->setOptions(), std::runtime_error);

    }
  }

}
