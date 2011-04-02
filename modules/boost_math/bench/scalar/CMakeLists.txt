##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  gamma_p_inv.cpp
  log1p.cpp
  digamma.cpp
  tgamma1pm1.cpp
  erfc.cpp
  ibetac_invb.cpp
  erf.cpp
  lgamma.cpp
  ibetac_inva.cpp
  round.cpp
  ellint_rj.cpp
  acosh.cpp
  double_factorial.cpp
  cyl_neumann.cpp
  ellint3_3.cpp
  ellint_rc.cpp
  itrunc.cpp
  betac.cpp
  spherical_harmonic.cpp
  ellint_rf.cpp
  ellint_rd.cpp
  ibeta.cpp
  cyl_bessel_k.cpp
  cyl_bessel_j.cpp
  laguerre_next.cpp
  erfc_inv.cpp
  expint.cpp
  ellint3_rd.cpp
  ibetac_inv.cpp
  tgamma_ratio.cpp
  beta.cpp
  sinhc_pi.cpp
  legendre_q.cpp
  expm1.cpp
  cyl_bessel_i.cpp
  legendre_next.cpp
  factorial.cpp
  sph_bessel.cpp
  hermite_next.cpp
  gamma_q_inva.cpp
  asinh.cpp
  tgamma.cpp
  ibeta_derivative.cpp
  gamma_p.cpp
  gamma_q.cpp
  trunc.cpp
  ibeta_inv.cpp
  hermite.cpp
  tgamma_delta_ratio.cpp
  legendre3_p.cpp
  ibetac.cpp
  powm1.cpp
  sph_neumann.cpp
  erf_inv.cpp
  gamma_q_inv.cpp
  ellint_2.cpp
  ellint_3.cpp
  ellint_1.cpp
  ibeta_inva.cpp
  ibeta_invb.cpp
  iround.cpp
  zeta.cpp
  spherical_harmonic_i.cpp
  tgamma2.cpp
  sqrt1pm1.cpp
  tgamma_lower.cpp
  hypot.cpp
  falling_factorial.cpp
  gamma_p_inva.cpp
  rising_factorial.cpp
  gamma_p_derivative.cpp
  legendre_p.cpp
  sinc_pi.cpp
  cbrt.cpp
  laguerre.cpp
  atanh.cpp
  spherical_harmonic_r.cpp
# List of scalar test files for toolbox boost_math
   )

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_bench(boost_math.scalar.${EXAMPLE}.bench ${EXAMPLE}.cpp)
ENDFOREACH()
