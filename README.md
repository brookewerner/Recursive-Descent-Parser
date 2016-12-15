# Recursive-Descent-Parser
C code for a recursive descent parser

Parses and prints a parse tree for mathematical expressions that follow the grammar.

Project for CSC 173 Computation & Formal Systems with Professor George Ferguson.

-----

Grammar:

    ‘e’ stands for the epsilon empty string

    <E>→<T><A>

    <A>→+<T><A>|-<T><A>|e

    <T>→<F><B>

    <B>→*<F><B>|/<F><B>|e

    <F>→<E>|<N>

    <N>→<D><C>

    <C>→<N>|e

    <D>→0|1|2|3|4|5|6|7|8|9

-----

Compile and run the code and follow prompt to enter an expression according to the grammar (accepts mathematical expressions containing the digits 0 through 9 and the operands +, -, /, * as well as expressions inside of parentheses).

-----

References:
 
> Foundations of Computer Science by Al Aho and Jeff Ullman. A copy of this book can be found here: http://infolab.stanford.edu/~ullman/focs.html
  
> Lectures from CSC 173 Computation & Formal Systems by Professor George Ferguson

-----

Collaborators:

Brooke Werner

Alana Zakroczemski

Sooyoung Kim
