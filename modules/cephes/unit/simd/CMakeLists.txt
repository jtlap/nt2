##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  chdtri.cpp
  chdtrc.cpp
  hyperg.cpp
  atan2.cpp
  kn.cpp
  yn.cpp
  spence.cpp
  beta.cpp
  bdtrc.cpp
  i0.cpp
  i1.cpp
  atan.cpp
  exp.cpp
  expx2.cpp
  bdtri.cpp
  sin.cpp
  i1e.cpp
  k0.cpp
  k1.cpp
  lgam.cpp
  sqrt.cpp
  atanh.cpp
  floor.cpp
  gdtr.cpp
  tan.cpp
  nbdtr.cpp
  fdtr.cpp
  iv.cpp
  igami.cpp
  lbeta.cpp
  k1e.cpp
  expn.cpp
  rgamma.cpp
  erf.cpp
  igamc.cpp
  powi.cpp
  tanh.cpp
  stdtr.cpp
  nbdtri.cpp
  nbdtrc.cpp
  asinh.cpp
  cotdg.cpp
  exp10.cpp
  ellpe.cpp
  log10.cpp
  cosdg.cpp
  k0e.cpp
  ellpk.cpp
  exp2.cpp
  log.cpp
  zeta.cpp
  pow.cpp
  fdtrc.cpp
  hyp2f1.cpp
  gamma.cpp
  acos.cpp
  erfc.cpp
  cot.cpp
  cos.cpp
  bdtr.cpp
  fdtri.cpp
  sinh.cpp
  pdtr.cpp
  gdtrc.cpp
  jn.cpp
  incbi.cpp
  jv.cpp
  log2.cpp
  ellik.cpp
  struve.cpp
  ndtri.cpp
  pdtrc.cpp
  ellie.cpp
  asin.cpp
  cosh.cpp
  j1.cpp
  j0.cpp
  incbps.cpp
  sindg.cpp
  chdtr.cpp
  tandg.cpp
  zetac.cpp
  incbet.cpp
  yv.cpp
  ceil.cpp
  i0e.cpp
  psi.cpp
  cbrt.cpp
  igam.cpp
  pdtri.cpp
  dawsn.cpp
  y0.cpp
  y1.cpp
  acosh.cpp
  ndtr.cpp
# List of simd test files for toolbox cephes
   )

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(cephes.simd.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
