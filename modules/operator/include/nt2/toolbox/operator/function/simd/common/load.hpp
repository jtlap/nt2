/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for no SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)(X)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< simd_< fundamental_<T>, X > >))
                      )

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_< tag::simd_<tag::fundamental_, X > >
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> : meta::strip<A2>::type {};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that;
      std::memcpy(&that, reinterpret_cast<type const*>(a0) + a1, sizeof that);
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd types with an offset
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)(Offset)(X)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< simd_< fundamental_<T>, X > >))
                        (mpl_integral_< integer_<Offset> >)
                      )

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_< tag::simd_<tag::fundamental_, X > >
                          , tag::mpl_integral_<tag::integer_>
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
       template<class Sig> struct result;
    template<class This, class A0,class A1,class A2,class A3>
    struct result<This(A0,A1,A2,A3)> : meta::strip<A2>::type {};

    NT2_FUNCTOR_CALL(4)
    {
      typedef typename NT2_RETURN_TYPE(4)::type type;
      type that;
      std::memcpy(&that, reinterpret_cast<type const*>(a0 + A3::value) + a1, sizeof that);
      return that;
    }
  };
} }

#endif
