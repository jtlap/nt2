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
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////////
  // simd::input_iterator reference a pack of N elements of type T that can only
  // be read.
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  input_iterator
        : boost::
          iterator_adaptor< input_iterator<T, C>
                          , T const*
                          , pack<T, C>
                          , std::random_access_iterator_tag
                          , pack<T, C> const
                          >
  {
  private:
    typedef pack<T,C>                               pack_type;


  public:
    input_iterator() : input_iterator::iterator_adaptor_(0) {}

    explicit input_iterator(T const* p)
    : input_iterator::
      iterator_adaptor_(p)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(p, C*sizeof(T))
      , "The constructor of iterator<T,C> has been called on a pointer "
        "which alignment is not compatible with the current SIMD extension."
      );
    }

  private:
    friend class boost::iterator_core_access;

    BOOST_FORCEINLINE
    typename input_iterator::reference dereference() const
    {
      return boost::simd::load<pack_type>(this->base());
    }

    BOOST_FORCEINLINE void increment()
    {
      this->base_reference() += C;
    }

    BOOST_FORCEINLINE void decrement()
    {
      this->base_reference() -= C;
    }

    BOOST_FORCEINLINE void advance(typename input_iterator::difference_type n)
    {
      this->base_reference() += n*C;
    }

    BOOST_FORCEINLINE
    typename input_iterator::difference_type distance_to(input_iterator const& other) const
    {
      return (other.base() - this->base()) / typename input_iterator::difference_type(C);
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
    return input_iterator<typename std::iterator_traits<Iterator>::value_type>(&*p);
  }

  template<std::size_t C, class Iterator>
  input_iterator<typename std::iterator_traits<Iterator>::value_type, C>
  input_begin(Iterator p)
  {
    return input_iterator<typename std::iterator_traits<Iterator>::value_type, C>(&*p);
  }

  template<class Iterator>
  input_iterator<typename std::iterator_traits<Iterator>::value_type>
  input_end(Iterator p)
  {
    return input_iterator<typename std::iterator_traits<Iterator>::value_type>(&*(p-1) + 1);
  }

  template<std::size_t C, class Iterator>
  input_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  input_end(Iterator p)
  {
    return input_iterator<typename std::iterator_traits<Iterator>::value_type, C>(&*(p-1) + 1);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // simd::output_iterator reference a pack of N elements of type T that can only
  // be write.
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t C = meta::cardinal_of< pack<T> >::value >
  struct  output_iterator
        :  boost::
           iterator_adaptor< output_iterator<T,C>
                           , T*
                           , pack<T, C>
                           , std::random_access_iterator_tag
                           , output_iterator<T,C> const
                           >
  {
  private:
    typedef pack<T,C> pack_type;

  public:
    output_iterator() : output_iterator::iterator_adaptor_(0) {}

    explicit output_iterator(T* p)
      : output_iterator::iterator_adaptor_(p)
    {
      BOOST_ASSERT_MSG
        ( boost::simd::is_aligned(p, C*sizeof(T))
        , "The constructor of iterator<T,C> has been called on a pointer "
          "which alignment is not compatible with current SIMD extension."
        );
    }

    template<class Expr>
    BOOST_FORCEINLINE
    void operator=(Expr const& right) const
    {
      boost::simd::store(right, this->base());
    }

  private:
    friend class boost::iterator_core_access;

    BOOST_FORCEINLINE
    typename output_iterator::reference dereference() const
    {
      return *this;
    }

    BOOST_FORCEINLINE void increment()
    {
      this->base_reference() += C;
    }

    BOOST_FORCEINLINE void decrement()
    {
      this->base_reference() -= C;
    }

    BOOST_FORCEINLINE void advance(typename output_iterator::difference_type n)
    {
      this->base_reference() += n*C;
    }

    BOOST_FORCEINLINE
    typename output_iterator::difference_type distance_to(output_iterator const& other) const
    {
      return (other.base() - this->base()) / typename output_iterator::difference_type(C);
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
    return output_iterator<typename std::iterator_traits<Iterator>::value_type>(&*p);
  }

  template<std::size_t C, class Iterator>
  output_iterator<typename std::iterator_traits<Iterator>::value_type, C>
  output_begin(Iterator p)
  {
    return output_iterator<typename std::iterator_traits<Iterator>::value_type, C>(&*p);
  }

  template<class Iterator>
  output_iterator<typename std::iterator_traits<Iterator>::value_type>
  output_end(Iterator p)
  {
    return output_iterator<typename std::iterator_traits<Iterator>::value_type>(&*(p-1) + 1);
  }

  template<std::size_t C, class Iterator>
  output_iterator<typename std::iterator_traits<Iterator>::value_type,C>
  output_end(Iterator p)
  {
    return output_iterator<typename std::iterator_traits<Iterator>::value_type, C>(&*(p-1) + 1);
  }

} }

#endif
