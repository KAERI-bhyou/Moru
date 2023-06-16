set(MKL_ARCH "intel64")
set(MKL_LINK "static")
set(MKL_THREADING "sequential")
set(MKL_INTERFACE "ilp64")
set(MKL_MPI "intelmpi")
set(Boost_NO_WARN_NEW_VERSIONS 1)

find_package(MPI           REQUIRED COMPONENTS CXX)
find_package(OpenMP        REQUIRED COMPONENTS CXX)
find_package(MKL           CONFIG REQUIRED COMPONENTS CXX)
find_package(TBB           CONFIG REQUIRED)
find_package(fmt           CONFIG REQUIRED)
find_package(spdlog        CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")
find_path(IF97_INCLUDE_DIRS "IF97.h")

set(MORU_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${EXPRTK_INCLUDE_DIRS}
    ${IF97_INCLUDE_DIRS}
    OpenMP::OpenMP_CXX
    MPI::MPI_CXX
    MKL::MKL
    TBB::tbb
)

set(MORU_LINK_LIBRARY
    OpenMP::OpenMP_CXX
    MPI::MPI_CXX
    MKL::MKL
    TBB::tbb
    nlohmann_json::nlohmann_json
    spdlog::spdlog
)