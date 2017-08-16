

SET(PROJECT_NAME jr3)

CMAKE_MINIMUM_REQUIRED(VERSION 2.7)

message ("GCL CMAKE_CURRENT_SOURCE_DIR = " ${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/
    /usr/include/eigen3/
    )

LINK_DIRECTORIES(
    #${CMAKE_CURRENT_SOURCE_DIR}/../../../lib
    )


SET(HEADERS
    #cController.h
    Jr3Sensor.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/dspfunc.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/fsensorLib.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/jr3.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/jr3_linux.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/jr3_lxrt.h
    #${CMAKE_CURRENT_SOURCE_DIR}/Jr3PciDriver/include/pcidsp.h
    )

SET(SOURCES
    #cController.cpp
    Jr3Sensor.cpp
    jr3DriverInterface.c

    )



add_executable( ${PROJECT_NAME} ${SOURCES} main.cpp)

#ADD_LIBRARY(${PROJECT_NAME} SHARED
#    ${HEADERS}
#    ${SOURCES}
#    )


#TARGET_LINK_LIBRARIES(${PROJECT_NAME}
#   yaml-cpp
#   rbdl
#   ${CHAI3D-DYN3D_LIBRARIES} 
#   ${CHAI3D_LIBRARIES} 
#   ${OPENGL_LIBRARIES}
#   )


