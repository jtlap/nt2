//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ILIFFE_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ILIFFE_BUFFER_HPP_INCLUDED

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::iliffe_buffer class
  **/
//==============================================================================
#include <nt2/sdk/meta/view_at.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <nt2/sdk/memory/adapted/iliffe_buffer.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    * \brief Multi-dimensionnal memory buffer adaptor.
    *
    * iliffe_buffer is a Buffer adaptor that aggregate a Data and an Index
    * buffer into an Iliffe vector to allow bidimensionnal access.
    *
    * \tparam Data  1D Buffer to remodel as data storage
    * \tparam Index 1D Buffer to remodel as indices storage
   **/
  //============================================================================
  template<typename Data, typename Index>
  struct iliffe_buffer
  {
    //==========================================================================
    /** Type of the allocator used in current buffer                          */
    //==========================================================================
    typedef typename Data::allocator_type               allocator_type;
    typedef typename Index::allocator_type              index_allocator_type;

    //==========================================================================
    /** Type of the value stored in current buffer                            */
    //==========================================================================
    typedef typename Data::value_type                   value_type;

    //==========================================================================
    /** Type of the iterator to the iliffe_buffer values                      */
    //==========================================================================
    typedef typename Data::iterator                     iterator;

    //==========================================================================
    /** Type of the const_iterator to the iliffe_buffer values                */
    //==========================================================================
    typedef typename Data::const_iterator               const_iterator;

    //==========================================================================
    /** Type of reference to a value                                          */
    //==========================================================================
    typedef typename Data::reference                    reference;

    //==========================================================================
    /** Type of reference to a constant value                                 */
    //==========================================================================
    typedef typename Data::const_reference              const_reference;

    //==========================================================================
    /** Type representing an amount of values                                 */
    //==========================================================================
    typedef typename Data::size_type                    size_type;

    //==========================================================================
    /** Type representing an offset between values                            */
    //==========================================================================
    typedef typename Data::difference_type              difference_type;

    //==========================================================================
    /**
     *  Default constructor builds an empty iliffe buffer
     *
     * /param alloc Optional allocator object to pass to the underlying
     *              buffers
     **/
    //==========================================================================
    iliffe_buffer ( allocator_type const& a = allocator_type() )
                  : data_(a), inner_(0)
    {
      //========================================================================
      // If index has some size, then we can retrieve the inner size
      // This is required to handle automatic internal buffers
      //========================================================================
      if( index_.size() && data_.size() )
      {
        inner_ = data_.size()/index_.size();
        make_links();
      }

      inner_up_ = data_.lower() + inner_ - 1;
    }

    //==========================================================================
    /**
      * Initializes a Iliffe buffer from a dimensions and bases set.
      *
      * \param sz FusionRandomAccessSequence containing the dimensions set
      *           of the buffer.
      * \param bs FusionRandomAccessSequence containing the base indices set
      *           of the buffer.
     **/
    //==========================================================================
    template<typename Sizes>
    iliffe_buffer( Sizes const& sz, allocator_type const& a = allocator_type() )
      : data_ ( data_size(sz), a )
      , index_( index_size(sz) )
      , inner_( boost::fusion::at_c<0>(sz) )
    {
      make_links();
      inner_up_ = data_.lower() + inner_ - 1;
    }

    //==========================================================================
    /**
      * Give access to the beginning of the values stored in the buffer.
      * begin() and end() are both returning un-biased iterator, making them
      * suitable arguments for standard algorithms. Note that such iterators
      * dont walk over padding.
      *
      * \return A pointer pointing to the beginning of the buffer segment
      * holding values.
     **/
    //==========================================================================
    iterator        begin()       { return data_.begin(); }
    const_iterator  begin() const { return data_.begin(); }

    //==========================================================================
    /**
      * Give access to the end of the values stored in the buffer.
      * begin() and end() are both returning un-biased iterator, making them
      * suitable arguments for standard algorithms. Note that such iterators
      * dont walk over padding.
      *
      * \return A pointer pointing past the last element of the buffer segment
      * holding values.
     **/
    //==========================================================================
    iterator        end()         { return data_.end(); }
    const_iterator  end() const   { return data_.end(); }

    //==========================================================================
    /**
      * Return the lowest indices of the iliffe_buffer
     **/
    //==========================================================================
    inline difference_type lower()        const { return data_.lower();   }
    inline difference_type inner_lower()  const { return data_.lower();   }
    inline difference_type outer_lower()  const { return index_.lower();  }

    //==========================================================================
    /**
      * Return the upper indices of the iliffe_buffer
     **/
    //==========================================================================
    inline difference_type upper()        const { return data_.upper();   }
    inline difference_type inner_upper()  const { return inner_up_;       }
    inline difference_type outer_upper()  const { return index_.upper();  }

    //==========================================================================
    /**
      * Return the sizes of the iliffe_buffer
     **/
    //==========================================================================
    inline size_type size()       const { return data_.size();  }
    inline size_type inner_size() const { return inner_;        }
    inline size_type outer_size() const { return index_.size(); }

    //==========================================================================
    /**
      * Return true if the iliffe_buffer contains no elements
     **/
    //==========================================================================
    inline bool empty() const { return size() == 0; }

    //==========================================================================
    /**
      * Reallocate a iliffe_bufer to a new size.
     **/
    //==========================================================================
    template<typename Sizes> inline void resize( Sizes const& szs )
    {
      data_.resize(data_size(szs));
      index_.resize(index_size(szs));
      inner_    = boost::fusion::at_c<0>(szs);
      inner_up_ = data_.lower() + inner_ - 1;
      make_links();
    }

    //==========================================================================
    /**
     * Access to a given position through the iliffe_buffer
     * \param pos 2D Index of the element to retrieve.
     **/
    //==========================================================================
    template<class Position>
    BOOST_FORCEINLINE reference operator[]( Position const& p )
    {
      return index_[meta::view_at<1>(p)][boost::fusion::at_c<0>(p)];
    }

    template<class Position>
    BOOST_FORCEINLINE const_reference operator[]( Position const& p ) const
    {
      return index_[meta::view_at<1>(p)][boost::fusion::at_c<0>(p)];
    }

    void swap( iliffe_buffer& src )
    {
      data_.swap(src.data_);
      boost::swap(inner_,src.inner_);
      boost::swap(inner_up_,src.inner_up_);
      index_swap(index_,src.index_);
    }

    protected:
    //==========================================================================
    // Partial swap based on actual sub-buffer type
    // TODO: Probably fix this properly in a non-concrete type based way ?
    //==========================================================================
    template<class TT, std::ptrdiff_t BB, class AA>
    void index_swap( buffer<TT,BB,AA>& local,buffer<TT,BB,AA>& src )
    {
      local.swap(src);
    }

    template<class TT, std::size_t SS, std::ptrdiff_t BB>
    void index_swap( array_buffer<TT,SS,BB>&, array_buffer<TT,SS,BB>& ) {}

    //==========================================================================
    // data_size computes the number of elements required to store the data
    // table of the Iliffe vector
    //==========================================================================
    template<class Seq>
    boost::fusion::vector<std::size_t> data_size(Seq const& s) const
    {
      boost::dispatch::functor<tag::multiplies_> func;

      return  boost::fusion::make_vector
              ( boost::fusion::fold ( boost::fusion::pop_front(s)
                                    , boost::fusion::front(s)
                                    , func
                                    )
              );
    }

    //==========================================================================
    // index_size computes the number of elements required to store the index
    // table of the Iliffe vector
    //==========================================================================
    template<class Seq>
    boost::fusion::vector<std::size_t> index_size(Seq const& s) const
    {
      boost::dispatch::functor<tag::multiplies_> func;

      return  boost::fusion::make_vector
              ( boost::fusion::fold ( boost::fusion::
                                      pop_front(boost::fusion::pop_front(s))
                                    , boost::fusion::
                                      front(boost::fusion::pop_front(s))
                                    , func
                                    )
              );
    }

    //==========================================================================
    //link performs the indexing of the Iliffe vector
    //==========================================================================
    void make_links()
    {
      typename Index::difference_type i = index_.lower();
      typename Index::difference_type u = index_.upper();

      index_[boost::fusion::make_vector(i++)] = data_.origin();
      for(; i <= u; ++i)
          index_[boost::fusion::make_vector(i)]
        = index_[boost::fusion::make_vector(i-1)] + inner_;
    }

    private:
    Data      data_;
    Index     index_;
    size_type inner_;
    size_type inner_up_;
  };

  template<typename D, typename I>
  void swap( iliffe_buffer<D,I>& a, iliffe_buffer<D,I>& b )
  {
    a.swap(b);
  }
} }

#include <nt2/sdk/memory/details/iliffe_buffer_1d.hpp>
#include <nt2/sdk/memory/details/iliffe_buffer_2d.hpp>

#endif
