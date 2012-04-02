//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RESHAPE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RESHAPE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/reshape.hpp>
#include <nt2/include/functions/box.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + of_size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reshape_, tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::reshape_
                                          , container::domain
                                          , A0&
                                          , box<A1>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
    {
      return  boost::proto::
              make_expr < nt2::tag::reshape_
                        , container::domain
                        > ( boost::cref(a0), boxify(a1) );
    }
  };
{
  //============================================================================
  // Generates linearize_ from expression + expression containing size
  //============================================================================
  ////NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reshape_, tag::cpu_
                            ////, (A0)
                            ////, (ast_<A0>)
                              ////(ast_<A1>)
                            ////)
  ////{
    ////typedef typename  boost::proto::
                      ////result_of::make_expr< nt2::tag::reshape_
                                          ////, container::domain
                                          ////, A0&
                                          ////, box<A1>
                                          ////>::type             result_type;
////
    ////BOOST_FORCEINLINE result_type operator()(A0& a0, A1 const& a1) const
    ////{
      ////return  boost::proto::
              ////make_expr < nt2::tag::reshape_
                        ////, container::domain
                        ////> ( boost::cref(a0), boxify(a1) );
    ////}
  ////};
} }

#endif
