################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    as_integer.cpp
    as_floating.cpp
    as_signed.cpp
    as_unsigned.cpp
    as.cpp
    cardinal_of.cpp
    downgrade.cpp
    hierarchy_of.cpp
    is_signed.cpp
    is_simd_specific.cpp
    make_integer.cpp
    make_floating.cpp
    bitwise_cast.cpp
    scalar_of.cpp
    sign_of.cpp
    upgrade.cpp
    iterator.cpp
    pack.cpp
    logical.cpp
    transform.cpp
   )

nt2_module_add_tests(boost.simd.sdk.simd.unit ${SOURCES})

