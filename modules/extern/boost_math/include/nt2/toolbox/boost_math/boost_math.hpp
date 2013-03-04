//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_BOOST_MATH_BOOST_MATH_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_BOOST_MATH_HPP_INCLUDED
#include <nt2/toolbox/boost_math/specific/interface.hpp>

//<include> please don't modify between these tags
#include <nt2/toolbox/boost_math/include/functions/gamma_p_inv.hpp>
#include <nt2/toolbox/boost_math/include/functions/log1p.hpp>
#include <nt2/toolbox/boost_math/include/functions/digamma.hpp>
#include <nt2/toolbox/boost_math/include/functions/tgamma1pm1.hpp>
#include <nt2/toolbox/boost_math/include/functions/erfc.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibetac_invb.hpp>
#include <nt2/toolbox/boost_math/include/functions/erf.hpp>
#include <nt2/toolbox/boost_math/include/functions/lgamma.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibetac_inva.hpp>
#include <nt2/toolbox/boost_math/include/functions/round.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_rj.hpp>
#include <nt2/toolbox/boost_math/include/functions/acosh.hpp>
#include <nt2/toolbox/boost_math/include/functions/double_factorial.hpp>
#include <nt2/toolbox/boost_math/include/functions/cyl_neumann.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint3_3.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_rc.hpp>
#include <nt2/toolbox/boost_math/include/functions/itrunc.hpp>
#include <nt2/toolbox/boost_math/include/functions/betac.hpp>
#include <nt2/toolbox/boost_math/include/functions/spherical_harmonic.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_rf.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_rd.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibeta.hpp>
#include <nt2/toolbox/boost_math/include/functions/cyl_bessel_k.hpp>
#include <nt2/toolbox/boost_math/include/functions/cyl_bessel_j.hpp>
#include <nt2/toolbox/boost_math/include/functions/laguerre_next.hpp>
#include <nt2/toolbox/boost_math/include/functions/erfc_inv.hpp>
#include <nt2/toolbox/boost_math/include/functions/expint.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint3_rd.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibetac_inv.hpp>
#include <nt2/toolbox/boost_math/include/functions/tgamma_ratio.hpp>
#include <nt2/toolbox/boost_math/include/functions/beta.hpp>
#include <nt2/toolbox/boost_math/include/functions/sinhc_pi.hpp>
#include <nt2/toolbox/boost_math/include/functions/legendre_q.hpp>
#include <nt2/toolbox/boost_math/include/functions/expm1.hpp>
#include <nt2/toolbox/boost_math/include/functions/cyl_bessel_i.hpp>
#include <nt2/toolbox/boost_math/include/functions/legendre_next.hpp>
#include <nt2/toolbox/boost_math/include/functions/factorial.hpp>
#include <nt2/toolbox/boost_math/include/functions/sph_bessel.hpp>
#include <nt2/toolbox/boost_math/include/functions/hermite_next.hpp>
#include <nt2/toolbox/boost_math/include/functions/gamma_q_inva.hpp>
#include <nt2/toolbox/boost_math/include/functions/asinh.hpp>
#include <nt2/toolbox/boost_math/include/functions/tgamma.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibeta_derivative.hpp>
#include <nt2/toolbox/boost_math/include/functions/gamma_p.hpp>
#include <nt2/toolbox/boost_math/include/functions/gamma_q.hpp>
#include <nt2/toolbox/boost_math/include/functions/trunc.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibeta_inv.hpp>
#include <nt2/toolbox/boost_math/include/functions/hermite.hpp>
#include <nt2/toolbox/boost_math/include/functions/tgamma_delta_ratio.hpp>
#include <nt2/toolbox/boost_math/include/functions/legendre3_p.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibetac.hpp>
#include <nt2/toolbox/boost_math/include/functions/powm1.hpp>
#include <nt2/toolbox/boost_math/include/functions/sph_neumann.hpp>
#include <nt2/toolbox/boost_math/include/functions/erf_inv.hpp>
#include <nt2/toolbox/boost_math/include/functions/gamma_q_inv.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_2.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_3.hpp>
#include <nt2/toolbox/boost_math/include/functions/ellint_1.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibeta_inva.hpp>
#include <nt2/toolbox/boost_math/include/functions/ibeta_invb.hpp>
#include <nt2/toolbox/boost_math/include/functions/iround.hpp>
#include <nt2/toolbox/boost_math/include/functions/zeta.hpp>
#include <nt2/toolbox/boost_math/include/functions/spherical_harmonic_i.hpp>
#include <nt2/toolbox/boost_math/include/functions/tgamma2.hpp>
#include <nt2/toolbox/boost_math/include/functions/sqrt1pm1.hpp>
#include <nt2/toolbox/boost_math/include/functions/tgamma_lower.hpp>
#include <nt2/toolbox/boost_math/include/functions/hypot.hpp>
#include <nt2/toolbox/boost_math/include/functions/falling_factorial.hpp>
#include <nt2/toolbox/boost_math/include/functions/gamma_p_inva.hpp>
#include <nt2/toolbox/boost_math/include/functions/rising_factorial.hpp>
#include <nt2/toolbox/boost_math/include/functions/gamma_p_derivative.hpp>
#include <nt2/toolbox/boost_math/include/functions/legendre_p.hpp>
#include <nt2/toolbox/boost_math/include/functions/sinc_pi.hpp>
#include <nt2/toolbox/boost_math/include/functions/cbrt.hpp>
#include <nt2/toolbox/boost_math/include/functions/laguerre.hpp>
#include <nt2/toolbox/boost_math/include/functions/atanh.hpp>
#include <nt2/toolbox/boost_math/include/functions/spherical_harmonic_r.hpp>
//<\include>

#endif
