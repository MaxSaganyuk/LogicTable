# LogicTable
CLI app that calculates logical equations and creates resulting logic tables. Uses my stringB for tracking specific chars in the string

## How to use?

After running .exe file in the terminal you enter the equation to be calculater.

Variables are one character long. Everything that is not a variable is an operator (also except whitespace ' '). 

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

<img src="readMe\1.png"></img>

