//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_REPMAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_REPMAT_HPP_INCLUDED

#include <nt2/core/functions/repmat.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates from an expression and an extent
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::repmat_
                                          , container::domain
                                          , A0 const&
                                          , box<sizes_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      return  boost::proto::
              make_expr<nt2::tag::repmat_, container::domain>
              ( boost::cref(a0)
              , boxify(a1)
              );
    }
  };

  //============================================================================
  // Generates from an expression and a size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::repmat_
                                          , container::domain
                                          , A0 const&
                                          , box<of_size_max>
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      BOOST_ASSERT_MSG
      ( nt2::isrow(a1)
      , "Error using repmat: Size vector must be a row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a1));
      nt2::memory::cast_copy(a1.raw(), a1.raw()+sz, &sizee[0]);

      return  boost::proto::
              make_expr<nt2::tag::repmat_, container::domain>
              ( boost::cref(a0)
              , boxify(sizee)
              );
    }
  };

  //============================================================================
  // Generates from an expression and a single size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::repmat_
                                          , container::domain
                                          , A0 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()( A0 const& a0, A1 const& a1 ) const
    {
      return  boost::proto::
              make_expr<nt2::tag::repmat_, container::domain>
              ( boost::cref(a0)
              , boxify(_2D(a1,a1))
              );
    }
  };

  //============================================================================
  // Generates from an expression and two sizes
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< arithmetic_<A1> >)
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::repmat_
                                          , container::domain
                                          , A0 const&
                                          , box<_2D>
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()( A0 const& a0, A1 const& a1, A2 const& a2 ) const
    {
      return  boost::proto::
              make_expr<nt2::tag::repmat_, container::domain>
              ( boost::cref(a0)
              , boxify(_2D(a1,a2))
              );
    }
  };
} }

#endif
