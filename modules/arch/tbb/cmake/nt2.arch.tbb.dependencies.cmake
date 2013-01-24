################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# avoid re-checking every time
if(DEFINED TBB_CXX_FLAGS AND NOT TBB_CXX_FLAGS)
  set(TBB_FOUND 0)
else()
  set(TBB_ROOT $ENV{TBBROOT} )
  set(TBB_ARCH $ENV{TBB_ARCH})
  if(DEFINED TBB_ROOT AND TBB_ARCH)
    include(nt2.info)
    set(TBB_INCLUDE_PATH "${TBB_ROOT}/include/")
    set(TBB_CXX_FLAGS "-DNT2_USE_TBB")
    set(TBB_FOUND 1)
    set(TBB_LIBRARY optimized tbb debug tbb_debug)
    if(DEFINED NT2_ARCH_X86_64)
      set(TBB_LIBRARY_PATH "${TBB_ROOT}/lib/intel64/${TBB_ARCH}/")
    elseif(DEFINED NT2_ARCH_X86)
      set(TBB_LIBRARY_PATH "${TBB_ROOT}/lib/ia32/${TBB_ARCH}/")
    else()
      set(TBB_FOUND 0)
    endif()
  endif()
endif()

set(NT2_ARCH.TBB_DEPENDENCIES_FOUND              ${TBB_FOUND})
set(NT2_ARCH.TBB_COMPILE_FLAGS               ${TBB_CXX_FLAGS})
set(NT2_ARCH.TBB_DEPENDENCIES_INCLUDE_DIR ${TBB_INCLUDE_PATH})
set(NT2_ARCH.TBB_DEPENDENCIES_LIBRARY_DIR ${TBB_LIBRARY_PATH})
set(NT2_ARCH.TBB_DEPENDENCIES_LIBRARIES        ${TBB_LIBRARY})

set(NT2_ARCH.TBB_DEPENDENCIES_EXTRA core.utility)
