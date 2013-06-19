################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

set(MAGMA_FOUND 0)
if(DEFINED MAGMA_CXX_FLAGS AND NOT MAGMA_CXX_FLAGS)
  set(MAGMA_FOUND 0)
else()

  # try to find libmagma
  find_library( MAGMA_MAGMA_LIBRARY
                NAMES magma
                PATHS /usr/local/lib /usr/lib ${MAGMA_ROOT}/lib
              )

  # try to find libmagmablas
  find_library( MAGMA_MAGMABLAS_LIBRARY
                NAMES magmablas
                PATHS /usr/local/lib /usr/lib ${MAGMA_ROOT}/lib
              )

  # try find magma.h
  find_path(  MAGMA_MAGMA_HEADER
              NAMES magma.h
              PATHS /usr/local/include /usr/include ${MAGMA_ROOT}/include
            )

  # if everything is there ...
  if(MAGMA_MAGMA_LIBRARY AND MAGMA_MAGMABLAS_LIBRARY AND MAGMA_MAGMA_HEADER)
    set(MAGMA_FOUND 1)
    set(MAGMA_INCLUDE_PATH "${MAGMA_MAGMA_HEADER}/")
    set(MAGMA_CXX_FLAGS "-DNT2_USE_MAGMA")
    set(MAGMA_LIBRARY ${MAGMA_MAGMA_LIBRARY} ${MAGMA_MAGMABLAS_LIBRARY})
  endif()
endif()

set(NT2_BINDING.MAGMA_DEPENDENCIES_FOUND              ${MAGMA_FOUND})
set(NT2_BINDING.MAGMA_COMPILE_FLAGS               ${MAGMA_CXX_FLAGS})
set(NT2_BINDING.MAGMA_DEPENDENCIES_INCLUDE_DIR ${MAGMA_INCLUDE_PATH})
set(NT2_BINDING.MAGMA_DEPENDENCIES_LIBRARIES        ${MAGMA_LIBRARY})

set(NT2_BINDING.MAGMA_DEPENDENCIES_EXTRA sdk.functor core.linalg)
