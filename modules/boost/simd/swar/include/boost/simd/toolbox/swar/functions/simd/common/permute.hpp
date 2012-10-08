//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_PERMUTE_HPP_INCLUDED

#include <boost/simd/toolbox/swar/functions/permute.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, tag::cpu_
                                      , (A0)(X)(P)
                                      , ((simd_< arithmetic_<A0>, X>))
                                        (target_< unspecified_<P> >)
                                      )
  {
    typedef A0                              result_type;
    typedef typename P::type                permutation_t;
    typedef meta::cardinal_of<result_type>  card_t;

    result_type operator()(A0 const& a0, P const&) const
    {
      result_type that;
      eval(a0, that, boost::mpl::int_<card_t::value-1>());
      return that;
    }

    template<class N>
    void eval(A0 const& a0, result_type& that, N const&) const
    {
      typedef typename boost::mpl::apply<permutation_t,N,card_t>::type idx_t;
      that[N::value] = (idx_t::value >= 0) ? a0[ idx_t::value ] : 0;
      eval(a0,that,boost::mpl::int_<N::value-1>());
    }

    void eval(A0 const& a0, result_type& that, boost::mpl::int_<-1> const&) const
    {}
  };
} } }

#endif
