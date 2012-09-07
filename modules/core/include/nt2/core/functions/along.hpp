//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ALONG_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core along
 *
 * \par Description
 * Applies an index \c ind on \c expr along the \c i-th dimension
 * by default \c i is the first non-singleton dimension of expr
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/along.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *   typename meta::call<tag::along_(A0)>::type
 *   along(A0& expr, A1 const& ind, A2 const& i);
 * }
 * \endcode
 *
 * \param expr the expression to index
 * \param ind the indexer
 * \param i the dimension on which to index
 * 
 * \return expr(_, ..., ind, ..., _) with \c ind at the \c i-th argument
 *  
 *  
**/

namespace nt2
{
  namespace tag
  {
    struct along_ : ext::elementwise_<along_>
    {
      typedef ext::elementwise_<along_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::along_       , along, 2)
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::along_  , along, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::along_       , along, 3)
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::along_  , along, 3)
}
#endif
