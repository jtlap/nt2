//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::find function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2
{
  namespace tag
  {
    struct find_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 2)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::find_, tag::cpu_, (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::find_(A0 const&, meta::as_<std::ptrdiff_t>)>::type result_type;

    result_type operator()(A0 const& a0) const
    {
      return find(a0, meta::as_<std::ptrdiff_t>());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::find_, tag::cpu_, (A0)(A1)
                            , (unspecified_<A0>)
                              (target_< scalar_< integer_<A1> > >)
                            )
  {
    typedef typename A0::value_type stype;
    typedef typename A1::type index_type;
    typedef nt2::memory::container<index_type, nt2::_1D> term;
    typedef boost::dispatch::meta::terminal_of_shared<term> result;
    typedef typename result::type result_type;

    result_type operator()(A0 const& a0, A1 const&) const
    {
      result_type ret = result::make();

      std::size_t m = nt2::numel(a0);
      for(std::size_t i=0; i!=m; ++i)
      {
        stype value = nt2::run(a0, i, meta::as_<stype>());
        if(value)
          boost::proto::value(ret).push_back(index_type(i+1));
      }

      return ret;
    }
  };
} }

#endif
