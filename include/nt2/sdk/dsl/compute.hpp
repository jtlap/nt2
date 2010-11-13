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

#include <boost/proto/proto.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/dsl/proto/transform/unpack.hpp>

////////////////////////////////////////////////////////////////////////////////
// compile take any NT2 AST and evaluate them based on actions defined in compute
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace dsl
{
    template <typename Locality> struct compile;

    template <typename Tag, typename Locality>
    struct functor_dispatch
        : boost::proto::
          unpack<
            boost::proto::call<
                functors::functor<Tag, Locality>
            >(compile<Locality>)
          >
    {};

    template <typename Locality, typename Tag, typename Dummy = void>
    struct compute
        : functor_dispatch<Tag, Locality> 
    {};

    template<typename Locality>
    struct compute<Locality, functors::terminal_>
        : boost::proto::
          call<
            functors::functor<functors::terminal_,Locality>(
                boost::proto::_value
              , boost::proto::_state
              , boost::proto::_data
            )
        >
    {};

    template <class Locality>
    struct compile
        : boost::proto::switch_<compile<Locality> >
    {
        template <typename Tag, typename Dummy = void>
        struct case_
            : boost::proto::otherwise<compute<Locality, Tag, Dummy> >
        {};
    };

} }

namespace boost { namespace proto
{
  template<class Locality>
  struct is_callable<nt2::dsl::compile<Locality> > : boost::mpl::true_  {};
  template<typename Tag, typename Locality>
  struct is_callable<nt2::dsl::compute<Tag, Locality> > : boost::mpl::true_  {};
} }

#endif
