#!/usr/bin/env python

import re
import os
import sys
import math
import json
import argparse
import collections

""" Tagged JSON with C-like types  """
CNull    = collections.namedtuple('CNull',    [])
CInt     = collections.namedtuple('CInt',     [])
CFloat   = collections.namedtuple('CFloat',   [])
CString  = collections.namedtuple('CString',  [])
CBool    = collections.namedtuple('CBool',    [])
CStruct  = collections.namedtuple('CStruct',  ['types', 'fields'])
CList    = collections.namedtuple('CList',    ['types'])
CPointer = collections.namedtuple('CPointer', ['type'])
CArray   = collections.namedtuple('CArray',   ['type', 'length'])

""" Override Equalities """
CNull.__eq__    = lambda x, y: isinstance(y, CNull)
CInt.__eq__     = lambda x, y: isinstance(y, CInt)
CFloat.__eq__   = lambda x, y: isinstance(y, CFloat)
CString.__eq__  = lambda x, y: isinstance(y, CString)
CBool.__eq__    = lambda x, y: isinstance(y, CBool)
CStruct.__eq__  = lambda x, y: isinstance(y, CStruct)  and x.types == y.types
CList.__eq__    = lambda x, y: isinstance(y, CList)    and x.types == y.types
CPointer.__eq__ = lambda x, y: isinstance(y, CPointer) and x.type  == y.type
CArray.__eq__   = lambda x, y: isinstance(y, CArray)  and x.type  == y.type and x.length == y.length


""" Convert a python object to a basic C-Tagged representation """
def obj2cjson(obj, **kw):
    
    """ Basic Types """
    if isinstance(obj, type(None)): return obj, CNull()
    if isinstance(obj, bool):       return obj, CBool()
    if isinstance(obj, int):        return obj, CInt()
    if isinstance(obj, float):      return obj, CFloat()
    if isinstance(obj, str):        return obj, CString()
    
    """ Object Type """
    if isinstance(obj, dict):
        
        pairs = []
        
        for k, v in obj.items():
            
            """ Manually fix any integer keys """
            if isinstance(k, int) and not kw.get('no_fix_int_keys', False):
                k = '_' + str(k)
            
            """ Can't fix any other non-string keys """
            if not isinstance(k, str):
                raise TypeError("Invalid Object Key '%s' is not string" % str(k))
            
            """ Replace any non-valid characters in string keys """
            if not re.match("[_A-Za-z][_a-zA-Z0-9]*$", k):
                
                ic = kw.get('key_fix_replacement', '_')
                
                if not kw.get('no_fix_invalid_keys', False):
                    if len(k) == 0: k = '_'
                    else:
                        if not re.match("[_A-Za-z]", k[0]):
                            if not re.match("[_a-zA-Z0-9]", k[0]):
                                k = ic + k[1:]
                            else:
                                k = '_' + k
                        
                        k = k[0] + ''.join([(ic if not re.match("[_a-zA-Z0-9]", kc) else kc) for kc in k[1:]])
                        
                else:
                    raise TypeError("Invalid Object Key '%s'" % k)
            
            if k in ('auto', 'break', 'case', 'char', 'const', 'continue',
                     'default', 'do', 'double', 'else', 'enum', 'extern',
                     'float', 'for', 'goto', 'if', 'int', 'long', 'register',
                     'return', 'short', 'signed', 'sizeof', 'static', 'struct',
                     'switch', 'typedef', 'union', 'unsigned', 'void', 'volatile',
                     'while'):
                  
                if not kw.get('no_fix_keyword_keys', False):
                    k = '_' + k
                else:
                    raise TypeError("Invalid Object Key '%s'" % k)
                
            
            pairs.append((k, v))
            
        obj = collections.OrderedDict(pairs)
        
        vals, typs = zip(*[obj2cjson(x) for x in obj.values()])
        
        return collections.OrderedDict(zip(obj.keys(), vals)), CStruct(types=tuple(typs), fields=tuple(obj.keys()))
    
    """ List Type """
    if isinstance(obj, list):
        obj, typs = zip(*[obj2cjson(x) for x in obj])
        return obj, CList(types=tuple(typs))
    
""" Remove all CList types from the marked-up JSON to make arrays homogeneous """
def cjson_unify(cjson, **kw):
    
    obj, typ = cjson
    
    """ Basic Types """
    if isinstance(typ, CNull):    return obj, typ
    if isinstance(typ, CInt):     return obj, typ
    if isinstance(typ, CFloat):   return obj, typ
    if isinstance(typ, CString):  return obj, typ
    if isinstance(typ, CBool):    return obj, typ
    if isinstance(typ, CArray):   return obj, typ
    if isinstance(typ, CPointer): return obj, typ
    
    """ Object Type """
    if isinstance(typ, CStruct):
        
        crcd = [cjson_unify((o, t), **kw) for o, t in zip(obj.values(), typ.types)]
        vals, typs = zip(*crcd)
        
        obj = collections.OrderedDict([(k, v) for k, v in zip(obj.keys(), vals)])
        typ = CStruct(types=typs, fields=tuple(obj.keys()))
        
        return obj, typ
    
    """ List Type """
    if isinstance(typ, CList):
        
        if obj == []: return obj, CArray(type=CNull(), length=0)
        
        crcd = [cjson_unify((o, t), **kw) for o, t in zip(obj, typ.types)]
        objs, typs = zip(*crcd)
        objs, typ = cjson_unify_list(objs, typs, **kw)
        
        return objs, CArray(type=typ, length=len(objs))
        

""" Unify a list of objects and a list of types to a single type """
def cjson_unify_list(objs, typs, **kw):
    
    """ Already Unified """
    if len(set(typs)) == 1: return objs, typs[0]
    
    """ Unify Pointers """
    if not kw.get('no_null_to_ptr', False):
        
        if all([isinstance(t, CPointer) for t in typs]):
            
            objs2, typ = cjson_unify_list(
                [o[0] for o in objs if o != None],
                [t.type for t in typs if not isinstance(t.type, CNull)],
                **kw)
            
            n = 0
            for i in range(len(objs)):
                if objs[i] is None: continue
                else:
                    objs[i] = [objs2[n]]
                    n += 1
            
            return objs, CPointer(type=typ)
        
    
    """ Unify Null and Structs """
    if not kw.get('no_null_to_obj', False):
        
        if (all([isinstance(t, CNull) or isinstance(t, CStruct) for t in typs])
        and any([isinstance(t, CNull) for t in typs])):
            
            objs  = [(None if o is None else [o]) for o in objs]
            typs  = [CPointer(type=t) for t in typs]
            
            return cjson_unify_list(objs, typs, **kw) 
    
    """ Unify Missing Struct Entries """
    if not kw.get('no_coerce_missing', False):
    
        if all([isinstance(t, CStruct) for t in typs]):
            
            if len(set([t.fields for t in typs])) > 1:
                
                fields = tuple(set(sum([list(t.fields) for t in typs], [])))
                types  = tuple()
                
                for f in fields:
                    for t in typs:
                        if f in t.fields:
                            types = types + (t.types[t.fields.index(f)],)
                            break
                
                objs = [collections.OrderedDict([
                        (k, o.get(k, None))
                        for k in fields
                    ])
                    for o in objs]
                
                typs = [CStruct(
                        types  = tuple([(t.types[t.fields.index(k)] if k in t.fields else CNull()) for k in fields]),
                        fields = fields
                    )
                    for t in typs]
                
                return cjson_unify_list(objs, typs, **kw)
    
    """ Unify Matching Struct Entries """
    if not kw.get('no_coerce_matching', False):
        if (all([isinstance(t, CStruct) for t in typs])
        and len(set([tuple(t.fields) for t in typs])) == 1):
            
            types = []
            
            for i, k in enumerate(objs[0].keys()):
                kobjs = [o[k]       for o in objs]
                ktyps = [t.types[i] for t in typs]
                
                kobjs, ktyp = cjson_unify_list(kobjs, ktyps, **kw)
                
                for j in range(len(objs)):
                    objs[j][k] = kobjs[j]

                types.append(ktyp)
                
            return objs, CStruct(types=tuple(types), fields=tuple(objs[0].keys()))
        
    """ Unify Bools with Ints """
    if not kw.get('no_bool_to_int', False):
        
        if all([isinstance(t, CBool) or isinstance(t, CInt) for t in typs]):
            return [int(o) for o in objs], CInt()
        
    """ Unify Ints with Floats """
    if not kw.get('no_int_to_float', False):
        
        if all([isinstance(t, CFloat) or isinstance(t, CInt) for t in typs]):
            return [float(o) for o in objs], CFloat()

    """ Unify Null with String """
    if not kw.get('no_null_to_str', False):
        
        if all([isinstance(t, CNull) or isinstance(t, CString) for t in typs]):
            return objs, CString()
    
    """ Unify Null with Int """
    if not kw.get('no_null_to_int', False):
        
        if (all([isinstance(t, CNull) or isinstance(t, CInt) for t in typs])
        and all([o >= 0 for o in objs if o != None])):
            
            return [-1 if o is None else o for o in objs], CInt()
    
    """ Unify Null with Bool """
    if not kw.get('no_null_to_bool', False):
        
        if all([isinstance(t, CNull) or isinstance(t, CBool) for t in typs]):
            
            return [False if o is None else o for o in objs], CBool()
    
    """ Unify Null with Float """
    if not kw.get('no_null_to_float', False):
        
        if all([isinstance(t, CNull) or isinstance(t, CFloat) for t in typs]):
            
            return [float('nan') if o is None else o for o in objs], CFloat()
    
    """ Unify Array with Pointer Struct """
    if not kw.get('no_array_to_ptr', False):
        
        if (all([isinstance(t, CArray) for t in typs])
        and len(set([t.length for t in typs])) > 1):
            
            objs = [collections.OrderedDict([('length', len(o)), ('values', o)]) for o in objs]
            typ  = CStruct(types=(CInt(), CPointer(typs[0].type)), fields=tuple(objs[0].keys()))
            
            return objs, typ
    
    """ Throw Error if still non-uniform """
    objlst = []
    
    for st in set(typs):
        for o, t in zip(objs, typs):
            if t == st:
                objlst.append(o)
    
    raise TypeError('Can\'t coerce json objects %s to the same type!' % json.dumps(objlst))
    
class NoObject: pass

""" Convert tagged objects to string representation """
def cjson_repr(typ, obj, name, typenames=set(), typedefs=[], idnt='', **kw):
    
    idnt_by = ('\t' if kw.get('indent_tab', False) else ' ') * kw.get('indent', 4)
    
    """ Basic Types """
    if isinstance(typ, CNull):   name = kw.get('null_type', 'void*')
    if isinstance(typ, CInt):    name = kw.get('int_type', 'long')
    if isinstance(typ, CFloat):  name = kw.get('float_type', 'double')
    if isinstance(typ, CBool):   name = kw.get('bool_type', 'bool')
    if isinstance(typ, CString): name = kw.get('string_type', 'const char*')
    
    """ Pointer Type """
    if isinstance(typ, CPointer):
        subname = name + kw.get('pointer_suffix', '')
        subtype, subdecl, typenames, typedefs = cjson_repr(typ.type, NoObject, subname, typenames, typedefs, **kw)
        name = subtype+'*'
    
    """ Array Type """
    if isinstance(typ, CArray):
        
        subname = name + kw.get('array_suffix', '_entry')
        subtype, subdecl, typenames, typedefs = cjson_repr(typ.type, NoObject, subname, typenames, typedefs, **kw)
        
        if not name in typenames:
            typenames.add(name)
            
            if not kw.get('no_array_count_uppercase', False):
                name_count = (name + kw.get('array_count_suffix', '_count')).upper()
            else:
                name_count = (name + kw.get('array_count_suffix', '_count'))
            
            if kw.get('array_count_define'):
                typedefs.append('#define %s %i' % (name_count, typ.length))
            else:
                typedefs.append('enum { %s = %i };' % (name_count, typ.length))
            
            typedefs.append('typedef ' + subtype + ' ' + name +'[' + name_count + '];')
        
    """ Struct Type """
    if isinstance(typ, CStruct):
        
        subtypes = []
        
        joiner = kw.get('field_infix', '_')

        for t, f in zip(typ.types, typ.fields):
            
            subtype, subdecl, typenames, typedefs = cjson_repr(
                t, NoObject, name + joiner + (f[0].upper() + f[1:] if kw.get('field_capitalize', False) else f), 
                typenames, typedefs, **kw)     
                
            subtypes.append(subtype)
            
        if not name in typenames:
            typenames.add(name)
            typedefs.append(
                'typedef struct {\n' +
                ''.join([idnt_by + t + ' ' + f + ';\n' for t, f in zip(subtypes, typ.fields)]) +
                '} ' + name + ';')
    
    """ No Decl Required """
    if obj is NoObject:
        return name, None, typenames, typedefs
    
    """ Basic Decls """
    if isinstance(typ, CNull):   decl = idnt + kw.get('null_value', 'NULL')
    if isinstance(typ, CInt):    decl = idnt + repr(obj)
    if isinstance(typ, CFloat):  decl = idnt + (kw.get('nan_value', 'NAN') if math.isnan(obj) else repr(obj))
    if isinstance(typ, CBool):   decl = idnt + (
        kw.get('true_value', 'true') if obj else 
        kw.get('false_value', 'false'))
    
    """ String Decls """
    if isinstance(typ, CString):
        
        if obj is None:
            decl = idnt + kw.get('null_value', 'NULL')
        else:
            decl = idnt + repr(obj)
        
        """ Convert single quote strings """
        if decl.strip().startswith('\''):
            decl = decl.replace('"', '\\"')
            decl = decl.replace('\'', '"')
            decl = decl.replace('\\\'', '\'')
 
    """ Pointer Type """
    if isinstance(typ, CPointer):
        
        if obj is None:
            decl = idnt + kw.get('null_value', 'NULL')
        else:
            if type(typ.type) in (CArray, CStruct, CPointer) or kw.get('no_inline_basic', False):
                contents = '\n' + ", \n".join([cjson_repr(typ.type, o, subname, typenames, typedefs, idnt+idnt_by, **kw)[1] for o in obj]) + '\n' + idnt
            else:
                contents = ", ".join([cjson_repr(typ.type, o, subname, typenames, typedefs, '', **kw)[1] for o in obj])
            
            decl = idnt + '(' + subtype + '[]){' + contents + '}'
    
    """ Array Types """
    if isinstance(typ, CArray):
        
        if type(typ.type) in (CArray, CStruct, CPointer) or kw.get('no_inline_basic', False):
            contents = '\n' + ", \n".join([cjson_repr(typ.type, o, subname, typenames, typedefs, idnt+idnt_by, **kw)[1] for o in obj]) + '\n' + idnt
        else:
            contents = ", ".join([cjson_repr(typ.type, o, subname, typenames, typedefs, '', **kw)[1] for o in obj])
        
        decl = idnt + '{' + contents + '}'
            
    """ Struct Type """
    if isinstance(typ, CStruct):
        
        joiner = kw.get('field_infix', '_')
        
        if kw.get('no_designated', False):
            decl = (idnt + '{\n' 
               + ', \n'.join([
               cjson_repr(t, o, name + joiner + (f[0].upper() + f[1:] if kw.get('field_capitalize', False) else f), typenames, typedefs, idnt + idnt_by, **kw)[1] 
               for o, t, f in zip(obj.values(), typ.types, typ.fields)])
               + '\n' + idnt + '}')
        else:
            decl = (idnt + '{\n' 
               + ', \n'.join([
                idnt + idnt_by + '.' + f + ' = ' + 
                cjson_repr(t, o, name + joiner + (f[0].upper() + f[1:] if kw.get('field_capitalize', False) else f), typenames, typedefs, idnt + idnt_by, **kw)[1].strip() 
                for o, t, f in zip(obj.values(), typ.types, typ.fields)])
               + '\n' + idnt + '}')
            
    """ Return """
    return name, decl, typenames, typedefs
    
    
""" Construct header and source files for representation of tagged JSON object """
def cjson2c(cjson, **kw):
    
    obj, typ = cjson
    
    header, source = '', ''
    type, decl, typenames, typedefs = cjson_repr(typ, obj, kw.pop('type'), **kw)
        
    for td in typedefs:
        header += '\n' + td + '\n'

    header += '\n' + 'extern ' + type + ' ' + kw.get('variable') + ';' + '\n'
    source += '\n' + type + ' ' + kw.get('variable') + ' = ' + decl + ';' + '\n'
    
    return header, source
    
""" Parse JSON and convert to C header and source files """
def json2c_file(filename, **kw):
    
    if kw.get('camel_case'):
        kw['field_infix'] = ''
        kw['array_suffix'] = 'Entry'
        kw['array_count_suffix'] = 'count'
        kw['field_capitalize'] = True
        kw['key_fix_replacement'] = ''
        
    """ Open JSON """
    with open(filename, 'r') as f:
    
        obj = json.load(f, object_pairs_hook=collections.OrderedDict)
        obj = cjson_unify(obj2cjson(obj, **kw), **kw)
    
    """ Generate String """
    
    typename = os.path.splitext(os.path.split(filename)[-1])[0]
    
    if not 'type'     in kw: kw['type']     = typename
    if not 'variable' in kw: kw['variable'] = typename + kw.get('field_infix', '_') + ('Object' if kw.get('field_capitalize', False) else 'object')
    
    header, source = cjson2c(obj, **kw)

    """ Additional Wrapping """
    headerfile = kw.get('header', os.path.splitext(filename)[0] + '.h')
    sourcefile = kw.get('source', os.path.splitext(filename)[0] + '.c')
    
    if not kw.get('no_math',    False): header = '#include <math.h>\n' + header
    if not kw.get('no_stdbool', False): header = '#include <stdbool.h>\n' + header
    if not kw.get('no_stdlib',  False): header = '#include <stdlib.h>\n' + header
    
    if not kw.get('no_guard', False):
    
        headerguard = os.path.splitext(os.path.split(headerfile)[1])[0] + '_h'
        
        if not kw.get('no-guard_uppercase', False): headerguard = headerguard.upper()

        header = (
            '#ifndef ' + headerguard + '\n'
          + '#define ' + headerguard + '\n\n'
          + header
          + '\n#endif\n')
    
    if not kw.get('no_include', False):
        source = '#include "' + headerfile + '"\n' + source + '\n'
    
    """ Output to file """
    with open(headerfile, 'w') as f: f.write(header)
    with open(sourcefile, 'w') as f: f.write(source)
    
""" Command line program """
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', type=str, help='input JSON file')
    parser.add_argument('-v', '--variable', type=str, help='name of C variable to create')
    parser.add_argument('-t', '--type',     type=str, help='name of base C type to create')
    parser.add_argument('-c', '--camel-case', action='store_true', help='a shortcut that sets several options so that nice output is produced for camel case keys')
    parser.add_argument('-hdr', '--header',   type=str, help='name of header file to output')
    parser.add_argument('-src', '--source',   type=str, help='name of source file to output')
    
    parser.add_argument('-i',  '--indent', type=int, help='indentation amount')
    parser.add_argument('-it', '--indent-tab', action='store_true', help='indent using tabs instead of spaces')
    
    parser.add_argument('--no-guard', type=str, help='don\'t include a header guard')
    parser.add_argument('--no-stdlib', type=str, help='don\'t include the stdlib header')
    parser.add_argument('--no-stdbool', type=str, help='don\'t include the stdbool header')
    parser.add_argument('--no-math', type=str, help='don\'t include the maths header')
    parser.add_argument('--no-include', type=str, help='don\'t include the header from the source file')
    
    parser.add_argument('--no-guard-uppercase', action='store_true', help='don\'t set the header guard to upper case')    
    parser.add_argument('--no-designated', action='store_true', help='don\'t use designated initialisers')
    parser.add_argument('--no-inline', action='store_true', help='don\'t print on a single line basic types in arrays')
    
    parser.add_argument('--array-suffix', type=str, help='type name suffix for inner array types, default is \'_entry\'')
    parser.add_argument('--pointer-suffix', type=str, help='type name suffix for inner pointer types')
    parser.add_argument('--field-infix', type=str, help='string to join field types with parents, default is \'_\'')    
    parser.add_argument('--field-capitalize', action='store_true', help='capitalize field names when using them in types')
    
    parser.add_argument('--array-count-suffix', type=str, help='string suffixed for array counts, default is \'_count\'')
    parser.add_argument('--array-count-define', action='store_true', help='use define instead of enum to declare array counts')
    parser.add_argument('--no-array-count-uppercase', action='store_true', help='don\'t set the array count values to upper case')
    
    parser.add_argument('--null-type', type=str, help='type name for null types, default is \'void*\'')
    parser.add_argument('--int-type', type=str, help='type name for int types, default is \'long\'')
    parser.add_argument('--float-type', type=str, help='type name for float types, default is \'double\'')
    parser.add_argument('--bool-type', type=str, help='type name for bool types, default is \'bool\'')
    parser.add_argument('--string-type', type=str, help='type name for string types, default is \'const char*\'')
    
    parser.add_argument('--null-value',  type=str, help='value for null, default is \'NULL\'')
    parser.add_argument('--true-value',  type=str, help='value for true, default is \'true\'')
    parser.add_argument('--false-value', type=str, help='value for false, default is \'false\'')
    parser.add_argument('--nan-value',   type=str, help='value for nan, default is \'NAN\'')

    parser.add_argument('--no-fix-int-keys', action='store_true', help='don\'t fix integer keys by converting them to strings')
    parser.add_argument('--no-fix-invalid-keys', action='store_true', help='don\'t fix keys with invalid characters')
    parser.add_argument('--no-fix-keyword-keys', action='store_true', help='don\'t fix keys which are C keywords')
    parser.add_argument('--key-fix-replacement', type=str, help='invalid key replacement character, default is \'_\'')
    
    parser.add_argument('--no-null-to-ptr',   action='store_true', help='don\'t coerce null and pointer types together')
    parser.add_argument('--no-null-to-int',   action='store_true', help='don\'t coerce null and integer types together')
    parser.add_argument('--no-null-to-float', action='store_true', help='don\'t coerce null and float types together')
    parser.add_argument('--no-null-to-bool',  action='store_true', help='don\'t coerce null and bool types together')
    parser.add_argument('--no-null-to-str',   action='store_true', help='don\'t coerce null and string types together')
    parser.add_argument('--no-null-to-obj',   action='store_true', help='don\'t coerce null and object types together')
    parser.add_argument('--no-bool-to-int',   action='store_true', help='don\'t coerce bool and int types together')
    parser.add_argument('--no-int-to-float',  action='store_true', help='don\'t coerce int and float types together')
    parser.add_argument('--no-array-to-ptr',  action='store_true', help='don\'t coerce array and pointer types together')
    parser.add_argument('--no-coerce-missing', action='store_true', help='don\'t coerce missing object entries')
    parser.add_argument('--no-coerce-matching', action='store_true', help='don\'t coerce matching object entries')
    
    json2c_file(**{ k : v for k, v in parser.parse_args().__dict__.items() if v != None})
    
if __name__ == '__main__':
    main()
    