//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_OUTPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_OUTPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/memory/details/output_iterator_base.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd
{
  /*!

  **/
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  output_iterator
        : details::output_iterator_base<T, C, tag::store_>
  {
    typedef details::output_iterator_base<T, C, tag::store_> parent;

    output_iterator() : parent(0)
    {

    }

    explicit output_iterator(T* p) : parent(p)
    {

    }

    using parent::operator=;
  };

  /*!

  **/
  template<class Iterator> BOOST_FORCEINLINE
  output_iterator<typename std::iterator_traits<Iterator>::value_type>
  output_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return output_iterator<value_type>(&*p);
  }

  template<std::size_t C, class Iterator> BOOST_FORCEINLINE
  output_iterator<typename std::iterator_traits<Iterator>::value_type, C>
  output_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return output_iterator<value_type, C>(&*p);
  }

  /*!

  **/
  template<class Iterator> BOOST_FORCEINLINE
  output_iterator<typename std::iterator_traits<Iterator>::value_type>
  output_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return output_iterator<value_type>(&*(p-1) + 1);
  }

  template<std::size_t C, class Iterator> BOOST_FORCEINLINE
  output_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  output_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    return output_iterator<value_type, C>(&*(p-1) + 1);
  }
} }

#endif
