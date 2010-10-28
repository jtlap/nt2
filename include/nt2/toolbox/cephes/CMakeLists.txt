##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.crg/LICENSE_1_0.txt
##############################################################################

ADD_SUBDIRECTORY(src/cephes_single)
ADD_SUBDIRECTORY(bench)
ADD_SUBDIRECTORY(unit)

##############################################################################
## TODO: Write command for building your own sources
##############################################################################

file( GLOB_RECURSE cephes_double_src
      ${PROJECT_SOURCE_DIR}/include/nt2/toolbox/cephes/src/cephes_double/*.c
    )


#add_library(nt2_cephesd STATIC ${cephes_double_src} )

