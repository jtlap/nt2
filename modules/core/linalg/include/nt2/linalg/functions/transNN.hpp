//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TRANSNN_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TRANSNN_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <boost/simd/constant/constants/zero.hpp>


namespace nt2 {  namespace tag
  {
    /*!
     * \brief Define the tag expm_ of functor expm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct transnn_ : tag::formal_
    {
       typedef tag::formal_ parent;
    };
  }
  /**
   * @brief compute transpose of statically sized small matrices
   *
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::transnn_       , transnn, 3)

    template < class T, int N > transnn(T& a0)
  {
    return transnn(a0,  boost::mpl::long_<N>(),  boost::mpl::long_<N>());
  }

}

#endif
