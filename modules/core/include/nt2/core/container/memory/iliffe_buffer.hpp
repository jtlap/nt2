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
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/config.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/meta/add_pointers.hpp>
#include <boost/fusion/include/single_view.hpp>
#include <nt2/core/container/memory/adapted/iliffe_buffer.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    * \brief Multi-dimensionnal memory buffer adaptor.
    *
    * iliffe_buffer is a Buffer adaptor that turns a 1D Buffer into a nD Buffer
    * by using the Iliffe vector allocation scheme to allow multi-dimensionnal
    * access by precomputing index tables of nD pointers.
    * 
    * \tparam Dimensions    Number of dimensions stored in this Buffer
    * \tparam Data          1D Buffer to remodel as data storage
    * \tparam Index         1D Buffer to remodel as indices storage
   **/
  //============================================================================
  template<typename Dimensions, typename Data, typename Index>
  struct iliffe_buffer
  {
    //==========================================================================
    /** Type of the allocator used in current buffer                          */
    //==========================================================================
    typedef typename Data::allocator_type                    allocator_type;
    typedef typename Index::allocator_type                   idx_allocator_t;

    //==========================================================================
    /** Type of the value stored in current buffer                            */
    //==========================================================================
    typedef typename Data::value_type                    value_type;

    //==========================================================================
    /** Type of the pointer giving access to the stored values                */
    //==========================================================================
    typedef typename Data::pointer                       pointer;

    //==========================================================================
    /** Type of the pointer giving access to the stored values as constants   */
    //==========================================================================
    typedef typename Data::const_pointer                 const_pointer;

    //==========================================================================
    /** Type of the iterator to the iliffe_buffer values                      */
    //==========================================================================
    typedef typename Data::pointer                       iterator;

    //==========================================================================
    /** Type of the const_iterator to the iliffe_buffer values                */
    //==========================================================================
    typedef typename Data::const_pointer                 const_iterator;

    //==========================================================================
    /** Type of reference to a value                                          */
    //==========================================================================
    typedef typename Data::reference                     reference;

    //==========================================================================
    /** Type of reference to a constant value                                 */
    //==========================================================================
    typedef typename Data::const_reference               const_reference;

    //==========================================================================
    /** Type representing an amount of values                                 */
    //==========================================================================
    typedef typename Data::size_type                     size_type;

    //==========================================================================
    /** Type representing an offset between values                            */
    //==========================================================================
    typedef typename Data::difference_type               difference_type;
    
    //==========================================================================
    /**
     *  Default constructor builds an empty iliffe buffer
     *
     * /param alloc Optionnal allocator object to pass to the underlying
     *              buffers
     **/
    //==========================================================================
    iliffe_buffer ( allocator_type const& alloc = allocator_type())
                  : data_(alloc), index_( idx_allocator_t(alloc) )
    {}

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
#if 0
    template<typename Sizes, typename Bases>
    iliffe_buffer ( Sizes const& sz
                  , Bases const& bs
                  , allocator_type const& alloc = allocator_type()
                  )
      : data_ ( slice<1>(sz, p); // changer ca
              , meta::view_at<0>(bs)
              , alloc
              )
      , index_( index_size(sz) // changer ca aussi
              , meta::view_at<Dimensions::value-1>(bs)
              , idx_allocator_t(alloc)
              )
    {
      // link
    }

    template<typename Sizes, typename Bases>
    iliffe_buffer ( Data const& src
                  , Sizes const& sz
                  , Bases const& bs
                  , allocator_type const& a = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
      : data_ ( src )
      , index_( index_size(sz)
              , meta::view_at<Dimensions::value-1>(bs)
              , idx_allocator_t(alloc)
              )
    {
      // link
    }
#endif

    //==========================================================================
    // Basic destructor - nothing fancy here \_/°>
    //==========================================================================
    ~iliffe_buffer() {}

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
        
    private:
    Data    data_;
    Index   index_;
    
#if 0
    iliffe_buffer( iliffe_buffer const& src ) {}

    //==========================================================================
    // Forward the canonical RestructurableBuffer interface
    //==========================================================================
    using parent::operator=

    using parent::operator[];

    //==========================================================================
    /**
      * Reallocate a iliffe_bufer to a new size.
     **/
    //==========================================================================
    template<typename Sizes> inline void resize( Sizes const& szs )
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == Dimensions::value)
      , BUFFER_SIZE_MISMATCH_WHEN_RESIZING_BUFFER
      , (Sizes)
      );
      
      parent::resize(szs);
    }

    //==========================================================================
    /**
      * Rebase an iliffe_bufer to a new base set.
     **/
    //==========================================================================
    template<typename Bases> inline void rebase( Bases const& bss )
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == Dimensions::value)
      , BUFFER_BASE_MISMATCH_WHEN_RESIZING_BUFFER
      , (Bases)
      );

      parent::rebase(bss);
    }

    //==========================================================================
    /**
      * Resize and rebase a iliffe_bufer to a new size/base set.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> inline void
    restructure( Sizes const& szs, Bases const& bss )
    {
      this->resize(szs);
      this->rebase(bss);
    }
    
    //==========================================================================
    /**
      * Initializes a Iliffe buffer by allocating memory for its own ownership.
      * For a given number of dimensions \c N , the constructor will allocate
      * enough memory to store N indexing tables and the actual data size as
      * defined by the sizes and padding parameters.
      *
      * \param szs FusionRandomAccessSequence containing the dimensions of the
      *            buffer
      * \param bss FusionRandomAccessSequence containing the base indices of the
      *            buffer
      * \param p   Padding strategy of the buffer
      * \param a   Allocator instance used by the buffer
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> inline void
    initialize( Sizes const&      szs
              , Bases const&      bss
              , Padding const&    p
              )
    {
      // Stores the outer base index required for proper deallocation
      idx_ = boost::fusion::at_c<Dimensions-1>(meta::permute_view<Sizes const,StorageOrder>(bss));

      // Computes the number of values to store
      size_type numel_ = slice<1>(meta::permute_view<Sizes const,StorageOrder>(szs),p);
      // If non-empty ...
      if(numel_ != 0)
      {
        // Computes the number of bytes for the data and the indexing
        size_type data_size_ = numel_ * sizeof(value_type);
        size_type idx_size_  = index_size(meta::permute_view<Sizes const,StorageOrder>(szs),p);


        // Allocate that much bytes
        index_buffer_.resize(idx_size_);
        data_buffer_.resize(data_size_);

        memory::byte* idx_ptr =  reinterpret_cast<memory::byte*>(index_buffer_.begin());

        // Points to the begining of the data block
        begin_ = reinterpret_cast<value_type*>(data_buffer_.begin());
        end_   = begin_ + data_size_;

        // Recursively fills out the index
        data_ = link( idx_ptr, begin_ - boost::fusion::at_c<0>(meta::permute_view<Sizes const,StorageOrder>(bss))
                      , meta::permute_view<Sizes const,StorageOrder>(szs) 
                      , meta::permute_view<Sizes const,StorageOrder>(bss)
                      , p
                    , boost::mpl::int_<Dimensions>()
                    );
      }
    }

    protected:
    //==========================================================================
    /*
     * index_size computes the number of bytes required to store the index table
     * of the Iliffe vector
     */
    //==========================================================================
    template<class Seq> inline std::size_t
    index_size(Seq const& s, Padding const& p) const
    {
      // The index section is the sum of all required index aligned
      // globally on the boundary value provided by p
      return align_on( index_size(s,boost::mpl::size_t<2>()), p.value() );
    }

    template<class Seq,std::size_t Index> inline std::size_t
    index_size(Seq const& s, boost::mpl::size_t<Index> const&) const
    {
        return  slice<Index>(s,no_padding()) * sizeof(void*)
              + index_size(s,boost::mpl::size_t<Index+1>());
    }

    template<class Seq> inline std::size_t
    index_size(Seq const& s, boost::mpl::size_t<Dimensions> const&) const
    {
      return slice<Dimensions>(s,no_padding()) * sizeof(void*);
    }

    //==========================================================================
    /*
     * link performs the indexing of the Iliffe vector
     */
    //==========================================================================
    template<typename Sizes, typename Bases, int D>
    typename meta::add_pointers<Type,D>::type
    link( memory::byte*   p
        , value_type*     base
        , Sizes const&    szs
        , Bases const&    bss
        , Padding const&  pd
        , boost::mpl::int_<D> const&
        )
    {
      // Retrieve the current pointer in the index
      typedef typename meta::add_pointers<Type,D>::type ptr_type;
      ptr_type ptr = reinterpret_cast<ptr_type>(p);

      // Retrieve the underlying indexed part
      size_type offset = slice<D>(szs,pd)*sizeof(void*);
      ptr[0] = link(p+offset,base,szs,bss,pd,boost::mpl::int_<D-1>());

      // Fill out the remaining indices
      size_type local_size = stride<D-1>(szs,pd);
      for(std::size_t i=1; i < slice<D>(szs,pd);++i)
        ptr[i] = ptr[i-1] + local_size;

      // Rebase the index
      ptr -= boost::fusion::at_c<D-1>(bss);
      return ptr;
    }

    template<typename Sizes, typename Bases>
    typename meta::add_pointers<Type,2>::type
    link( memory::byte*   p
        , value_type*     base
        , Sizes const&    szs
        , Bases const&    bss
        , Padding const&  pd
        , boost::mpl::int_<2> const&
        )
    {
      // Retrieve the current pointer in the index
      typedef typename meta::add_pointers<Type,2>::type ptr_type;
      ptr_type ptr = reinterpret_cast<ptr_type>(p);

      // Points to the beginning of the data block
      ptr[0] = base;

      // Fill out the remaining indices
      std::size_t local_size = stride<1>(szs,pd);
      for(std::size_t i=1; i < slice<2>(szs,pd);++i)
        ptr[i] = ptr[i-1] + local_size;

      // Rebase the index
      ptr -= boost::fusion::at_c<1>(bss);
      return ptr;
    }
#endif
  };

  //============================================================================
  /**
   * iliffe_buffer is specialized in 1D case to not allocate any indexing table.
   * Note that we don't specify any special 1D Index type but just ignore it.
   **/
  //============================================================================
  template<typename Data, typename Index>
  struct iliffe_buffer<boost::mpl::size_t<1>,Data,Index> : private Data
  {    
    typedef Data                              parent;
    typedef typename parent::allocator_type   allocator_type;
    typedef typename parent::value_type       value_type;
    typedef typename parent::pointer          iterator;
    typedef typename parent::const_pointer    const_iterator;
    typedef typename parent::reference        reference;
    typedef typename parent::const_reference  const_reference;
    typedef typename parent::size_type        size_type;
    typedef typename parent::difference_type  difference_type;

    iliffe_buffer( allocator_type const& a = allocator_type()) : parent(a) {}

    template<typename Sizes, typename Bases>
    iliffe_buffer ( Sizes const& sz
                  , Bases const& bs
                  , allocator_type const& a = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
    : parent(sz,bs,a)
    {}
    
    template<typename Sizes, typename Bases>
    iliffe_buffer ( Data const& src
                  , Sizes const& sz
                  , Bases const& bs
                  , allocator_type const& a = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
    : parent(src,sz,bs,a)
    {}
    
    iliffe_buffer( iliffe_buffer const& src ) : parent(src) {}

    //==========================================================================
    // Forward the canonical Buffer interface
    //==========================================================================
    using parent::operator=;
    using parent::begin;
    using parent::end;

    //==========================================================================
    // Data acces through Position
    //==========================================================================
    template<class Position>
    reference operator[]( Position const& pos )
    {
      return dereference(static_cast<parent&>(*this),pos);
    }
    
    template<class Position>
    const_reference operator[]( Position const& pos ) const
    {
      return dereference(static_cast<parent const&>(*this),pos);
    }
    
    //==========================================================================
    /**
      * Reallocate a iliffe_bufer to a new size.
     **/
    //==========================================================================
    template<typename Sizes> inline void resize( Sizes const& szs )
    {
      parent::resize(szs);
    }

    //==========================================================================
    /**
      * Rebase an iliffe_bufer to a new base set.
     **/
    //==========================================================================
    template<typename Bases> inline void rebase( Bases const& bss )
    {
      parent::rebase(bss);
    }

    //==========================================================================
    /**
      * Resize and rebase a iliffe_bufer to a new size/base set.
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> inline void
    restructure( Sizes const& szs, Bases const& bss )
    {
      parent::resize(szs,bss);
    }
  };
} }

#endif
