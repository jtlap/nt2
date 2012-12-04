//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_META_SITE_OF_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_META_SITE_OF_HPP_INCLUDED

#include <boost/dispatch/functor/functor.hpp>

/*!
 * \file
 * \brief Implements a meta-function giving the \c Site type from \ref boost::dispatch::functor type
 */

namespace boost { namespace dispatch
{
  //============================================================================
  /*!
   * \ingroup functors
   * This meta-function gives \c Site from \ref functor type

   * \param \ref functor type
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantic:
   *
   * For any \ref functor :
   * \code
   * typedef site_of<make_functor<Tag, Site>::type>::type type;
   * \endcode
   *
   * is equivalent to
   *
   * \code
   * typedef Site type;
   * \endcode
   */
  //============================================================================
  template <typename T>
  struct site_of;

  template< typename Tag, typename Site>
  struct site_of<functor<Tag, Site > >
  {
    typedef Site type;
  };


} }

#endif
