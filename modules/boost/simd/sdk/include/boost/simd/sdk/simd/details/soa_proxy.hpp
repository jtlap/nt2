//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_SOA_PROXY_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_SOA_PROXY_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>

namespace boost { namespace simd { namespace tag
{
  struct insert_;
  struct extract_;
} } }

namespace boost { namespace simd { namespace details
{
  template<class T, class X>
  struct soa_proxy
  {
    soa_proxy(native<T, X>& data_, std::size_t index_) : data(data_), index(index_)
    {
    }

    soa_proxy const& operator=(T const& other) const
    {
      typename dispatch::make_functor<tag::insert_, T>::type()(other, data, index);
      return *this;
    }

    operator T() const
    {
      return typename dispatch::make_functor<tag::extract_, T>::type()(data, index);
    }

    T const operator()() const
    {
      return static_cast<T const&>(*this);
    }

    native<T, X>& data;
    std::size_t index;

    friend bool operator!(soa_proxy const& a0) { return !a0(); }
    friend bool operator==(soa_proxy const& a0, soa_proxy const& a1) { return a0() == a1(); }
    template<class U> friend bool operator==(U const& a0, soa_proxy const& a1) { return a0 == a1(); }
    template<class U> friend bool operator==(soa_proxy const& a0, U const& a1) { return a0() == a1; }
    friend bool operator!=(soa_proxy const& a0, soa_proxy const& a1) { return a0() != a1(); }
    template<class U> friend bool operator!=(U const& a0, soa_proxy const& a1) { return a0 != a1(); }
    template<class U> friend bool operator!=(soa_proxy const& a0, U const& a1) { return a0() != a1; }
    friend std::ostream& operator<<(std::ostream& a0, soa_proxy const& a1) { return a0 << a1(); }
  };

  template<class T>
  struct soa_iterator_base
  {
    soa_iterator_base(T& data_, std::size_t index_ = 0) : data(data_), index(index_) {}

  protected:
    friend class iterator_core_access;

    void increment()
    {
      ++index;
    }

    void advance(std::size_t n)
    {
      index += n;
    }

    void decrement()
    {
      --index;
    }

    std::ptrdiff_t distance_to(soa_iterator_base const& other) const
    {
      return other.index - index;
    }

    bool equal(soa_iterator_base const& other) const
    {
      return index == other.index;
    }

    T& data;
    std::size_t index;
  };

  template<class T, class X>
  struct soa_iterator
    : soa_iterator_base< native<T, X> >
    , iterator_facade<soa_iterator<T, X>, T, std::random_access_iterator_tag, soa_proxy<T, X> >
  {
    soa_iterator(native<T, X>& data_, std::size_t index_ = 0) : soa_iterator_base< native<T, X> >(data_, index_) {}

  private:
    friend class iterator_core_access;

    soa_proxy<T, X> dereference() const
    {
      return soa_proxy<T, X>(this->data, this->index);
    }
  };

  template<class T, class X>
  struct soa_const_iterator
    : soa_iterator_base< native<T, X> const >
    , iterator_facade< soa_const_iterator<T, X>, T
                     , std::random_access_iterator_tag, T const
                     >
  {
    soa_const_iterator(native<T, X> const& data_, std::size_t index_ = 0)
     : soa_iterator_base< native<T, X> const >(data_, index_) {}

  private:
    friend class iterator_core_access;

    T const dereference() const
    {
      return typename dispatch::make_functor<tag::extract_, T>::type()(this->data, this->index);
    }
  };
} } }

#endif
