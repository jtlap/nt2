/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_LOAD_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for SIMD packs
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// load pack without offset
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , tag::cpu_
                            , (A0)(A1)(A2)(T)(C)(Sema)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< expr_< A2
                                              , domain_< boost::simd::domain<T,C> >
                                              , tag::terminal_
                                              , Sema
                                              >
                                       >
                              ))
                            )
  {
    typedef typename A2::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(3) { return result_type(a0,a1); }
  };
} } }


////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd pack with suboffset
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , tag::cpu_
                            , (A0)(A1)(A2)(T)(C)(Sema)(A3)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< expr_< A2
                                              , domain_< boost::simd::domain<T,C> >
                                              , tag::terminal_
                                              , Sema
                                              >
                                       >
                              ))
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename A2::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(4) { return result_type(a0,a1,a3); }
  };
} } }

#endif
