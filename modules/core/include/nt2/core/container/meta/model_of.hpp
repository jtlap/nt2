//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_MODEL_OF_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_MODEL_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the model_of meta-function
 */

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * model_of generates a meta-function
   *
   * \tparam T Buffer type to introspect
   */
  //============================================================================
  template<typename T> struct model_of
  {
    typedef
    struct make
    {
      template<typename X> struct apply { typedef X type; };
    }   type;
  };
} }

#endif
