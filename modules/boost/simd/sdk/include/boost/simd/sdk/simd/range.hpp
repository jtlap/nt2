/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_RANGE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_RANGE_HPP_INCLUDED

#include <boost/simd/sdk/simd/iterator.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace simd
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

      template<class This, class Type, class Cardinal>
      struct result<This(Type,Cardinal)>
      {
        typedef boost::
        iterator_range <simd::
                        input_iterator<typename boost::
                                       remove_reference<Type>::type::value_type
                                      ,boost::
                                       remove_reference<Cardinal>::type::value
                                      >
                       >  type;
      };

      template<class This, class Type>
      struct result<This(Type)>
      {
        typedef typename boost::mpl::
                if_< dispatch::meta::
                     is_iterator<typename boost::remove_reference<Type>::type>
                   , typename boost::remove_reference<Type>::type::value_type
                   , typename boost::
                     iterator_value<typename boost::
                                    remove_reference<Type>::type::const_iterator
                                   >::type
                   >::type value_type;

        typedef typename
        result<This(Type, meta::cardinal_of< pack<value_type> >)>::type type;
      };

      template<class Range, class Cardinal> inline
      typename result<range(Range,Cardinal)>::type
      operator()(Range const& rng, Cardinal const&) const
      {
        return boost::make_iterator_range( simd::input_begin(boost::begin(rng))
                                         , simd::input_end(boost::end(rng))
                                         );
      }

      template<class Range> inline
      typename result<range(Range)>::type
      operator()(Range const& rng) const
      {
        return boost::make_iterator_range( simd::input_begin(boost::begin(rng))
                                         , simd::input_end(boost::end(rng))
                                         );
      }

      template<class ForwardIterator, class Cardinal> inline
      typename result<range(ForwardIterator,Cardinal)>::type
      operator()( ForwardIterator const& begin, ForwardIterator const& end
                , Cardinal const&) const
      {
        return boost::make_iterator_range( simd::input_begin(begin)
                                         , simd::input_end(end)
                                         );
      }

      template<class ForwardIterator> inline
      typename result<range(ForwardIterator)>::type
      operator()(ForwardIterator const& begin, ForwardIterator const& end) const
      {
        return boost::make_iterator_range( simd::input_begin(begin)
                                         , simd::input_end(end)
                                         );
      }
    };
  }

  template<std::size_t N, class ContiguousRange>
  typename dispatch::meta::
  result_of<result::range(ContiguousRange,boost::mpl::int_<N>)>::type
  range( ContiguousRange const& rng )
  {
    result::range callee;
    return callee(rng,boost::mpl::size_t<N>());
  }

  template<class ContiguousRange>
  typename dispatch::meta::result_of<result::range(ContiguousRange)>::type
  range( ContiguousRange const& rng )
  {
    result::range callee;
    return callee(rng);
  }

  template<std::size_t N, class ForwardIterator>
  typename dispatch::meta::
  result_of<result::range(ForwardIterator,boost::mpl::int_<N>)>::type
  range( ForwardIterator const& begin, ForwardIterator const& end )
  {
    result::range callee;
    return callee(begin,end,boost::mpl::size_t<N>());
  }

  template<class ForwardIterator>
  typename dispatch::meta::result_of<result::range(ForwardIterator)>::type
  range( ForwardIterator const& begin, ForwardIterator const& end )
  {
    result::range callee;
    return callee(begin,end);
  }

} }

#endif
