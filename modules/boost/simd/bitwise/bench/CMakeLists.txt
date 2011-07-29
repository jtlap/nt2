##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

##############################################################################
###     Toolbox bitwise bench tests
##############################################################################

ADD_CUSTOM_TARGET(boost.simd.bitwise.scalar.bench)
ADD_CUSTOM_TARGET(boost.simd.bitwise.simd.bench)
ADD_DEPENDENCIES(boost.simd.bitwise.bench boost.simd.bitwise.scalar.bench boost.simd.bitwise.simd.bench)

nt2_module_use_modules(boost.simd.unit)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)
