[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['return right shift of the first operand by the second',
                          "that must be of integer type and of the same number",
                          "of elements as the first parameter",
                          "Infix notation can be used with operator '>>'"],
         'equalparams'   : False,
         'param_1'       : ["must be integer"],
         'return'        : ["a value of the type of the first parameter"],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : ['T','iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'r_t',
            },
         'type_defs' : [],
         'types' : ['integer_','real_'],
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
                [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2'], ['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>(),boost::simd::One<iT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<iT>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::One<iT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'integer_   ' : {
                 'boost::simd::Mone<T>(),boost::simd::One<iT>()' : {'result' : 'boost::simd::Valmax<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::One<iT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::One<T>(),boost::simd::Zero<iT>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::One<iT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'boost::simd::One<T>(),boost::simd::Zero<iT>()' : {'result' : 'boost::simd::One<r_t>()','ulp_thresh' : '0',},
                 'boost::simd::Zero<T>(),boost::simd::One<iT>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['boost::simd::shift_right(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['a0>>a1'],
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
