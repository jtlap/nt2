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
#include <nt2/toolbox/crlibm/include/functions/exp_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/acos_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/exp.hpp>
#include <nt2/toolbox/crlibm/include/functions/exp_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/exp_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/exp_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/acos_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/log1p_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/atan.hpp>
#include <nt2/toolbox/crlibm/include/functions/sin.hpp>
#include <nt2/toolbox/crlibm/include/functions/asinpi.hpp>
#include <nt2/toolbox/crlibm/include/functions/tan.hpp>
#include <nt2/toolbox/crlibm/include/functions/tanpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/tanpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/tanpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/tanpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/log2_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/log1p.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinh_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinh_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/log2_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log2_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinh_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinh_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log2_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/tanpi.hpp>
#include <nt2/toolbox/crlibm/include/functions/asin_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/tan_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/tan_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/cos.hpp>
#include <nt2/toolbox/crlibm/include/functions/tan_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/tan_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/log10.hpp>
#include <nt2/toolbox/crlibm/include/functions/cos_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/cos_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/cos_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log.hpp>
#include <nt2/toolbox/crlibm/include/functions/cos_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/atan_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinh.hpp>
#include <nt2/toolbox/crlibm/include/functions/atanpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/acos.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/log1p_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/atanpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/acospi.hpp>
#include <nt2/toolbox/crlibm/include/functions/log1p_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/atanpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/log1p_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/atanpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/expm1.hpp>
#include <nt2/toolbox/crlibm/include/functions/atan_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/asinpi_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/expm1_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/asinpi_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/atanpi.hpp>
#include <nt2/toolbox/crlibm/include/functions/asinpi_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/atan_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/log2.hpp>
#include <nt2/toolbox/crlibm/include/functions/asinpi_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/acos_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/log_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/cosh_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/log10_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log10_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/acos_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/sinpi.hpp>
#include <nt2/toolbox/crlibm/include/functions/cosh_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/log10_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/cosh_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/log10_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/cosh_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/asin.hpp>
#include <nt2/toolbox/crlibm/include/functions/asin_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/asin_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/cosh.hpp>
#include <nt2/toolbox/crlibm/include/functions/expm1_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/atan_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/asin_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/sin_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/pow_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/sin_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/expm1_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/sin_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/sin_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/cospi_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/cospi_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/cospi_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/cospi_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/acospi_rd.hpp>
#include <nt2/toolbox/crlibm/include/functions/acospi_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/acospi_ru.hpp>
#include <nt2/toolbox/crlibm/include/functions/acospi_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/cospi.hpp>
#include <nt2/toolbox/crlibm/include/functions/expm1_rz.hpp>
#include <nt2/toolbox/crlibm/include/functions/log_ru.hpp>
//<\include>

#endif
