//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_FDLIBM_FDLIBM_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FDLIBM_HPP_INCLUDED

//<include> please don't modify between these tags
#include <nt2/toolbox/fdlibm/include/functions/gamma.hpp>
#include <nt2/toolbox/fdlibm/include/functions/log1p.hpp>
#include <nt2/toolbox/fdlibm/include/functions/modf.hpp>
#include <nt2/toolbox/fdlibm/include/functions/exp.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_jn.hpp>
#include <nt2/toolbox/fdlibm/include/functions/erfc.hpp>
#include <nt2/toolbox/fdlibm/include/functions/erf.hpp>
#include <nt2/toolbox/fdlibm/include/functions/atan2.hpp>
#include <nt2/toolbox/fdlibm/include/functions/tanh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/expm1.hpp>
#include <nt2/toolbox/fdlibm/include/functions/ldexp.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_sinh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/acos.hpp>
#include <nt2/toolbox/fdlibm/include/functions/remainder.hpp>
#include <nt2/toolbox/fdlibm/include/functions/significand.hpp>
#include <nt2/toolbox/fdlibm/include/functions/sinh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_pow.hpp>
#include <nt2/toolbox/fdlibm/include/functions/jn.hpp>
#include <nt2/toolbox/fdlibm/include/functions/ceil.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_asin.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_log10.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_gamma.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_hypot.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_yn.hpp>
#include <nt2/toolbox/fdlibm/include/functions/yn.hpp>
#include <nt2/toolbox/fdlibm/include/functions/atan.hpp>
#include <nt2/toolbox/fdlibm/include/functions/fmod.hpp>
#include <nt2/toolbox/fdlibm/include/functions/scalbn.hpp>
#include <nt2/toolbox/fdlibm/include/functions/asinh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_sqrt.hpp>
#include <nt2/toolbox/fdlibm/include/functions/nextafter.hpp>
#include <nt2/toolbox/fdlibm/include/functions/sin.hpp>
#include <nt2/toolbox/fdlibm/include/functions/log10.hpp>
#include <nt2/toolbox/fdlibm/include/functions/finite.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_cosh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/pow.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_fmod.hpp>
#include <nt2/toolbox/fdlibm/include/functions/cbrt.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_lgamma.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_atan2.hpp>
#include <nt2/toolbox/fdlibm/include/functions/frexp.hpp>
#include <nt2/toolbox/fdlibm/include/functions/lgamma.hpp>
#include <nt2/toolbox/fdlibm/include/functions/sqrt.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_acosh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/ilogb.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_j0.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_j1.hpp>
#include <nt2/toolbox/fdlibm/include/functions/cos.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_y1.hpp>
#include <nt2/toolbox/fdlibm/include/functions/floor.hpp>
#include <nt2/toolbox/fdlibm/include/functions/fabs.hpp>
#include <nt2/toolbox/fdlibm/include/functions/log.hpp>
#include <nt2/toolbox/fdlibm/include/functions/isnan.hpp>
#include <nt2/toolbox/fdlibm/include/functions/asin.hpp>
#include <nt2/toolbox/fdlibm/include/functions/tan.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_acos.hpp>
#include <nt2/toolbox/fdlibm/include/functions/y1.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_exp.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_y0.hpp>
#include <nt2/toolbox/fdlibm/include/functions/logb.hpp>
#include <nt2/toolbox/fdlibm/include/functions/hypot.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_atanh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_log.hpp>
#include <nt2/toolbox/fdlibm/include/functions/cosh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/j1.hpp>
#include <nt2/toolbox/fdlibm/include/functions/j0.hpp>
#include <nt2/toolbox/fdlibm/include/functions/acosh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/rint.hpp>
#include <nt2/toolbox/fdlibm/include/functions/y0.hpp>
#include <nt2/toolbox/fdlibm/include/functions/atanh.hpp>
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_remainder.hpp>
//<\include>

#endif
