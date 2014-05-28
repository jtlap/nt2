//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_INNER_SCAN_STEP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_INNER_SCAN_STEP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the inner_scan_step function
**/

namespace nt2
{
  /*!
    @brief PreScan over inner dimension

    Folds elements of @c a2 along inner dimension, possibly in parallel, and
    conditionnaly store the result in @c a1.

    @param Summary Value containing the updated summary
    @param Out Expression to store result in
    @param In Expression to reduce
    @param Bop Function to apply for binary reduction, first argument is accumulator
    @param Range Pair containing linear offset and number of element to process
  **/
  namespace details
  {
    template<class Summary, class Out, class In, class Bop,class Range>
    inline Result inner_scan_step(Summary& summary, Out& out, In& in, Bop const& bop, Range const & range, bool prescan)
    {
      std::size_t begin = range.first;
      std::size_t size = range.second;

      for(std::size_t i = begin; i != begin+size; i++)
      {
       summary = bop(summary, nt2::run(in, i, meta::as_<Out>()));
       if(!prescan) nt2::run(out, i, summary);
      }
    }
  }

};

#endif
