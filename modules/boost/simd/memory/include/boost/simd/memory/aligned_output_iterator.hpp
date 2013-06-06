//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_OUTPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/memory/details/output_iterator_base.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd
{
  /*!

  **/
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  aligned_output_iterator
        : details::output_iterator_base<T, C, tag::aligned_store_>
  {
    typedef details::output_iterator_base<T, C, tag::aligned_store_> parent;

    aligned_output_iterator() : parent(0)
    {

    }

    explicit  aligned_output_iterator(T* p) : parent(p)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(p, C*sizeof(T))
      , "The constructor of iterator<T,C> has been called on a pointer "
        "which alignment is not compatible with current SIMD extension."
      );
    }

    using parent::operator=;
  };

  /*!

  **/
  template<class Iterator> BOOST_FORCEINLINE
  aligned_output_iterator<typename std::iterator_traits<Iterator>::value_type>
  aligned_output_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_output_iterator<value_type>(&*p);
  }

  /// @overload
  template<std::size_t C, class Iterator> BOOST_FORCEINLINE
  aligned_output_iterator<typename std::iterator_traits<Iterator>::value_type, C>
  aligned_output_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_output_iterator<value_type, C>(&*p);
  }

  /*!

  **/
  template<class Iterator> BOOST_FORCEINLINE
  aligned_output_iterator<typename std::iterator_traits<Iterator>::value_type>
  aligned_output_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_output_iterator<value_type>(&*(p-1) + 1);
  }

  /// @overload
  template<std::size_t C, class Iterator> BOOST_FORCEINLINE
  aligned_output_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  aligned_output_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return aligned_output_iterator<value_type, C>(&*(p-1) + 1);
  }
} }

#endif
