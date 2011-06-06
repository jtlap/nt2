################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(cephes)
nt2_module_configure_toolbox(cephes 0)

include(nt2.info)
set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} -DANSIC")
if(NT2_COMPILER_GNU_C)
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} -fno-builtin")
elseif(NT2_COMPILER_MSVC)
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} /Oi-")
endif()

ADD_SUBDIRECTORY(cephes_single)
ADD_SUBDIRECTORY(cephes_double)

# 80-bit long double, x86 only, disabled on Windows
if(NT2_ARCH_X86 AND NOT NT2_OS_WINDOWS)
  ADD_SUBDIRECTORY(cephes_ldouble)
ENDIF()
