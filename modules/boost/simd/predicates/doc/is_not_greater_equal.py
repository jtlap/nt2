[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Returns True<A0>() if a0 is not greater or equal to a1 else returns False<A0>().','\par',
                          'Due to existence of nan, this is not equivalent to \c not(is_greater_equal(a0,a1))'],   
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::simd::meta::logical<T>::type',
            },
         'simd_types' : ['real_', 'signed_int_', 'unsigned_int_'],
         'special' : ['predicate'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 21/02/2011',
             'included' : ['#include <boost/simd/sdk/simd/logical.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 21/02/2011',
            },
         'ranges' : {
             'default' : [['T(-10000)', 'T(10000)'], ['T(-10000)', 'T(10000)']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Two<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 '-boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Half<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Quarter<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Two<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Two<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::is_not_greater_equal(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['boost::simd::is_not_greater_equal(a0,a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
    },
]
