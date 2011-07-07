##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

##############################################################################
###     Toolbox arithmetic bench tests
##############################################################################

ADD_CUSTOM_TARGET(simd_arithmetic.scalar.bench)
ADD_CUSTOM_TARGET(simd_arithmetic.simd.bench)
ADD_DEPENDENCIES(simd_arithmetic.bench simd_arithmetic.scalar.bench simd_arithmetic.simd.bench)

nt2_module_use_modules(simd_unit)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)
