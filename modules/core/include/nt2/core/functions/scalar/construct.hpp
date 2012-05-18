//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_CONSTRUCT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_CONSTRUCT_HPP_INCLUDED

#include <nt2/core/functions/construct.hpp>
#include <nt2/include/functions/scalar/multiplies.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/dispatch/meta/fusion.hpp>
#include <boost/fusion/include/fold.hpp>

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::iterator_;

  //============================================================================
  // Construct a terminal from a size and a Iterator pair
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_< unspecified_<A0> >)
                              (fusion_sequence_<A1>)
                              (iterator_< scalar_< arithmetic_<A2> > >)
                              (iterator_< scalar_< arithmetic_<A3> > >)                              
                            )
  {
    typedef void result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()(A0& a0, A1 const& a1, A2 const& a2, A3 const&) const
    {
      //========================================================================
      // Check we don't copy more than expected
      //========================================================================
      BOOST_ASSERT_MSG
      ( boost::fusion::fold ( a1
                            , boost::mpl::size_t<1>()
                            , functor<tag::multiplies_>()
                            )
        == 1
      , "Source range is not of size 1."
      );
      
      a0 = *a2;
    }
  };
} }

#endif
