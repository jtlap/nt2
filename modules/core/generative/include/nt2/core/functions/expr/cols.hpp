//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_COLS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_COLS_HPP_INCLUDED

#include <nt2/core/functions/cols.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/memory/copy.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates cols from expression (support size(a) + type calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cols_, tag::cpu_
                            , (A0)(T)
                            , (ast_<A0>)
                              (scalar_< arithmetic_<T> >)
                            )
  {
    typedef meta::constant_<nt2::tag::cols_,T> constant_t;
    typedef typename  boost::proto::result_of
                    ::make_expr < nt2::tag::cols_
                                , container::domain
                                , box<_2D>
                                , box<constant_t>
                                , meta::as_<T>
                                >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& start) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0) && (nt2::ndims(a0) <= 2)
      , "Error using cols: Size vector must be a 2D row vector."
      );

      _2D sizee;
      nt2::memory::cast_copy(a0.raw(), a0.raw()+2, &sizee[0]);

      return boost::proto::make_expr< nt2::tag::cols_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(constant_t(start))
                                      , meta::as_<T>()
                                      );
    }
  };
} }

#endif
