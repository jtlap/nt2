##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

ADD_CUSTOM_TARGET(gsl_specfun.scalar.bench)
ADD_CUSTOM_TARGET(gsl_specfun.simd.bench)
ADD_DEPENDENCIES(gsl_specfun.bench gsl_specfun.scalar.bench gsl_specfun.simd.bench)

##****************************************************************************
##*     Toolbox gsl_specfun bench tests
##****************************************************************************

ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)
