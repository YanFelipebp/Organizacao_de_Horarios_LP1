# 🕐 Organizador de Horários Escolares com Grafos

Projeto final da disciplina de **Linguagem de Programação I**, que implementa em C uma solução para o problema de **alocação de horários de turmas com conflitos**, utilizando **representação de grafos**, **algoritmo guloso com ordenação por grau (Welsh-Powell)** e aplicando conceitos de **structs, matrizes dinâmicas, arquivos, ponteiros e recursão**.

---

## 👨‍💻 Equipe

- **Yan Felipe Buceles Pinto**
- **Ricardo Antonio Soares Ferreira**

---

## 📝 Enunciado do Projeto

### 🎯 Objetivo

Criar um programa que leia turmas e seus conflitos (turmas que compartilham alunos), represente o problema como um grafo, e determine a menor quantidade de horários possível para que **nenhuma turma com conflito tenha aula no mesmo horário**.

### 📘 Contexto do Problema

Uma escola está organizando os horários de suas turmas. Algumas turmas têm alunos em comum, e por isso **não podem ser alocadas no mesmo horário**. A tarefa é **colorir o grafo** dessas turmas com o menor número de cores (horários), garantindo que vértices conectados (turmas com conflito) tenham cores diferentes.


---

## ⚙️ Especificações Técnicas

### ✔️ Entrada

O programa lê um arquivo no formato `.txt`, com:

 1-  N: Número total de turmas.
 
 2- Lista de conflitos entre turmas: Cada par de turmas com alunos em comum.

 
- `p edge V E`: define o número de vértices (turmas) e arestas (conflitos)
- `e X Y`: conflito entre as turmas X e Y (elas não podem ter aula no mesmo horário)

### ✔️ Saída Esperada

- O menor número de horários (cores) utilizados
- Lista de quais turmas estão em cada horário

📌 Exemplo de Saída:
```
=== RESULTADO DA ALOCACAO DE HORARIOS ===
Total de horarios necessarios: 3

Agrupamento por horario:
Horario 1: 1 4
Horario 2: 2 5
Horario 3: 3 6
```

---

## ✨ Funcionalidades Implementadas

- Leitura estruturada do arquivo de entrada
- Representação do grafo por **matriz de adjacência dinâmica**
- Cálculo do **grau de cada turma** (quantidade de conflitos)
- **Ordenação por grau** (Welsh-Powell)
- Algoritmo guloso de coloração dos vértices
- Impressão da alocação final por horário
- Uso de **recursão** para mostrar graus das turmas
- Alocação e liberação dinâmica de memória

---

## 💡 Lógica do Algoritmo

1. **Leitura do arquivo** e construção da matriz de adjacência com conflitos.
2. **Cálculo dos graus** de cada turma.
3. **Ordenação decrescente** das turmas por grau (quanto mais conectada, mais cedo será colorida).
4. Aplicação de **algoritmo guloso**:
   - Atribui à turma o **menor horário** disponível que não está sendo usada por nenhum de seus vizinhos (turmas em conflito).
5. Impressão agrupada das turmas por horário.

---

## 🔁 Recursos utilizados

- `struct Turma`: para armazenar número da turma, grau e horário
- `int **matriz`: matriz de adjacência dinâmica
- Funções com ponteiros e uso de `malloc`, `calloc`, `free`
- Recursão na função `mostrarGrausRecursivo()`
- Bubble Sort para ordenação das turmas por grau

---

## ✅ Conclusão

Este projeto apresenta uma solução prática e eficiente para o problema de alocação de horários escolares com base em conflitos entre turmas, aplicando diversos conceitos estudados na disciplina de **Linguagem de Programação I**, tais como:

- Manipulação de arquivos
- Alocação dinâmica de memória
- Ponteiros e structs
- Algoritmos de ordenação
- Recursão
- Uso de **comandos básicos da linguagem C**, como:
  - Laços de repetição (`for`, `while`)
  - Comandos condicionais (`if`, `else`)
  - Declaração e chamada de funções
  - Vetores e matrizes
  - Passagem de parâmetros por referência

Esses recursos foram integrados em um programa modular e funcional, capaz de resolver um problema real de forma clara, estruturada e didática.


   







