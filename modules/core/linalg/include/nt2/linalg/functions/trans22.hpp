//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TRANS22_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TRANS22_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag trans22_ of functor trans22
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct trans22_ : boost::dispatch::tag::formal_
    {
       typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /**
   * @brief compute in place transpose of statically sized 3x3 matrix
   *
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::trans22_, trans22, (A0&), 1)


}

#endif
