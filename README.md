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