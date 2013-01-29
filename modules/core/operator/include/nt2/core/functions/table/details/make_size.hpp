//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_MAKE_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_MAKE_SIZE_HPP_INCLUDED

#include <nt2/sdk/meta/is_colon.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/relative_size.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/sdk/meta/safe_at.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Build a of_size for size_of
  template< int N
          , class Domain
          , class Shape
          , class Sizes, class Bases
          , class Children
          >
  struct make_size;
                                                                                                   \
  #define M1(z,n,t)                                                                                \
  mpl_value                                                                                        \
  < typename meta::                                                                                \
    call< tag::relative_size_                                                                      \
        ( typename  boost::proto::result_of::child_c<Children, n>::type                            \
        , typename  boost::fusion::result_of::                                                     \
                    at_c<typename meta::strip<Sizes>::type, n>::type                               \
        , typename  boost::fusion::result_of::                                                     \
                    at_c<typename meta::strip<Bases>::type, n>::type                               \
        )                                                                                          \
        >::type                                                                                    \
  >::value                                                                                         \
  /**/

  #define M2(z,n,t)                                                                                \
  that[n] = nt2::relative_size( boost::proto::child_c<n>(children)                                 \
                              , boost::fusion::at_c<n>(sz)                                         \
                              , boost::fusion::at_c<n>(bs)                                         \
                              );                                                                   \
  /**/

  #define M3(z,n,t)                                                                                \
  template<class Dummy>                                                                            \
  struct impl<n, Dummy>                                                                            \
  {                                                                                                \
    BOOST_FORCEINLINE                                                                              \
    static result_type call(Sizes const& sz, Bases const& bs, Children const& children)            \
    {                                                                                              \
      result_type that;                                                                            \
      BOOST_PP_REPEAT(n, M2, t)                                                                    \
      return that;                                                                                 \
    }                                                                                              \
  };                                                                                               \
  /**/

  #define M0(z,n,t)                                                                                \
  template< class Domain                                                                           \
          , class Shape, class Sizes, class Bases                                                  \
          , class Children                                                                         \
          >                                                                                        \
  struct make_size<n, Domain, Shape, Sizes, Bases, Children>                                       \
  {                                                                                                \
    typedef of_size_<BOOST_PP_ENUM(n, M1, n)> result_type;                                         \
                                                                                                   \
    template<int N, class Dummy = void>                                                            \
    struct impl {};                                                                                \
                                                                                                   \
    BOOST_PP_REPEAT(BOOST_PP_INC(n), M3, n)                                                        \
                                                                                                   \
    BOOST_FORCEINLINE result_type                                                                  \
    operator()(Shape const&, Sizes const& s, Bases const& b, Children const& children) const       \
    {                                                                                              \
      return impl<result_type::static_size>::call(s, b, children);                                 \
    }                                                                                              \
  };                                                                                               \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2, BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)
  #undef M0
  #undef M1
  #undef M2
  #undef M3

  template<class Seq>
  struct is_definitely_not_vector
  {
    static const std::size_t n = Seq::static_size;
    static const bool value = n > 1 && meta::mpl_safe_at_c<typename Seq::values_type, 1, boost::mpl::long_<1> >::type::value != -1;
    typedef boost::mpl::bool_<value> type;
  };

  template<class Seq>
  struct is_definitely_vector
  {
    static const std::size_t n = Seq::static_size;
    static const bool value = n <= 1u || (n == 2u && meta::mpl_safe_at_c<typename Seq::values_type, 0, boost::mpl::long_<1> >::type::value == 1);
    typedef boost::mpl::bool_<value> type;
  };

  template< class Domain
          , class Shape, class Sizes, class Bases
          , class Children
          >
  struct make_size<1, Domain, Shape, Sizes, Bases, Children>
  {
    typedef typename boost::proto::result_of::child_c<Children&, 0>::value_type::extent_type idx0_sz;
    static const std::size_t shape_min = Shape::static_size > 2u ? 2u : Shape::static_size;
    static const std::size_t size_max = idx0_sz::static_size > shape_min ? idx0_sz::static_size : shape_min;
    typedef typename nt2::make_size<size_max>::type size_max_type;

    typedef typename boost::mpl::
            if_< boost::mpl::and_< is_definitely_vector<Shape>, is_definitely_vector<idx0_sz> >
               , typename boost::mpl::if_c< Shape::static_size == 1u, nt2::of_size_<-1>, nt2::of_size_<1, -1> >::type
               , typename boost::mpl::
                 if_< boost::mpl::or_< is_definitely_not_vector<Shape>, is_definitely_not_vector<idx0_sz> >
                    , idx0_sz
                    , size_max_type
                    >::type
               >::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(Shape const& shp, Sizes const& sz, Bases const& bs, Children const& children) const
    {
      std::size_t s = nt2::relative_size( boost::proto::child_c<0>(children)
                                        , boost::fusion::at_c<0>(sz)
                                        , boost::fusion::at_c<0>(bs)
                                        );

      idx0_sz const& idx0 = boost::proto::child_c<0>(children).extent();
      std::size_t n = nt2::ndims(shp);
      std::size_t m = nt2::ndims(idx0);

      bool idx0_vector = m == 1u || ( m == 2u && boost::fusion::at_c<0>(idx0) == 1u);
      if(idx0_vector && n == 1u) // column vector
        return nt2::of_size(s);

      if(idx0_vector && n == 2u && boost::fusion::at_c<0>(shp) == 1u) // row vector
        return nt2::of_size(1u, s);

      return boost::proto::child_c<0>(children).extent();
    }
  };
} }

#endif
