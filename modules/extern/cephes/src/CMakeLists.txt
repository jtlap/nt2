################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(extern.cephes)
nt2_module_configure_toolbox(cephes 0)

include(nt2.info)
add_definitions(-DANSIC)
if(NT2_COMPILER_GCC)
  add_definitions(-fno-builtin -fno-strict-aliasing)
elseif(NT2_COMPILER_MSVC)
  add_definitions(/Oi-)
endif()

ADD_SUBDIRECTORY(cephes_single)
ADD_SUBDIRECTORY(cephes_double)

# 80-bit long double, x86 only, disabled on Windows
if(NT2_ARCH_X86 AND NOT NT2_OS_WINDOWS)
  ADD_SUBDIRECTORY(cephes_ldouble)
ENDIF()
