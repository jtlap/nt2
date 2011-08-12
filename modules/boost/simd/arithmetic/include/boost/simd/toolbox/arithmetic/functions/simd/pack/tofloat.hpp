//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_PACK_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_PACK_TOFLOAT_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/simd/pack/meta/retarget.hpp>

////////////////////////////////////////////////////////////////////////////////
// Allow tofloat_ to eat up w/e as a type as long as cardinal is correct
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd
{
  template<class T, class N> template<class Dummy>
  struct  grammar_cases<T,N>::case_<boost::simd::tag::tofloat_, Dummy>
        : boost::proto::
          unary_expr< boost::simd::tag::tofloat_ , grammar<boost::proto::_, N> >
  {};
} }

////////////////////////////////////////////////////////////////////////////////
// Say to compute that tofloat_ need to retarget its inner evaluation process
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  template<class Target>
  struct  compute<boost::simd::tag::tofloat_,Target>
        : boost::proto::
          call< functor < boost::simd::tag::tofloat_
                        , Target
                        > ( compile< compute<boost::mpl::_1, Target> >
                            ( boost::proto::_child0
                            , boost::simd::meta::retarget(boost::proto::_child0)
                            , boost::proto::_data
                            )
                          )
              >
  {};
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tofloat_, tag::cpu_,  (A0)(T)(C)(Tag)(S)
                            , ((expr_<A0, domain_< simd::domain<T,C> >,Tag,S>))
                            )
  {
    // tofloat MUST return something living in the domain<real,Card>
    // so we compute the destination domain so proto is A-OK with it.
    typedef typename dispatch::meta::as_real<T>::type real_type;
    typedef typename boost::proto::result_of::
    make_expr < boost::simd::tag::tofloat_ , simd::domain<real_type,C>
                              , A0 const&
              >::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_real<T>::type real_type;
      return boost::proto::make_expr< boost::simd::tag::tofloat_
                                    , simd::domain<real_type,C>
                                    , A0 const&
                                    >( boost::cref(a0) );
    }
  };
} } }

#endif
