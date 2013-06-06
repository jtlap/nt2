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
#ifndef NT2_STATISTICS_FUNCTIONS_KSTEST_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_KSTEST_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_cau kstest
 *
 * \par Description
 * kolmogorov-Smirnov test
 * compute the ks statistic d  and the significance level p from
 * a distribution sample x and the cumulative distribution functor f.
 * small value of p means the data is significantly far from the distribution
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/kstest.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::kstest_(A0)>::type
 *     kstest(const A0 & a0, const A1 & cdf);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag kstest_ of functor kstest
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct kstest_ : tag::formal_ { typedef tag::formal_ parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::kstest_, kstest, 2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::kstest_, kstest, (A0 const&)(A1 const&)(A2&),3)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::kstest_, kstest, (A0 const&)(A1 const&)(A2&)(A2&),3)


}

#endif
