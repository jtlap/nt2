//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_SPLAT_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/splat.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/load.hpp>
#include <boost/simd/include/functions/simd/tofloat.hpp>
#include <boost/simd/include/functions/simd/toint.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // With no idea what we're doing, just fill the vector piecewise
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< unspecified_<A0> >)
                              ((target_< simd_< unspecified_<A1>, X > >))
                            )
  {
    typedef typename A1::type result_type;

    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::scalar_of<result_type>::type sA1;

      result_type tmp;
      for(unsigned int i = 0; i != meta::cardinal_of<result_type>::value; ++i)
        tmp[i] = static_cast<sA1>(a0);

      return tmp;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::splat_, tag::cpu_
                                      , (A0)(A1)(X)(Y)
                                      , (mpl::equal_to
                                        < boost::simd::meta::cardinal_of<A0>
                                        , boost::simd::meta
                                          ::cardinal_of<typename A1::type>
                                        >
                                        )
                                      , ((simd_< unspecified_<A0>, X >))
                                        ((target_< simd_< unspecified_<A1>, Y > >))
                                      )
  {
    typedef typename A1::type result_type;

    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::scalar_of<result_type>::type sA1;

      BOOST_SIMD_ALIGNED_TYPE(sA1) tmp[meta::cardinal_of<A0>::value];
      for(unsigned int i = 0; i != meta::cardinal_of<result_type>::value; ++i)
      {
        tmp[i] = static_cast<sA1>(a0[i]);
      }

      return load<result_type>(&tmp[0]);
    }
  };

  //============================================================================
  // Splatting a SIMD value to another can use bitwise_cast, toint or tofloat (optimizations)
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::splat_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (mpl::equal_to
                                          < boost::simd::meta::cardinal_of<A0>
                                          , boost::simd::meta
                                            ::cardinal_of<typename A1::type>
                                          >
                                        )
                                      , ((simd_< arithmetic_<A0>, X >))
                                        ((target_< simd_< arithmetic_<A1>,X> >))
                                      )
  {
    typedef typename A1::type result_type;

    inline result_type operator()(const A0& a0, const A1&) const
    {
      return bitwise_cast<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::splat_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (mpl::equal_to
                                          < boost::simd::meta::cardinal_of<A0>
                                          , boost::simd::meta
                                            ::cardinal_of<typename A1::type>
                                          >
                                        )
                                      , ((simd_< integer_<A0>, X >))
                                        ((target_< simd_< floating_<A1>, X > >))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return simd::tofloat(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::splat_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , (mpl::equal_to
                                          < boost::simd::meta::cardinal_of<A0>
                                          , boost::simd::meta
                                            ::cardinal_of<typename A1::type>
                                          >
                                        )
                                      , ((simd_< floating_<A0>, X >))
                                        ((target_< simd_< integer_<A1>, X > >))
                                      )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return bitwise_cast<result_type>(simd::toint(a0));
    }
  };
} } }

#endif
