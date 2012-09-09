
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  zeta.cpp
  trunc.cpp
  tgamma_ratio.cpp
  tgamma_lower.cpp
  tgamma_delta_ratio.cpp
  tgamma2.cpp
  tgamma1pm1.cpp
  tgamma.cpp
  sqrt1pm1.cpp
  spherical_harmonic_r.cpp
  spherical_harmonic_i.cpp
  spherical_harmonic.cpp
  sph_neumann.cpp
  sph_bessel.cpp
  sinhc_pi.cpp
  sinc_pi.cpp
  round.cpp
  rising_factorial.cpp
  powm1.cpp
  log1p.cpp
  lgamma.cpp
  legendre_q.cpp
  legendre_p.cpp
  legendre_next.cpp
  legendre3_p.cpp
  laguerre_next.cpp
  laguerre.cpp
  itrunc.cpp
  iround.cpp
  ibetac_invb.cpp
  ibetac_inva.cpp
  ibetac_inv.cpp
  ibetac.cpp
  ibeta_invb.cpp
  ibeta_inva.cpp
  ibeta_inv.cpp
  ibeta_derivative.cpp
  ibeta.cpp
  hypot.cpp
  hermite_next.cpp
  hermite.cpp
  gamma_q_inva.cpp
  gamma_q_inv.cpp
  gamma_q.cpp
  gamma_p_inva.cpp
  gamma_p_inv.cpp
  gamma_p_derivative.cpp
  gamma_p.cpp
  falling_factorial.cpp
  factorial.cpp
  expm1.cpp
  expint.cpp
  erfc_inv.cpp
  erfc.cpp
  erf_inv.cpp
  erf.cpp
  ellint_rj.cpp
  ellint_rf.cpp
  ellint_rd.cpp
  ellint_rc.cpp
  ellint_3.cpp
  ellint_2.cpp
  ellint_1.cpp
  ellint3_rd.cpp
  ellint3_3.cpp
  double_factorial.cpp
  digamma.cpp
  cyl_neumann.cpp
  cyl_bessel_k.cpp
  cyl_bessel_j.cpp
  cyl_bessel_i.cpp
  cbrt.cpp
  betac.cpp
  beta.cpp
  atanh.cpp
  asinh.cpp
  acosh.cpp
# List of scalar test files for toolbox boost_math
   )

nt2_module_add_tests(extern.boost_math.scalar.cover ${SOURCES})

