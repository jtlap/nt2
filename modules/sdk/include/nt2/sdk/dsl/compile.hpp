/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPILE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPILE_HPP_INCLUDED

#include <boost/proto/transform.hpp>
#include <nt2/sdk/dsl/proto/unpack.hpp>

////////////////////////////////////////////////////////////////////////////////
// compile recursively traverse a nt2 AST to perform a given trasnformation
// defined by externally extendable PFO
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Phase,class Target>
  struct compile
      : boost::proto::switch_< compile<Phase,Target> >
  {
    template <typename Tag, typename Dummy = void>
    struct  case_
          : boost::proto::
            otherwise < typename boost::mpl::apply<Phase,Tag,Target>::type >
    {};
  };
} }

namespace boost { namespace proto
{
  template<class Phase,class Target>
  struct  is_callable<nt2::meta::compile<Phase,Target> >
        : boost::mpl::true_  {};
} }

#endif
