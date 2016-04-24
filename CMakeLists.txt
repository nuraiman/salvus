cmake_minimum_required(VERSION 2.8.7)
project(salvus)

###############################################
# Set all necessary variables here.
# These variables can be set at the command line:
# `cmake ../ -DPETSC_DIR=/opt/petsc`
# or via `ccmake ../`, hitting `c`, editing the
# respective variable, and then `g`
SET(PETSC_DIR /opt/petsc CACHE PATH "PETSC install directory")
SET(EIGEN_INCLUDE /usr/include/eigen3 CACHE PATH "Eigen install directory")
###############################################

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of the builds, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(MPI REQUIRED)

link_directories(${PETSC_DIR}/lib)

FILE(GLOB QuadAutoGen src/cxx/Element/HyperCube/Quad/Autogen/*.c)
FILE(GLOB TriAutoGen src/cxx/Element/Simplex/Triangle/Autogen/*.c)

include_directories(
  ${MPI_INCLUDE_PATH}
  ${PETSC_DIR}/include/
  ${EIGEN_INCLUDE}
  src/cxx
  src/cxx/Testing
  src/cxx/Element
  src/cxx/Element/HyperCube
  src/cxx/Element/HyperCube/Quad
  src/cxx/Element/HyperCube/Quad/Autogen
  src/cxx/Element/HyperCube/Hex
  src/cxx/Element/Simplex
  src/cxx/Element/Simplex/Triangle
  src/cxx/Element/Simplex/Triangle/Autogen
  src/cxx/Element/Simplex/Tetrahedron
  src/cxx/Model)

set(SALVUS_SOURCES
  src/cxx/Problem/Problem.cpp
  src/cxx/Problem/FieldIo.cpp
  src/cxx/Problem/NewmarkGeneral.cpp
  src/cxx/Problem/NewmarkTesting.cpp
  src/cxx/Mesh/Mesh.cpp
  src/cxx/Mesh/ElasticNewmark2D.cpp
  src/cxx/Mesh/ScalarNewmark2D.cpp
  src/cxx/Element/Element.cpp
  src/cxx/Element/HyperCube/Quad.cpp
  src/cxx/Element/HyperCube/Quad/Elastic.cpp
  src/cxx/Element/HyperCube/Quad/Acoustic.cpp
  src/cxx/Element/HyperCube/Hexahedra.cpp
  src/cxx/Element/HyperCube/Hex/AcousticHex.cpp
  src/cxx/Element/Simplex/Triangle.cpp
  src/cxx/Element/Simplex/Triangle/AcousticTri.cpp
  src/cxx/Model/ExodusModel.cpp
  src/cxx/Utilities/Utilities.cpp
  src/cxx/Utilities/Options.cpp
  src/cxx/Source/Source.cpp
  src/cxx/Receiver/Receiver.cpp
  src/cxx/Receiver/ReceiverHdf5.cpp
  src/cxx/Utilities/kdtree.c
  ${QuadAutoGen}
  ${TriAutoGen}
  )      
            
add_executable(salvus
  ${SALVUS_SOURCES}
  src/cxx/Main.cpp)

add_executable(salvus_test
  ${SALVUS_SOURCES}
  src/cxx/Testing/test_main.cpp
  src/cxx/Testing/test_hexahedra.cpp
  src/cxx/Testing/test_exactsolution.cpp
  src/cxx/Testing/test_source.cpp
  src/cxx/Testing/test_receiver.cpp)

# run `make` (or `make -j5`) to build `salvus` executable
target_link_libraries(salvus ${MPI_LIBRARIES} petsc exodus netcdf hdf5)
# run `make salvus_test` to build testing executable.
target_link_libraries(salvus_test ${MPI_LIBRARIES} petsc exodus netcdf hdf5)
set_target_properties(salvus_test PROPERTIES EXCLUDE_FROM_ALL TRUE) # doesn't get built by `make`