/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED

#include <nt2/extension/parameters.hpp>

////////////////////////////////////////////////////////////////////////////////
// Define tag for table_ related domain specialization
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  struct table_{};
} }

////////////////////////////////////////////////////////////////////////////////
// Tell proto that in the container::domain, all expressions should be
// wrapped in container::expr<> using container::generator. Moreover, build the
// relationship between domains with respect to the value of the dimension.
// Table of dimension N are living in a domain which is upward-compatible with
// table of dimension N+1, adn thus up to NT2_MAX_DIMENSIONS
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace container
{
  template<int Dim>
  struct  domain<tag::table_, boost::mpl::int_<Dim> >
        : boost::proto::domain< container::generator< tag::table_
                                                    , boost::mpl::int_<Dim>
                                                    >
                              , container::grammar
                              , domain<tag::table_,boost::mpl::int_<Dim+1> >
                              >
  {};

  template<>
  struct  domain<tag::table_, boost::mpl::int_<NT2_MAX_DIMENSIONS> >
        : boost::proto::domain< container::generator< tag::table_
                                                    , boost::mpl::
                                                      int_<NT2_MAX_DIMENSIONS>
                                                    >
                              , container::grammar
                              >
  {};
} }

#endif
