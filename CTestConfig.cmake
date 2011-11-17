################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
set(CTEST_PROJECT_NAME "NT2")
set(CTEST_NIGHTLY_START_TIME "00:00:00 CET")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "cdash.lri.fr")
set(CTEST_DROP_LOCATION "/submit.php?project=NT2")
set(CTEST_DROP_SITE_CDASH TRUE)

set(CTEST_MEMORYCHECK_SUPPRESSIONS_FILE ${CTEST_SOURCE_DIRECTORY}/valgrind.supp)
