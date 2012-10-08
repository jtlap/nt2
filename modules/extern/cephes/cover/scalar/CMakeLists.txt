
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  zetac.cpp
  zeta.cpp
  yv.cpp
  yn.cpp
  y1.cpp
  y0.cpp
  tanh.cpp
  tandg.cpp
  tan.cpp
  struve.cpp
  stdtr.cpp
  sqrt.cpp
  spence.cpp
  sinh.cpp
  sindg.cpp
  sin.cpp
  rgamma.cpp
  psi.cpp
  powi.cpp
  pow.cpp
  pdtri.cpp
  pdtrc.cpp
  pdtr.cpp
  ndtri.cpp
  ndtr.cpp
  nbdtri.cpp
  nbdtrc.cpp
  nbdtr.cpp
  log2.cpp
  log10.cpp
  log.cpp
  lgam.cpp
  lbeta.cpp
  kn.cpp
  k1e.cpp
  k1.cpp
  k0e.cpp
  k0.cpp
  jv.cpp
  jn.cpp
  j1.cpp
  j0.cpp
  iv.cpp
  incbps.cpp
  incbi.cpp
  incbet.cpp
  igami.cpp
  igamc.cpp
  igam.cpp
  i1e.cpp
  i1.cpp
  i0e.cpp
  i0.cpp
  hyperg.cpp
  hyp2f1.cpp
  gdtrc.cpp
  gdtr.cpp
  gamma.cpp
  floor.cpp
  fdtri.cpp
  fdtrc.cpp
  fdtr.cpp
  expx2.cpp
  expn.cpp
  exp2.cpp
  exp10.cpp
  exp.cpp
  erfc.cpp
  erf.cpp
  ellpk.cpp
  ellpe.cpp
  ellik.cpp
  ellie.cpp
  dawsn.cpp
  cotdg.cpp
  cot.cpp
  cosh.cpp
  cosdg.cpp
  cos.cpp
  chdtri.cpp
  chdtrc.cpp
  chdtr.cpp
  ceil.cpp
  cbrt.cpp
  beta.cpp
  bdtri.cpp
  bdtrc.cpp
  bdtr.cpp
  atanh.cpp
  atan2.cpp
  atan.cpp
  asinh.cpp
  asin.cpp
  acosh.cpp
  acos.cpp
# List of scalar test files for toolbox cephes
   )

nt2_module_add_tests(extern.cephes.scalar.cover ${SOURCES})

