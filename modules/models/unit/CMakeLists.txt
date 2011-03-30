##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

##############################################################################
###     Toolbox models unit tests
##############################################################################

ADD_CUSTOM_TARGET(models.scalar.unit)
ADD_CUSTOM_TARGET(models.simd.unit)
ADD_DEPENDENCIES(models.unit models.scalar.unit models.simd.unit)

#ADD_SUBDIRECTORY(scalar) # FIXME
#ADD_SUBDIRECTORY(simd) # FIXME
