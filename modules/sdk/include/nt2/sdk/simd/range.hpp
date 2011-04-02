/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_RANGE_HPP_INCLUDED
#define NT2_SDK_SIMD_RANGE_HPP_INCLUDED

#include <nt2/sdk/simd/end.hpp>
#include <nt2/sdk/simd/begin.hpp>
#include <boost/range/iterator_range.hpp>

namespace nt2 { namespace simd
{
  namespace result
  {
    ////////////////////////////////////////////////////////////////////////////
    // simd::range build  a range from simd::begin and simd::end. This range
    // cover the inner parts of the original range in which SIMD operations can
    // be applied.
    ////////////////////////////////////////////////////////////////////////////
    struct range
    {
      template<class Sig> struct result;

      template<class This, class Range, class Cardinal>
      struct result<This(Range,Cardinal)>
      {
        typedef
        boost::iterator_range < simd::iterator< typename boost::
                                                iterator_value< typename Range
                                                                ::const_iterator
                                                            >::type
                                            , Cardinal::value
                                            >
                              >  type;
      };

      template<class Range, class Cardinal> inline
      typename result<range(Range,Cardinal)>::type
      operator()(Range const& rng, Cardinal const&) const
      {
        typename result<range(Range,Cardinal)>::type
        that(simd::begin<Cardinal::value>(rng),simd::end<Cardinal::value>(rng));

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
      typename result<range(Range)>::type
      operator()(Range const& rng) const
      {
        typename result<range(Range)>::type
        that(simd::begin(rng),simd::end(rng));

        return that;
      }
    };
  }
} }

namespace nt2 { namespace simd
{
  template<std::size_t N, class ContiguousRange>
  typename std::tr1::
  result_of<result::range(ContiguousRange,boost::mpl::int_<N>)>::type
  range( ContiguousRange const& rng )
  {
    result::range callee;
    return callee(rng,boost::mpl::int_<N>());
  }

  template<class ContiguousRange>
  typename std::tr1::result_of<result::range(ContiguousRange)>::type
  range( ContiguousRange const& rng )
  {
    result::range callee;
    return callee(rng);
  }
} }

#endif
