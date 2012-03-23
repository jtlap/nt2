//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INNER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/inner_fold.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_fold_, tag::cpu_, (A0)(S0)(A1)(A2)(A3)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (ast_< A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                            )
  {
    typedef void  result_type;
    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1, A2 const& a2, A3 const& a3 ) const
    {


    }
  };

} }

#endif
