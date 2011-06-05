
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
ADD_CUSTOM_TARGET(fuzzy.scalar.cover)
ADD_CUSTOM_TARGET(fuzzy.simd.cover)
ADD_DEPENDENCIES(fuzzy.cover fuzzy.scalar.cover fuzzy.simd.cover)

##############################################################################
# Toolbox fuzzy cover tests
##############################################################################
nt2_module_use_modules(cover predicates)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)

