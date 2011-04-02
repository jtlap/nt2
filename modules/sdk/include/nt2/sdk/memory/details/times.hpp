/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_TIMES_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_TIMES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Activates operator * on mpl integral with integral
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/times.hpp>
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/functor/operators.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Make nultiplies works with mpl::integral types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::multiplies_ , tag::cpu_
                      , (A0)(A1)
                      , (mpl_integral_< integer_<A0> >)(integer_<A1>)
                      )

NT2_REGISTER_DISPATCH ( tag::multiplies_ , tag::cpu_
                      , (A0)(A1)
                      , (integer_<A0>)(mpl_integral_< integer_<A1> >)
                      )

NT2_REGISTER_DISPATCH ( tag::multiplies_ , tag::cpu_
                      , (A0)(A1)
                      , (mpl_integral_< integer_<A0> >)
                        (mpl_integral_< integer_<A1> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::multiplies_( tag::mpl_integral_<tag::integer_>
                                , tag::integer_
                                )
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A1 a1;
      typedef typename meta::strip<A0>::type arg0;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,arg0::value*a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return A0::value*a1; }
  };

  template<class Dummy>
  struct  call< tag::multiplies_( tag::integer_
                                , tag::mpl_integral_<tag::integer_>
                                )
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)>
    {
      static A0 a0;
      typedef typename meta::strip<A1>::type arg1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,arg1::value*a0)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0*A1::value; }
  };

  template<class Dummy>
  struct  call< tag::multiplies_( tag::mpl_integral_<tag::integer_>
                                , tag::mpl_integral_<tag::integer_>
                                )
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct  result<This(A0,A1)>
          : boost::mpl::times < typename meta::strip<A0>::type
                              , typename meta::strip<A1>::type
                              >
    {};

    NT2_FUNCTOR_CALL(2)
    {
      return typename NT2_RETURN_TYPE(2)::type();
    }
  };
} }

#endif
