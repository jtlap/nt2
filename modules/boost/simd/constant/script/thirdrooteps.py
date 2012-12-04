[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "Constant $Fct$", "the third root of constant eps",
                           "\\\\arg 1 for integer types",
                           "\\\\arg 6.055454452393343e-06 for double",
                           "\\\\arg 4.9215667e-03 for float"],
         'type_dependant' : True,
         'return' : ["type T value"],
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
