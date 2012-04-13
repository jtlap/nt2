//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ROWS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ROWS_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/rows.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/first_index.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates rows from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rows_, tag::cpu_
                            , (A0)(T)
                            , (ast_<A0>)
                              (scalar_< arithmetic_<T> >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::rows_
      , container::domain
      , box<_2D>
      , box<nt2::details::rows<T> >
      , meta::as_<T>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& start) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0) && (nt2::ndims(a0) <= 2)
      , "Error using rows: Size vector must be a 2D row vector."
      );

      _2D sizee;
      std::copy(a0.raw(), a0.raw()+2, &sizee[0]);

      return boost::proto::make_expr< nt2::tag::rows_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(nt2::details::rows<T>(start))
                                        , meta::as_<T>()
                                      );
    }
  };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rows_scaled_, tag::cpu_
//                               , (A0)(T)(T1)
//                             , (ast_<A0>)
//                               (scalar_< arithmetic_<T> >)
//                               (scalar_< arithmetic_<T1> > )
//                             )
//   {
//     typedef typename  boost::proto::
//       result_of::make_expr< nt2::tag::rows_
//       , container::domain
//       , box<_2D>
//       , box<nt2::details::rows_scaled<T, T1> >
//       , meta::as_<T>
//       >::type             result_type;

//     BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& start, T1 const& h) const
//     {
//       // Expression must be a row vector
//       BOOST_ASSERT_MSG
//       ( nt2::isrow(a0) && (nt2::ndims(a0) <= 2)
//       , "Error using rows: Size vector must be a 2D row vector."
//       );

//       _2D sizee;
//       std::copy(a0.raw(), a0.raw()+2, &sizee[0]);

//       return boost::proto::make_expr< nt2::tag::rows_scaled_
//                                     , container::domain
//                                     > ( boxify(sizee)
//                                       , boxify(nt2::details::rows_scaled<T, T1>(start, h))
//                                         , meta::as_<T>()
//                                       );
//     }
//   };  
} }

#endif
