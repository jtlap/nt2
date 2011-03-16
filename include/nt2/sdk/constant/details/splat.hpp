/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_SPLAT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_SPLAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// splat for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

NT2_REGISTER_DISPATCH ( tag::splat_
                      , tag::cpu_
                      , (A0)(A1)
                      , (fundamental_<A0>)(target_< fundamental_<A1> >)
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::splat_(tag::fundamental_,tag::target_<tag::fundamental_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0, class Target>
    struct result<This(A0,Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type result_type;
      details::ignore_unused(a1); 
      result_type that = static_cast<result_type>(a0);
      return that;
    }
  };
} }

#endif
