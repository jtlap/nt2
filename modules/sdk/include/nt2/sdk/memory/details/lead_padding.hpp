/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_LEAD_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_LEAD_PADDING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Implementation of the no_padding strategy for memory allocation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/fusion.hpp>
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class Origin>
  struct hierarchy_of< nt2::memory::lead_padding, Origin>
  {
    typedef nt2::ext::padding_<nt2::memory::lead_padding>  type;
  };
} } }

namespace nt2 { namespace ext
{
  template<class A0, class A2, class Dummy>
  struct implement< tag::slice_
                    ( fusion_sequence_<A0>, padding_<memory::lead_padding>
                    , mpl_integral_<scalar_<integer_<A2> > >
                    )
                  , tag::cpu_, Dummy
                  >
  {
    ////////////////////////////////////////////////////////////////////////////
    // Computes the actual result type depending on A0 size and A2 value
    ////////////////////////////////////////////////////////////////////////////
    typedef A2        arg0;
    typedef A2        arg2;
    typedef boost::fusion::result_of::size<arg0>  size_;
    static  A0 const& s;

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( true_case
    ,   slice<2>(s,memory::no_padding())
      * boost::simd::memory::align_on( boost::fusion::at_c<0>(s), 0UL )
    );

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( false_case, slice<arg2::value>(s,memory::no_padding())
    );

    typedef typename boost::mpl::eval_if_c< (arg2::value == 1)
                                          , true_case
                                          , false_case
                                          >::type             result_type;

    inline result_type
    operator()( A0 const& a0, memory::lead_padding const& p, A2 const& ) const
    {
      return eval(a0, p.value(), boost::mpl::bool_<(A2::value==1)>() );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 == 1
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval( A0 const& a0, std::size_t p, boost::mpl::true_ const& ) const
    {
      return   slice<2>(a0,memory::no_padding())
             * boost::simd::memory::align_on( boost::fusion::at_c<0>(a0), p );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 >= 1
    ////////////////////////////////////////////////////////////////////////////
    inline result_type eval( A0 const& a0, std::size_t,boost::mpl::false_ const& ) const
    {
      return slice<A2::value>(a0,memory::no_padding());
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // stride Functor implementation - Do nothing except on inner dimension
  //////////////////////////////////////////////////////////////////////////////
  template<class A0, class A2, class Dummy>
  struct implement< tag::stride_
                    ( fusion_sequence_<A0>, padding_<memory::lead_padding>
                    , mpl_integral_< scalar_< integer_<A2> > >
                    )
                  , tag::cpu_, Dummy
                  >

  {
    ////////////////////////////////////////////////////////////////////////////
    // Computes the actual result type depending on A0 size and A2 value
    ////////////////////////////////////////////////////////////////////////////
    typedef A2        arg0;
    typedef A2        arg2;
    static  A0 const& s;

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( true_case
    , boost::simd::memory::align_on( boost::fusion::at_c<0>(s), 0UL )
    );

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    ( false_case, boost::fusion::at_c<arg2::value-1>(s) );

    typedef typename boost::mpl::eval_if_c< (arg2::value == 1)
                                          , true_case
                                          , false_case
                                          >::type               result_type;

    inline result_type
    operator()( A0 const& a0, memory::lead_padding const& p, A2 const& ) const
    {
      return eval(a0, p.value(), boost::mpl::bool_<(A2::value==1)>() );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 == 1
    ////////////////////////////////////////////////////////////////////////////
    inline result_type 
    eval(A0 const& a0, std::size_t p, boost::mpl::true_ const&) const
    {
      return boost::simd::memory::align_on( boost::fusion::at_c<0>(a0), p );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Implementation when A2 >= 1
    ////////////////////////////////////////////////////////////////////////////
    inline result_type 
    eval(A0 const& a0, std::size_t, boost::mpl::false_ const&) const
    {
      return boost::fusion::at_c<A2::value-1>(a0);
    }
  };
} }

#endif
