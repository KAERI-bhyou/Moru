set(MKL_ARCH "intel64")
set(MKL_LINK "static")
set(MKL_THREADING "sequential")
set(MKL_INTERFACE "ilp64")
set(MKL_MPI "intelmpi")
set(Boost_NO_WARN_NEW_VERSIONS 1)
set(Boost_USE_STATIC_LIBS true)

find_package(MPI           REQUIRED COMPONENTS CXX)
find_package(OpenMP        REQUIRED COMPONENTS CXX)
find_package(MKL           CONFIG REQUIRED COMPONENTS CXX)
find_package(TBB           CONFIG REQUIRED)
find_package(Boost         REQUIRED COMPONENTS)
find_package(fmt           CONFIG REQUIRED)
find_package(spdlog        CONFIG REQUIRED)

find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")
# find_path(IF97_INCLUDE_DIRS "IF97.h")

message("Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIRS}")
message("Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

set(MAGI_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${EXPRTK_INCLUDE_DIRS}
    ${IF97_INCLUDE_DIRS}
    OpenMP::OpenMP_CXX
    MPI::MPI_CXX
    MKL::MKL
    TBB::tbb
    # nlohmann_json::nlohmann_json
)

set(MAGI_LINK_LIBRARY
    ${Boost_LIBRARIES}
    OpenMP::OpenMP_CXX
    MPI::MPI_CXX
    MKL::MKL
    TBB::tbb
    # nlohmann_json::nlohmann_json
)