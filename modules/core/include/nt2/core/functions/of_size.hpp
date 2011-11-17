#if !BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_OF_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_OF_SIZE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the of_size functions
 */

#include <nt2/core/settings/size.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2
{
  #if defined(DOXYGEN_ONLY)
  //============================================================================
  /*!
   * Builds a nD extent from a list of \c n dimension values.
   *
   * \param d Values to use as dimensions
   *
   * \usage
   *
   * \code
   * #include <iostream>
   * #include <nt2/core/functions/of_size.hpp>
   *
   * int main()
   * {
   *   std::cout << nt2::of_size(3,3,4) << "\n";
   * }
   * \endcode
   */
  //============================================================================
  template<class ...Dims> _nD of_size(Dims const& d...);
  #endif

  _0D inline of_size() { return _0D(); }

  #define   BOOST_PP_FILENAME_1 "nt2/core/functions/of_size.hpp"
  #define   BOOST_PP_ITERATION_LIMITS (1, NT2_MAX_DIMENSIONS)
  #include  BOOST_PP_ITERATE()

  //============================================================================
  /*!
   * Builds a nD extent from a Range of dimensions
   *
   * \param begin Iterator to the start of the Sequence containing the dimension
   * values
   * \param end Iterator to the end of the Sequence containing the dimension
   * values
   *
   * \return an extent of the maximum number of dimensions allowed which value
   * have been set accordingly to the Range values.
   * \usage
   *
   * \code
   * #include <iostream>
   * #include <nt2/core/functions/of_size.hpp>
   *
   * int main()
   * {
   *   int d[3] = { 3,3,4 };
   *   std::cout << nt2::of_size(&d[0], &d[0]+3) << "\n";
   * }
   * \endcode
   */
  //============================================================================
  template<class Iterator> inline
  typename boost::
           disable_if< boost::is_integral<Iterator>
                     , BOOST_PP_CAT(BOOST_PP_CAT(_,NT2_MAX_DIMENSIONS),D)
                     >::type
  of_size(Iterator const& begin, Iterator const& end)
  {
    BOOST_PP_CAT(BOOST_PP_CAT(_,NT2_MAX_DIMENSIONS),D) that(begin,end);
    return that;
  }
}

#endif

#else
#define N BOOST_PP_ITERATION()

  template<BOOST_PP_ENUM_PARAMS(N,class D)> inline
  BOOST_PP_CAT(BOOST_PP_CAT(_,N),D)
  of_size(BOOST_PP_ENUM_BINARY_PARAMS(N,const D, &d))
  {
    BOOST_PP_CAT(BOOST_PP_CAT(_,N),D) that(BOOST_PP_ENUM_PARAMS(N,d));

    return that;
  }

#undef N

#endif
