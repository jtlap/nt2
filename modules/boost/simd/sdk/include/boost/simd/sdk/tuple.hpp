#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_TUPLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_TUPLE_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/fusion/support.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/size.hpp>

#define TUPLE_TYPES(z, n, t) typedef T##n m##n##_type;
#define TUPLE_MEMBERS(z, n, t) T##n m##n;
#define TUPLE_CTORS(z, n, t) tuple(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& a)) BOOST_PP_EXPR_IF(n, :) BOOST_PP_ENUM(n, TUPLE_CTORS_, ~) {}
#define TUPLE_CTORS_(z, n, t) m##n(a##n)

namespace boost { namespace simd
{
  namespace tag
  {
    struct tuple_ {};
  }
  
  template<BOOST_PP_ENUM_BINARY_PARAMS(BOOST_DISPATCH_MAX_ARITY, class T, = void BOOST_PP_INTERCEPT)>
  struct tuple;
  
  namespace details
  {
    template<class Seq, class Lambda, int N>
    struct as_tuple;
  }
  
  namespace meta
  {
    template<class Seq, class Lambda = boost::dispatch::identity>
    struct as_tuple
     : details::as_tuple<Seq, Lambda, fusion::result_of::size<Seq>::type::value>
    {
    };
  }
  
} }

namespace boost { namespace fusion { namespace extension
{
  template<>
  struct is_sequence_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply : mpl::true_
    {
    };
  };

  template<>
  struct is_view_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply : mpl::false_
    {
    };
  };
  
  template<>
  struct size_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply
     : mpl::size_t<Seq::static_size>
    {
    };
  };
  
  template<>
  struct at_impl<boost::simd::tag::tuple_>
  {
    template<class Seq, int N>
    struct apply_c;
    
    template<class Seq, class N>
    struct apply : apply_c<Seq, N::value>
    {
    };
  };
  
  template<>
  struct value_at_impl<boost::simd::tag::tuple_>
  {
    template<class Seq, int N>
    struct apply_c;
    
    template<class Seq, class N>
    struct apply : apply_c<Seq, N::value>
    {
    };
  };

  template<>
  struct begin_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply
    {
      typedef boost::simd::at_iterator<Seq, 0> type;
      BOOST_FORCEINLINE static type call(Seq& seq)
      {
        return type(seq);
      }
    };
  };

  template<>
  struct end_impl<boost::simd::tag::tuple_>
  {
    template<class Seq>
    struct apply
    {
      typedef boost::simd::at_iterator<Seq, Seq::static_size> type;
      BOOST_FORCEINLINE static type call(Seq& seq)
      {
        return type(seq);
      }
    };
  };

} } }

namespace boost { namespace simd
{
  template<class Seq, int N>
  typename fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq const, N>::type at_c(Seq const& seq)
  {
    return fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq const, N>::call(seq);
  }
  
  template<class Seq, int N>
  typename fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq, N>::type at_c(Seq& seq)
  {
    return fusion::extension::template at_impl<tag::tuple_>::template apply_c<Seq, N>::call(seq);
  }
} }

#define HEAD <BOOST_PP_ENUM_PARAMS(N, T)>
#define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_PP_DEC(BOOST_DISPATCH_MAX_ARITY), "boost/simd/sdk/tuple.hpp"))
#include BOOST_PP_ITERATE()

#undef HEAD
#define HEAD
#define BOOST_PP_ITERATION_PARAMS_1 (3, ( BOOST_DISPATCH_MAX_ARITY, BOOST_DISPATCH_MAX_ARITY, "boost/simd/sdk/tuple.hpp"))
#include BOOST_PP_ITERATE()

#undef HEAD
#undef TUPLE_CTORS_
#undef TUPLE_CTORS
#undef TUPLE_MEMBERS
#undef TUPLE_TYPES

#endif

#else /* BOOST_PP_IS_ITERATING */

#define N BOOST_PP_ITERATION()

namespace boost { namespace simd
{
  template<BOOST_PP_ENUM_PARAMS(N, class T)>
  struct tuple HEAD
  {
    typedef tag::tuple_ fusion_tag;
    static const std::size_t static_size = N;
    BOOST_PP_REPEAT(N, TUPLE_TYPES, ~)
    
    BOOST_PP_REPEAT(BOOST_PP_INC(N), TUPLE_CTORS, ~)
    BOOST_PP_REPEAT(N, TUPLE_MEMBERS, ~)
  };
} }

namespace boost { namespace simd { namespace details
{
  template<class Seq, class Lambda>
  struct as_tuple<Seq, Lambda, N>
  {
    #define M0(z, n, t) typename boost::mpl::apply<Lambda, typename fusion::result_of::value_at_c<Seq, n>::type>::type
    typedef tuple<BOOST_PP_ENUM(N, M0, ~)> type;
    #undef M0
  };
} } }

namespace boost { namespace fusion { namespace extension
{
  template<class Seq>
  struct value_at_impl<boost::simd::tag::tuple_>
  ::apply_c<Seq, BOOST_PP_DEC(N) >
  {
    typedef typename Seq::BOOST_PP_CAT(BOOST_PP_CAT(m, BOOST_PP_DEC(N)), _type) type;
  };
  
  template<class Seq>
  struct at_impl<boost::simd::tag::tuple_>
  ::apply_c<Seq, BOOST_PP_DEC(N) >
  {
    typedef typename Seq::BOOST_PP_CAT(BOOST_PP_CAT(m, BOOST_PP_DEC(N)), _type)& type;
    BOOST_FORCEINLINE static type call(Seq& seq)
    {
      return seq.BOOST_PP_CAT(m, BOOST_PP_DEC(N));
    }
  };
  
  template<class Seq>
  struct at_impl<boost::simd::tag::tuple_>
  ::apply_c<Seq const, BOOST_PP_DEC(N) >
  {
    typedef typename Seq::BOOST_PP_CAT(BOOST_PP_CAT(m, BOOST_PP_DEC(N)), _type) const& type;
    BOOST_FORCEINLINE static type call(Seq const& seq)
    {
      return seq.BOOST_PP_CAT(m, BOOST_PP_DEC(N));
    }
  };
} } }

#endif
