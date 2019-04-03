# NewLanguageProject
[LabProg Project 1](https://github.com/fabio-noga/NewLanguageProject)
*by* @fabio-noga *and* @luistrinta

##Exemplos de utilização
#ATRIBUIÇÃO, ADIÇÃO, SUBTRAÇÃO ,MULTIPLICAÇÃO E DIVIZÃO
```
a=42  ;
a = 8+a;
a=a-  10;
a =a*a;
a= a/ 100;
```
#READ
```
ler(a);
```
>Ler variável a: _

#WRITE
```
a=16;
escrever(a);
escrever(42);
escrever(b);
```
>Variável a: 16
>Número: 42
>Variavel b não declarada

#LABEL
```
label z1
```
neste caso a label z1 será adicionado à hashtable de labels.

#GOTO
```
goto z1;
goto z2;
```
z1 existindo, o programa continua onde esta label se encontra.
z2 não existindo, o programa devolve
>Label Inexistente

#IF
```
a=42;
if a escrever(a);
a=0;
if a escrever(a);
```
>Variavel a: 42

***

##EXEMPLOS DE PROGRAMAS
#FOR LOOP
```
ler(z);
label z1;
z = z - 1;
escrever(z);
if z goto z1;
quit;
```
>Ler variavel z: *5*
>Variavel z: 4
>Variavel z: 3
>Variavel z: 2
>Variavel z: 1
>Variavel z: 0

##GERAL
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
>Ler variavel k: *5*
>Variavel p: 11
>Variavel p: 22
>Variavel p: 1
>Variavel k: 5
>Número: 42
