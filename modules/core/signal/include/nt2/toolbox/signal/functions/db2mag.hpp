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
#ifndef NT2_TOOLBOX_SIGNAL_FUNCTIONS_DB2MAG_HPP_INCLUDED
#define NT2_TOOLBOX_SIGNAL_FUNCTIONS_DB2MAG_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Define the tag db2mag_ of functor db2mag
     *        in namespace nt2::tag for toolbox signal
    **/
    struct db2mag_ : ext::elementwise_<db2mag_>
    {
      typedef ext::elementwise_<db2mag_> parent;
    };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::db2mag_, db2mag, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::db2mag_, db2mag, 2)
}

#endif
