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
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/mpl/comparison.hpp>

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct value_type<nt2::tag::split_, Domain, 1, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type::value_type stype;
    typedef typename meta::upgrade<stype>::type type;
  };

  template<class Domain, class Expr>
  struct value_type<nt2::tag::group_, Domain, 1, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type::value_type stype;
    typedef typename meta::downgrade<stype>::type type;
  };

  template<class Domain, class Expr>
  struct value_type<nt2::tag::bitwise_cast_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::type child0;
    typedef typename boost::proto::result_of::value<child0>::value_type::type type;
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

  // bitwise_cast
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_<A0, nt2::tag::bitwise_cast_, boost::mpl::long_<2> >))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename run_value<A0, Data>::type result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      return nt2::bitwise_cast<result_type>(nt2::run(boost::proto::child_c<0>(a0), p, data));
    }
  };

  // split
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , (mpl::greater< mpl::sizeof_<typename A0::value_type>
                                           , mpl::sizeof_<typename boost::proto::result_of::child_c<A0&, 0>::value_type::value_type>
                                           >
                              )
                            , ((node_<A0, nt2::tag::split_, boost::mpl::long_<1> >))
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename run_value<A0, Data>::type rvec;
    typedef typename meta::downgrade<rvec>::type vec;
    typedef rvec result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      rvec r0, r1;
      nt2::split(nt2::run(boost::proto::child_c<0>(a0), p, data), r1, r0);

      // FIXME: only works if p is scalar
      return p/a0.leading_size() % meta::cardinal_of<vec>::value ? r0 : r1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_<A0, nt2::tag::split_, boost::mpl::long_<1> >))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename run_value<A0, Data>::type result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      return result_type(nt2::run(boost::proto::child_c<0>(a0), p, data));
    }
  };

  // group
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(X)
                            , (mpl::less< mpl::sizeof_<typename A0::value_type>
                                        , mpl::sizeof_<typename boost::proto::result_of::child_c<A0&, 0>::value_type::value_type>
                                        >
                              )
                            , ((node_<A0, nt2::tag::group_, boost::mpl::long_<1> >))
                              (generic_< integer_<State> >)
                              ((target_< simd_< unspecified_<Data>, X > >))
                            )
  {
    typedef typename run_value<A0, Data>::type rvec;
    typedef typename meta::upgrade<rvec>::type vec;
    typedef rvec result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      vec v0, v1;
      v0 = run(boost::proto::child_c<0>(a0), p, data);
      v1 = run(boost::proto::child_c<0>(a0), p+meta::cardinal_of<vec>::value, data);

      return nt2::group(v0, v1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_<A0, nt2::tag::group_, boost::mpl::long_<1> >))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename run_value<A0, Data>::type result_type;

    result_type operator()(A0& a0, State const& p, Data const& data) const
    {
      return result_type(nt2::run(boost::proto::child_c<0>(a0), p, data));
    }
  };

  // upgrade -- split recursively
  template<class Expr, class From, class To, class Enable = void>
  struct cast_upgrade
  {
    typedef typename meta::call<tag::split_(Expr&)>::type as_split;
    typedef cast_upgrade<as_split const, typename as_split::value_type, To> rec;
    typedef typename rec::result_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return rec()(nt2::split(e));
    }
  };

  template<class Expr, class From, class To>
  struct cast_upgrade<Expr, From, To, typename boost::enable_if_c< sizeof(From) >= sizeof(To) >::type>
  {
    typedef Expr& result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return e;
    }
  };

  // downgrade -- group recursively
  template<class Expr, class From, class To, class Enable = void>
  struct cast_downgrade
  {
    typedef typename meta::call<tag::group_(Expr&)>::type as_group;
    typedef cast_downgrade<as_group const, typename as_group::value_type, To> rec;
    typedef typename rec::result_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return rec()(nt2::group(e));
    }
  };

  template<class Expr, class From, class To>
  struct cast_downgrade<Expr, From, To, typename boost::enable_if_c< sizeof(From) <= sizeof(To) >::type>
  {
    typedef Expr& result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return e;
    }
  };

  // intfloat -- call tofloat, toint or nothing depending on case
  template<class Expr, class From, class To, class Enable = void>
  struct cast_intfloat
  {
    typedef Expr& result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return e;
    }
  };

  template<class Expr, class From, class To>
  struct cast_intfloat<Expr, From, To, typename boost::enable_if_c< meta::is_integral<From>::value && meta::is_floating_point<To>::value >::type>
  {
    typedef typename meta::call<tag::tofloat_(Expr&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return nt2::tofloat(e);
    }
  };

  template<class Expr, class From, class To>
  struct cast_intfloat<Expr, From, To, typename boost::enable_if_c< meta::is_floating_point<From>::value && meta::is_integral<To>::value>::type>
  {
    typedef typename meta::call<tag::toint_(Expr&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return nt2::toint(e);
    }
  };

  // sign -- change sign if necessary
  template<class Expr, class From, class To, class Enable = void>
  struct cast_sign
  {
    typedef Expr& result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return e;
    }
  };

  template<class Expr, class From, class To>
  struct cast_sign<Expr, From, To, typename boost::enable_if_c< meta::is_integral<To>::value && meta::is_signed<From>::value != meta::is_signed<To>::value>::type>
  {
    typedef typename boost::dispatch::meta::make_integer<sizeof(From), typename meta::sign_of<To>::type>::type type;
    typedef typename meta::call<tag::bitwise_cast_(Expr&, meta::as_<type>)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return nt2::bitwise_cast<type>(e);
    }
  };

  // cast
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cast_, tag::cpu_
                            , (A0)(To)
                            , (ast_<A0>)
                              (target_< scalar_< arithmetic_<To> > >)
                            )
  {
    typedef typename To::type       to;

    template<class T>
    struct as_arg
         : boost::remove_reference<typename boost::dispatch::meta::as_ref<T>::type>
    {};

    typedef cast_upgrade<A0, typename A0::value_type, to> upgrade;
    typedef typename as_arg<typename upgrade::result_type>::type upgraded;

    typedef cast_intfloat<upgraded, typename upgraded::value_type, to> type;
    typedef typename as_arg<typename type::result_type>::type typed;

    typedef cast_sign<typed, typename typed::value_type, to> sign;
    typedef typename as_arg<typename sign::result_type>::type signed_;

    typedef cast_downgrade<signed_, typename signed_::value_type, to> downgrade;
    typedef typename downgrade::result_type result_type;

    result_type operator()(A0& a0, To const&) const
    {
      return downgrade()(sign()(type()(upgrade()(a0))));
    }
  };
} }

#endif
