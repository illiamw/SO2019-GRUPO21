
# Cálculo do numero Pi
## SO2019-GRUPO21
### Colabores:
- Bruner
- Cleyton
- William


## Cálculo do numero pi
A motivação para o calculo do numero pi neste trabalho, tem como alvo analisar o desempenho de desenvolvimento sequencial e paralela dos algoritmos citados na secção Algoritmos, através disso utiliza iterações N = 10⁹ com resultados apresentados com 6 casas decimais. (averiguar funcionamento).

## Algoritmos
- Gauss-Legendre
- Borwein
- Monte Carlo

## Black Scholes (Monte Carlo)

Neste algoritmo também analisaremos seu desempenho sequecial e paralelo. 
Sobre o algoritmo, este elaborado por dois cientistas chamados Fisher Black e Myron Scholes, que adaptaram
uma fórmula física para descrever um fenômeno financeiro que é a precificação de
derivativos. Este modelo foi proposto pela primeira vez em 1973, e fez seus criadores
ganharem o prêmio Nobel de 1997 (http://pt.wikipedia.org/wiki/Black-Scholes).



## Instrução de compilação e execução

A execução a seguir conometrica a execução dos algoritmos servindo como paramentro para analise de eficiencia das abordagens sequencial e paralela.

## Sequencial
### Gauss-Legendre
Compilação
```bash
gcc GlSeq.c -o GlSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "%e" ./GlSeq.o < entrada_pi.txt > saida_pi.txt
```
### Borwein
Compilação
```bash
gcc BorSeq.c -o BorSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "\n%e" ./BorSeq.o < entrada_pi.txt > saida_pi.txt
```

### Monte Carlo
Compilação
```bash
gcc MontSeq.c -o MontSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "\n%e" ./MontSeq.o < entrada_pi.txt > saida_pi.txt
```
### Black Scholes
Compilação
```bash
gcc BlackSeq.c -o BlackSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "%e" ./BlackSeq.o < entrada_blackscholes.txt > saida_blackscholes.txt
```

## Paralelo
### Gauss-Legendre
Compilação
```bash
gcc GlSeq.c -o GlSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "%e" ./GlSeq.o < entrada_pi.txt > saida_pi.txt
```
### Borwein
Compilação
```bash
gcc BorSeq.c -o BorSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "\n%e" ./BorSeq.o < entrada_pi.txt > saida_pi.txt
```

### Monte Carlo
Compilação
```bash
gcc MontSeq.c -o MontSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "\n%e" ./MontSeq.o < entrada_pi.txt > saida_pi.txt
```
### Black Scholes
Compilação
```bash
gcc BlackSeq.c -o BlackSeq.o  -lm
```
Execução
```bash
/usr/bin/time -f "%e" ./BlackSeq.o < entrada_blackscholes.txt > saida_blackscholes.txt
```

Obs: Comando '-lm' fixa as funções da biblioteca math.h

