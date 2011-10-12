[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['With one parameter it is equivalent to \c next',
                          'It is in the type \c A0, the least  \c A0 elementwise strictly greater than  \c a0.','\par',   
                          'With two parameters, the second is an integer value  \c n',
                          'and the result is equivalent to applying \c next \c abs(n) times to  \c a0.'],   
          'special_synopsis' : [
                "template<class A0> inline",
                "A0 predecessor(A0 const& a0);",
                " ",
                "template<class A0,class A1> inline",
                "A0 predecessor(A0 const& a0,const A1& n);",
                ],
            'max_arity' : '2',
            'return' :['a value of type A0'],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/next.hpp>',
                           '#include <boost/simd/include/constants/eps_related.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100']],
             'unsigned_int_' : [['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<r_t>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Valmin<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Mone<r_t>()+boost::simd::Eps<r_t>()/2',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<r_t>()+boost::simd::Eps<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Mindenormal<T>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Inf<r_t>()',
                },
             'signed_int_' : {
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<r_t>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
             'unsigned_int_' : {
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<r_t>()',
                 'boost::simd::One<T>()' : 'boost::simd::Two<r_t>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' :  {
                 'default' : ['boost::simd::successor(a0)'],
                    },
             'property_value' : {
                 'default' : ['boost::simd::next(a0)'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
    {
     'functor' : {
         'description' : ['with two parameters, the second is an integer value n',
                          'and it is equivalent to applying \c next abs(n) times to a0'],   
         'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : ['typedef typename boost::dispatch::meta::as_integer<T>::type iT;'],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 04/12/2010',
             'included' : ['#include <boost/simd/include/functions/next.hpp>',
                           '#include <boost/simd/include/constants/eps_related.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 12/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['iT(2)', 'iT(2)']],
             'signed_int_' : [['-100', '100'], ['iT(2)', 'iT(2)']],
             'unsigned_int_' : [['0', '100'], ['iT(2)', 'iT(2)']],
            },
         'specific_values' : {},
         'verif_test' : {
             'property_call' :  {
                 'default' : ['boost::simd::successor(a0,a1)'],
                    },
             'property_value' : {
                 'default' : ['boost::simd::next(boost::simd::next(a0))'],
                },
             'ulp_thresh' : '0',
            },
        },
     'version' : '0.1',
    },
]
