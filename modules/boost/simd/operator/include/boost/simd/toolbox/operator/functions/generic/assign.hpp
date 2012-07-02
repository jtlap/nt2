//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_GENERIC_ASSIGN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_GENERIC_ASSIGN_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/assign.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::assign_, tag::cpu_, (A0)
                                    , (generic_<unspecified_<A0> >)
                                      (generic_<unspecified_<A0> >)
                                    )
  {
    typedef A0& result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, const A0& a1) const
    {
      return a0 = a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::assign_, tag::cpu_, (A0)(A1)
                                    , (generic_<unspecified_<A0> >)
                                      (unspecified_<A1>)
                                    )
  {
    typedef A0& result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, const A0& a1) const
    {
      return a0 = a1;
    }
  };
} } }

#if 0
namespace nt2 { namespace container { template<class Expr, class Result, class Dummy> struct expression; struct domain; } }

namespace boost { namespace simd { namespace ext
{
  template<class T, long Arity = T::proto_arity_c>
  struct as_child_ref_expr
  {
    typedef T type;
    static type& call(T& t)
    {
      return t;
    }
  };

  template<class T>
  struct as_child_ref_expr<T, 0l>
  {
    typedef T& type;
    static type call(T& t)
    {
      return t;
    }
  };

  template<class T, class Enable = void>
  struct as_child_ref
  {
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<T&> > expr;
    typedef nt2::container::expression<expr, T&, boost::proto::is_proto_expr> type;
    static type call(T& t)
    {
      return type(expr::make(t));
    }
  };

  template<class T>
  struct as_child_ref<T, typename T::proto_is_expr_>
       : as_child_ref_expr<T>
  {
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::assign_, tag::formal_, (A0)(A1)
                                      , (mpl::or_< proto::is_expr<A0>, proto::is_expr<A1> >)
                                      , (unspecified_<A0>)
                                        (unspecified_<A1>)
                                      )
  {
    typedef boost::proto::basic_expr< boost::proto::tag::assign, boost::proto::list2< typename ext::as_child_ref<A0>::type, typename boost::proto::result_of::as_child<A1, nt2::container::domain>::type >, 2 > expr;
    typedef nt2::container::expression<expr, typename boost::dispatch::meta::semantic_of<A0&>::type, boost::proto::is_proto_expr> result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(A0& a0, const A1& a1) const
    {
      expr that = { ext::as_child_ref<A0>::call(a0), boost::proto::as_child<nt2::container::domain>(a1) };
      return result_type(that);
    }
  };
} } }
#endif

#endif
