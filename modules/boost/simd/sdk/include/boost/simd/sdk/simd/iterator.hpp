/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_ITERATOR_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////////
  // simd::iterator reference a pack of N elements of type T
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  iterator
        : public  boost
                  ::iterator_adaptor< iterator<T,C>
                                    , typename pack<T,C>::data_type const *
                                    , pack<T,C> const
                                    , boost::random_access_traversal_tag
                                    , pack<T,C> const
                                    >
  {
    private:
    struct enabler {};

    typedef pack<T,C> const * pack_type;
    typedef typename pack<T,C>::data_type* native_type;

    public:
    iterator() : iterator::iterator_adaptor_(0) {}

    explicit  iterator(T* p)
            : iterator::iterator_adaptor_(reinterpret_cast<native_type>(p)) {}

    explicit  iterator(T const* p)
            : iterator::iterator_adaptor_(reinterpret_cast<native_type>(p)) {}

    private:
    friend class boost::iterator_core_access;

    typename iterator::reference dereference() const
    {
      return *(reinterpret_cast<pack_type>(this->base()));
    }
  };

  template<class T>
  iterator<T> begin(T* p){ return iterator<T>(p); }

  template<class T,std::size_t C>
  iterator<T,C> begin(T* p){ return iterator<T,C>(p); }

  template<class T>
  iterator<T> end(T* p){ return iterator<T>(p); }

  template<class T,std::size_t C>
  iterator<T,C> end(T* p){ return iterator<T,C>(p); }

} }

#endif
