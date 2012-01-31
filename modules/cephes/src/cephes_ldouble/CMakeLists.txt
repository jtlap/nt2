##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.crg/LICENSE_1_0.txt
##############################################################################

##############################################################################
## Double precision libm
##############################################################################

SET( SOURCES
     acoshl.c  asinl.c asinhl.c atanl.c atanhl.c bdtrl.c  
     btdtrl.c cbrtl.c  chdtrl.c clogl.c cmplxl.c  
     coshl.c  elliel.c ellikl.c ellpel.c ellpjl.c ellpkl.c 
     expl.c expm1l.c exp10l.c exp2l.c  expx2l.c   fdtrl.c  mtherr.c
     gammal.c gdtrl.c  igamil.c incbetl.c 
     incbil.c igaml.c isnanl.c j0l.c j1l.c jnl.c
     logl.c log2l.c log10l.c log1pl.c nbdtrl.c ndtril.c pdtrl.c 
     polevll.c  powl.c powil.c 
     sinl.c sinhl.c stdtrl.c 
     tanl.c tanhl.c unityl.c ynl.c 
     sqrtl.c floorl.c 
    )
#airyl.c betal.c chbevll.c dawsnl.c drandl.c expnl.c fabsl.c facl.c fresnll.c 
#hyp2f1l.c  hypergl.c  i0l.c i1l.c ivl.c jvl.c  k0l.c k1l.c knl.c kolmogorovl.c 
#lrandl.c planckl.c polmiscl.c polylogl.c polynl.c shichil.c sicil.c spencel.c 
#zetal.c zetacl.c ndtrl.c psil.c sindgl.c struvel.c tandgl.c setprecl.c econst.c
#mtherrl.c rgammal.c roundl.c 

# const.c does not define constants in a strict C way in UNK mode,
# so we force IEEE754 little-endian on x86 to avoid problems.
IF(NT2_ARCH_X86)
  SET(NT2_CURRENT_FLAGS "${NT2_CURRENT_FLAGS} -DIBMPC")
ENDIF()

nt2_module_add_library(nt2_cephesl ${SOURCES})
