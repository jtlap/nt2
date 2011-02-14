/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_DIGITS_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_DIGITS_HPP_INCLUDED

#include <nt2/sdk/constant/splat.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over digits<N>
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_TPL ( tag::digit_<N>
                          , tag::cpu_
                          , (nt2::int64_t N)(class A0)
                          , (target_< fundamental_<A0> >)
                          )

////////////////////////////////////////////////////////////////////////////////
// call to digits<N> : reuse splat so the code stay generic anc can be reused
// in non-scalar cases later (see SIMD for example)
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template< nt2::int64_t N, class Dummy >
  struct  call< tag::digit_<N>(tag::target_<tag::fundamental_> )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type result_type;
      result_type that = splat<result_type>(N);
      return that;
    }
  };
} }

#endif
