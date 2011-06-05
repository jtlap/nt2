
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Add global cover driver rules
################################################################################
ADD_CUSTOM_TARGET(hyperbolic.scalar.cover)
ADD_CUSTOM_TARGET(hyperbolic.simd.cover)
ADD_DEPENDENCIES(hyperbolic.cover hyperbolic.scalar.cover hyperbolic.simd.cover)

##############################################################################
# Toolbox hyperbolic cover tests
##############################################################################
nt2_module_use_modules(cover predicates arithmetic exponential cephes libc boost_math)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)

