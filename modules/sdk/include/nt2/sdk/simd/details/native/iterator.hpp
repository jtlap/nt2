/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_ITERATOR_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_ITERATOR_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>

namespace nt2 { namespace details
{
  template<class Native>
  struct  native_iterator
        : boost::iterator_facade< native_iterator<Native>
                                , typename Native::value_type
                                , boost::random_access_traversal_tag
                                , typename Native::const_reference
                                >
  {
    public:
    native_iterator() : idx(0) {}

    explicit
    native_iterator( Native const& v, std::size_t i ) : data(v), idx(i) {}

    private:
    friend class boost::iterator_core_access;

    void increment() { idx++; }
    void decrement() { idx--; }

    bool equal(native_iterator const& other) const  { return idx == other.idx; }
    typename Native::value_type dereference() const { return data[idx]; }

    Native        data;
    std::size_t   idx;
  };

} }

#endif
