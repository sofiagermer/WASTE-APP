cmake_minimum_required(VERSION 3.19)
project(WASTE_APP)

set(CMAKE_CXX_STANDARD 14)

add_executable(WASTE_APP main.cpp TrashContainer.cpp TrashContainer.h House.cpp House.h GarbageCollectionFacility.cpp GarbageCollectionFacility.h User.cpp User.h Car.cpp Car.h Driver.cpp Driver.h Menu.cpp Menu.h Graph.cpp Graph.h MapPoint.cpp MapPoint.h)