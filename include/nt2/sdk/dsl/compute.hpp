/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPUTE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPUTE_HPP_INCLUDED

#include <nt2/sdk/dsl/compile.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/details/tags.hpp>

////////////////////////////////////////////////////////////////////////////////
// compute evaluates a nt2 AST by passing its elements through a raw functor
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template <class Tag, class Target>
  struct compute
      : boost::proto::
        unpack< boost::proto::
                call< functor<Tag, Target> >(compile< compute < boost::mpl::_1
                                                              , boost::mpl::_2
                                                              >
                                                    , Target
                                                    >
                                            )
              >
  {};

  template<class Target>
  struct  compute<tag::terminal_,Target>
        : boost::proto::
          call< functor < tag::terminal_
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
  template<class Tag, class Target>
  struct  is_callable<nt2::meta::compute<Tag, Target> >
        : boost::mpl::true_  {};
} }

#endif
