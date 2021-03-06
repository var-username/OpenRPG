/*
roll - roll-parser.h
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_ROLL_PARSER_H_
#define SRC_ROLL_PARSER_H_

#ifdef _WIN32
#   include "roll/exports/parser_exports.h"
#else
#   define ROLL_PARSER_EXPORT
#endif

#include "roll/die.h"

#define FUDGE_DIE       -2 // represents a fudge die

/* parse tree nodes ops */
#define OP_ERR          -1 // Error node (halts tree traversal)
#define OP_NUMBER        1 // number node
#define OP_DIE           2 // n-sided die node
#define OP_TIMES         3 // multiplication node
#define OP_DIV           4 // integer division node
#define OP_PLUS          5 // addition node
#define OP_MINUS         6 // subtraction node
#define OP_MOD           7 // modulo node
#define OP_HIGH          8 // keep highest results node
#define OP_LOW           9 // keep lowest resutls node
#define OP_GT           10 // keep results greater than
#define OP_GE           11 // keep results greater or equal than
#define OP_LT           12 // keep results less than
#define OP_LE           13 // keep results less or equal than
#define OP_NE           14 // keep results not equal to
#define OP_EXPR         15 // notates the top of an Expression

namespace ORPG {
    namespace Roll {
        /**
         * @desc prints the version info when -V or --version is an argument to the command.
         * This adhears to the GNU standard for version printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void ROLL_PARSER_EXPORT print_version_flag();

        /**
         * @desc prints the help info when -h or --help is an argument to the command.
         * This adhears to the GNU standard for help printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void ROLL_PARSER_EXPORT print_help_flag();

        /**
         * @desc prints the version info when version, ver, v, or V are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void ROLL_PARSER_EXPORT print_basic_version();

        /**
         * @desc prints the help info when help, h, or H are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void ROLL_PARSER_EXPORT print_basic_help();
    }

    /* node of the intermediate representation parse tree */
    struct ROLL_PARSER_EXPORT parse_node {
        struct parse_node* left;    // left node
        struct parse_node* right;   // right node
        struct parse_node* parent;  // this nodes parent
        short int op;               // node type
        int value;                  // node value
    };

    class ROLL_PARSER_EXPORT ExpressionTree {
    private:
        parse_node* allocate_node();
        parse_node* new_number(struct parse_node* cur, int* numBytesToRead = 0);
        parse_node* new_op(struct parse_node* cur, short int op);
        parse_node* new_die(struct parse_node* cur);
        parse_node* node_error(struct parse_node* node);
        
        int parse_input_string(std::string* buff, int* numBytesRead, int maxBytesToRead);
        int parse_tree(struct parse_node* node);
        bool build_expression_tree();
        
        std::string tree_string(struct parse_node* node, int indent, std::string pre = "head->");
        
        int globalReadOffset = 0;
        struct parse_node* head = allocate_node();
        std::string inputString = "1d20";
    public:
        /**
         * @desc sets the input string to be scanned and parsed equal to the string exp
         * @param const std::string exp - the string to become the input string
         */
        bool set_expression(const std::string exp);
        
        /**
         * @desc parses the parse_node tree and returns the end result of the expression
         * @return int - the end result of the expression
         */
        int parse_expression() { return parse_tree(head); };
        
        /**
         * @desc outputs an error with ERROR_CODE if there
         *     would be an addition overflow
         * @param int op1 - an integer to be added
         * @param int op2 - an integer to be added
         * @return int - op1 + op2
         */
        int checked_sum(int op1, int op2);

        /**
         * @desc outputs an error with ERROR_CODE if there
         *     would be a multiplication overflow
         * @param int op1 - an integer to be multiplied
         * @param int op2 - an integer to be multiply by
         * @return int - op1 * op2
         */
        int checked_multiplication(int op1, int op2);
        
        /**
         * @desc returns a string of the tree starting with
         *     the top node node and taking precidence over the left node
         * @return string - a string representation of the current tree
         */
        std::string to_string() { 
            if(head->op == 0) {
                return "expression not yet set";
            }

            if(head->op == OP_ERR) {
                return "invalid expression";
            }

            return tree_string(head, 0); 
        };

        /**
         * @desc returns the input string that was give to the parser
         * @return string - the string that was give as input to the parser
         */
        std::string get_input_string() { return inputString; }

        // TODO sanatize input - lets not get people (or ourselves) hacked!
        static bool is_expression_valid(const std::string exp);
    };
}

#endif  /* SRC_ROLL_PARSER_H_ */
