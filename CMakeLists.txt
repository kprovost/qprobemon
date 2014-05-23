cmake_minimum_required(VERSION 2.8)

project(qprobemon)
find_package(Qt4 REQUIRED QtCore QtGui)

set(SRC src/main.cpp)
set(HDR )

qt4_wrap_cpp(HDR_MOC ${HDR})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(qprobemon ${SRC} ${HDR_MOC})
target_link_libraries(qprobemon ${QT_LIBRARIES})
install(TARGETS qprobemon DESTINATION bin)
