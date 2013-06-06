//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_INPUT_ITERATOR_BASE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_INPUT_ITERATOR_BASE_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost { namespace simd { namespace details
{
  /*!
    @brief Read-only SIMD iterator

    aligned_input_iterator adapt a pointer to an into a standard compliant
    iterator

    @tparam T Type pointed to by the iterator
    @tparam C Width of the SIMD register to use as iteration value
  **/
  template<typename T, std::size_t C, typename Load>
  struct  input_iterator_base
        : boost::iterator_adaptor< input_iterator_base<T, C, Load>
                                 , T const*
                                 , pack<T, C>
                                 , std::random_access_iterator_tag
                                 , pack<T, C> const
                                 >
  {
    /// Default constructor
    input_iterator_base() : input_iterator_base::iterator_adaptor_(0) {}

    /// Constructor from an aligned pointer
    explicit  input_iterator_base(T const* p)
            : input_iterator_base::iterator_adaptor_(p)
    {}

    protected:
    /// INTERNAL ONLY
    friend class boost::iterator_core_access;

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    typename input_iterator_base::reference dereference() const
    {
      dispatch::functor<Load> callee;
      return callee(this->base(), dispatch::meta::as_< pack<T,C> >() );
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE void increment() { this->base_reference() += C; }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE void decrement() { this->base_reference() -= C; }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE
    void advance(typename input_iterator_base::difference_type n)
    {
      this->base_reference() += n*C;
    }

    /// INTERNAL ONLY
    BOOST_FORCEINLINE typename input_iterator_base::difference_type
    distance_to(input_iterator_base const& other) const
    {
      static typename input_iterator_base::difference_type diff_card = C;
      return (other.base() - this->base()) / diff_card;
    }
  };
} } }

#endif
