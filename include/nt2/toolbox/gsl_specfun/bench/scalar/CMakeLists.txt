##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  gsl_sf_sinc.cpp
  gsl_sf_beta_inc.cpp
  gsl_sf_bessel_i1_scaled.cpp
  gsl_sf_log_1plusx_mx.cpp
  gsl_sf_beta.cpp
  gsl_sf_bessel_In_scaled.cpp
  gsl_sf_log_erfc.cpp
  gsl_sf_bessel_k1_scaled.cpp
  gsl_sf_fermi_dirac_mhalf.cpp
  gsl_sf_gamma_inc.cpp
  gsl_sf_erfc.cpp
  gsl_sf_bessel_jl.cpp
  gsl_sf_fermi_dirac_3half.cpp
  gsl_sf_lambert_Wm1.cpp
  gsl_sf_hyperg_2F1_conj.cpp
  gsl_sf_lnbeta.cpp
  gsl_sf_exprel.cpp
  gsl_sf_lnchoose.cpp
  gsl_sf_atanint.cpp
  gsl_sf_conicalP_1.cpp
  gsl_sf_conicalP_0.cpp
  gsl_sf_poch.cpp
  gsl_sf_hypot.cpp
  gsl_sf_legendre_H3d.cpp
  gsl_sf_hyperg_2F1_renorm.cpp
  gsl_sf_fermi_dirac_0.cpp
  gsl_sf_fermi_dirac_1.cpp
  gsl_sf_zeta.cpp
  gsl_sf_psi_1piy.cpp
  gsl_sf_bessel_Knu.cpp
  gsl_sf_bessel_j1.cpp
  gsl_sf_expm1.cpp
  gsl_sf_expint_E1.cpp
  gsl_sf_expint_E2.cpp
  gsl_sf_fermi_dirac_half.cpp
  gsl_sf_log_1plusx.cpp
  gsl_sf_bessel_Inu.cpp
  gsl_sf_dawson.cpp
  gsl_sf_fermi_dirac_2.cpp
  gsl_sf_clausen.cpp
  gsl_sf_lncosh.cpp
  gsl_sf_exprel_n.cpp
  gsl_sf_pochrel.cpp
  gsl_sf_lndoublefact.cpp
  gsl_sf_bessel_Klu_scaled_.cpp
  gsl_sf_hyperg_0F1.cpp
  gsl_sf_bessel_j0.cpp
  gsl_sf_bessel_Inu_scaled_.cpp
  gsl_sf_legendre_sphPlm.cpp
  gsl_sf_fermi_dirac_int.cpp
  gsl_sf_hyperg_2F1.cpp
  gsl_sf_hyperg_2F0.cpp
  gsl_sf_bessel_yl.cpp
  gsl_sf_fermi_dirac_m1.cpp
  gsl_sf_exp.cpp
  gsl_sf_gammainv.cpp
  gsl_sf_Shi.cpp
  gsl_sf_gamma_inc_P.cpp
  gsl_sf_angle_restrict_symm.cpp
  gsl_sf_bessel_i0_scaled.cpp
  gsl_sf_bessel_K0_scaled.cpp
  gsl_sf_debye_4.cpp
  gsl_sf_debye_5.cpp
  gsl_sf_debye_6.cpp
  gsl_sf_debye_1.cpp
  gsl_sf_debye_2.cpp
  gsl_sf_debye_3.cpp
  gsl_sf_legendre_H3d_0.cpp
  gsl_sf_legendre_H3d_1.cpp
  gsl_sf_lnpoch.cpp
  gsl_sf_fermi_dirac_inc_0.cpp
  gsl_sf_gamma.cpp
  gsl_sf_lambert_W0.cpp
  gsl_sf_bessel_I0.cpp
  gsl_sf_bessel_I1.cpp
  gsl_sf_dilog.cpp
  gsl_sf_log.cpp
  gsl_sf_conicalP_cyl_reg.cpp
  gsl_sf_expint_Ei.cpp
  gsl_sf_taylorcoeff.cpp
  gsl_sf_hzeta.cpp
  gsl_sf_fact.cpp
  gsl_sf_bessel_Yn.cpp
  gsl_sf_exprel_2.cpp
  gsl_sf_conicalP_half.cpp
  gsl_sf_hazard.cpp
  gsl_sf_hyperg_U.cpp
  gsl_sf_psi_n.cpp
  gsl_sf_gammastar.cpp
  gsl_sf_angle_restrict_pos.cpp
  gsl_sf_lnsinh.cpp
  gsl_sf_bessel_k0_scaled.cpp
  gsl_sf_erf_Z.cpp
  gsl_sf_erf.cpp
  gsl_sf_erf_Q.cpp
  gsl_sf_bessel_K1_scaled.cpp
  gsl_sf_bessel_In.cpp
  gsl_sf_doublefact.cpp
  gsl_sf_bessel_il_scaled.cpp
  gsl_sf_hyperg_2F1_conj_renorm.cpp
  gsl_sf_bessel_Jnu.cpp
  gsl_sf_psi_1.cpp
  gsl_sf_lnfact.cpp
  gsl_sf_choose.cpp
  gsl_sf_gegenpoly_2.cpp
  gsl_sf_legendre_P3.cpp
  gsl_sf_bessel_Knu_scaled_.cpp
  gsl_sf_expint_E1_scaled.cpp
  gsl_sf_bessel_Y0.cpp
  gsl_sf_bessel_Y1.cpp
  gsl_sf_bessel_I0_scaled.cpp
  gsl_sf_log_abs.cpp
  gsl_sf_zetam1.cpp
  gsl_sf_laguerre_1.cpp
  gsl_sf_laguerre_3.cpp
  gsl_sf_laguerre_2.cpp
  gsl_sf_bessel_y0.cpp
  gsl_sf_psi.cpp
  gsl_sf_bessel_K0.cpp
  gsl_sf_bessel_K1.cpp
  gsl_sf_bessel_Ynu.cpp
  gsl_sf_gegenpoly_3.cpp
  gsl_sf_bessel_Jn.cpp
  gsl_sf_gegenpoly_1.cpp
  gsl_sf_cos.cpp
  gsl_sf_lngamma.cpp
  gsl_sf_bessel_y1.cpp
  gsl_sf_bessel_kl_scaled.cpp
  gsl_sf_hyperg_1F1.cpp
  gsl_sf_legendre_Q0.cpp
  gsl_sf_legendre_Q1.cpp
  gsl_sf_bessel_I1_scaled.cpp
  gsl_sf_expint_Ei_scaled.cpp
  gsl_sf_legendre_Pl.cpp
  gsl_sf_bessel_Kn_scaled.cpp
  gsl_sf_expint_E2_scaled.cpp
  gsl_sf_gamma_inc_Q.cpp
  gsl_sf_gegenpoly_n.cpp
  gsl_sf_bessel_J1.cpp
  gsl_sf_bessel_J0.cpp
  gsl_sf_bessel_Kn.cpp
  gsl_sf_exp_mult.cpp
  gsl_sf_conicalP_sph_reg.cpp
  gsl_sf_Ci.cpp
  gsl_sf_laguerre_n.cpp
  gsl_sf_legendre_P1.cpp
  gsl_sf_bessel_Klu.cpp
  gsl_sf_legendre_P2.cpp
  gsl_sf_sin.cpp
  gsl_sf_hyperg_1F1_int.cpp
  gsl_sf_legendre_Plm.cpp
  gsl_sf_conicalP_mhalf.cpp
  gsl_sf_legendre_Ql.cpp
  gsl_sf_Chi.cpp
  gsl_sf_eta.cpp
  gsl_sf_expint_3.cpp
# List of scalar test files for toolbox gsl_specfun
   )

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  ##**************************************************************************
  ## Build the executable filename from the example source filename
  ##**************************************************************************
  STRING(REGEX REPLACE ".cpp" ".gsl_specfun.scalar.bench" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-gsl_specfun.scalar.bench" TEST "${EXAMPLE}")

  ##**************************************************************************
  ## Add as a target
  ##**************************************************************************
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  TARGET_LINK_LIBRARIES(${EXECUTABLE} gsl)
  TARGET_LINK_LIBRARIES(${EXECUTABLE} gslcblas)


ENDFOREACH()