//==============================================================================
//         Copyright 2014               Jean-Thierry Lapreste
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_TMUL_NP_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_TMUL_NP_HPP_INCLUDED

#include <boost/simd/matprod/functions/tmul_np.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_np.hpp>
#include <boost/simd/matprod/functions/simd/common/transn.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace ext
{


  // return ta*b
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tmul_np_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                    )

  {
    typedef typename dispatch::meta::strip<B>::type result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b) const
    {
      return mul_np(transn(a), b);
    }
  };


  //ta*b is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tmul_np_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(R)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b, R & r) const
    {
       mul_np(transn(a), b, r);
    }
  };

  //alpha*ta*b is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tmul_np_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(R)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, R & r) const
    {
      mul_np(alpha, transn(a), b, r);
    }

  };

  //r receives beta*r+ alpha*ta*b
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tmul_np_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(BETA)(R)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, const BETA& beta, R & r) const
    {
       mul_np(alpha, transn(a), b, beta, r);
    }
  };
} } }

#endif
