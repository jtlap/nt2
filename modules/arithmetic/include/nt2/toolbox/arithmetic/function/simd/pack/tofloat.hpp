//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_PACK_TOFLOAT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_PACK_TOFLOAT_HPP_INCLUDED

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/simd/pack/meta/retarget.hpp>

////////////////////////////////////////////////////////////////////////////////
// Allow tofloat_ to eat up w/e as a type as long as cardinal is correct
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace simd
{
  template<class T, class N> template<class Dummy>
  struct  grammar_cases<T,N>::case_<tag::tofloat_, Dummy>
        : boost::proto::
          unary_expr< tag::tofloat_ , grammar<boost::proto::_, N> >
  {};
} }

////////////////////////////////////////////////////////////////////////////////
// Say to compute that tofloat_ need to retarget its inner evaluation process
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Target>
  struct  compute<tag::tofloat_,Target>
        : boost::proto::
          call< functor < tag::tofloat_
                        , Target
                        > ( compile< compute<boost::mpl::_1, Target> >
                            ( boost::proto::_child0
                            , retarget(boost::proto::_child0)
                            , boost::proto::_data
                            )
                          )
              >
  {};

  NT2_FUNCTOR_IMPLEMENTATION( tag::tofloat_, tag::cpu_,  (A0)(T)(C)(Tag)(S)
                            , ((expr_<A0, domain_< simd::domain<T,C> >,Tag,S>))
                            )
  {
    // tofloat MUST return something living in the domain<real,Card>
    // so we compute the destination domain so proto is A-OK with it.
    typedef typename meta::as_real<T>::type real_type;
    typedef typename boost::proto::result_of::
    make_expr < tag::tofloat_ , simd::domain<real_type,C>
                              , typename meta::strip<A0>::type const&
              >::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<T>::type real_type;
      return boost::proto::make_expr< tag::tofloat_
                                    , simd::domain<real_type,C>
                                    , A0 const&
                                    >( boost::cref(a0) );
    }
  };
} }

#endif
