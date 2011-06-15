################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(matlab)

set(NT2_MW_LIBRARY "${CMAKE_SHARED_LIBRARY_PREFIX}nt2_mw${CMAKE_SHARED_LIBRARY_SUFFIX}")

if(NOT EXISTS ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
  file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
endif()
if(NOT EXISTS ${LIBRARY_OUTPUT_PATH})
  file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
endif()

add_custom_target(nt2_mw_lib
                  COMMAND ${MATLAB_BIN_DIR}/mcc -B "csharedlib:libnt2_mw" -d ${CMAKE_CURRENT_BINARY_DIR} feval
                 )
add_custom_target(nt2_mw_mv_header
                  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/libnt2_mw.h ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/libnt2_mw.h
                  DEPENDS nt2_mw_lib
                  )
add_custom_target(nt2_mw_mv_lib
                  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_BINARY_DIR}/${NT2_MW_LIBRARY} ${LIBRARY_OUTPUT_PATH}/${NT2_MW_LIBRARY}
                  DEPENDS nt2_mw_lib
                  )
add_custom_target(nt2_mw
                  DEPENDS nt2_mw_mv_header nt2_mw_mv_lib
                 )

install(FILES ${LIBRARY_OUTPUT_PATH}/${NT2_MW_LIBRARY}
        DESTINATION lib
        COMPONENT ${NT2_CURRENT_MODULE}
       )
