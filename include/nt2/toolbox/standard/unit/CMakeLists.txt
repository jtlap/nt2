##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

################################################################################
# Add global unit driver rules
################################################################################
ADD_CUSTOM_TARGET(standard.scalar.unit)
ADD_CUSTOM_TARGET(standard.simd.unit)
ADD_CUSTOM_TARGET(standard.unit)

##****************************************************************************
##*     Toolbox standard unit tests
##****************************************************************************

ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)

################################################################################
# Add driver rule dependencies
################################################################################
ADD_DEPENDENCIES(standard.unit standard.scalar.unit)
ADD_DEPENDENCIES(standard.unit standard.simd.unit)
ADD_DEPENDENCIES(unit standard.unit)