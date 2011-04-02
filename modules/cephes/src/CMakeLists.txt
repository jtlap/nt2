################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

nt2_module_source_setup(cephes)

set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} -DANSIC")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} -fno-builtin")
elseif(MSVC)
  set(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} /Oi-")
endif()

ADD_SUBDIRECTORY(cephes_single)
ADD_SUBDIRECTORY(cephes_double)
IF(NOT WIN32)
  ADD_SUBDIRECTORY(cephes_ldouble)
ENDIF()
