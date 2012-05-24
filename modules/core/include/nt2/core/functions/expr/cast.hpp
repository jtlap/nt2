//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_CAST_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_CAST_HPP_INCLUDED

#include <nt2/core/functions/cast.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/greater.hpp>

namespace nt2 { namespace tag { struct cast_impl_ : boost::dispatch::tag::formal_ { typedef boost::dispatch::tag::formal_ parent; }; } }

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct generator<nt2::tag::cast_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::type child0;
    typedef typename boost::dispatch::meta::semantic_of<child0>::type semantic;
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::type child1;
    typedef typename boost::proto::result_of::value<child1>::value_type::type T;
    typedef expression< typename boost::remove_const<Expr>::type
                      , typename boost::dispatch::meta::factory_of< semantic, typename meta::scalar_of<semantic>::type >::type::template
                        apply<T>::type
                      >                                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  template<class Domain, class Expr>
  struct size_of<nt2::tag::cast_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr, 0>::type  child0;
    typedef typename child0::extent_type                              result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };
} } }

namespace nt2 { namespace ext
{
  template<class Expr, class Data>
  struct run_value
   : meta::strip<typename meta::scalar_of<Expr>::type>
  {
  };

  template<class Expr, class Target>
  struct run_value<Expr, meta::as_<Target> > : run_value<Expr, Target> {};

  template<class Expr, class T, class X>
  struct run_value<Expr, boost::simd::native<T, X> >
  {
    typedef boost::simd::native<typename meta::strip<typename meta::scalar_of<Expr>::type>::type, X> type;
  };

  // scalar impl general
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cast_, tag::cpu_
                            , (A0)(To)
                            , (scalar_< unspecified_<A0> >)
                              (target_< scalar_< unspecified_<To> > >)
                            )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      return result_type(a0);
    }
  };

  // signedness change
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cast_, tag::cpu_
                            , (A0)(To)
                            , (scalar_< signed_<A0> >)
                              (target_< scalar_< unsigned_<To> > >)
                            )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      typedef typename meta::as_unsigned<A0>::type uA0;
      return result_type(uA0(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cast_, tag::cpu_
                            , (A0)(To)
                            , (scalar_< unsigned_<A0> >)
                              (target_< scalar_< signed_<To> > >)
                            )
  {
    typedef typename To::type result_type;
    result_type operator()(A0 const& a0, To const&) const
    {
      typedef typename meta::as_signed<A0>::type sA0;
      return result_type(sA0(a0));
    }
  };

  // identity / signedness
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::cast_impl_, tag::cpu_
                            , (A0)/*(T)(N)*/(To)(State)(Data)
                            , (is_same< typename meta::as_signed<typename A0::value_type>::type, typename meta::as_signed<typename To::type>::type >)
                            , (ast_<A0>) // ((expr_< generic_< unspecified_<A0> >, T, N>))
                              (target_< scalar_< unspecified_<To> > >)
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename run_value<To, Data>::type result_type;
    result_type operator()(A0& a0, To const&, State const& p, Data const& data) const
    {
      return bitwise_cast<result_type>(nt2::run(a0, p, data));
    }
  };

  // scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cast_impl_, tag::cpu_
                            , (A0)(T)(N)(To)(State)(Data)
                            , ((expr_< generic_< unspecified_<A0> >, T, N>))
                              (target_< scalar_< unspecified_<To> > >)
                              (generic_< integer_<State> >)
                              ((target_< scalar_< unspecified_<Data> > >))
                            )
  {
    typedef typename To::type result_type;
    result_type operator()(A0& a0, To const&, State const& p, Data const& data) const
    {
      return cast<result_type>(nt2::run(a0, p, data));
    }
  };

  // toint -- convert to int then upgrade/downgrade
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::cast_impl_, tag::cpu_
                            , (A0)/*(T)(N)*/(To)(State)(Data)(X)
                            , (mpl::and_< meta::is_floating_point<typename A0::value_type>
                                        , mpl::equal_to< mpl::sizeof_<typename To::type>
                                                       , mpl::sizeof_<typename A0::value_type>
                                                       >
                                        >)
                            , (ast_<A0>) //((expr_< generic_< floating_<A0> >, T, N>))
                              (target_< scalar_< integer_<To> > >)
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename meta::call<tag::toint_(A0&)>::type as_int;
    typedef typename meta::call<tag::cast_impl_(as_int, To const&, State const&, Data const&)>::type result_type;

    result_type operator()(A0& a0, To const& to, State const& p, Data const& data) const
    {
      return typename make_functor<tag::cast_impl_, A0>::type()(nt2::toint(a0), to, p, data);
    }
  };

  // tofloat -- upgrade/downgrade then convert to float
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::cast_impl_, tag::cpu_
                            , (A0)/*(T)(N)*/(To)(State)(Data)(X)
                            , (meta::is_integral<typename A0::value_type>)
                            , (ast_<A0>) //((expr_< generic_< integer_<A0> >, T, N>))
                              (target_< scalar_< floating_<To> > >)
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename meta::as_integer<To>::type int_type;
    typedef typename meta::call<tag::cast_impl_(A0&, int_type const&, State const&, Data const&)>::type inner;
    typedef typename meta::call<tag::tofloat_(inner)>::type result_type;

    result_type operator()(A0& a0, To const& to, State const& p, Data const& data) const
    {
      return nt2::tofloat(typename make_functor<tag::cast_impl_, A0>::type()(a0, int_type(), p, data));
    }
  };

  // upgrade
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::cast_impl_, tag::cpu_
                            , (A0)(To)(State)(Data)(X)
                            , (mpl::less< mpl::sizeof_< typename A0::value_type >, mpl::sizeof_< typename To::type > >)
                            , (ast_<A0>)
                              (target_< scalar_< arithmetic_<To> > >)
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename run_value<To, Data>::type rvec;
    typedef typename meta::downgrade<rvec>::type vec;
    typedef rvec result_type;

    result_type operator()(A0& a0, To const& to, State const& p, Data const& data) const
    {
      rvec r0, r1;
      nt2::split(typename make_functor<tag::cast_impl_, A0>::type()(a0, meta::as_<typename meta::scalar_of<vec>::type>(), p, data), r1, r0);

      // FIXME: only works if p is scalar
      return p/a0.leading_size() % meta::cardinal_of<vec>::value ? r0 : r1;
    }
  };

  // downgrade
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::cast_impl_, tag::cpu_
                            , (A0)(To)(State)(Data)(X)
                            , (mpl::and_< mpl::greater< mpl::sizeof_< typename A0::value_type >, mpl::sizeof_< typename To::type > >
                                        , mpl::or_< mpl::not_< meta::is_integral<typename A0::value_type> >
                                                  , meta::is_integral<typename To::type>
                                                  >
                                        >)
                            , (ast_<A0>)
                              (target_< scalar_< arithmetic_<To> > >)
                              (generic_< integer_<State> >)
                              ((target_< simd_< fundamental_<Data>, X > >))
                            )
  {
    typedef typename run_value<To, Data>::type rvec;
    typedef typename meta::upgrade<rvec>::type vec;
    typedef rvec result_type;

    result_type operator()(A0& a0, To const& to, State const& p, Data const& data) const
    {
      vec v0, v1;
      v0 = typename make_functor<tag::cast_impl_, A0>::type()(a0, meta::as_<typename meta::scalar_of<vec>::type>(), p, data);

      // FIXME: doesn't work if not enough data
      v1 = typename make_functor<tag::cast_impl_, A0>::type()(a0, meta::as_<typename meta::scalar_of<vec>::type>(), p+meta::cardinal_of<vec>::value, data);
      return nt2::group(v0, v1);
    }
  };

  // call impl from run
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(N)(State)(Data)
                            , ((node_<A0, nt2::tag::cast_, N>))
                              (generic_< integer_<State> >)
                              (unspecified_<Data>)
                            )
  {
    typedef typename boost::proto::result_of::child_c<A0&, 0>::type child0;
    typedef typename boost::proto::result_of::child_c<A0&, 1>::type child1;
    typedef typename boost::proto::result_of::value<child1>::value_type T;

    typedef typename meta::call<tag::cast_impl_(child0, T const&, State const&, Data const&)>::type result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      return typename make_functor<tag::cast_impl_, A0>::type()(boost::proto::child_c<0>(a0), boost::proto::value(boost::proto::child_c<1>(a0)), p, data);
    }
  };
} }

#endif
