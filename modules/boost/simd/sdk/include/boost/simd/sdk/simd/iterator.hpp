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
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>
#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd
{
////////////////////////////////////////////////////////////////////////////////
// simd::input_iterator reference a pack of N elements of type T that can only
// be read.
////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  input_iterator
        : public  boost
                  ::iterator_adaptor< input_iterator<T,C>
                                    , typename pack< typename dispatch::meta::
                                                     strip<T>::type
                                                   , C
                                                   >::data_type const*
                                    , pack< typename dispatch::meta::
                                            strip<T>::type
                                          , C
                                          >
                                    , boost::random_access_traversal_tag
                                    , pack< typename dispatch::meta::
                                            strip<T>::type
                                          , C
                                          >
                                    >
  {
    private:
    struct enabler {};

    public:
    typedef typename dispatch::meta::strip<T>::type   strip_t;
    typedef pack<strip_t,C>                         pack_type;
    typedef typename pack<strip_t,C>::data_type   native_type;
    typedef native_type*                             iterator;
    typedef native_type const*                 const_iterator;

    input_iterator() : input_iterator::iterator_adaptor_(0) {}

    explicit input_iterator(const strip_t* p)
    : input_iterator::
      iterator_adaptor_(reinterpret_cast<const_iterator>(p))
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(p,sizeof(native_type))
      , "The constructor of iterator<T,C> has been called on a pointer"
        "which alignment is not compatible with current SIMD extension."
      );
    }

    template<class U, std::size_t V>
    input_iterator( input_iterator<U,V> const& other
                  , typename
                    boost::enable_if< boost::mpl::and_< boost::is_same<T,U>
                                                      , boost::mpl::bool_<C==V>
                                                      >
                                    , enabler
                                    >::type = enabler()
                  ) : input_iterator::iterator_adaptor_(other.base()) {}

    private:
    friend class boost::iterator_core_access;

    BOOST_DISPATCH_FORCE_INLINE
    typename input_iterator::reference dereference() const
    {
      pack_type that;
      that = boost::simd::
             load<pack_type>(reinterpret_cast<const_iterator>(this->base()),0);
      return that;
    }
  };

////////////////////////////////////////////////////////////////////////////////
// simd::input_begin()/simd::input_end() functions wrap scalar begin/end
// iterators for input_iterator.
////////////////////////////////////////////////////////////////////////////////
  template<class Iterator>
  input_iterator<typename std::iterator_traits<Iterator>::value_type>
  input_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type const* tmp = &(*p);
    return input_iterator<value_type>(tmp);
  }

  template<class Iterator, std::size_t C>
  input_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  input_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type const* tmp = &(*p);
    return input_iterator<value_type,C>(tmp);
  }

  template<class Iterator>
  input_iterator<typename std::iterator_traits<Iterator>::value_type>
  input_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type const* tmp = &(*(p-1));
    return input_iterator<value_type>(tmp+1);
  }

  template<class Iterator, std::size_t C>
  input_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  input_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type const* tmp = &(*(p-1));
    return input_iterator<value_type,C>(tmp+1);
  }

////////////////////////////////////////////////////////////////////////////////
// simd::output_iterator reference a pack of N elements of type T that can only
// be write.
////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  output_iterator
    : public  boost
              ::iterator_adaptor< output_iterator<T,C>
                                , typename pack< typename dispatch::meta::
                                                 strip<T>::type
                                                 , C
                                                 >::data_type*
                                , pack< typename dispatch::meta::
                                        strip<T>::type
                                      , C
                                      >
                                , boost::random_access_traversal_tag
                                , output_iterator<T,C>
                                >
  {
  private:
    struct enabler {};

  public:

    typedef pack<T,C> pack_type;
    typedef typename pack<T,C>::data_type native_;
    typedef typename native_::native_type native_type;

    output_iterator() : output_iterator::iterator_adaptor_(0) {}

    explicit output_iterator(T* p)
      : output_iterator::iterator_adaptor_(reinterpret_cast<native_*>(p))
    {
      BOOST_ASSERT_MSG
        ( boost::simd::is_aligned(p,sizeof(native_type))
        , "The constructor of iterator<T,C> has been called on a pointer"
          "which alignment is not compatible with current SIMD extension."
        );
    }

    template<class U, std::size_t V>
    output_iterator( output_iterator<U,V> const& other
                   , typename
                     boost::enable_if< boost::mpl::and_< boost::is_same<T,U>
                                                       , boost::mpl::bool_<C==V>
                                                       >
                                    , enabler
                                    >::type = enabler()
                   ) : output_iterator::iterator_adaptor_(other.base()) {}

    BOOST_DISPATCH_FORCE_INLINE
    void operator=(pack_type const& right)
    {
      boost::simd::store(right, reinterpret_cast<T*>(this->base()), 0);
    }

    template<class Expr>
    BOOST_DISPATCH_FORCE_INLINE
    void operator=(Expr const& right)
    {
      boost::simd::store(right, reinterpret_cast<T*>(this->base()), 0);
    }

  private:
    friend class boost::iterator_core_access;

    BOOST_DISPATCH_FORCE_INLINE
    typename output_iterator::reference dereference() const
    {
      return *this;
    }
  };

////////////////////////////////////////////////////////////////////////////////
// simd::output_begin()/simd::output_end() functions wrap scalar begin/end
// iterators for output_iterator.
////////////////////////////////////////////////////////////////////////////////
  template<class Iterator>
  output_iterator<typename std::iterator_traits<Iterator>::value_type>
  output_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type* tmp = &(*p);
    return output_iterator<value_type>(tmp);
  }

  template<class Iterator, std::size_t C>
  output_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  output_begin(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type* tmp = &(*p);
    return output_iterator<value_type,C>(tmp);
  }

  template<class Iterator>
  output_iterator<typename std::iterator_traits<Iterator>::value_type>
  output_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type* tmp = &(*(p-1));
    return output_iterator<value_type>(tmp+1);
  }

  template<class Iterator, std::size_t C>
  output_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  output_end(Iterator p)
  {
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    value_type* tmp = &(*(p-1));
    return output_iterator<value_type,C>(tmp+1);
  }

} }

#endif
