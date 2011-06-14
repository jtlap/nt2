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
ADD_CUSTOM_TARGET(cephes.scalar.bench)
ADD_DEPENDENCIES(cephes.bench cephes.scalar.bench)

##****************************************************************************
##*     Toolbox cephes bench tests
##****************************************************************************

nt2_module_use_modules(unit)
ADD_SUBDIRECTORY(scalar)
