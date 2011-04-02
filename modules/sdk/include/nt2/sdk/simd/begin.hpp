/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_BEGIN_HPP_INCLUDED
#define NT2_SDK_SIMD_BEGIN_HPP_INCLUDED

#include <nt2/sdk/simd/iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <nt2/sdk/simd/meta/native_cardinal.hpp>

namespace nt2 { namespace simd
{
  namespace result
  {
    ////////////////////////////////////////////////////////////////////////////
    // simd::begin either take a Cardinal or use th enative cardinal of the
    // Range value type
    ////////////////////////////////////////////////////////////////////////////
    struct begin
    {
      template<class Sig> struct result;

      template<class This, class Range, class Cardinal>
      struct result<This(Range,Cardinal)>
      {
        typedef
        simd::iterator< typename boost
                        ::iterator_value<typename Range::const_iterator>::type
                      , Cardinal::value
                      >                             type;
      };

      template<class Range, class Cardinal> inline
      typename result<begin(Range,Cardinal)>::type
      operator()(Range const& rng, Cardinal const&) const
      {
        using nt2::memory::align_on;
        typedef typename Range::const_iterator                it_type;
        typedef typename boost::iterator_value<it_type>::type type;

        typename result<begin(Range,Cardinal)>::type
        that(align_on<Cardinal::value*sizeof(type)>(&(*(boost::begin(rng)))));
        return that;
      }

      template<class This, class Range>
      struct result<This(Range)>
      {
        typedef typename
        boost::iterator_value<typename Range::const_iterator>::type value_type;

        typedef typename
        result<This(Range, meta::native_cardinal<value_type>)>::type type;
      };

      template<class Range> inline
      typename result<begin(Range)>::type
      operator()(Range const& rng) const
      {
        typedef typename
        boost::iterator_value<typename Range::const_iterator>::type value_type;
        return this->operator()(rng,meta::native_cardinal<value_type>());
      }
    };
  }
} }

namespace nt2 { namespace simd
{
  template<std::size_t N, class ContiguousRange>
  typename std::tr1::
  result_of<result::begin(ContiguousRange,boost::mpl::int_<N>)>::type
  begin( ContiguousRange const& rng )
  {
    result::begin callee;
    return callee(rng,boost::mpl::int_<N>());
  }

  template<class ContiguousRange>
  typename std::tr1::result_of<result::begin(ContiguousRange)>::type
  begin( ContiguousRange const& rng )
  {
    result::begin callee;
    return callee(rng);
  }
} }

#endif
