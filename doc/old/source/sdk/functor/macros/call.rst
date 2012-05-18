.. _functor_call_macro:

Function Implementation Macros
==============================

Description
^^^^^^^^^^^

The following macros can be used to implement overloads of the :ref:`functor_call`
class for a given tag and type category. Various level of details are provided
to supply proper boilerplate code in case of specific function signature.

.. seealso::

  :ref:`howto_custom_function`

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/functor/preprocessor/call.hpp>

NT2_FUNCTOR_CALL
^^^^^^^^^^^^^^^^

.. index::
    single: NT2_FUNCTOR_CALL

Synopsis
--------

.. code-block:: cpp

  #define NT2_FUNCTOR_CALL(N)

Description
-----------
Generate a ``N`` arguments ``operator()`` prototype for current
:ref:`functor_call` overload without any type dispatching.

Arguments
---------

  +-----------+---------------------------------------+
  | Arguments |  Description                          |
  +===========+=======================================+
  | ``N``     | Number of function arguments          |
  +-----------+---------------------------------------+


.. _functor_call_dispatch:

NT2_FUNCTOR_CALL_DISPATCH
^^^^^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_FUNCTOR_CALL_DISPATCH

Synopsis
--------

.. code-block:: cpp

  #define NT2_FUNCTOR_CALL_DISPATCH(N,TYPE,SETS)

Description
-----------
Generate a ``N`` arguments ``operator()`` prototype for current :ref:`functor_call`
overload. This operator acts as the main functor entry point and performs type
matching and tag-dispatching of type ``TYPE`` with respect to category list ``SETS``.
This macro also generate the common overload for unsupported type dispatch.

Arguments
---------

  +-----------+-----------------------------------------------------------------+
  | Arguments |  Description                                                    |
  +===========+=================================================================+
  | ``N``     | Number of function arguments                                    |
  +-----------+-----------------------------------------------------------------+
  | ``TYPE``  | Type used for tag-dispachting                                   |
  +-----------+-----------------------------------------------------------------+
  | ``SETS``  | Preprocessor array containing the list of dispatch target types |
  +-----------+-----------------------------------------------------------------+

.. _functor_call_eval_if:

NT2_FUNCTOR_CALL_EVAL_IF
^^^^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_FUNCTOR_CALL_EVAL_IF

Synopsis
--------

.. code-block:: cpp

  #define NT2_FUNCTOR_CALL_EVAL_IF(N,SET)

Description
-----------
Generate a ``N`` arguments ``eval`` tag-dispatched function for current :ref:`functor_call`
overload. This particular function is bound to be called when argument types hierarchy tag
is resolved to ``SET``.

Arguments
---------

  +-----------+---------------------------------------+
  | Arguments |  Description                          |
  +===========+=======================================+
  | ``N``     | Number of function arguments          |
  +-----------+---------------------------------------+
  | ``SET``   | Internal type hierarchy tag to match  |
  +-----------+---------------------------------------+

NT2_CALL_RETURN_TYPE
^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_CALL_RETURN_TYPE

Synopsis
--------

.. code-block:: cpp

  #define NT2_CALL_RETURN_TYPE(N)

Description
-----------
Generate the |result_of|_ call for computing return type of current
:ref:`functor_call` overload.

Arguments
---------

  +-----------+---------------------------------------+
  | Arguments |  Description                          |
  +===========+=======================================+
  | ``N``     | Number of function arguments          |
  +-----------+---------------------------------------+

NT2_FUNCTOR_CALL_DEFAULT
^^^^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: NT2_FUNCTOR_CALL_DEFAULT

Synopsis
--------

.. code-block:: cpp

  #define NT2_FUNCTOR_CALL_DEFAULT(N)

Description
-----------
Generate a ``N`` arguments default overload for unsupported type.
This overload trigger a static assertion if called.

Arguments
---------

  +-----------+---------------------------------------+
  | Arguments |  Description                          |
  +===========+=======================================+
  | ``N``     | Number of function arguments          |
  +-----------+---------------------------------------+
