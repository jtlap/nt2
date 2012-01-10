/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_GLOBAL_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_GLOBAL_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Implementation of the no_padding strategy for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/meta/fusion.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <nt2/sdk/memory/details/no_padding.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class Origin>
  struct hierarchy_of< nt2::memory::global_padding, Origin>
  {
    typedef nt2::ext::padding_<nt2::memory::global_padding>  type;
  };
} } }

////////////////////////////////////////////////////////////////////////////////
// slice implementation for global_padding strategy
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class A0, class A2, class Dummy>
  struct implement< tag::slice_
                    ( fusion_sequence_<A0>, padding_<memory::global_padding>
                    , mpl_integral_<scalar_<integer_<A2> > >
                    )
                  , tag::cpu_, Dummy
                  >
  {
    ////////////////////////////////////////////////////////////////////////////
    // Computes the actual result type depending on A0 size and A2 value
    ////////////////////////////////////////////////////////////////////////////
    static  A0 const& s;
    typedef A2        arg2;

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( true_case
    , boost::simd::memory::align_on( slice<1>(s,memory::no_padding()), 0UL )
    );

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( false_case , slice<arg2::value>(s,memory::no_padding()) );

    typedef typename boost::mpl::eval_if_c< (arg2::value == 1)
                                          , true_case
                                          , false_case
                                          >::type             result_type;

    inline result_type
    operator()(A0 const& a0, memory::global_padding const& p, A2 const& ) const
    {
      return eval(a0, p.value(), boost::mpl::bool_<A2::value==1>() );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when size<A0> == A2
    ////////////////////////////////////////////////////////////////////////////
    inline result_type 
    eval(A0 const& a0, std::size_t p,boost::mpl::true_ const&) const
    {
      return boost::simd::memory::align_on(slice<1>(a0,memory::no_padding()),p);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when size<A0> != A2
    ////////////////////////////////////////////////////////////////////////////
    inline result_type 
    eval(A0 const& a0,std::size_t ,boost::mpl::false_ const&) const
    {
      return slice<A2::value>(a0,memory::no_padding());
    }
  };
} }

#endif
