find_path(RV_CPP_UTILS_INCLUDE_DIR rv/io/csv.h
          HINTS ${CMAKE_CURRENT_LIST_DIR}/../include)

find_library(RV_CPP_UTILS_LIBRARY NAMES rv_cpp_utils
             HINTS ${CMAKE_CURRENT_LIST_DIR}/../build )


find_package(OpenCV REQUIRED core imgproc highgui objdetect)
find_package(Boost COMPONENTS system chrono regex timer filesystem program_options thread REQUIRED)
find_package(Protobuf REQUIRED)
find_package(ZLIB REQUIRED)

#Eigen
set(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
if(NOT EIGEN3_INCLUDE_DIR)
    message(FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()
# Eigen should not use parallelization
add_definitions(-DEIGEN_DONT_PARALLELIZE)





find_package(OpenMP)
if (OPENMP_FOUND)
    message(STATUS "OpenMP was found.")
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS})
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS})
endif(OPENMP_FOUND)


#check optional components
if(rv_cpp_utils_FIND_COMPONENTS)
  message(STATUS "rv_cpp_utils components: ${rv_cpp_utils_FIND_COMPONENTS}")

  foreach(COMPONENT ${rv_cpp_utils_FIND_COMPONENTS})
    string(TOUPPER ${COMPONENT} UPPERCOMPONENT)
    
    if(${UPPERCOMPONENT} STREQUAL "CAMERA_PMD")
      find_path(PMD_INCLUDE_DIR NAMES pmdsdk2.h pmddatadescription.h pmdsdk2common.h)
      find_library(PMD_LIBRARY NAMES pmdaccess2)
      
      if(WIN32)
        set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
        file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/camboardpico.W64.pap DESTINATION ${BIN_DIR})
        file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/camboardpicoproc.W64.ppp DESTINATION ${BIN_DIR})
      elseif(UNIX)
        set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})
        file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/camboardpico.L64.pap DESTINATION ${BIN_DIR})
        file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/camboardpicoproc.L64.ppp DESTINATION ${BIN_DIR})
      endif()
      file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/2410933.dat DESTINATION ${BIN_DIR})
      file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/11140935.dat DESTINATION ${BIN_DIR})
      file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/11700935.dat DESTINATION ${BIN_DIR})
      file(COPY ${CMAKE_CURRENT_LIST_DIR}/../lib/pmd/cbm_snscfg.dat DESTINATION ${BIN_DIR})
    endif()
    
    if(${UPPERCOMPONENT} STREQUAL "CAMERA_CREATIVE_325")
      find_path(CREATIVE_INCLUDE_DIR NAMES DepthSense.hxx
                HINTS /opt/softkinetic/DepthSenseSDK/include)
      find_library(CREATIVE_LIBRARY NAMES DepthSense DepthSensePlugins udev
                   HINTS /opt/softkinetic/DepthSenseSDK/lib)
    endif()
  endforeach()
endif()


set(RV_CPP_UTILS_INCLUDE_DIRS 
  ${RV_CPP_UTILS_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${PMD_INCLUDE_DIR}
  ${CREATIVE_INCLUDE_DIR}
  ${EIGEN3_INCLUDE_DIR}
  ${ZLIB_INCLUDE_DIRS}
)

set(RV_CPP_UTILS_LIBRARIES 
  ${RV_CPP_UTILS_LIBRARY} 
  ${OpenCV_LIBS} 
  ${Boost_LIBRARIES} 
  ${PROTOBUF_LIBRARIES}
  ${PMD_LIBRARY}
  ${CREATIVE_LIBRARY}
  ${ZLIB_LIBRARIES}
)

message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(rv_cpp_utils  DEFAULT_MSG
                                  RV_CPP_UTILS_INCLUDE_DIR RV_CPP_UTILS_LIBRARY)

mark_as_advanced(RV_CPP_UTILS_INCLUDE_DIR RV_CPP_UTILS_LIBRARY)
