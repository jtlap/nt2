//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ALONG_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ALONG_INDEX_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core along_index
 *
 * \par Description
 * Computes the linear index \c ind along the \c i-th dimension
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/along_index.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *   typename meta::call<tag::along_index_(A0)>::type
 *   along_index(A0& ind, A1 const& i, A2 const& sz);
 * }
 * \endcode
 *
 * \param ind the indexer
 * \param i the dimension on which to index
 * \param sz the size of the data being indexed
 *
 * \return expr(_, ..., ind, ..., _) with \c ind at the \c i-th argument
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    struct along_index_ : ext::elementwise_<along_index_>
    {
      typedef ext::elementwise_<along_index_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::along_index_       , along_index, 3)
}

#endif
