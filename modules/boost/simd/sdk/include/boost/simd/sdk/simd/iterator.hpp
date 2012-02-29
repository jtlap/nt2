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
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/error/assert.hpp>

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
                                    , typename pack<T,C>::data_type*
                                    , pack<T,C>
                                    , boost::random_access_traversal_tag
                                    , pack<T,C>
                                    >
  {
    private:
    struct enabler {};

    public:

    typedef pack<T,C> pack_type;
    typedef typename pack<T,C>::data_type native_type;

    input_iterator() : input_iterator::iterator_adaptor_(0) {}

    explicit input_iterator(T* p)
    : input_iterator::iterator_adaptor_(reinterpret_cast<native_type*>(p))
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(p,sizeof(native_type))
      , "The constructor of iterator<T,C> has been called on a pointer"
        "which alignment is not compatible with current SIMD extension."
      );
    }

    private:
    friend class boost::iterator_core_access;

    BOOST_DISPATCH_FORCE_INLINE
    typename input_iterator::reference dereference() const
    {
      pack_type that;
      that = boost::simd::load<pack_type>(reinterpret_cast<T*>(this->base()),0);
      return that;
    }
  };

////////////////////////////////////////////////////////////////////////////////
// simd::input_begin()/simd::input_end() functions wrap scalar begin/end 
// iterators for input_iterator.    
////////////////////////////////////////////////////////////////////////////////
  template<class Iterator>
  input_iterator<typename boost::pointee<Iterator>::type>
  input_begin(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*p);
    return input_iterator<typename boost::pointee<Iterator>::type>(tmp);
  }

  template<class Iterator, std::size_t C>
  input_iterator<typename boost::pointee<Iterator>::type,C>
  input_begin(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*p);
    return input_iterator<typename boost::pointee<Iterator>::type,C>(tmp);
  }

  template<class Iterator>
  input_iterator<typename boost::pointee<Iterator>::type>
  input_end(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*(p-1));
    return input_iterator<typename boost::pointee<Iterator>::type>(tmp+1);
  }

  template<class Iterator, std::size_t C>
  input_iterator<typename boost::pointee<Iterator>::type,C>
  input_end(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*(p-1));
    return input_iterator<typename boost::pointee<Iterator>::type,C>(tmp+1);
  }

////////////////////////////////////////////////////////////////////////////////
// The class proxy is returned by output_iterator for handling proper memory
// writing without loss of performance.
////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value>
  struct proxy
  {
  public:

    typedef pack<T,C>                      pack_type;
    typedef typename pack<T,C>::data_type  native_type;

    proxy(T* p) : mem(p) {}
    proxy(proxy const& px){ mem = px.mem; }

    BOOST_DISPATCH_FORCE_INLINE
    void operator=(pack_type const& right)
    {
      boost::simd::store(right, mem, 0);
    }

    template<class Expr>
    BOOST_DISPATCH_FORCE_INLINE
    void operator=(Expr const& right)
    {
      boost::simd::store(right, mem, 0);
    }

  private:
    T* mem;
  };

////////////////////////////////////////////////////////////////////////////////
// simd::output_iterator reference a pack of N elements of type T that can only 
// be write.
////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  output_iterator
    : public  boost
              ::iterator_adaptor< output_iterator<T,C>
                                , typename pack<T,C>::data_type*
                                , pack<T,C>
                                , boost::random_access_traversal_tag
                                , proxy<T,C>
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
        ( boost::simd::memory::is_aligned(p,sizeof(native_type))
        , "The constructor of iterator<T,C> has been called on a pointer"
          "which alignment is not compatible with current SIMD extension."
        );
    }

  private:
    friend class boost::iterator_core_access;

    BOOST_DISPATCH_FORCE_INLINE
    typename output_iterator::reference dereference() const
    {
      return proxy<T,C>(reinterpret_cast<T*>(this->base()));
    }
  };

////////////////////////////////////////////////////////////////////////////////
// simd::output_begin()/simd::output_end() functions wrap scalar begin/end 
// iterators for output_iterator.    
////////////////////////////////////////////////////////////////////////////////
  template<class Iterator>
  output_iterator<typename boost::pointee<Iterator>::type>
  output_begin(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*p);
    return output_iterator<typename boost::pointee<Iterator>::type>(tmp);
  }
  
  template<class Iterator, std::size_t C>
  output_iterator<typename boost::pointee<Iterator>::type,C>
  output_begin(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*p);
    return output_iterator<typename boost::pointee<Iterator>::type,C>(tmp);
  }
  
  template<class Iterator>
  output_iterator<typename boost::pointee<Iterator>::type>
  output_end(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*(p-1));
    return output_iterator<typename boost::pointee<Iterator>::type>(tmp+1);
  }
  
  template<class Iterator, std::size_t C>
  output_iterator<typename boost::pointee<Iterator>::type,C>
  output_end(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*(p-1));
    return output_iterator<typename boost::pointee<Iterator>::type,C>(tmp+1);
  }
  
} }

#endif
