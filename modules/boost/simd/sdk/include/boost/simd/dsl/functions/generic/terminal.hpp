//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_TERMINAL_HPP_INCLUDED

#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/proto/traits.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/shared_ptr.hpp>

namespace boost { namespace simd { namespace ext
{
  // Terminal returns ASTs by reference, Box by value
  BOOST_SIMD_REGISTER_DISPATCH_TO( boost::simd::tag::terminal_, tag::formal_
                            , (A0)
                            , (ast_<A0>)
                            , identity
                            )

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::box_, tag::formal_, (A0), (ast_<A0>) )
  {
    typedef typename boost::remove_const<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const { return a0; }
  };

  // When evaluating a terminal, get its value
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::terminal_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    typedef typename proto::result_of::value<A0&>::type result_type;
    
    BOOST_FORCEINLINE result_type
    operator()(A0& a0) const
    {
      return boost::proto::value(a0);
    }
  };

  // Terminal functions on non-ASTs do nothing
  BOOST_SIMD_REGISTER_DISPATCH_TO( boost::simd::tag::terminal_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            , identity
                            )
  BOOST_SIMD_REGISTER_DISPATCH_TO( boost::simd::tag::terminal_, tag::cpu_
                            , (A0)
                            , (generic_< unspecified_<A0> >)
                            , identity
                            )

  // Except dereference, which dereferences
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::dereference_, tag::cpu_, (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename A0::element_type& result_type;
    BOOST_FORCEINLINE result_type operator()(A0& a0) const { return *a0.get(); }
  };

  // All terminals other than the actual terminal tag call the tag on the value
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::dereference_, tag::cpu_, (A0)(T0)
                            , (mpl::not_< is_same<T0, boost::simd::tag::terminal_> >)
                            , ((expr_< unspecified_<A0>, T0, boost::mpl::long_<0> >))
                            )
  {
    typedef typename dispatch::meta::
            call<T0(typename boost::proto::result_of::value<A0&>::type)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return dispatch::functor<T0>()(boost::proto::value(a0));
    }
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of< boost::shared_ptr<T> >
  {
    typedef T type;
  };
} } }

#endif
