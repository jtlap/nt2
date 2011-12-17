[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['return the logical and of the two parameters',
                          'the operands must of the same type',
                          'the result type is the common one or bool in scalar case',
                          "Infix notation can be used with operator '&&'"
                         ],
          'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::simd::meta::logical<T>::type',
            },
         'special' : ['predicate'],
         'type_defs' : [],
         'types' : ['integer_','real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include <boost/simd/sdk/simd/logical.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0',},
                },
             'integer_   ' : {
                 'boost::simd::Mone<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::logical_and(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0&&a1'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'integer_' : ['0'],
                },
            },
        },
    },
]
