[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "Constant $Fct$, maximum value of a type.",
                           "\\\\arg int8    -128, uint8    0,",
                           "\\\\arg int16 -32768, uint16 0,",
                           "\\\\arg int32 -2147483648, uint32 0,",
                           "\\\\arg int64 -9223372036854775808, uint64 0,"
                           "\\\\arg float \\\\f$-\infty\\\\f$, double \\\\f$-\infty\\\\f$,"],
         'return' : ["type T value"],
         'type_dependant' : True,
         'template' : True,
         'module' : 'boost',
         'special' : ['constant'],
         'arity' : '0',
         'call_types' : [],
         'ret_arity' : '0',
         'tpl' : '<T>',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_', 'signed_int_','unsigned_int_'],
         'type_defs' : [],
         'types' : ['real_',  'signed_int_','unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 02/10/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 02/10/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
            },
         'specific_values' : {
             'default' : {
                 '-' : {'result' : 'T(1)','ulp_thresh' : '0',},
                },
            },
        },
    },
]
