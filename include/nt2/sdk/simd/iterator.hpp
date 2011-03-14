/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_ITERATOR_HPP_INCLUDED
#define NT2_SDK_SIMD_ITERATOR_HPP_INCLUDED

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////////
  // simd::iterator reference a pack of N elements of type T
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::native_cardinal<T>::value >
  struct  iterator
        : public  boost
                  ::iterator_adaptor< iterator<T,C>
                                    , typename pack<T,C>::data_type::parent const*
                                    , pack<T,C> const
                                    , boost::random_access_traversal_tag
                                    , pack<T,C> const
                                    >
  {
    private:
    struct enabler {};

    typedef typename pack<T,C>::data_type::parent const* native_type;
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
      pack<T,C> that(reinterpret_cast<T const*>(this->base()),0);
      return that;
    }
  };
} }

#endif
