/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_TRACE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GENERAL_TRACE_HPP_INCLUDED
#include <nt2/include/functions/trace.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/constants/zero.hpp>
// #include <nt2/include/functions/sum.hpp>
// #include <nt2/include/functions/diag_of.hpp>

//sum of diagonal elements even if a is not square

namespace nt2{ namespace ext 
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::trace_, tag::cpu_,
                                (A0)
                                ,((ast_<A0>))
                                )
  {
    typedef typename A0::value_type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(ismatrix(a0), "a0 is not a matrix or vector in trace call");
      int n = nt2::min(height(a0), width(a0));
      result_type r = Zero<result_type>(); 
      for(int i=first_index<1>(a0); i < first_index<1>(a0)+n; ++i)
        {
          r+= a0(i, i); 
        }
      //      result_type r = sum(diag_of(a0)); //TODO
      return r; 
    }
  };

} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of trace.hpp<2>
// /////////////////////////////////////////////////////////////////////////////
