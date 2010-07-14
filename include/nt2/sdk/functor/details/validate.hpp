/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_VALIDATE_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_VALIDATE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// User-overloadable validation meta-function
//* TODO : Documentation:http://nt2.lri.fr/sdk/howto/functor.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/unknown.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // By default, any call is valid
  //////////////////////////////////////////////////////////////////////////////
  template<class Function,class Category,class Info>
  struct validate
  {
    typedef boost::mpl::true_ result_type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Except for unknown type sequence that we want to prohibite
  //////////////////////////////////////////////////////////////////////////////
  template<class Function,class Info>
  struct validate<Function,tag::unknown,Info>
  {
    typedef boost::mpl::false_ result_type;
  };
} }

#endif
