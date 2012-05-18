.. _allocator:

allocator
=========

.. index::
    single: allocator

Description
^^^^^^^^^^^

``allocator`` is a generic memory allocator which predifines the memory managment for NT² containers. It's the default allocator used when a NT² container is instantiated. ``allocator`` respects the concept of allocator according to the STL.

.. seealso::

  :ref:`allocate`, :ref:`deallocate`, :ref:`reallocate`,

Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+--------------------+
  | Parameter | Requirement                  | Description        |
  +===========+==============================+====================+
  | 	T     | None                         | Element type       |
  +-----------+------------------------------+--------------------+
 
Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/memory/allocator.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace memory
  {
    // Allocate a raw buffer of bytes
    template<class T> struct allocator
    {
   
      // Internal typedefs
      typedef T               value_type;
      typedef T*              pointer;
      typedef T const*        const_pointer;
      typedef T&              reference;
      typedef T const&        const_reference;
      typedef std::size_t     size_type;
      typedef std::ptrdiff_t  difference_type;

      template<class U> struct rebind;

      // Ctor/dtor
                        allocator() {}
      template<class U> allocator(allocator<U> const& ) {}
                       ~allocator() {}

      allocator& operator=(allocator const& );

      // Address handling
      pointer       address(reference r);
      const_pointer address(const_reference r); 

      // Size handling
      size_type max_size() const;

      // Object lifetime handling
      void construct(pointer p, const T& t);
      void destroy(pointer p);

      // Memory handling
      pointer allocate( size_type c, const void* = 0 ) const;
      void deallocate (pointer p, size_type s) const;

      // Extended Allocator interface -- reallocate
      pointer resize(pointer p, size_type n, size_type o );
    };
  } }

Operators
^^^^^^^^^

operator(Args const&... )
-------------------------

.. index::
    single: allocator; operator(Args const&... )

**Synopsis:**

.. code-block:: cpp

	template<class T>
  	bool operator== (allocator<T> const&, allocator<T> const&)		 
 
.. code-block:: cpp

  	template<class T>
  	bool operator!= (allocator<T> const&, allocator<T> const&)

**Description:** 
  Compares two allocators. If the two allocators don't hold the same type, a compile error appears.

Types
^^^^^

struct result
-------------

.. index::
    single: allocator; rebind

**Synopsis:**

.. code-block:: cpp

    template<class U> struct rebind;

**Description:** 
  This structure allows an ``allocator`` for an object of type T to allocate memory for an object of type U.
