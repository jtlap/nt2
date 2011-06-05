
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
ADD_CUSTOM_TARGET(bessel.scalar.cover)
ADD_CUSTOM_TARGET(bessel.simd.cover)
ADD_DEPENDENCIES(bessel.cover bessel.scalar.cover bessel.simd.cover)

##############################################################################
# Toolbox bessel cover tests
##############################################################################
nt2_module_use_modules(cover predicates arithmetic trigonometric exponential cephes)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)

