
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
ADD_CUSTOM_TARGET(fdlibm.scalar.cover)
ADD_DEPENDENCIES(fdlibm.cover fdlibm.scalar.cover )

##############################################################################
# Toolbox fdlibm cover tests
##############################################################################
nt2_module_use_modules( unit
                        core.arithmetic core.ieee         core.trigonometric
                        core.hyperbolic core.exponential  core.euler
                        core.bessel
                      )
ADD_SUBDIRECTORY(scalar)

