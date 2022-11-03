# BlockScript

Blockscript is a general purpose scripting language which can be used to write Blockchain applications.

## Grammar Backus-Naur-Form

```
<expression> ::= <equality> | <tenary> ;
<tenary> ::= <equality> "?" <expression> ":" <expression> ;
<equality> ::= <comparison> (("==" | "!=") <comparison>)* ;
<comparison> ::= <term> ((">" | "<" | "<=" | ">=") <term>)* ;
<term> ::= <factor> (("-" | "+") <factor>)* ;
<factor> ::= <unary> (("*" | "/") <unary>)* ;
<unary> ::= ( "-" | "!" | "~" ) <unary> | <primary> ;
<primary> ::= NUMBER | STRING | "true" | "false" | "null" | "(" expression ")" ;
```

## Precendece 
| Operator                               | Precedence                                        |
| -------------------------------------- | ------------------------------------------------- |
| postfix decrement and increment        | `--` `++`                                         |
| prefix decrement and increment & unary | `--` `++` `+` `-` `!` `~` `!`                     |
| multiplicative                         | `*` `/` `%`                                       |
| additive                               | `+` `-`                                           |
| shift                                  | `>>` `<<`                                         |
| relational                             | `>` `>=` `<` `<=`                                 |
| equality                               | `==` `!=`                                         |
| bitwise AND                            | `&`                                               |
| bitwise exclusive OR                   | `^`                                               |
| bitwise inclusive OR                   | `|`                                               |
| logical AND                            | `&&`                                              |
| logical OR                             | `||`                                              |
| tenary                                 | `? :`                                             |
| assignment                             | `=` `+=` `-=` `*=` `%=` `&=` `^=` `|=` `<<=` `>>=`|


Example Bs-Script code snippet

```
class Hello {
    val hello : string = "Hello"; 
}

class Greetings < Hello {
    var greeting : string;
    init(var greeting : string) {
        this.greeting = greeting;
    }

    say_hello() : void {
        println(super.hello + " " + this.greeting + "!");
    }
}

val hello_world : Greetings = Greetings("Martin");

hello_world.say_hello();

```
