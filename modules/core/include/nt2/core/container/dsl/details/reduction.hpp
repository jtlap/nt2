//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_REDUCTION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_REDUCTION_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/utility/of_size/predef.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/terminal.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/proto/traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

namespace nt2 { namespace container { namespace ext
{
  template<class T>
  struct of_size_reduce;

  #define M0(z, n, t)                                                                              \
  template<BOOST_PP_ENUM_PARAMS(n, std::ptrdiff_t D)>                                              \
  struct of_size_reduce< of_size_< BOOST_PP_ENUM_PARAMS(n, D) > >                                  \
  {                                                                                                \
    typedef of_size_<1 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) BOOST_PP_ENUM_SHIFTED_PARAMS(n, D)> type; \
  };                                                                                               \
  /**/
  BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)
  #undef M0

  //============================================================================
  // This is the factorized size_of for all reduction function.
  // For any given reduction function tag RED, the registration of their
  // size_of is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct size_of<RED,Domain,N,Expr> : reduction_size_of<Expr, N>
  //  {};
  // } } }
  //
  //============================================================================
  template<class RED, int N, class Expr> struct reduction_size_of;

  template<class RED, class Expr> struct reduction_size_of<RED,2,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename child0::extent_type                                    ext_t;
    typedef typename nt2::make_size<ext_t::static_size>::type               result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type res = boost::proto::child_c<0>(e).extent();
      std::size_t red_dim = nt2::terminal(boost::proto::child_c<1>(e)) - 1;

      // If we reduce over the number of dimensions, do nothing
      if(red_dim < result_type::static_size) res[red_dim] = 1;

      return res;
    }
  };

  template<class RED, class Expr> struct reduction_size_of<RED,1,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename child0::extent_type                                    ext_t;
    typedef typename of_size_reduce<ext_t>::type                            result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      ext_t sz = boost::proto::child_c<0>(e).extent();
      std::size_t d = nt2::firstnonsingleton(sz);

      result_type res;
      for(std::size_t i=0; i!=std::min(d, res.size()); ++i)
        res[i] = 1;
      for(std::size_t i=d; i<res.size(); ++i)
        res[i] = sz[i];
      return res;
    }
  };

  //============================================================================
  // This is the factorized generator for all reduction function.
  // For any given reduction function tag RED, the registration of their
  // reshaper is simply :
  //
  // namespace nt2 { namespace container { namespace ext
  // {
  //  template<class Domain, class Expr, int N>
  //  struct generator<RED,Domain,N,Expr> : reduction_generator<Expr>
  //  {};
  // } } }
  //
  //============================================================================
  template<class RED, int N, class Expr> struct reduction_generator
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::type             expr_t;
    typedef typename meta::scalar_of<expr_t>::type                                sstype;
    typedef typename meta::call<RED(sstype)>::type                                value_type;

    typedef typename reduction_size_of<RED,N,Expr>::result_type                   size_type;
    typedef typename boost::mpl::
    if_< boost::is_same< size_type, _0D >
       , value_type
       , memory::container<value_type, size_type>
       >::type                                                                    type;

    typedef expression< typename boost::remove_const<Expr>::type
                      , type
                      >                                                           result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif
