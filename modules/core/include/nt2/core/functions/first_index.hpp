//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIRST_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIRST_INDEX_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::first_index function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct first_index_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * Return the first valid index of a given expression along a given dimension.
   */
  //============================================================================
  template<std::size_t Dims,class A0>
  typename  boost::dispatch::meta::
            call<tag::first_index_(A0 const&, boost::mpl::size_t<Dims>)>::type
  first_index(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::first_index_, A0>::type callee;
    return callee(a0, boost::mpl::size_t<Dims>() );
  }

  template<class A0, class Dim>
  typename  boost::dispatch::meta::
            call<tag::first_index_(A0 const&, Dim const&)>::type
  first_index(A0 const& a0, Dim const& dim)
  {
    typename boost::dispatch::make_functor<tag::first_index_, A0>::type callee;
    return callee(a0, dim);
  }
}

#endif
