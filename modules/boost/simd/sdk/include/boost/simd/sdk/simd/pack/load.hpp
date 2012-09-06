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
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// load pack without offset
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              (target_< ast_<A2> >)
                            )
  {
    typedef typename proto::domain_of<typename A2::type>::type  domain;
    typedef dispatch::meta::
            as_<typename dispatch::meta::
                semantic_of<typename A2::type>::type
               >  value;
   
    typedef typename proto::result_of::
            make_expr<tag::load_, domain, const A0&, const A1&, const value&>::type
    result_type;
   
    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 const&) const
    {
      return boost::proto::detail::
             make_expr_<tag::load_, domain, const A0&, const A1&, const value&>()(a0, a1, value());
    }
  };
} } }


////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd pack with suboffset
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_ , tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              (target_< ast_<A2> >)
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename proto::domain_of<typename A2::type>::type  domain;
    typedef dispatch::meta::
            as_<typename dispatch::meta::
                semantic_of<typename A2::type>::type
               >  value;
   
    typedef typename proto::result_of::
            make_expr<tag::load_, domain, const A0&, const A1&, const value&, const A3&>::type
    result_type;
   
    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 const&, A3 const& a3) const
    {
      return boost::proto::detail::
             make_expr_<tag::load_, domain, const A0&, const A1&, const value&, const A3&>()(a0, a1, value(), a3);
    }
  };
} } }

#endif
