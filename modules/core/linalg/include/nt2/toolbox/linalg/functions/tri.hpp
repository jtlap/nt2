//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_TRI_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_TRI_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements tri function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines tri function tag
    struct tri_ : boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef boost::dispatch::tag::formal_  parent;
    };
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::tri_, tri
                                  , (A0&)(A1 const&)
                                  , 2
                                  );

  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::tri_, tri
                                  , (A0&)(A1 const&)(A2&)
                                  , 3
                                  );
}

#endif
