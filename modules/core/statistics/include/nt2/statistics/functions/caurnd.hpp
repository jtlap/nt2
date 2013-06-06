//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_STATISTICS_FUNCTIONS_CAURND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CAURND_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau caurnd
 *
 * \par Description
 * cauchy pseudo random numbers generator : inverse cumulative method using rand
 * All rnd (cumulative distribution functions  can be called with the syntax
 * r = xxxrnd(param_1, ...,  param_n,  sizing_params)
 * the type of params elements determines the type of the output expression elements.
 * cauchy has 2 parameters: median and scale
 * parameters elements have no defaults
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/caurnd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::caurnd_(A0)>::type
 *     caurnd(const A0 & m, const A1 & l, ... dimensions);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag caurnd_ of functor caurnd
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct caurnd_ : boost::dispatch::tag::formal_ { typedef boost::dispatch::tag::formal_ parent; };
  }

 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 2)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 3)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 4)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 5)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 6)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::caurnd_, caurnd, 7)
}



#endif
