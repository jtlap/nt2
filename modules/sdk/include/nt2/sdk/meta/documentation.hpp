#error "This file is for documentation purpose only."

/*!
 * \ingroup functors
 * \defgroup hierarchy Type Hierarchies
 *
 * This module defines all the tag class describing a type \ref Hierarchy.
 */

/*!
 * \ingroup sdk
 * \defgroup extensions Extension points
 *
 * This module gather \nt2 extension points, ie classes and functions designed
 * to help external extensions of internal functions and \metafunctions
 */

/*!
 * \ingroup meta
 * \defgroup metafunctions Meta-Functions
 * This module gathers \metafunction required by \nt2 internal.
 */

namespace boost { namespace dispatch
{
  /*!
   * \ingroup extensions
   * Various functions and \meta-functions of \nt2 provides a protocol to extend
   * them for new types or usages. boost::dispatch::ext is open to external modifications for
   * this purpose of extensibility
   */
  namespace ext {}

  /*!
   * Namespace containing all Boost.Dispatch meta-functions and meta-function classes
   */
  namespace meta {}
} }
