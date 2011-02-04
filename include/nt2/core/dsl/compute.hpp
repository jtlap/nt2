/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_DSL_COMPUTE_HPP_INCLUDED
#define NT2_CORE_DSL_COMPUTE_HPP_INCLUDED

#include <nt2/sdk/dsl/compile.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/details/tags.hpp>

////////////////////////////////////////////////////////////////////////////////
// compute evaluates a nt2 AST numerically
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  template<class Tag> struct compute_ {};
} }

namespace nt2 { namespace meta
{
  template <class Target, class Tag>
  struct compute
      : boost::proto::
        unpack< boost::proto::
                call< functor < tag::compute_<Tag>
                              , Target
                              >
                    >(compile<compute,Target>)
              >
  {};

  template<class Target>
  struct  compute<Target, tag::terminal_>
        : boost::proto::
          call< functor < tag::compute_<tag::terminal_>
                        , Target
                        > ( boost::proto::_value
                          , boost::proto::_state
                          , boost::proto::_data
                          )
              >
  {};
} }

namespace boost { namespace proto
{
  template<class Target,class Tag>
  struct  is_callable<nt2::meta::compute<Target, Tag> >
        : boost::mpl::true_  {};
} }

#endif
