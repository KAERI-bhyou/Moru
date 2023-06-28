file(
  GLOB_RECURSE
    MORU_SRC CONFIGURE_DEPENDS
      ${CMAKE_CURRENT_SOURCE_DIR}/src/components/code.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/components/input.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/components/workflow.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/extractor.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/fftbm.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/generator.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/perturbator.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/sampler.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/config.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/runner.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/worker.cpp
)