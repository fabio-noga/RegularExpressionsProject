# RegularExpressionsProject
[LabProg Project 1](https://github.com/fabio-noga/NewLanguageProject)
(available April 8)
*by* Fábio Nogueira 201706376 e Luís Trinta 201707192.

A leitura do programa pode ser feita da forma
>./newLanguage

para ler a partir do stin ou
>./newLanguage test.txt

para ler a partir de um ficheiro 

## Exemplos de utilização
### ATRIBUIÇÃO, ADIÇÃO, SUBTRAÇÃO ,MULTIPLICAÇÃO E DIVISÃO
##### Input
```
a=42  ;
a = 8+a;
a=a-  10;
a =a*a;
a= a/ 100;
```
### READ
##### Input
```
ler(a);
```
##### Output
```
Ler variável a: _
```

### WRITE
##### Input
```
a=16;
escrever(a);
escrever(42);
escrever(b);
```
##### Output
```
Variável a: 16
Número: 42
Variavel b não declarada
```
### LABEL
##### Input
```
label z1
```
neste caso a label z1 será adicionado à hashtable de labels.

### GOTO
##### Input
```
goto z1;
goto z2;
```
z1 existindo, o programa continua onde esta label se encontra.
z2 não existindo, o programa devolve
##### Output
```
Label Inexistente
```
### IF
##### Input
```
a=42;
if a escrever(a);
a=0;
if a escrever(a);
```
##### Output
```
>Variavel a: 42
```
***

## EXEMPLOS DE PROGRAMAS
### FOR LOOP
##### Input
```
ler(z);
label z1;
z = z - 1;
escrever(z);
if z goto z1;
quit;
```
##### Output
```
Ler variavel z: 5
Variavel z: 4
Variavel z: 3
Variavel z: 2
Variavel z: 1
Variavel z: 0
```
### FACTORIAL
#### Input
```

ler(i)
k = 1
label l1
k = k*i
i=i-1
if i goto l1
escrever(k)
quit;

```
#### Output
```
Ler variavel i: 6
Variavel k: 720

```
### GERAL
##### Input
```
ler(k);
p = 6 + k;
escrever(p);
if p goto L1;
p = p/2;
escrever(p);
goto L2;
label L1;
p = 2*p;
escrever(p);
p=1;
if p escrever(p);
label L2;
escrever(k);
escrever(42);
quit;

z=42;
escrever(z);
```
##### Output
```
Ler variavel k: 5
Variavel p: 11
Variavel p: 22
Variavel p: 1
Variavel k: 5
Número: 42
```

## Estrutura 
```
structs.h
└── proglist.h
    ├── proglist.c
    └── varhash.h
         ├── varhash.c
         └── proj.h
             ├── use_proj.c
             └── proj.c
```
