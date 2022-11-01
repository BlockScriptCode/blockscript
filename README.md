# BlockScript

Blockscript is a general purpose scripting language which can be used to write Blockchain applications.

## Grammar Backus-Naur-Form
Example Bs-Script code snippet

```
class HelloWorld {
    static val hello : string = "Hello";
    var greeting : string;
    init(var greeting : string) {
        this.greeting = greeting;
    }

    say_hello() : void {
        println(hello + " " + this.greeting + "!");
    }
}

val hello_world : HelloWorld = HelloWorld("Martin");

hello_world.say_hello();

```

program = {declaration}

declaration = classDeclaration | fnDeclaration | structDeclaration

typeDeclaration = 

