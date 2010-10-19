//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_COTPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_COTPI_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo.hpp>
#include <nt2/include/functions/copysign.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<fast_cotpi_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_cotpi(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<fast_cotpi_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (real_,signed_, unsigned_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      return impl::trig_base<A0,pi_tag, fast_tag, tag::simd_type>::cota(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       signed_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return b_or(nt2::copysign(Inf<type>(), simd::native_cast<type>(a0)), is_nez(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       unsigned_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return b_or(Inf<type>(), is_nez(a0)); 
    }    
  };
} }

      
#endif
