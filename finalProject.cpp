// finalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


#include <stdio.h>
#include <string>
#include <iostream> 
#include <sstream>
#include <cctype>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sstream>

struct variable
{
    std::string name;
    std::string definition;
    int intdef = NULL;
};

//this creates a global variable that we can add
class global
{
public:
    variable* array;
    int count = 0;

    //the constructor makes an array of variables
    global()
    {
        array = new variable[999];
    }

    //there are different insert types this one inserts using a variable
    void insert(variable var)
    {
        array[count] = var;
        count++;
    }

    //inserts from two strings
    void insert(std::string var, std::string equal)
    {
        array[count].name = var;
        array[count].definition = equal;
        count++;
    }

    void insert(std::string var, int intdef)
    {
        array[count].name = var;
        array[count].intdef = intdef;
        count++;
    }

    //inserts from one strings
    void insert(std::string var)
    {
        array[count].name = var;
        count++;
    }

    //prints array
    void print_array()
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].definition != "")
            {
                std::cout << "variable: " << array[i].name << " = " << array[i].definition << std::endl;
            }
            else
            {
                std::cout << "variable: " << array[i].name << " = " << array[i].intdef << std::endl;
            }
        }
    }

    void print_var(std::string var)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                if (array[i].definition != "")
                {
                    std::cout << array[i].definition << std::endl;
                }
                else
                {
                    std::cout << array[i].intdef << std::endl;
                }
                break;
            }
        }
    }

    //used to change a variable to equal something else or something
    void equals(std::string var, std::string equal)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                array[i].definition = equal;
                break;
            }
        }
    }

    void equals(std::string var, int intdef)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                array[i].intdef = intdef;
                break;
            }
        }
    }

    //used to find a variable and return what it equals
    std::string finddef(std::string var)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                return array[i].definition;
                break;
            }
        }
        return NULL;
    }

    int findint(std::string var)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                return array[i].intdef;
                break;
            }
        }
        return NULL;
    }

    //used to see if a varriable is in global
    bool findbool(std::string var)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                return true;
            }
        }
        return false;
    }

    void definitionReplace(std::string var, std::string definition)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                array[i].definition = definition;
            }
        }
    }

    void definitionReplace(std::string var, int intdef)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                array[i].intdef = intdef;
            }
        }
    }

    //plus plus doesnt work
    void varPlusPlus(std::string var)
    {
        for (int i = 0; i < count; i++)
        {
            if (array[i].name == var)
            {
                array[i].intdef++;
            }
        }
    }

};

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void match(std::string stri);
void LETstatement();
void PRINTstatement();
void NEXTstatement();
void statement();
void IFstatement();
void ELSEstatement();
bool boolexpr();
void print_function();
void expr();

/* Variables */
int charClass;
int inttemp;
char lexeme[100];
std::string str[100];
std::string word;
char nextChar;
int lexLen;
int token;
int nextToken;

std::string output[100];
int outputline = 0;


int line = 0;
std::string ID;

std::fstream file("test1.txt", std::ios::in | std::ios::out);
global var;


//this makes a lookup table that we can use to tokenize everything
enum TokenCode
{
    LETTER, DIGIT, UNKNOWN, QUOTE, END_LINE,

    ADD_OP, SUB_OP, MULT_OP, DIV_OP, LEFT_PAREN, RIGHT_PAREN,
    LESS_THAN, GREATER_THAN, COLON, EQUALS, IF, ELSE, AND, OR,

    LET, FOR, PRINT, PRINT_STRING, NEXT, TO, GOTO,

    INT_LIT, IDENT, ASSIGN_OP
};

int main(int argc, char** argv)
{
    //it sees a blank at the start so you have to do getChar() to start
    getChar();
    do
    {
        lex();
    } while (nextToken != EOF);

    size_t i = 0;

    while (output[i] != "")
    {
        std::cout << output[i] << std::endl;
        i++;
    }

    return 0;
}

void print_function()
{
    std::stringstream ss;
    ss << "Line Number:" << line << "     Lexeme:" << word << "     nextToken:" << nextToken << "     Id:" << ID;
    output[outputline] = ss.str();
    outputline++;
}

//this is used to lookup characters
//this is where we add new characters when we find them
int lookup(char ch)
{
    switch (ch)
    {
    case('('):
    {
        addChar();
        nextToken = LEFT_PAREN;
        ID = "left_parenthesis";
        break;
    }

    case(')'):
    {
        addChar();
        nextToken = RIGHT_PAREN;
        ID = "right_parenthesis";
        break;
    }

    case('+'):
    {
        addChar();
        nextToken = ADD_OP;
        ID = "plus";
        break;
    }

    case('-'):
    {
        addChar();
        nextToken = SUB_OP;
        ID = "minus";
        break;
    }

    case('*'):
    {
        addChar();
        nextToken = MULT_OP;
        ID = "multiply";
        break;
    }

    case('/'):
    {
        addChar();
        nextToken = DIV_OP;
        ID = "divide";
        break;
    }

    case('>'):
    {
        addChar();
        nextToken = GREATER_THAN;
        ID = "greater_than";
        break;
    }

    case('<'):
    {
        addChar();
        nextToken = LESS_THAN;
        ID = "less_than";
        break;
    }

    case(':'):
    {
        addChar();
        nextToken = COLON;
        ID = "colon";
        break;
    }

    case('='):
    {
        addChar();
        nextToken = EQUALS;
        ID = "equals";
        break;
    }
    default:
    {
        addChar();
        nextToken = EOF;
        break;
    }

    }
    return nextToken;
}

//this adds whatever character we read from the file to a string called word to use later
void addChar()
{
    word += nextChar;
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
}

//this gets the character and checks what kind of token it is
void getChar()
{
    //this is used to get the next character in the file and stores it in nextChar
    file.get(nextChar);
    if (!file.eof())
    {
        //checks to see if nextChar is a letter
        if (isalpha(nextChar))
        {
            charClass = LETTER;
        }
        //checks to see if nextChar is a digit
        else if (isdigit(nextChar))
        {
            charClass = DIGIT;
        }
        //checks to see if nextChar is a starting a string
        else if (nextChar == '"')
        {
            charClass = QUOTE;
        }
        //checks to see if nextChar is the end of a line
        else if (nextChar == '\n')
        {
            charClass = END_LINE;
        }
        //this will lead to use lookup() to see if its a character
        else
        {
            charClass = UNKNOWN;
        }
    }
    else
    {
        charClass = EOF;
    }
}

//finds the next non blank in the file
void getNonBlank()
{
    while (nextChar == ' ')
    {
        getChar();
    }

}

//this is the lexer we call this to go to the next token
int lex()
{

    lexLen = 0;
    getNonBlank();
    word = "";
    ID = "";

    //charClass should have been set from the getChar()
    switch (charClass)
    {
    case LETTER:
    {
        word = "";

        addChar();
        getChar();
        if (charClass != END_LINE)
        {
            while (charClass == LETTER || charClass == DIGIT)
            {
                addChar();
                getChar();
            }
        }
        match(word);

        print_function();

        statement();

        return nextToken;
    }

    case DIGIT:
    {
        addChar();
        getChar();
        while (charClass == DIGIT)
        {
            addChar();
            getChar();
        }

        nextToken = INT_LIT;

        ID = "int_literal";

        print_function();

        break;
    }

    case QUOTE:
    {
        word = "";

        word += nextChar;
        file.get(nextChar);

        while (nextChar != '"')
        {
            addChar();

            file.get(nextChar);
        }

        word += nextChar;
        //file.get(nextChar);
        getChar();

        nextToken = PRINT_STRING;

        ID = "quote";

        print_function();

        break;
    }
    case END_LINE:
    {
        word = "";
        addChar();
        getChar();

        line++;

        //have find statement here to see if the position is already in the lines[]
        //setPosition();

        nextToken = END_LINE;

        return nextToken;
    }
    case UNKNOWN:
    {
        lookup(nextChar);
        getChar();

        print_function();

        break;
    }

    case EOF:
    {
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    }

    return nextToken;
}

void statement()
{
    switch (nextToken)
    {
    case LET:
    {
        //std::cout << "LET statement entered" << std::endl;

        LETstatement();

        //std::cout << "LET statement exited" << std::endl;

        break;
    }

    case FOR:
    {
        //std::cout << "FOR statement entered" << std::endl;

        //std::cout << "FOR statement exited" << std::endl;

        break;
    }
    case PRINT:
    {
        //std::cout << "PRINT statement entered" << std::endl;

        PRINTstatement();

        //std::cout << "PRINT statement exited" << std::endl;

        break;
    }
    case NEXT:
    {
        //std::cout << "NEXT statement entered" << std::endl;

        //NEXTstatement();

        //std::cout << "NEXT statement exited" << std::endl;

        break;
    }
    case TO:
    {
        //std::cout << "TO statement entered" << std::endl;



        //std::cout << "TO statement exited" << std::endl;

        break;
    }
    case GOTO:
    {
        //std::cout << "GOTO statement entered" << std::endl;

        //GOTOstatement();

        //std::cout << "GOTO statement exited" << std::endl;

        break;
    }
    case IF:
    {
        //std::cout << "IF statement entered" << std::endl;

        //IFstatement();

        //std::cout << "IF statement exited" << std::endl;

        break;
    }
    case ELSE:
    {
        //std::cout << "ELSE statement entered" << std::endl;

        //ELSEstatement();

        //std::cout << "ELSE statement exited" << std::endl;

        break;
    }
    }
}

//this is used to see if the word we find is a reserved word and checks the table for it
void match(std::string stri)
{
    if (stri == "LET")
    {
        nextToken = LET;
        ID = "let_statement";
    }
    else if (stri == "FOR")
    {
        nextToken = FOR;
        ID = "for_statement";
    }
    else if (stri == "PRINT")
    {
        nextToken = PRINT;
        ID = "print_statement";
    }
    else if (stri == "TO")
    {
        nextToken = TO;
        ID = "to_statement";
    }
    else if (stri == "GOTO")
    {
        nextToken = GOTO;
        ID = "goto_statement";
    }
    else if (stri == "NEXT")
    {
        nextToken = NEXT;
        ID = "next_statement";
    }
    else if (stri == "IF")
    {
        nextToken = IF;
        ID = "if_statement";
    }
    else if (stri == "ELSE")
    {
        nextToken = ELSE;
        ID = "else_statement";
    }
    else
    {
        if (!var.findbool(stri))
        {
            var.insert(stri);
        }

        nextToken = IDENT;
        ID = "identifier";
    }
}

void expr()
{
    std::string striTemp = word;
    int intTemp = var.findint(lexeme);
    int temp;


    while (nextToken != END_LINE)
    {
        lex();
        //operations
        switch (nextToken)
        {
        case(ADD_OP):
        {
            lex();
            if (nextToken == INT_LIT)
            {

                std::stringstream ss(word);
                ss >> temp;

                intTemp += temp;
            }
            break;
        }
        case(SUB_OP):
        {
            lex();
            if (nextToken == INT_LIT)
            {

                std::stringstream ss(lexeme);
                ss >> temp;

                intTemp -= temp;
            }
            break;
        }
        case(MULT_OP):
        {
            lex();
            if (nextToken == INT_LIT)
            {
                

                std::stringstream ss(lexeme);
                ss >> temp;

                intTemp *= temp;
            }
            break;
        }
        case(DIV_OP):
        {
            lex();
            if (nextToken == INT_LIT)
            {
                

                std::stringstream ss(lexeme);
                ss >> temp;

                intTemp /= temp;
            }
            break;
        }
        }
    }

    var.equals(striTemp, intTemp);
}

//there are different kinds of LET statements
//LET i
//LET i = 5 
//LET i = 5 : LET j = 5
//this will check one let statement and so all should be checked because of the if statements
void LETstatement()
{
    std::string temp;
    lex();
    if (nextToken == IDENT) //CHECKING FOR IDENT
    {
        temp = lexeme;
        lex();
        if (nextToken == EQUALS)//CHECKING FOR EQUALS
        {
            lex();
            if (nextToken != END_LINE)//CHECKING FOR END OF LINE
            {
                std::stringstream deg(lexeme);
                deg >> inttemp;
                if (inttemp == NULL)
                {
                    var.equals(temp, lexeme);
                }
                else
                {
                    var.equals(temp, inttemp);
                }
            }//EXIT END OF LINE IF
            else
            {
                std::cout << "error in line " << line - 1 << std::endl;
                exit;
            }
        }//EXIT EQUALS IF
        else
        {
            std::cout << "error in line " << line << std::endl;
            exit;
        }
    }//EXIT IDENT IF
    else
    {
        std::cout << "error in line " << line << std::endl;
        exit;
    }
}

void PRINTstatement()
{
    lex();
    int inttemp = var.findint(word);
    std::string temp = word;
    expr();
    if (var.findbool(temp))
    {
        var.print_var(temp);
    }
    else
    {
        printf(lexeme);
    }
    var.equals(temp, inttemp);
}

void NEXTstatement()
{
    lex();
    var.varPlusPlus(lexeme);
}

//IF (X > MAX) GOTO 100
//IF x > MAX GOTO 100
void IFstatement()
{
    if (nextToken != IF)
    {

    }
    else
    {
        lex();
        if (boolexpr())
        {
            lex();
            statement();

            if (nextToken == ELSE)
            {
                lex();
                statement();
            }
        }
        else
        {
            while (nextChar != '\n')
            {
                file.get(nextChar);
            }
        }
    }
}

void ELSEstatement()
{

}

// 
bool boolexpr()
{
    bool temp{};

    lex();
    if (nextToken == IDENT) // checking if the first token is an identifier
    {
        std::string left = lexeme;

        lex();
        if (nextToken == GREATER_THAN)
        {
            lex();
            if (nextToken == IDENT)
            {
                std::string right = lexeme;

                lex();

                if (var.findint(left) >= var.findint(right))
                {
                    temp = true;
                }
                else
                {
                    temp = false;
                }
            }
            else if (nextToken == DIGIT)
            {
                int right;
                std::stringstream ss(lexeme);
                ss >> right;

                lex();

                if (var.findint(left) >= right)
                {
                    temp = true;
                }
                else
                {
                    temp = false;
                }
            }
        }
        else if (nextToken == LESS_THAN)
        {
            lex();
            if (nextToken == IDENT)
            {
                std::string right = lexeme;

                lex();

                if (var.findint(left) <= var.findint(right))
                {
                    temp = true;
                }
                else
                {
                    temp = false;
                }
            }
            else if (nextToken <= DIGIT)
            {
                int right;
                std::stringstream ss(lexeme);
                ss >> right;

                lex();

                if (var.findint(left) == right)
                {
                    temp = true;
                }
                else
                {
                    temp = false;
                }
            }
        }
        else if (nextToken == EQUALS)
        {
            lex();
            if (nextToken == IDENT)
            {
                std::string right = lexeme;

                lex();
                if (var.finddef(left) != "")
                {
                    if (var.finddef(left) == var.finddef(right))
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
                else
                {
                    if (var.findint(left) == var.findint(right))
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
            }
            else if (nextToken == DIGIT)
            {
                int right;
                std::stringstream ss(lexeme);
                ss >> right;

                lex();

                if (var.findint(left) == right)
                {
                    temp = true;
                }
                else
                {
                    temp = false;
                }
            }
            else if (nextToken == PRINT_STRING)
            {
                std::string right = lexeme;

                lex();

                if (var.finddef(left) != "")
                {
                    if (var.finddef(left) == right)
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
            }
        }
        // 7 > _
        else if (nextToken == DIGIT)
        {
            int left;
            std::stringstream ss(lexeme);
            ss >> left;

            lex();

            if (nextToken == GREATER_THAN)
            {
                lex();
                if (nextToken == IDENT)
                {
                    std::string right = lexeme;

                    lex();

                    if (left >= var.findint(right))
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
                else
                {
                    int right;
                    std::stringstream ss(lexeme);
                    ss >> right;

                    lex();

                    if (left > right)
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }

            }
            else if (nextToken == LESS_THAN)
            {
                lex();
                if (nextToken == IDENT)
                {
                    std::string right = lexeme;

                    lex();

                    if (left <= var.findint(right))
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
                else
                {
                    int right;
                    std::stringstream ss(lexeme);
                    ss >> right;

                    lex();

                    if (left < right)
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
            }
            else if (nextToken == EQUALS)
            {
                lex();

                if (nextToken == IDENT)
                {
                    std::string right = lexeme;

                    lex();

                    if (left == var.findint(right))
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
                else
                {
                    int right;
                    std::stringstream ss(lexeme);
                    ss >> right;

                    lex();

                    if (left == right)
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
            }
        }

        else if (nextToken == PRINT_STRING)
        {
            std::string left = lexeme;

            lex();

            if (nextToken == EQUALS)
            {
                lex();

                if (nextToken == IDENT)
                {
                    std::string right = lexeme;

                    lex();
                    if (left == var.finddef(right))
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
                else
                {
                    std::string right;

                    if (left == right)
                    {
                        temp = true;
                    }
                    else
                    {
                        temp = false;
                    }
                }
            }
        }
    }

    lex();

    if (nextToken == OR)
    {
        if (temp == true)
        {
            return true;
        }
        else
        {
            boolexpr();
        }
    }
    else if (nextToken == AND)
    {
        if (temp == false)
        {
            return false;
        }
        else
        {
            boolexpr();
        }
    }
    else
    {
        return temp;
    }
}