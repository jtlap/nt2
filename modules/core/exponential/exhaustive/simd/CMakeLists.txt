##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET(SOURCES
    log.cpp
    log2.cpp
    log10.cpp
    exp.cpp
    exp2.cpp
    exp10.cpp
    cbrt.cpp
    expm1.cpp
    log1p.cpp
    expx2.cpp
    pow.cpp
   )

nt2_module_add_tests(core.exponential.simd.exhaustive ${SOURCES})
