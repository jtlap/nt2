################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.doc)

nt2_module_doc( boost.simd.doc
                simd.qbk
              )

if(NOT IS_DIRECTORY ${NT2_BINARY_DIR}/doc/html/simd)
  file(MAKE_DIRECTORY ${NT2_BINARY_DIR}/doc/html/simd)
endif()
