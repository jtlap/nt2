//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_BOOST_MATH_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_BOOST_MATH_HPP_INCLUDED
#include <nt2/toolbox/boost_math/specific/interface.hpp>

//<include> please don't modify between these tags
#include <nt2/toolbox/boost_math/include/gamma_p_inv.hpp>
#include <nt2/toolbox/boost_math/include/log1p.hpp>
#include <nt2/toolbox/boost_math/include/digamma.hpp>
#include <nt2/toolbox/boost_math/include/tgamma1pm1.hpp>
#include <nt2/toolbox/boost_math/include/erfc.hpp>
#include <nt2/toolbox/boost_math/include/ibetac_invb.hpp>
#include <nt2/toolbox/boost_math/include/erf.hpp>
#include <nt2/toolbox/boost_math/include/lgamma.hpp>
#include <nt2/toolbox/boost_math/include/ibetac_inva.hpp>
#include <nt2/toolbox/boost_math/include/round.hpp>
#include <nt2/toolbox/boost_math/include/ellint_rj.hpp>
#include <nt2/toolbox/boost_math/include/acosh.hpp>
#include <nt2/toolbox/boost_math/include/double_factorial.hpp>
#include <nt2/toolbox/boost_math/include/cyl_neumann.hpp>
#include <nt2/toolbox/boost_math/include/ellint3_3.hpp>
#include <nt2/toolbox/boost_math/include/ellint_rc.hpp>
#include <nt2/toolbox/boost_math/include/itrunc.hpp>
#include <nt2/toolbox/boost_math/include/betac.hpp>
#include <nt2/toolbox/boost_math/include/spherical_harmonic.hpp>
#include <nt2/toolbox/boost_math/include/ellint_rf.hpp>
#include <nt2/toolbox/boost_math/include/ellint_rd.hpp>
#include <nt2/toolbox/boost_math/include/ibeta.hpp>
#include <nt2/toolbox/boost_math/include/cyl_bessel_k.hpp>
#include <nt2/toolbox/boost_math/include/cyl_bessel_j.hpp>
#include <nt2/toolbox/boost_math/include/laguerre_next.hpp>
#include <nt2/toolbox/boost_math/include/erfc_inv.hpp>
#include <nt2/toolbox/boost_math/include/expint.hpp>
#include <nt2/toolbox/boost_math/include/ellint3_rd.hpp>
#include <nt2/toolbox/boost_math/include/ibetac_inv.hpp>
#include <nt2/toolbox/boost_math/include/tgamma_ratio.hpp>
#include <nt2/toolbox/boost_math/include/beta.hpp>
#include <nt2/toolbox/boost_math/include/sinhc_pi.hpp>
#include <nt2/toolbox/boost_math/include/legendre_q.hpp>
#include <nt2/toolbox/boost_math/include/expm1.hpp>
#include <nt2/toolbox/boost_math/include/cyl_bessel_i.hpp>
#include <nt2/toolbox/boost_math/include/legendre_next.hpp>
#include <nt2/toolbox/boost_math/include/factorial.hpp>
#include <nt2/toolbox/boost_math/include/sph_bessel.hpp>
#include <nt2/toolbox/boost_math/include/hermite_next.hpp>
#include <nt2/toolbox/boost_math/include/gamma_q_inva.hpp>
#include <nt2/toolbox/boost_math/include/asinh.hpp>
#include <nt2/toolbox/boost_math/include/tgamma.hpp>
#include <nt2/toolbox/boost_math/include/ibeta_derivative.hpp>
#include <nt2/toolbox/boost_math/include/gamma_p.hpp>
#include <nt2/toolbox/boost_math/include/gamma_q.hpp>
#include <nt2/toolbox/boost_math/include/trunc.hpp>
#include <nt2/toolbox/boost_math/include/ibeta_inv.hpp>
#include <nt2/toolbox/boost_math/include/hermite.hpp>
#include <nt2/toolbox/boost_math/include/tgamma_delta_ratio.hpp>
#include <nt2/toolbox/boost_math/include/legendre3_p.hpp>
#include <nt2/toolbox/boost_math/include/ibetac.hpp>
#include <nt2/toolbox/boost_math/include/powm1.hpp>
#include <nt2/toolbox/boost_math/include/sph_neumann.hpp>
#include <nt2/toolbox/boost_math/include/erf_inv.hpp>
#include <nt2/toolbox/boost_math/include/gamma_q_inv.hpp>
#include <nt2/toolbox/boost_math/include/ellint_2.hpp>
#include <nt2/toolbox/boost_math/include/ellint_3.hpp>
#include <nt2/toolbox/boost_math/include/ellint_1.hpp>
#include <nt2/toolbox/boost_math/include/ibeta_inva.hpp>
#include <nt2/toolbox/boost_math/include/ibeta_invb.hpp>
#include <nt2/toolbox/boost_math/include/iround.hpp>
#include <nt2/toolbox/boost_math/include/zeta.hpp>
#include <nt2/toolbox/boost_math/include/spherical_harmonic_i.hpp>
#include <nt2/toolbox/boost_math/include/tgamma2.hpp>
#include <nt2/toolbox/boost_math/include/sqrt1pm1.hpp>
#include <nt2/toolbox/boost_math/include/tgamma_lower.hpp>
#include <nt2/toolbox/boost_math/include/hypot.hpp>
#include <nt2/toolbox/boost_math/include/falling_factorial.hpp>
#include <nt2/toolbox/boost_math/include/gamma_p_inva.hpp>
#include <nt2/toolbox/boost_math/include/rising_factorial.hpp>
#include <nt2/toolbox/boost_math/include/gamma_p_derivative.hpp>
#include <nt2/toolbox/boost_math/include/legendre_p.hpp>
#include <nt2/toolbox/boost_math/include/sinc_pi.hpp>
#include <nt2/toolbox/boost_math/include/cbrt.hpp>
#include <nt2/toolbox/boost_math/include/laguerre.hpp>
#include <nt2/toolbox/boost_math/include/atanh.hpp>
#include <nt2/toolbox/boost_math/include/spherical_harmonic_r.hpp>
//<\include>

#endif
