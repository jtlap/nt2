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
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/simd/meta/native_cardinal.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/array.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd
{
////////////////////////////////////////////////////////////////////////////////
// simd::shifted_iterator reference sequence of k pack of N elements of type T.
// Each inner simd iterator of the sequence is shifted by one element by default.
////////////////////////////////////////////////////////////////////////////////
  template<class Type, std::size_t Depth>
  struct shifted_iterator
  : public  boost
            ::iterator_facade< shifted_iterator<Type, Depth>
                             , boost::array< pack<Type>, Depth> const
                             , boost::forward_traversal_tag
                             >
  {
  public:

    typedef Type                                        value_type;
    typedef Type*                                       pointer_type;
    typedef pack<Type>                                  pack_type;
    typedef shifted_iterator<Type, Depth>               derived_type;
    typedef std::size_t                                 difference_type;
    typedef boost::array< pack<Type>, Depth>            sequence_type;
    typedef boost::mpl::size_t<Depth>                   static_size;
    //typedef boost::mpl::size_t<Step>                    static_step;


    explicit shifted_iterator(pointer_type p) : base(p)
    { fill(static_size::value-1); }

  protected:

    void fill(difference_type const& sequence_size)
    {
      if(sequence_size == 0) seq[0] = unaligned_load<pack_type>(base);
      else
      {
        seq[sequence_size] = unaligned_load<pack_type>(base+sequence_size);
        fill(sequence_size-1);
      }
    }

    void update( pointer_type const& p)
    {
      for(int i=0; i<static_size::value-1; ++i) { seq[i] = seq[i+1]; }
      seq[static_size::value-1] = unaligned_load<pack_type>(base+(static_size::value-1));
    }

  private:
    friend class boost::iterator_core_access;

    void increment()
    {
      base++;
      update(base);
    }

    bool equal(derived_type const& other) const { return (this->base == other.base); }

    sequence_type const& dereference() const { return seq; }

    pointer_type  base;
    mutable sequence_type seq;
  };

  template< std::size_t Depth, class Iterator>
  shifted_iterator<typename boost::pointee<Iterator>::type, Depth>
  begin(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*p);
    return shifted_iterator<typename boost::pointee<Iterator>::type, Depth>(tmp);
  }

  template<std::size_t Depth,class Iterator>
  shifted_iterator<typename boost::pointee<Iterator>::type, Depth>
  end(Iterator p)
  {
    typedef typename boost::pointee<Iterator>::type value_type;
    value_type* tmp = &(*((p-1)-(meta::native_cardinal<value_type>::value+Depth)));
    return shifted_iterator<typename boost::pointee<Iterator>::type, Depth>(tmp+1);
  }

} }

#endif
