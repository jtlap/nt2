//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_ATAN2_HPP_INCLUDED

#include <nt2/toolbox/trigonometric/functions/atan2.hpp>
#include <nt2/toolbox/trigonometric/functions/scalar/impl/invtrig.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/if_else_zero.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_gtz.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pi.hpp>

namespace nt2 { namespace ext
{
  namespace impl = nt2::details::internal;
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan2_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FORCE_INLINE
      result_type operator()(A0 a0, A0 a1) const
    {
      if (nt2::is_nan(a0) || nt2::is_nan(a1)) return nt2::Nan<result_type>();
      if (nt2::is_inf(a0) && nt2::is_inf(a1))
      {
        a0 = nt2::copysign(nt2::One<A0>(), a0);
        a1 = nt2::copysign(nt2::One<A0>(), a1);
      }
      A0 z = impl::invtrig_base<result_type,radian_tag, tag::not_simd_type>::kernel_atan(a0/a1);
      z = nt2::if_else(nt2::is_gtz(a1), z, nt2::Pi<A0>()-z)*nt2::signnz(a0);
      return nt2::if_else(nt2::is_eqz(a0), nt2::if_else_zero(nt2::is_ltz(a1), nt2::Pi<A0>()), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan2_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::atan2(result_type(a0),result_type(a1));
    }
  };
} }


#endif
