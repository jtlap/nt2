//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_SIZE_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/include/functions/relative_size.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/sdk/meta/is_colon.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // If the result of a size computation is a MPL Integral, keep it;
  // If not, return -1 so the of_size will be flagged as dynamic
  //============================================================================
  template<class T, class Enable = void>
  struct mpl_value : boost::mpl::int_<-1> {};

  template<class T>
  struct mpl_value < T
                   , typename boost::
                     enable_if < boost::
                                 is_class< typename meta::strip<T>::type >
                               >::type
                   >
    : meta::strip<T>::type
  {};

  // build size
  template<int N, class Sizes, class Children>
  struct make_size;

  #define M1(z,n,t)                                                             \
  mpl_value < typename meta::                                                   \
              call< tag::relative_size_                                         \
                  ( typename boost::fusion::result_of::at_c<Children, n>::type  \
                  , Sizes, boost::mpl::int_<n>, boost::mpl::int_<t>             \
                  )                                                             \
                  >::type                                                       \
            >::value                                                            \
  /**/

  #define M2(z,n,t)                                                           \
  that[n] = nt2::relative_size( boost::fusion::at_c<n>(children), sz          \
                              , boost::mpl::int_<n>(), boost::mpl::int_<t>()  \
                              );                                              \
  /**/

  #define M3(z,n,t)                                       \
  template<class Dummy>                                   \
  struct impl<n, Dummy>                                   \
  {                                                       \
    BOOST_DISPATCH_FORCE_INLINE                           \
    static result_type call(Sizes sz, Children children)  \
    {                                                     \
      result_type that;                                   \
      BOOST_PP_REPEAT(n, M2, t)                           \
      return that;                                        \
    }                                                     \
  };

  #define M0(z,n,t)                                               \
  template<class Sizes, class Children>                           \
  struct make_size<n, Sizes, Children>                            \
  {                                                               \
    typedef of_size_<BOOST_PP_ENUM(n, M1, n)> result_type;        \
                                                                  \
    template<int N, class Dummy = void>                           \
    struct impl {};                                               \
                                                                  \
    BOOST_PP_REPEAT(BOOST_PP_INC(n), M3, n)                       \
                                                                  \
    BOOST_DISPATCH_FORCE_INLINE                                   \
    result_type operator()(Sizes sz, Children children) const     \
    {                                                             \
      return impl<result_type::static_size>::call(sz, children);  \
    }                                                             \
  };

  BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)
  #undef M0
  #undef M1
  #undef M2
  #undef M3
} }

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Size of a function call node is depends of the indexers
  //============================================================================
  template<class Expr, class Domain, int N>
  struct size_of<tag::function_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 0>::type           child0;

    typedef typename boost::fusion::result_of
                          ::pop_front<Expr const>::type       childN;

    typedef typename size_transform<Domain>::template
            result<size_transform<Domain>(child0)>::type      sz;

    typedef details::make_size<N-1, sz, childN>               impl;
    typedef typename impl::result_type                        result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(Expr& e) const
    {
      return impl()( size_transform<Domain>()(boost::proto::child_c<0>(e))
                   , boost::fusion::pop_front(e)
                   );
    }
  };

  //============================================================================
  // Unary function call node case: if argument is not colon, keep shape
  //============================================================================
  template<class Expr, class Domain>
  struct size_of<tag::function_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 0>::type     child0;

    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 1>::type     child1;

    template<bool B, class Dummy = void>
    struct apply;

    template<class Dummy>
    struct apply<true, Dummy> // is colon
    {
      typedef typename meta::call<tag::numel_(child0)>::type num;
      typedef of_size_< details::mpl_value<num>::value > result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr& e) const
      {
        return result_type(numel(boost::proto::child_c<0>(e)));
      }
    };

    template<class Dummy>
    struct apply<false, Dummy> // is not colon
    {
      typedef typename size_transform<Domain>::template
              result<size_transform<Domain>(child1)>::type result_type;

      BOOST_FORCEINLINE result_type
      operator()(Expr& e) const
      {
        return size_transform<Domain>()(boost::proto::child_c<1>(e));
      }
    };

    typedef apply< meta::is_colon<child1>::value >      impl;
    typedef typename impl::result_type                  result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& e) const
    {
      return impl()(e);
    }
  };
} } }

#endif
