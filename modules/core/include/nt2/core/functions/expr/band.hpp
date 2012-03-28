//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BAND_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/band.hpp>
#include <nt2/include/functions/box.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/core/functions/details/band.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Unary band
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::band_, tag::cpu_, (A0), (ast_<A0>) )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::band_
                                          , container::domain
                                          , A0 const&
                                          , box<nt2::details::band>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using band: First input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::band_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , boxify(nt2::details::band())
                                      );
    }
  };

  //============================================================================
  // Binary band 1
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::offset_band1_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::offset_band1_
                                          , container::domain
                                          , A0 const&
                                          , box<nt2::details::offset_band1>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using band: First input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::offset_band1_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , boxify(nt2::details::offset_band1(a1))
                                      );
    }
  };

  //============================================================================
  // Binary band 2
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::offset_band2_, tag::cpu_
                              , (A0)(A1)(A2)
                            , (ast_<A0>)
                              (scalar_< integer_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::offset_band2_
                                          , container::domain
                                          , A0 const&
                                          , box<nt2::details::offset_band2>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      // Expression must be a matrix
      BOOST_ASSERT_MSG( nt2::ismatrix(a0)
                      , "Error using band: First input must be 2D."
                      );

      return boost::proto::make_expr< nt2::tag::offset_band2_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , boxify(nt2::details::offset_band2(a1, a2))
                                      );
    }
  };  
} }

#endif
