##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.crg/LICENSE_1_0.txt
##############################################################################

##############################################################################
## Single precision libm
##############################################################################

SET( SOURCES
      acoshf.c  airyf.c   asinf.c   asinhf.c  atanf.c 
      atanhf.c  bdtrf.c   betaf.c   cbrtf.c   chbevlf.c 
      chdtrf.c  clogf.c   cmplxf.c  constf.c  coshf.c 
      dawsnf.c  ellief.c  ellikf.c  ellpef.c  ellpkf.c 
      ellpjf.c  expf.c    exp2f.c   exp10f.c  expnf.c 
      expx2f.c  facf.c    fdtrf.c   floorf.c  fresnlf.c
      gammaf.c  gdtrf.c   hypergf.c hyp2f1f.c igamf.c 
      igamif.c  incbetf.c incbif.c  i0f.c     i1f.c 
      ivf.c     j0f.c     j1f.c     jnf.c     jvf.c 
      k0f.c     k1f.c     knf.c     logf.c    log2f.c
      log10f.c  nbdtrf.c  ndtrf.c   ndtrif.c  pdtrf.c 
      polynf.c  powif.c   powf.c    psif.c    rgammaf.c 
      shichif.c sicif.c   sindgf.c  sinf.c    sinhf.c 
      spencef.c sqrtf.c   stdtrf.c  struvef.c tandgf.c 
      tanf.c    tanhf.c   ynf.c     zetaf.c   zetacf.c  
      polevlf.c setprec.c mtherr.c
    )

nt2_module_add_library(nt2_cephesf ${SOURCES})
