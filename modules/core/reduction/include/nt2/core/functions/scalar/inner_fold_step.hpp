//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INNER_FOLD_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INNER_FOLD_STEP_HPP_INCLUDED

#include <nt2/core/functions/inner_fold_step.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates inner_fold_step
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::inner_fold_step_, tag::cpu_
            , (A0)(A1)(A2)(A3)(A4)
            , (unspecified_<A0>)
              ((ast_<A1, nt2::container::domain>))
              (unspecified_<A2>)
              (unspecified_<A3>)
              (unspecified_<A4>)
              )

{
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const & a4)
    {
      std::size_t begin = a4.first;
      std::size_t size  = a4.second;

      for(std::size_t i = begin; i < begin+size; ++i)
       out = bop(out, nt2::run(in, i, meta::as_<A0>()));
    }
};
} }

#endif

