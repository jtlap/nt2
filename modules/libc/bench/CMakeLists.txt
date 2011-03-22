##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

################################################################################
# Add global bench driver rules
################################################################################
ADD_CUSTOM_TARGET(libc.scalar.bench)
ADD_CUSTOM_TARGET(libc.simd.bench)
ADD_CUSTOM_TARGET(libc.bench)

##****************************************************************************
##*     Toolbox libc bench tests
##****************************************************************************

ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)

################################################################################
# Add driver rule dependencies
################################################################################
ADD_DEPENDENCIES(libc.bench libc.scalar.bench)
ADD_DEPENDENCIES(libc.bench libc.simd.bench)
#ADD_DEPENDENCIES(bench libc.bench)