import re

#Expresion regular para usar en las variables
casovar = r'^DEFINE\s+\$_[A-Z][a-zA-Z]*$'

#Expresion regular para operaciones
casodp = r'^DP\s+\$_[A-Z][a-zA-Z]*\s+(ASIG|[\+\*\>\==])'

#Expresion regular para string
dpstr = r'#(.*?)#'

#Expresion regular para enteros
dpint = r'^\d+$'

#Expresion regular para mostrar
casomostrar = r'^MOSTRAR\((\$_[A-Z][a-zA-Z]*)\)$'

#Expresion regular if
condicionif = r'^if\((\$_[A-Z][a-zA-Z]*)\)\s*\{$'
ifnose=r'^\s*if\s*\(\$_[A-Z][a-zA-Z]*\)\s*\{'
ifespacio = r'^if\s*\(\s*\$_[A-Z][a-zA-Z]*\s*\)\s*\{$'
dentroif= r'^if\s*\((.*?)\)'

#Expresion regular que usare para sacar lo entre los parentesis de if
ifespace=r'if\s*\((.*?)\)'

#Expresion regular variobles en if
casovarif = r'^\s*DEFINE\s+\$_[A-Z][a-zA-Z]*$'

#Expresion regular para operacion en if
casodpif = r'^\s*DP\s+\$_[A-Z][a-zA-Z]*\s+(ASIG|[\+\*\>\==])'

#Expresion regular para mostrar en if
casomostrarif = r'^\s*MOSTRAR\((\$_[A-Z][a-zA-Z]*)\)$'

#Expresion regular que usare para sacar lo entre los parentesis de mostrar
varmos = r'MOSTRAR\((.*?)\)'

#Expresion regular para else 
casoelse =  r'^\s*\}\s*else\s*\{'

#Expresion regular para los cierres de ciclos
cierrellave = r'^}\s*$'

#crea diccionario bacio 
variables = {}

with open('codigo.txt', 'r') as f:
    lineas = f.readlines()

arch_s = 'output.txt'
with open(arch_s, 'w') as f:
    f.write("")


#---------------------------------------------------------------------------------------------------------------------------- 
'''
def sonvariables(lineas, variables):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
...
***
No retorna nada
***
Funcion que revisa todas las lineas del codigo, si cumple con el patron para ser variable revisa si esta en el diccionario variables,
si no esta, guarda la clave como variable, en caso de estar en variables imprime por pantalla que la variable ya esta definida
si encuentra un if llamara a la funcion saltoespaciovar.
si encuentra que cumple con una operacion, else, mostrar, una llave cerrando "}", pasara a la siguiente linea
en caso de no cumplir con nada de esto imprimira: "Mala Sintaxis en la línea (N° de la linea)"
 
'''
#---------------------------------------------------------------------------------------------------------------------------- 
 


#---------------------------------------------------------------------------------------------------------------------------- 
def sonvariables(lineas, variables):
    i = 0
    while i < len(lineas):
        if re.match(casovar, lineas[i]):
            a = lineas[i]
            _, variable = a.split()
            if variable in variables:
                print("La variable de nombre " + variable + " ya se encuentra definida en la línea " + str(i + 1) + '\n')
                break
            else:
                variables[variable] = None

        elif re.match(condicionif, lineas[i]) or re.match(ifespacio, lineas[i]):
            i = saltoespaciovar(lineas, i)

        elif re.match(casodp, lineas[i]) or re.match(casoelse, lineas[i]) or re.match(casomostrar, lineas[i]) or re.match(cierrellave, lineas[i]):
            pass

        else:
            print("Mala Sintaxis en la línea " + str(i + 1) + "\n")
        i += 1
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def saltoespacio(lineas, comun):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : comun, indice compartido por varias funciones, el cual se va actualizando y funciona como contador.
...
***
No retorna nada
***
Esta funcion si encuentra un if saltara a la linea en la que dicho if termina y retorna el numero de dicha linea (la linea del 
else correspondiente).
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def saltoespacio(lineas, comun):
    i = comun + 1
    nvanidado = 1  
    while i < len(lineas):
        linea = lineas[i].strip()

        if re.match(condicionif, linea) or re.match(ifespacio, linea) or re.match(ifespace, linea):
            nvanidado +=1


        if re.match(casoelse, linea):
            nvanidado -= 1  
            if nvanidado == 0:
                return i+1  

        i += 1
    return i
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def saltoespaciovar(lineas, comun):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : comun, indice compartido por varias funciones, para que asi en muchos casos sigan desde dicho indice.
...
***
Retorna i, un entero 
***
Esta funcion si encuentra un if saltara a la linea en la que termina el else correspondiente a dicho if y retorna el numero 
de dicha linea.
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def saltoespaciovar(lineas, comun):
    i = comun + 1
    nvanidado = 1  
    while i < len(lineas):
        linea = lineas[i].strip()

        if re.match(condicionif, linea) or re.match(ifespacio, linea) or re.match(ifespace, linea):
            nvanidado += 1  

        if re.match(cierrellave, linea):
            nvanidado -= 1  
            if nvanidado == 0:
                break  

        i += 1
    return i
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def opereichon(lineas, variables):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
...
***
No retorna nada
***
Revisa si las lineas cumplen con el patron de operaciones y desarrolla dichas operaciones
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def opereichon(lineas, variables):
    i = 0
    while i < len(lineas):
        if re.match(casodp, lineas[i]):
            a = lineas[i].split()
            variable = a[1]
            operacion = a[2]

            if variable not in variables:
                print("Variable no definida en la línea " + str(i + 1) + '\n')
                break

            if operacion == 'ASIG':
                val = a[3:]
                cadena = ' '.join(val)

                if re.match(dpstr, cadena):
                    substring = cadena[1:-1]
                    variables[variable] = substring
                elif re.match(dpint, a[3]):
                    variables[variable] = int(a[3])
                elif a[3] == True:
                    variables[variable] = True
                elif a[3] == False:
                    variables[variable] = False
                else:
                    break

            elif operacion == '*':  # solo entero
                mult1 = variables.get(a[3])
                mult2 = variables.get(a[4])
                if isinstance(mult1, int) and isinstance(mult2, int):
                    variables[variable] = mult1 * mult2
                else:
                    print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.")
                    break

            elif operacion == '==':  # no bool
                val1 = variables.get(a[3])
                val2 = variables.get(a[4])
                if isinstance(val1, int) and isinstance(val2, int) or isinstance(val1, str) and isinstance(val2, str):
                    if val1 == val2:
                        variables[variable] = True
                    else: 
                        variables[variable] = False
                        
                else:
                    print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.")
                    break
                    

            elif operacion == '>':  # solo entero
                mult1 = variables.get(a[3])
                mult2 = variables.get(a[4])
                if isinstance(mult1, int) and isinstance(mult2, int):
                    variables[variable] = True if mult1 > mult2 else False
                else:
                    print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.")
                    break

            elif operacion == '+':
                val1 = variables.get(a[3])
                val2 = variables.get(a[4])
                if isinstance(val1, str) and isinstance(val2, str):
                    variables[variable] = val1 + val2
                elif isinstance(val1, int) and isinstance(val2, int):
                    variables[variable] = val1 + val2
                elif isinstance(val1, str) and isinstance(val2, int):
                    variables[variable] = val1 + str(val2)
                elif isinstance(val1, int) and isinstance(val2, str):
                    variables[variable] = str(val1) + val2
                else:
                    print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.")
                    break

        i += 1
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def mostrar(lineas, variables):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
...
***
No retorna nada
***
Evalua si las lineas cumplen con el patron de mostrar, de ser el caso si la variable esta definida escribe el valor de dicha
variable en el archivo, sino imprime variable no definida.
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def mostrar(lineas, variables):
    i = 0
    while i < len(lineas):
        if re.match(casomostrar, lineas[i]):
            a = lineas[i]
            b = re.match(varmos, a)
            if b:
                c = b.group(1)
                if c in variables:
                    with open(arch_s, 'a') as f:
                        f.write(str(variables[c]) + '\n')
                else:
                    print("Variable no está definida")

        i += 1
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def evaluar_condicional(lineas, variables,i=0):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
Parametro 3 : i=0, una variable que se crea aqui mismo y se usa de contador, es un entero 
...
***
Tipo de Retorno o None
***
Revisa si cumple con algun patron creado para if, si cumple revisa que la variable asociada sea booleana, si cumple dependiendo del
valor llamara otras funciones leerelif o saltoespacio y leerelse.
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def evaluar_condicional(lineas, variables,i=0):
    while i < len(lineas):
        a = lineas[i].strip()
        if re.match(condicionif, a) or re.match(ifespacio, a) or re.match(ifnose, a):
            b = re.search(condicionif, a) 
            c = re.search(ifespace, a)
            e=re.search(dentroif, a)     
            if b or c or e:
                if b:
                    d = b.group(1)
                elif c:
                    d = c.group(1)
                elif e:
                    d = c.group(1)


                val = variables.get(d)
                if val == True or val == False:
                    if val == True:
                        i = i + 1 
                        i = leerelif(lineas, variables, i)
                        break

                    elif val== False:
                        i = saltoespacio(lineas, i,)  
                        i=leerelse(lineas, variables, i)
                else:
                    print("La operación condicional en la línea " + str(i + 1) + " es incompatible con el tipo de dato ife"  + '\n')
                    break

        i += 1
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def leerelse(lineas, variables,comun):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
Parametro 3 : comun, indice compartido por varias funciones, para que asi en muchos casos sigan desde dicho indice.
...
***
Retorno i, el cual es entero usado como contador 
***
Resive la linea siguiente al else si es que el programa entro en el, evalua si las lineas siguentes cumplen con el lenguaje
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def leerelse(lineas, variables,comun):
    i = comun
    while i < len(lineas):
        linea = lineas[i].strip()
        if re.match(cierrellave, linea):
            break
        elif re.match(condicionif, linea) or re.match(ifespacio, linea):
            evaluar_condicional(lineas, variables, i)
            break

        elif re.match(casovarif, linea):
            sonvariablesif(linea, variables, i)

        elif re.match(casodpif, linea):
            opereichonif(linea, variables, i)

        elif re.match(casomostrarif, linea):
            mostrarif(linea, variables, i)
            
        i += 1
    return i
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def leerelif(lineas, variables, comun):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
Parametro 3 : comun, indice compartido por varias funciones, para que asi en muchos casos sigan desde dicho indice.
...
***
Retorno i, el cual es entero usado como contador 
***
Resive la linea siguiente al if si es que el programa entro en el, evalua si las lineas siguentes cumplen con el lenguaje
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def leerelif(lineas, variables, comun):
    i = comun
    while i < len(lineas):
        linea = lineas[i].strip()
        if re.match(casoelse, linea):
            break
        elif re.match(condicionif, linea) or re.match(ifespacio, linea):
            evaluar_condicional(lineas, variables, i)
            break

        elif re.match(casovarif, linea):
            sonvariablesif(linea, variables, i)

        elif re.match(casodpif, linea):
            opereichonif(linea, variables, i)

        elif re.match(casomostrarif, linea):
            mostrarif(linea, variables, i)


        else:
            print("Mala Sintaxis en la línea ",(i+1))
            break


        i += 1
    return i
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def sonvariablesif(linea, variables, comun):
***
Parametro 1 : linea, sera una linea especifica, la cual es dada por otra funcion
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
Parametro 3 : comun, indice compartido por varias funciones, para que asi en muchos casos sigan desde dicho indice.
...
***
Retorno i, el cual es entero usado como contador 
***
Revisa si la linea cumple el patron para las variables en if si encuentra lineas mal escritas lo imprime, y si cumplen con 
casos bien escritos no asociados a variable (operaciones, condicionales, etc) pasa de ellas.
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def sonvariablesif(linea, variables, comun):
    i = comun

    if re.match(casovarif, linea):
        _,variable=linea.split()

        if variable in variables:
            print("La variable de nombre " + variable + " ya se encuentra definida en la línea " + str(i+ 1) + " de los ifs"+'\n')

        else:
            variables[variable] = None

    elif re.match(casoelse, linea):
        print("La línea " + str(i + 1) + " no está bien escrita.\n")


    elif re.match(casodpif, linea) or re.match(casoelse, linea) or re.match(casomostrarif, linea) or re.match(condicionif, linea) or re.match(ifespacio, linea):
        pass

    else:
        print("La línea " + str(i + 1) + " no está bien escrita.\n")

    i += 1
    return i
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def opereichonif(linea, variables, comun):
***
Parametro 1 : linea, sera una linea especifica, la cual es dada por otra funcion
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
Parametro 3 : comun, indice compartido por varias funciones, para que asi en muchos casos sigan desde dicho indice.
...
***
Tipo de Retorno o None
***
Revisa si la linea cumple el patron para las operaciones en if, y las lleva a cabo sino imprime el fallo respectivo
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
def opereichonif(linea, variables, comun):
    i = comun
    a = lineas[i].strip()

    if re.match(casodpif, linea):
        a = linea.split()
        variable = a[1]
        operacion = a[2]

        if variable not in variables:
            print("Variable no definida en la línea " + str(i + 1) + '\n')

        if operacion == 'ASIG':
            val = a[3:]
            cadena = ' '.join(val)

            if re.match(dpstr, cadena):
                substring = cadena[1:-1]
                variables[variable] = substring
            elif re.match(dpint, a[3]):
                variables[variable] = int(a[3])
            elif a[3] == True:
                variables[variable] = True
            elif a[3] == False:
                variables[variable] = False
            else:
                print("La línea " + str(i + 1) + " no está bien escrita.\n")

                

        elif operacion == '*':  # solo entero
            mult1 = variables.get(a[3])
            mult2 = variables.get(a[4])
            if isinstance(mult1, int) and isinstance(mult2, int):
                variables[variable] = mult1 * mult2
            else:
                print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.\n")
                pass

        elif operacion == '==':  # no bool
            val1 = variables.get(a[3])
            val2 = variables.get(a[4])
            if isinstance(val1, str) and isinstance(val2, str) or isinstance(val1, str) and isinstance(val2, str) :
                if val1 ==val2:
                    variables[variable] = True
                else:
                    variables[variable] = False
            else:
                print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.\n")

        elif operacion == '>':  # solo entero
            mult1 = variables.get(a[3])
            mult2 = variables.get(a[4])
            if isinstance(mult1, int) and isinstance(mult2, int):
                variables[variable] = True if mult1 > mult2 else False
            else:
                print("La operación DP en la línea " + str(i + 1) + " es incompatible al tipo de dato.\n")


        elif operacion == '+':
            val1 = variables.get(a[3])
            val2 = variables.get(a[4])
            if isinstance(val1, str) and isinstance(val2, str):
                variables[variable] = val1 + val2
            elif isinstance(val1, int) and isinstance(val2, int):
                variables[variable] = val1 + val2
            elif isinstance(val1, str) and isinstance(val2, int):
                variables[variable] = val1 + str(val2)
            elif isinstance(val1, int) and isinstance(val2, str):
                variables[variable] = str(val1) + val2
            else:
                print("La operación DP " + str(i + 1) + " es incompatible al tipo de dato. ")
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 
'''
def mostrarif(linea, variables, comun):
***
Parametro 1 : lineas, seran las lineas del archivo
Parametro 2 : variables, el diccionario que se creo inicialmente vacio, pero se modificara
Parametro 3 : comun, indice compartido por varias funciones, para que asi en muchos casos sigan desde dicho indice.
...
***
Tipo de Retorno o None
***
Evalua si las lineas cumplen con el patron de casomostrarif, de ser el caso si la variable esta definida escribe el valor de dicha
variable en el archivo, sino imprime variable no definida.
'''
#---------------------------------------------------------------------------------------------------------------------------- 

#---------------------------------------------------------------------------------------------------------------------------- 

def mostrarif(linea, variables, comun):
    i = comun
    if re.match(casomostrarif, linea):
        b = re.match(varmos, linea)
        if b:
            c = b.group(1)
            if c in variables:
                with open(arch_s, 'a') as f:
                    f.write(str(variables[c]) + '\n')
            else:
                print("Variable no definida en la línea " + str(i + 1) + '\n')

    i += 1
#---------------------------------------------------------------------------------------------------------------------------- 


sonvariables(lineas, variables)
opereichon(lineas, variables)
evaluar_condicional(lineas, variables)
mostrar(lineas, variables)


