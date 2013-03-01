################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.blas)

if(NOT NT2_BLAS_FOUND OR NOT NT2_LAPACK_FOUND)
  set(NT2_CORE.LINALG_DEPENDENCIES_FOUND 0)
else()
  set(NT2_CORE.LINALG_DEPENDENCIES_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_LAPACK_LIBRARIES})
  set(NT2_CORE.LINALG_LINK_FLAGS ${NT2_BLAS_LINK_FLAGS})
  set(NT2_CORE.LINALG_DEPENDENCIES_EXTRA sdk.functor core.arithmetic core.random core.combinatorial core.exponential core.trigonometric type.complex.sdk)
endif()

foreach(library ${NT2_LAPACK_LIBRARIES})
  get_filename_component(NAME ${library} NAME_WE)
  string(TOLOWER ${NAME} NAME)
  if(${NAME} MATCHES "lapack")
    get_filename_component(PATH ${library} REALPATH)
    string(REGEX MATCH ".([0-9][0-9.]*)$" VERSION ${PATH})
    string(REGEX REPLACE "^\\." "" VERSION "${VERSION}")
    if(VERSION AND "${VERSION}" VERSION_LESS 3.3)
      message(STATUS "[nt2.linalg] LAPACK version older than 3.3, using workaround")
      set(NT2_CORE.LINALG_COMPILE_FLAGS "-DNT2_LAPACK_3_2_WORKAROUND")
    endif()
  endif()
endforeach()
