[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['return the bitwise or of the first parameter',
                          'with the bitwise complement of the second parameter.',
                          '\par',
                          'The operands must share the same bit size and',
                          'the result type is the one of the first operand'],
          'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'type_defs' : [],
         'types' : ['real_', 'integer_'],
         'simd_types' : ['real_', 'integer_'],
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
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
            },
         'specific_values' : {
            'integer_' : {
                 'boost::simd::Mone<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Minf<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Nan<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::bitwise_ornot(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['r_t(a0|(~a1))'],
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
