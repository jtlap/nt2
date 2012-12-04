[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['The function returns the first entry shifted right or left',
                          'by the absolute value of second entry according to its sign.'],
         'param_1' : ['must be an integer value'],
         'return'  : ['returns a value of the type of the first parameter'],
            'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['integer_'],
         'type_defs' : [],
         'types' : ['integer_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['T(0)', 'sizeof(T)*8-1']],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Inf<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'signed_int_   ' : {
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::rshr(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['boost::simd::rshr(a0,a1)'],
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
