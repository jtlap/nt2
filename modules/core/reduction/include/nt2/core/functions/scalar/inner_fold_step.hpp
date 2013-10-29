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
            , (Out)(In)(Neutral)(Bop)(Range)
            , (unspecified_<Out>)
              ((ast_<In, nt2::container::domain>))
              (unspecified_<Neutral>)
              (unspecified_<Bop>)
              (unspecified_<Range>)
              )

{
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Neutral const& neutral, Bop const& bop, Range const & range)
    {
      std::size_t begin = range.first;
      std::size_t size  = range.second;

      for(std::size_t i = begin; i < begin+size; ++i)
       out = bop(out, nt2::run(in, i, meta::as_<Out>()));
    }
};
} }

#endif

