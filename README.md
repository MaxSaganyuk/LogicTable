# LogicTable
CLI app that calculates logical equations and creates resulting logic tables. Uses my stringB for tracking specific chars in the string

## How to use?

After running .exe file in the terminal you enter the equation to be calculated.

Variables are one character long. Everything that is not an operator is a variable (also except whitespace ' '). 

Avalible operators include:

| Operator       | Char  | Tyoe    |
|----------------|-------|---------|
| Negation/Not   | !     | Unary   |
| Parentheses    | ( )   | Special |
| Conjuntion/And | &     | Binary  |
| Exclusive Or   | ^     | Binary  |
| Disjunction/Or | \|    | Binary  |
| Implication    | >     | Binary  |
| Equivalence    | =     | Binary  |

Sorted from top to bottom by priority

Example: 

Is equivalence of a and b and inverted xor between a and b are the same thing (are equivalent) for every possible a and b

<img src="readMe\1.png"></img>

