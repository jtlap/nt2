//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CRLIBM_CRLIBM_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_CRLIBM_HPP_INCLUDED
#include <nt2/toolbox/crlibm/specific/interface.hpp>

//<include> please don't modify between these tags
#include <nt2/toolbox/crlibm/include/exp_rn.hpp>
#include <nt2/toolbox/crlibm/include/acos_rz.hpp>
#include <nt2/toolbox/crlibm/include/exp.hpp>
#include <nt2/toolbox/crlibm/include/exp_rd.hpp>
#include <nt2/toolbox/crlibm/include/exp_rz.hpp>
#include <nt2/toolbox/crlibm/include/exp_ru.hpp>
#include <nt2/toolbox/crlibm/include/acos_ru.hpp>
#include <nt2/toolbox/crlibm/include/log1p_rz.hpp>
#include <nt2/toolbox/crlibm/include/atan.hpp>
#include <nt2/toolbox/crlibm/include/sin.hpp>
#include <nt2/toolbox/crlibm/include/asinpi.hpp>
#include <nt2/toolbox/crlibm/include/tan.hpp>
#include <nt2/toolbox/crlibm/include/tanpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/tanpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/tanpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/tanpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/log2_ru.hpp>
#include <nt2/toolbox/crlibm/include/log1p.hpp>
#include <nt2/toolbox/crlibm/include/sinh_rd.hpp>
#include <nt2/toolbox/crlibm/include/sinh_rn.hpp>
#include <nt2/toolbox/crlibm/include/log2_rz.hpp>
#include <nt2/toolbox/crlibm/include/log2_rd.hpp>
#include <nt2/toolbox/crlibm/include/sinh_ru.hpp>
#include <nt2/toolbox/crlibm/include/sinh_rz.hpp>
#include <nt2/toolbox/crlibm/include/sinpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/log2_rn.hpp>
#include <nt2/toolbox/crlibm/include/tanpi.hpp>
#include <nt2/toolbox/crlibm/include/asin_rn.hpp>
#include <nt2/toolbox/crlibm/include/tan_ru.hpp>
#include <nt2/toolbox/crlibm/include/tan_rz.hpp>
#include <nt2/toolbox/crlibm/include/cos.hpp>
#include <nt2/toolbox/crlibm/include/tan_rd.hpp>
#include <nt2/toolbox/crlibm/include/tan_rn.hpp>
#include <nt2/toolbox/crlibm/include/log10.hpp>
#include <nt2/toolbox/crlibm/include/cos_rn.hpp>
#include <nt2/toolbox/crlibm/include/cos_rd.hpp>
#include <nt2/toolbox/crlibm/include/cos_rz.hpp>
#include <nt2/toolbox/crlibm/include/log.hpp>
#include <nt2/toolbox/crlibm/include/cos_ru.hpp>
#include <nt2/toolbox/crlibm/include/atan_ru.hpp>
#include <nt2/toolbox/crlibm/include/sinh.hpp>
#include <nt2/toolbox/crlibm/include/atanpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/acos.hpp>
#include <nt2/toolbox/crlibm/include/sinpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/log1p_ru.hpp>
#include <nt2/toolbox/crlibm/include/atanpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/sinpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/acospi.hpp>
#include <nt2/toolbox/crlibm/include/log1p_rn.hpp>
#include <nt2/toolbox/crlibm/include/atanpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/sinpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/log1p_rd.hpp>
#include <nt2/toolbox/crlibm/include/atanpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/expm1.hpp>
#include <nt2/toolbox/crlibm/include/atan_rz.hpp>
#include <nt2/toolbox/crlibm/include/asinpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/expm1_ru.hpp>
#include <nt2/toolbox/crlibm/include/asinpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/atanpi.hpp>
#include <nt2/toolbox/crlibm/include/asinpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/atan_rd.hpp>
#include <nt2/toolbox/crlibm/include/log2.hpp>
#include <nt2/toolbox/crlibm/include/asinpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/acos_rn.hpp>
#include <nt2/toolbox/crlibm/include/log_rd.hpp>
#include <nt2/toolbox/crlibm/include/cosh_rd.hpp>
#include <nt2/toolbox/crlibm/include/log10_rz.hpp>
#include <nt2/toolbox/crlibm/include/log10_ru.hpp>
#include <nt2/toolbox/crlibm/include/acos_rd.hpp>
#include <nt2/toolbox/crlibm/include/sinpi.hpp>
#include <nt2/toolbox/crlibm/include/cosh_rn.hpp>
#include <nt2/toolbox/crlibm/include/log10_rn.hpp>
#include <nt2/toolbox/crlibm/include/cosh_ru.hpp>
#include <nt2/toolbox/crlibm/include/log10_rd.hpp>
#include <nt2/toolbox/crlibm/include/cosh_rz.hpp>
#include <nt2/toolbox/crlibm/include/log_rz.hpp>
#include <nt2/toolbox/crlibm/include/asin.hpp>
#include <nt2/toolbox/crlibm/include/asin_rz.hpp>
#include <nt2/toolbox/crlibm/include/asin_ru.hpp>
#include <nt2/toolbox/crlibm/include/cosh.hpp>
#include <nt2/toolbox/crlibm/include/expm1_rn.hpp>
#include <nt2/toolbox/crlibm/include/atan_rn.hpp>
#include <nt2/toolbox/crlibm/include/asin_rd.hpp>
#include <nt2/toolbox/crlibm/include/sin_rn.hpp>
#include <nt2/toolbox/crlibm/include/pow_rn.hpp>
#include <nt2/toolbox/crlibm/include/sin_rd.hpp>
#include <nt2/toolbox/crlibm/include/expm1_rd.hpp>
#include <nt2/toolbox/crlibm/include/sin_rz.hpp>
#include <nt2/toolbox/crlibm/include/sin_ru.hpp>
#include <nt2/toolbox/crlibm/include/cospi_rn.hpp>
#include <nt2/toolbox/crlibm/include/cospi_rd.hpp>
#include <nt2/toolbox/crlibm/include/cospi_rz.hpp>
#include <nt2/toolbox/crlibm/include/log_rn.hpp>
#include <nt2/toolbox/crlibm/include/cospi_ru.hpp>
#include <nt2/toolbox/crlibm/include/acospi_rd.hpp>
#include <nt2/toolbox/crlibm/include/acospi_rn.hpp>
#include <nt2/toolbox/crlibm/include/acospi_ru.hpp>
#include <nt2/toolbox/crlibm/include/acospi_rz.hpp>
#include <nt2/toolbox/crlibm/include/cospi.hpp>
#include <nt2/toolbox/crlibm/include/expm1_rz.hpp>
#include <nt2/toolbox/crlibm/include/log_ru.hpp>
//<\include>

#endif
