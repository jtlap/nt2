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
#ifndef NT2_TOOLBOX_SIGNAL_FUNCTIONS_POW2DB_HPP_INCLUDED
#define NT2_TOOLBOX_SIGNAL_FUNCTIONS_POW2DB_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup signal
 * \defgroupsignal_pow2db pow2db
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag pow2db_ of functor pow2db
     *        in namespace nt2::tag for toolbox signal
    **/
    struct pow2db_ : ext::elementwise_<pow2db_> { typedef ext::elementwise_<pow2db_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2db_, pow2db, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2db_, pow2db, 2)
}



#endif
