[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['return the logical negation of the parameter,',
                          'i.e. True or False of the entry type according that ',
                          'the input is zero or non zero',
                         ],
          'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
                'default' : 'typename boost::simd::meta::as_logical<T>::type',
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
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::True< boost::simd::logical<T> >()' : {'result' : 'boost::simd::False<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::False< boost::simd::logical<T> >()' : {'result' : 'boost::simd::True<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::logical_not(a0)'],
                },
             'property_value' : {
                 'integer_' : ['!a0'],
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
