.. _unit_tests:

Predicates Macros
=================

Description
^^^^^^^^^^^
The following macros encapsulate a whole test routine based on some expected behavior
on some expression-based predicates. In case of failure, the proper counters are
updated and reported at the end of the test suite.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/unit/tests.hpp>

Predicates
^^^^^^^^^^

NT2_TEST
-------------

.. index::
    single: NT2_TEST

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST(XPR)

**Description:** If ``XPR`` evaluates to ``false``, the test is considered a
failure and reported as such.

NT2_TEST_EQUAL
--------------

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST_EQUAL(A,B)

**Description:** Check if ``A`` and ``B`` are equal. If not, report the test as
failed.

NT2_TEST_NOT_EQUAL
------------------

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST_NOT_EQUAL(A,B)

**Description:** Check if ``A`` and ``B`` are not equal. If not, report the test
as failed.

NT2_TEST_LESSER
---------------

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST_LESSER(A,B)

**Description:** Check if ``A`` is lesser than ``B``. If not, report the test as
failed.

NT2_TEST_GREATER
-----------------

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST_GREATER(A,B)

**Description:** Check if ``A`` is greater than ``B``. If not, report the test as
failed.

NT2_TEST_LESSER_EQUAL
---------------------

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST_LESSER_EQUAL(A,B)

**Description:** Check if ``A`` is lesser or equal to ``B``. If not, report the
test as failed.

NT2_TEST_GREATER_EQUAL
---------------------------

**Synopsis:**

.. code-block:: cpp

  #define NT2_TEST_GREATER_EQUAL(A,B)

**Description:** Check if ``A`` is greater or equal to ``B``. If not, report the
test as failed.
