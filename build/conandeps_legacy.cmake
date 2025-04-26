message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(Eigen3)
find_package(GSL)
find_package(qcdnum)

set(CONANDEPS_LEGACY  Eigen3::Eigen  GSL::gsl  qcdnum::qcdnum )