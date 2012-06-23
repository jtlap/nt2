/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_UNALIGNED_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// unaligned load for SIMD packs
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , tag::cpu_
                            , (A0)(A1)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              (target_< ast_< unspecified_<A1> > >)
                            )
  {
    typedef typename proto::domain_of<typename A1::type>::type  domain;
    typedef dispatch::meta::
            as_<typename dispatch::meta::
                semantic_of<typename A1::type>::type
               >  value;

    typedef typename proto::result_of::
            make_expr<tag::unaligned_load_, domain, const A0&, const value&>::type
    result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0 const& a0, A1 const&) const
    {
      return boost::proto::detail::
             make_expr_<tag::unaligned_load_, domain, const A0&, const value&>()(a0, value());
    }
  };
} } }

#endif
