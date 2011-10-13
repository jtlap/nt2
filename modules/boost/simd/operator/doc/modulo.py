[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['return the elementwise modulo of the two parameters',
                          "Infix notation can be used with operator '%'",
                          "Does not work for floating point entries.",],
          'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'r_t',
            },
         'type_defs' : [],
         'simd_types' : ['integer_'],
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
             'default' : [
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::One<T>()', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Two<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::Two<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'integer_   ' : {
                 'boost::simd::Mone<T>(),boost::simd::Zero<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Two<T>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::Two<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::modulo(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0%a1'],
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
