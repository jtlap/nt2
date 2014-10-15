//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TRANS33_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TRANS33_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag trans33_ of functor trans33
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct trans33_ : boost::dispatch::tag::formal_
    {
       typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /**
   * @brief compute in place transpose of statically sized 3x3 matrix
   *
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::trans33_, trans33, (A0&), 1)


}

#endif
