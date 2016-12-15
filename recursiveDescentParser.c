/*
 COLLABORATORS: Brooke Werner, Alana Zakroczemski, Sooyoung Kim
 REFERENCES:
 Foundations of Computer Science by Al Aho and Jeff Ullman. A copy of this book can be found here: http://infolab.stanford.edu/~ullman/focs.html
 Lectures from CSC 173 Computation & Formal Systems by Professor George Ferguson
 */

#include <stdio.h>
#include <stdlib.h>
#define FAILED NULL

typedef struct NODE *TREE;

/* makes tree from bottom up*/
struct NODE{
	char label;
	TREE leftmostChild, rightSibling;
};

TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
//b/c we have "two" expression, terms, and numbers, we have to assign different character values when creating the nodes
//besides 'E', 'T', 'N'
TREE expression1();
TREE expression2();//I'm going to arbitrarily assign 'A'
TREE term1();
TREE term2();//I'm going to arbitrarily assign it 'B'
TREE factor();
TREE number1();
TREE number2();//I'm going to arbitrarily assign it 'C'
TREE digit();
/* ^^^ to define the function that we are using to
parse the expression */

TREE parseTree; /* holds the result of the parse tree */
char *nextTerminal; /* current position in input string */
char *nextInputCharacter; //next input character in string

TREE makeNode0(char x) { /*makes node with zero children*/
	TREE root;
	/* making tree with node x with no right or left children */
	root = (TREE) malloc(sizeof(struct NODE));
	root->label = x;
	root->leftmostChild = NULL;
	root->rightSibling = NULL;
	return root;
}

TREE makeNode1(char x, TREE t){ /* makes node with one child */
	/* creates root node and uses makeNode0 to follow single node
	tree conditions */
	TREE root;
	root = makeNode0(x);

	/* the new tree has the root be the previous left most child,
	therefore making the tree from the bottom up */
	root->leftmostChild = t;

	return root;
}

TREE makeNode2(char x, TREE t1, TREE t2){
/* makes node with 2 children */
	TREE root;
	root = makeNode1(x, t1); /* creates new root to attach
	to attach t1 to it, and then strings the rest together */
	t1->rightSibling = t2;
    //root->rightSibling = t2;
	/* ^^^connects all the rest together from the bottom up */
	return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3){
/* makes node with 3 children */
	TREE root;
//    t1->rightSibling = t2;
//    t2->rightSibling = t3;
	root = makeNode1(x, t1); /* creates new root to attach
	to attach t1 to it, and then strings the rest together */
	t1->rightSibling = t2;
	t2->rightSibling = t3;
	/* ^^^connects all the rest together from the bottom up */
	return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4){
/* makes node with four children */
	TREE root;
	root = makeNode1(x, t1); /* creates new root to attach
	to attach t1 to it, and then strings the rest together */
	t1->rightSibling = t2;
	t2->rightSibling = t3;
	t3->rightSibling = t4;
	/* ^^^connects all the rest together from the bottom up */
	return root;
}

//parses a digit from input and returns a tree if successful
TREE digit() {

    printf("Parsing for digit: %c\n", *nextTerminal);
    if(*nextTerminal == '0') {

        nextTerminal++;
        return makeNode1('D', makeNode0('0'));

    } else if(*nextTerminal == '1') {

        nextTerminal++;
        return makeNode1('D', makeNode0('1'));

    } else if(*nextTerminal == '2') {

        nextTerminal++;
        printf("%s\n",nextTerminal);
        return makeNode1('D', makeNode0('2'));

    } else if(*nextTerminal == '3') {

        nextTerminal++;
        return makeNode1('D', makeNode0('3'));

    } else if(*nextTerminal == '4') {

        nextTerminal++;
        return makeNode1('D', makeNode0('4'));

    } else if(*nextTerminal == '5') {

        nextTerminal++;
        return makeNode1('D', makeNode0('5'));

    } else if(*nextTerminal == '6') {

        nextTerminal++;
        return makeNode1('D', makeNode0('6'));

    } else if(*nextTerminal == '7') {

        nextTerminal++;
        return makeNode1('D', makeNode0('7'));

    } else if(*nextTerminal == '8') {

        nextTerminal++;
        return makeNode1('D', makeNode0('8'));

    } else if(*nextTerminal == '9') {

        nextTerminal++;
        return makeNode1('D', makeNode0('9'));

    } else {
        printf("failing on %c\n", *nextTerminal);
        return FAILED;
    }
}

//parses a number from the input and returns trees if successful
TREE number2() {

        TREE numb1;

    //this tests whether or not the next character is empty
    if(*nextTerminal == '\0' || *nextTerminal == '*' || *nextTerminal == '/' || *nextTerminal == ')'
    || *nextTerminal == '+' || *nextTerminal == '-' || *nextTerminal == '(') {

       return makeNode1('C', makeNode0('e')); //******

    } else {

        printf("calling number1()\n");
        numb1 = number1();
        //to check if this is actually a number1
        if (numb1 != FAILED) {

            return makeNode1('C', numb1);

        } else {

            return FAILED;
        }
    }
}


TREE number1() {

    TREE dig, numb2;

    dig = digit();
    //checking to see if the first non-terminal is a digit
    if (dig != FAILED) {

        numb2 = number2();

        //checking to see if the second non-terminal is a number2
        if(numb2 != FAILED) {

           return makeNode2('N', dig, numb2); //******

        } else {

            return FAILED;
        }
    } else {

        return FAILED;
    }
}

//parses a factor from the input and returns trees if successful
TREE factor() {

    TREE exp, numb;

    if(*nextTerminal == '(') {
    //first production of <factor>

        nextTerminal++;
        exp = expression1();

        printf("next Terminal: %s", nextTerminal);

        if(exp != FAILED && *nextTerminal == ')') {

            nextTerminal++;
            return makeNode3('F', makeNode0('('), exp, makeNode0(')'));

        } else {

            return FAILED;
        }

    } else {
    //second production of <factor>

        numb = number1();

        if (numb == FAILED) {

            return FAILED;

        } else {

            return makeNode1('F', numb);
        }
    }
}

//parses a term from input and returns a tree if successful
TREE term2() {

    TREE fact, t2;

    if(*nextTerminal == '*') {
            //first production of t1

        nextTerminal++;
        fact = factor();

        //checking to see if first non-terminal is a factor
        if(fact != FAILED) {

            t2 = term2();

            //checking to see if the second non-terminal is a term2
            if(t2 != FAILED) {

               return makeNode3('B', makeNode0('*'), fact, t2); //******

            } else {

                return FAILED;
            }

        } else {

            return FAILED;
        }


    } else if(*nextTerminal == '/') {
        //second production of t2

        nextTerminal++;
        fact = factor();

        //checking to see if first non-terminal is a factor
        if(fact != FAILED) {

            t2 = term2();

            //checking to see if the second non-terminal is a term2
            if(t2 != FAILED) {

               return makeNode3('B', makeNode0('/'), fact, t2); //*****

            } else {

                return FAILED;
            }

        } else {

            return FAILED;
        }

    } else {
        //third production of t2

        return makeNode1('B', makeNode0('e')); //******
    }
}

TREE term1() {

    TREE fact, t2;

    fact = factor();
    //checking to see if the first non-terminal is a fact
    if (fact != FAILED) {

        t2 = term2();

        //checking to see if the second non-terminal is a term2
        if(t2 != FAILED) {

           return makeNode2('T', fact, t2); //******

        } else {

            return FAILED;
        }
    } else {

        return FAILED;
    }
}

//parses an expression from input and returns a tree if successful
TREE expression2(){

    TREE t1, e2;

    if(*nextTerminal == '+') {
        //first production of e2

        nextTerminal++;
        t1 = term1();

        //checking to see if first non-terminal is a term1
        if(t1 != FAILED) {

            e2 = expression2();

            //checking to see if the second non-terminal is a expression2
            if(e2 != FAILED) {

               return makeNode3('A', makeNode0('+'), t1, e2); //******

            } else {

                return FAILED;
            }

        } else {

            return FAILED;
        }


    } else if(*nextTerminal == '-') {
        //second production of e2

        nextTerminal++;
        t1 = term1();

        //checking to see if first non-terminal is a term1
        if(t1 != FAILED) {

            e2 = expression2();

            //checking to see if the second non-terminal is a expression2
            if(e2 != FAILED) {

               return makeNode3('A', makeNode0('-'), t1, e2); //******

            } else {

                return FAILED;
            }

        } else {

            return FAILED;
        }

    } else {

        //third production of e2

       return makeNode1('A', makeNode0('e')); //******
    }
}

TREE expression1(){

    TREE t1, e2;

    t1 = term1();
    //checking to see if the first non-terminal is a digit
    if (t1 != FAILED) {

        e2 = expression2();

        //checking to see if the second non-terminal is a number2
        if(e2 != FAILED) {

            return makeNode2('E', t1, e2); //******

        } else {

            return FAILED;
        }
    } else {

        return FAILED;
    }
}

void printTree(TREE treeToPrint, int start, int numIndented) { //int start is a boolean val of if on the root node

    if (treeToPrint == FAILED && start == 1) {
        printf("failed - cannot parse this input\n");
    } else {
        
        printf("\n");
        for (int i = 0; i < numIndented; i++) {
            printf("\t");
        }
        
        printf("(%c", treeToPrint->label);
        
        if (treeToPrint->leftmostChild != NULL) {
            printTree(treeToPrint->leftmostChild, 0, numIndented+1);
        } else {
            printf(")");
        }

        if (treeToPrint->rightSibling != NULL) {
            printTree(treeToPrint->rightSibling, 0, numIndented);
        } else {
            printf(")");
        }

    }
}

void printRoot(TREE treeRoot, int start, int numIndented) {
    if (treeRoot == FAILED && start == 1) {
        printf("failed - cannot parse this input\n");
    } else {
        for (int i = 0; i < numIndented; i++) {
            printf("\t");
        }
        printf("\n(");
        
        printf("%c", treeRoot->label);
        
        if(treeRoot->leftmostChild != NULL) {
            printRoot(treeRoot->leftmostChild, 0, numIndented+1);
        }
        
        if(treeRoot->rightSibling != NULL) {
            printRoot(treeRoot->rightSibling, 0, numIndented);
        }
        
        printf(")");
        
    }
}

int main(){

	char expression[20]; /*random length string (a string is just
	an array of characters) for how long an expression possibly could be,
	you can make it larger if you want */

	printf("Type in the expression with no spaces in between\n"); /* no spaces
	because when parsed we dont want the 'spaces' to attempt to fit somewhere in the tree */
	scanf("%s", expression);
	printf("The expression you typed was %s\n", expression);

    /* takes in an expression and then separates each character in the expression in the array that we are going to fit in the parse tree */

	nextTerminal = expression; /* <-- what user entered above is nextTerminal */
	parseTree = expression1();
    printTree(parseTree, 1, 0);
    //printRoot(parseTree, 1, 0);
    printf("\n");
}
