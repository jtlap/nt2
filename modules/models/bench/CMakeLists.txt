##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

##############################################################################
###     Toolbox models bench tests
##############################################################################

ADD_CUSTOM_TARGET(models.scalar.bench)
ADD_CUSTOM_TARGET(models.simd.bench)
ADD_DEPENDENCIES(models.bench models.scalar.bench models.simd.bench)

ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)
