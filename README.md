# BlockScript

Blockscript is a general purpose scripting language which can be used to write Blockchain applications.

## Grammar Backus-Naur-Form

```
// Declarations
<declaration> ::= <class-declaration>
| <fn-declaration>
| <var-declaration>
| <statement> ;

<class-declaration> ::= "class" IDENTIFIER ( "<" IDENTIFIER )?
"{" function* "}" ;
<fn-declaration> ::= "fn" <function> ;
<var-declaration> ::= ("var" | "val") IDENTIFIER (":" <type-identifer>)* ("=" <expression>)* ";" ;

// Statements
<statement> ::= <expr-stmt>
| <for-stmt>
| <if-stmt>
| <return-stmt>
| <while-stmt>
| <block-stmt> ;


<expr-stmt> ::= <expression> ";" ;
<for-stmt> ::= "for" "(" ( <var-declaration> | <expr-stmt> | ";" ) <expression>? ";" <expression>? ")" <statement> ;
<if-stmt> ::= "if" "(" <expression> ")" <statement> ( "else" <statement> )? ;
<return-stmt> ::= "return" <expression>? ";" ;
<while-stmt> ::= "while" "(" <expression> ")" <statement> ;
<block-stmt> ::= "{" <declaration>* "}" ;


// Expressions

expression → assignment ;
assignment → ( call "." )? IDENTIFIER "=" assignment
| logic_or ;
logic_or → logic_and ( "or" logic_and )* ;
logic_and → equality ( "and" equality )* ;
equality → comparison ( ( "!=" | "==" ) comparison )* ;
comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term → factor ( ( "-" | "+" ) factor )* ;
factor → unary ( ( "/" | "*" ) unary )* ;
unary → ( "!" | "-" ) unary | call ;
call → primary ( "(" arguments? ")" | "." IDENTIFIER )* ;
primary → "true" | "false" | "nil" | "this"
| NUMBER | STRING | IDENTIFIER | "(" expression ")"
| "super" "." IDENTIFIER ;

<expression> ::= <assignment> ;
<assignment> ::= (call ".")? IDENTIFIER "=" <assignment> | <tenary> ;
<call> ::= <primary> ( "(" <arguments>? ")" | "." IDENTIFER )* ;
<tenary> ::= <bitwise-inc-or> "?" <expression> ":" <expression> ;
<bitwise-inc-or> ::= <bitwise-exc-or> ("|" <bitwise-exc-or>) ;
<bitwise-exc-or> ::= <bitwise-and> ("^" <bitwise-and>)* ;
<bitwise-and> ::= <equality> ("&" <equality>)* ;
<equality> ::= <comparison> (("==" | "!=") <comparison>)* ;
<comparison> ::= <shift> ((">" | "<" | "<=" | ">=") <shift>)* ;
<shift> ::= <term> (("<<" | ">>") <term>)* ;
<term> ::= <factor> (("-" | "+") <factor>)* ;
<factor> ::= <unary> (("*" | "/" | "%") <unary>)* ;
<pre-unary> ::= ( "-" | "!" | "~" | "++" | "--") <pre-unary> | <pos-unary> ;
<pos-unary> ::= <primary> ("--" | "++")*
<type-identifer> ::= "int8" | "u_int8" | "int16" | "u_int16" | "int32" | "u_int32" 
                    | "int64" | "u_int64" | "float32" | "float64" | "bool" | "string" | IDENTIFIER ;
<primary> ::= NUMBER | STRING | "true" | "false" | "null" | "(" expression ")" | "super" "." IDENTIFER | this ;

// Utilities
<function> ::= IDENTIFIER "(" <parameters>? ")" <block-stmt> ;
<parameters> ::= IDENTIFIER ( "," IDENTIFIER )* ;
<arguments> ::= <expression> ( "," <expression> )* ;

// Terminals
NUMBER → DIGIT+ ( "." DIGIT+ )? ;
STRING → "\"" <any char except "\"">* "\"" ;
IDENTIFIER → ALPHA ( ALPHA | DIGIT )* ;
ALPHA → "a" ... "z" | "A" ... "Z" | "_" ;
DIGIT → "0" ... "9" ;
```

## Precendece 
| Operator                               | Precedence                                          |
| -------------------------------------- | --------------------------------------------------- |
| postfix decrement and increment        | `--` `++`                                           |
| prefix decrement and increment & unary | `--` `++` `+` `-` `!` `~` `!`                       |
| multiplicative                         | `*` `/` `%`                                         |
| additive                               | `+` `-`                                             |
| shift                                  | `>>` `<<`                                           |
| relational                             | `>` `>=` `<` `<=`                                   |
| equality                               | `==` `!=`                                           |
| bitwise AND                            | `&`                                                 |
| bitwise exclusive OR                   | `^`                                                 |
| bitwise inclusive OR                   | `\|`                                                |
| logical AND                            | `&&`                                                |
| logical OR                             | `\|\|`                                              |
| tenary                                 | `? :`                                               |
| assignment                             | `=` `+=` `-=` `*=` `%=` `&=` `^=` `\|=` `<<=` `>>=` |


Example Bs-Script code snippet

```scala
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
