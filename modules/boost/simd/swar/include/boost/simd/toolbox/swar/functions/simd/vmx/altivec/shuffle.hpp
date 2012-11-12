//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHUFFLE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT
#include <boost/simd/toolbox/swar/functions/shuffle.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/toolbox/swar/functions/details/perm.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <nt2/sdk/meta/display_type.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::altivec_
                                    , (A0)(P)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                                     result_type;
    typedef P                                      permutation_t;
    typedef meta::cardinal_of<result_type>         card_t;
    typedef mpl::vector<>                          empty_t;
    typedef typename mpl::copy< mpl::range_c<std::size_t,0,card_t::value>
                     , mpl::back_inserter<empty_t> 
                     >::type range_t;
    typedef typename mpl::transform< range_t
                                   , mpl::apply_wrap2< typename permutation_t::type
                                                     , mpl::_1,card_t
                                                     >
                                   >::type result_t;
    typedef mpl::transform< result_t
                          , mpl::if_< mpl::equal_to< mpl::_1
                                                   , mpl::size_t<-1> 
                                                   >
                                    , mpl::char_<0x00>
                                    , mpl::char_<0xFF>
                                    >
                          >::type mask_t;

    template<bool B> struct selector {};

    result_type operator()(A0 const& a0, P const&) const
    {
      return eval(a0, selector<mpl::contains<result_t,mpl::size_t<-1> >::value>());
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, selector<false> const&) const
    {
      result_type that = vec_perm(a0(),a0(),details::permute<P,card_t::value>::call()); 
      return that;
    }

    BOOST_FORCEINLINE result_type eval(A0 const& a0, selector<true> const&) const
    {
      native<uint8_t> mask = make<result_type>( mpl::at<mask_t, 0>::type::value
                                              , mpl::at<mask_t, 1>::type::value
                                              , mpl::at<mask_t, 2>::type::value
                                              , mpl::at<mask_t, 3>::type::value
                                              , mpl::at<mask_t, 4>::type::value
                                              , mpl::at<mask_t, 5>::type::value
                                              , mpl::at<mask_t, 6>::type::value
                                              , mpl::at<mask_t, 7>::type::value
                                              , mpl::at<mask_t, 8>::type::value
                                              , mpl::at<mask_t, 9>::type::value
                                              , mpl::at<mask_t,10>::type::value
                                              , mpl::at<mask_t,11>::type::value
                                              , mpl::at<mask_t,12>::type::value
                                              , mpl::at<mask_t,13>::type::value
                                              , mpl::at<mask_t,14>::type::value
                                              , mpl::at<mask_t,15>::type::value
                                              );

      result_type that = vec_perm(a0(),a0(),details::permute<P,card_t::value>::call()); 
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shuffle_
                                    , boost::simd::tag::altivec_
                                    , (A0)(P)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                                      ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                                      (target_< unspecified_<P> >)
                                    )
  {
    typedef A0                              result_type;
    typedef P                               permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a0, A0 const& a1, P const&) const
    {
      return vec_perm(a0(),a1(),details::permute<P,card_t::value>::call());  
    }
  };
} } }

#endif
#endif