project(cv_cpp_utils)

cmake_minimum_required(VERSION 2.6)


set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -pg")
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -g -pg")
# message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

##-----------------------------------------------------------------------------
#Eigen
set(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
if(NOT EIGEN3_INCLUDE_DIR)
    message(FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()
include_directories(${EIGEN3_INCLUDE_DIR})
# Eigen should not use parallelization
add_definitions(-DEIGEN_DONT_PARALLELIZE)


##-----------------------------------------------------------------------------
#OpenCV
find_package(OpenCV REQUIRED core imgproc highgui objdetect)
if (OpenCV_FOUND)
    message(STATUS "OpenCV ${OpenCV_VERSION} was found.")
    message(STATUS "OpenCV LIBS: ${OpenCV_LIBS}")
    include_directories(${OpenCV_INCLUDE_DIR})
else (OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV was not found.")
endif (OpenCV_FOUND)

##-----------------------------------------------------------------------------
#Boost
find_package(Boost COMPONENTS system chrono regex timer filesystem program_options REQUIRED)
if (Boost_FOUND)
    message(STATUS "Boost was found.")
    include_directories(${Boost_INCLUDE_DIR})
else (Boost_FOUND)
    message(FATAL_ERROR "Boost was not found.")
endif (Boost_FOUND)


##-----------------------------------------------------------------------------
#Zlib
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
  message(STATUS "ZLIB was found.")
  include_directories(${ZLIB_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "ZLIB was not found.")
endif()



##-----------------------------------------------------------------------------
#OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
  message(STATUS "OpenMP was found.")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else(OPENMP_FOUND)
  message(ERROR "OpenMP was not found.")
endif(OPENMP_FOUND)

##-----------------------------------------------------------------------------
#Protobuffers
find_package(Protobuf REQUIRED)
message(STATUS "PROTOBUF_LIBRARIES: ${PROTOBUF_LIBRARIES}")


# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories("include")

set(RV_LEARNUTILITIES_SRC
  #rv/cout
  src/rv/cout/colored_text_output.cpp
  #rv/ml/rf
  include/rv/ml/rf/proto/rf.pb.cc
  src/rv/ml/rf/data/imgreplicatebordersample.cpp
  src/rv/ml/rf/data/imgsample.cpp
  src/rv/ml/rf/data/patchsample.cpp
  src/rv/ml/rf/data/matsample.cpp
  src/rv/ml/rf/common.cpp
  src/rv/ml/rf/data/single_storage_sample.cpp
  src/rv/ml/rf/leafnodefcn/classificationleafnodefcn.cpp
  src/rv/ml/rf/leafnodefcn/leafnodefcn.cpp
  src/rv/ml/rf/leafnodefcn/make_leaf_node_fcn.cpp
  src/rv/ml/rf/leafnodefcn/meanregressionleafnodefcn.cpp
  src/rv/ml/rf/leafnodefcn/meanstdregressionleafnodefcn.cpp
  src/rv/ml/rf/leafnodefcn/medianregressionleafnodefcn.cpp
  src/rv/ml/rf/leafnodefcn/regressionregressionleafnodefcn.cpp
  src/rv/ml/rf/node/leafnode.cpp
  src/rv/ml/rf/node/splitnode.cpp
  src/rv/ml/rf/node/make_node.cpp
  src/rv/ml/rf/splitevaluator/splitevaluator.cpp
  src/rv/ml/rf/splitevaluator/informationgainclassificationsplitevaluator.cpp
  src/rv/ml/rf/splitevaluator/giniclassificationsplitevaluator.cpp
  src/rv/ml/rf/splitevaluator/tracecovregressionsplitevaluator.cpp
  src/rv/ml/rf/splitevaluator/weighted_trace_cov_regression_split_evaluator.cpp
  src/rv/ml/rf/splitevaluator/variancereductionregressionsplitevaluator.cpp
  src/rv/ml/rf/splitevaluator/make_split_evaluator.cpp
  src/rv/ml/rf/splitfunction/make_split_function.cpp
  src/rv/ml/rf/splitfunction/splitfunction.cpp
  src/rv/ml/rf/splitfunction/splitfunctionpixeldifference.cpp
  src/rv/ml/rf/splitfunction/splitfunctionpixeldifferencedependent.cpp
  src/rv/ml/rf/splitfunction/splitfunctionpixelvalue.cpp
  src/rv/ml/rf/splitfunction/split_function_basis_fcn.cpp
  src/rv/ml/rf/train/trainforest.cpp 
  src/rv/ml/rf/train/traintree.cpp 
  src/rv/ml/rf/train/traintreequeued.cpp
  src/rv/ml/rf/train/traintreerecursive.cpp
  src/rv/ml/rf/tree.cpp
  src/rv/ml/rf/forest.cpp
  #rv/ml/svm
  lib/liblinear/linear.cpp
  lib/liblinear/tron.cpp
  lib/liblinear/blas/daxpy.c
  lib/liblinear/blas/ddot.c
  lib/liblinear/blas/dnrm2.c
  lib/liblinear/blas/dscal.c
)

##-----------------------------------------------------------------------------
# Create Library
add_library(rv_cpp_utils SHARED ${RV_LEARNUTILITIES_SRC})
target_link_libraries(rv_cpp_utils ${OpenCV_LIBS} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} ${ZLIB_LIBRARIES})




