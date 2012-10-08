
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  tanpi_rz.cpp
  tanpi_ru.cpp
  tanpi_rn.cpp
  tanpi_rd.cpp
  tanpi.cpp
  tan_rz.cpp
  tan_ru.cpp
  tan_rn.cpp
  tan_rd.cpp
  tan.cpp
  sinpi_rz.cpp
  sinpi_ru.cpp
  sinpi_rn.cpp
  sinpi_rd.cpp
  sinpi.cpp
  sinh_rz.cpp
  sinh_ru.cpp
  sinh_rn.cpp
  sinh_rd.cpp
  sinh.cpp
  sin_rz.cpp
  sin_ru.cpp
  sin_rn.cpp
  sin_rd.cpp
  sin.cpp
  pow_rn.cpp
  log_rz.cpp
  log_ru.cpp
  log_rn.cpp
  log_rd.cpp
  log2_rz.cpp
  log2_ru.cpp
  log2_rn.cpp
  log2_rd.cpp
  log2.cpp
  log1p_rz.cpp
  log1p_ru.cpp
  log1p_rn.cpp
  log1p_rd.cpp
  log1p.cpp
  log10_rz.cpp
  log10_ru.cpp
  log10_rn.cpp
  log10_rd.cpp
  log10.cpp
  log.cpp
  expm1_rz.cpp
  expm1_ru.cpp
  expm1_rn.cpp
  expm1_rd.cpp
  expm1.cpp
  exp_rz.cpp
  exp_ru.cpp
  exp_rn.cpp
  exp_rd.cpp
  exp.cpp
  cospi_rz.cpp
  cospi_ru.cpp
  cospi_rn.cpp
  cospi_rd.cpp
  cospi.cpp
  cosh_rz.cpp
  cosh_ru.cpp
  cosh_rn.cpp
  cosh_rd.cpp
  cosh.cpp
  cos_rz.cpp
  cos_ru.cpp
  cos_rn.cpp
  cos_rd.cpp
  cos.cpp
  atanpi_rz.cpp
  atanpi_ru.cpp
  atanpi_rn.cpp
  atanpi_rd.cpp
  atanpi.cpp
  atan_rz.cpp
  atan_ru.cpp
  atan_rn.cpp
  atan_rd.cpp
  atan.cpp
  asinpi_rz.cpp
  asinpi_ru.cpp
  asinpi_rn.cpp
  asinpi_rd.cpp
  asinpi.cpp
  asin_rz.cpp
  asin_ru.cpp
  asin_rn.cpp
  asin_rd.cpp
  asin.cpp
  acospi_rz.cpp
  acospi_ru.cpp
  acospi_rn.cpp
  acospi_rd.cpp
  acospi.cpp
  acos_rz.cpp
  acos_ru.cpp
  acos_rn.cpp
  acos_rd.cpp
  acos.cpp
# List of scalar test files for toolbox crlibm
   )

nt2_module_add_tests(extern.crlibm.scalar.cover ${SOURCES})

