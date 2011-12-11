################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    add_pointers.cpp
    all.cpp
    any.cpp
    as.cpp
    as_integer.cpp
    as_floating.cpp
    as_signed.cpp
    as_unsigned.cpp
    cardinal_of.cpp
    downgrade.cpp
    floating.cpp
    fusion.cpp
    hierarchy.cpp
    is_result_of_supported.cpp
    is_scalar.cpp
    is_signed.cpp
    m_arithmetic.cpp
    make_integer.cpp
    make_floating.cpp
    scalar_of.cpp
    sign_of.cpp
    strip.cpp
    upgrade.cpp
    view_at.cpp
    permute_view.cpp
   )

nt2_module_add_tests(sdk.meta.unit ${SOURCES})
