//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_INNER_FOLD_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_INNER_FOLD_STEP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the inner_fold_step function
**/

namespace nt2
{
  /*!
    @brief PreFold over inner dimension

    Folds elements of @c a1 along inner dimension, possibly in parallel, and
    store the result in @c a0.

    @param Out Expression to store result in
    @param In Expression to reduce
    @param Bop Function to apply for binary reduction, first argument is accumulator
    @param Range Pair containing linear offset and number of element to process
  **/
  namespace details
  {
    template<class Out, class In, class Bop, class Range>
	inline Out inner_fold_step(Out & out, In& in, Bop const& bop, Range const & range)
    {
      static const std::size_t N = boost::simd::meta::cardinal_of<Out>::value;
      std::size_t begin = range.first;
      std::size_t size = range.second;

      BOOST_ASSERT_MSG( (size % N) == 0, "Range for inner_fold_step not divisible by N");

      for(std::size_t i = begin; i != begin+size; i+=N)
       out = bop(out, nt2::run(in, i, meta::as_<Out>()));

      return out;
    }
  }

};

#endif
