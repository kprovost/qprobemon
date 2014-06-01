cmake_minimum_required(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

project(qprobemon)
find_package(Qt4 REQUIRED QtCore QtGui)
find_package(Iw REQUIRED)
find_package(pcap REQUIRED)

set(SRC
    src/main.cpp
    src/InterfaceManager.cpp
    src/MacAddress.cpp
    src/MainWindow.cpp
    src/Packet.cpp
    src/ProbeRequestFilter.cpp
    src/Sniffer.cpp)

set(HDR
    src/InterfaceManager.h
    src/MacAddress.h
    src/MainWindow.h
    src/Packet.h
    src/ProbeRequestFilter.h
    src/Sniffer.h)

qt4_wrap_cpp(HDR_MOC ${HDR})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(CMAKE_CXX_FLAGS "-g -Wall -Werror")

include_directories(${IW_INCLUDE_DIR})
include_directories(${PCAP_INCLUDE_DIR})

add_executable(qprobemon ${SRC} ${HDR_MOC})
target_link_libraries(qprobemon ${QT_LIBRARIES} ${IW_LIBRARIES} ${PCAP_LIBRARIES})
install(TARGETS qprobemon DESTINATION bin)
