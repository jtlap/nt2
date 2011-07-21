/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_COMPUTE_HPP_INCLUDED
#define BOOST_SIMD_SDK_DSL_COMPUTE_HPP_INCLUDED

#include <boost/simd/sdk/dsl/compile.hpp>
#include <boost/dispatch/functor/functor.hpp>

////////////////////////////////////////////////////////////////////////////////
// compute evaluates a nt2 AST by passing its elements through a raw functor
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd {  namespace meta
{
  template <class Tag, class Target>
  struct compute
      : boost::proto::
        unpack< boost::proto::
                call< functor<Tag, Target> >(compile< compute < boost::mpl::_1
                                                              , Target
                                                              >
                                                    >
                                            )
              >
  {};

  template<class Target>
  struct  compute<tag::terminal_,Target>
        : boost::proto::
          call< functor < boost::proto::tag::terminal
                        , Target
                        > ( boost::proto::_value
                          , boost::proto::_state
                          , boost::proto::_data
                          )
              >
  {};
} } }

namespace boost { namespace proto
{
  template<class Tag, class Target>
  struct  is_callable<boost::simd::meta::compute<Tag, Target> >
        : boost::mpl::true_  {};
} }

#endif
