//Nikhil Krishna
//niekrish
//CMPS-12B/M
//BSTClient.c
//Implements a parser method used to create the UI to test BST




//---------------------------------------------------------------------
// BSTClient.c
// Input oriented Test client for Binary Search Tree ADT
// see file BSTUI.h for definition of commands and acceptable input details.
// 
//---------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <ctype.h>
#include "BST.h"
#include "BSTUI.h"		

/******************  function prototypes  *****************************/

void doQuit();
void showHelp();
void doErase( BSTObj **ptrT);
void doHeight( BSTObj *T);
void doHeight();
void doInsert(BSTObj **ptrT, char *arg);
void doPrint(BSTObj *T, char *order);
void doFind(BSTObj *T, char *term);
int inputLengthOK(char *inputStr);
void doDelete(BSTObj **ptrT, char *arg);

/******************  function prototypes  *****************************/
/*
 * parseInput 
 *    Processes the text string input and divides the input into words that are 
 *    returned on w1, w2, w3
 *    This supports commands that have at most one argument:
 *    return the command in w1, first argument in w2, w3 for trailing junk
 *
 *    Return value indicates the outcome of parsing. Could be OK result which is command that
 *    was detected, e.g.
 *	  CMD_HELP
 *    of it could be an error was detected, e.g.
 *	  NO_ARGS_NEEDED	  
 *
 */
int parseInput(char *input, char *w1, char *w2, char *w3){
    int	    numArgs;

    /*
     * take the raw input string and read the contents to determine the action
     * fill in the argument if the command requires one.
     */
    
    // break the request up into words separated by whitespace
 
    numArgs = sscanf(input, "%s %s %s", w1, w2, w3);
    //printf("numArg = %d from sscanf w1 = %s, w2= %s, w3= %s\n",numArgs, w1, w2, w3);


    if (numArgs == EOF ) {
	// no words, tell the user they can get help
        return CMD_NONE;
    }

    if (numArgs == 0 ) {
	// no words, tell the user they can get help
        return CMD_NONE;
    }
  
    if (strcasecmp(CMD_HELP_STR, w1) == 0) {
        if (numArgs > 1) {
	    return NO_ARGS_NEEDED;
        }
        else {
	    return(CMD_HELP);
        }
    }

    if (strcasecmp(CMD_ERASE_STR, w1) == 0) {
	 if (numArgs > 1) {
            return NO_ARGS_NEEDED;
        }
	else{
		return(CMD_ERASE);
	}
	// your code here
    }
	

    if (strcasecmp(CMD_QUIT_STR, w1) == 0) {
	 if (numArgs > 1) {
            return NO_ARGS_NEEDED;
        }
	else{
		return(CMD_QUIT);
	}
	// your code here
    }

    if (strcasecmp(CMD_HEIGHT_STR, w1) == 0) {
	 if (numArgs > 1) {
            return NO_ARGS_NEEDED;
        }
	else{
		return(CMD_HEIGHT);
	}
	// your code here
    }
    
    if (strcasecmp(CMD_INSERT_STR, w1) == 0) {
	 if (numArgs != 2) {
		if(numArgs == 1){
			return NEED_MORE_ARG;
		}else{
			return INPUT_EXTRA_ARGUMENT;
		}
        }else{
		return(CMD_INSERT);
	}
          // your code here
    }

    if (strcasecmp(CMD_PRINT_STR, w1) == 0) {
          // your code here
          if (numArgs != 2) {
                if(numArgs == 1){
                        return CMD_PRINT_SINGLE;
                }else{
                        return INPUT_EXTRA_ARGUMENT;;
                }
        }else{
                return(CMD_PRINT);
        }
    }

    if (strcasecmp(CMD_FIND_STR, w1) == 0) {
	 // your code here
	 if (numArgs != 2) {
                if(numArgs == 1){
                        return NEED_MORE_ARG;
                }else{
                        return INPUT_EXTRA_ARGUMENT;
                }
        }else{
                return(CMD_FIND);
        }

    }


    if (strcasecmp(CMD_DELETE_STR, w1) == 0) {
	 // your code here
	 if (numArgs != 2) {
                if(numArgs == 1){
                        return NEED_MORE_ARG;
                }else{
                        return INPUT_EXTRA_ARGUMENT;
                }
        }else{
                return(CMD_DELETE);
        }
    }

    // don't know what this is, doesn't match any commands
    
    return CMD_UNK;
}


/*
 * Parse the input, do the command or generate and error
 */
int main(int argc, char* argv[]){

    BSTObj  *T;
    char    str[MAX_INPUT_LENGTH+3];	// one more for one character over and null
    char    cmdStr[MAX_INPUT_LENGTH +1];
    char    arg1[MAX_INPUT_LENGTH +1];
    char    arg2[MAX_INPUT_LENGTH +1];
    char   *inputStr;
    int     action;
    int     input_from_terminal;
    
    T = NULL;

    input_from_terminal = isatty(fileno(stdin));
    
    if (input_from_terminal)
	printf(COMMAND_PROMPT);

    // note that fgets reads the newline character "\n" and includes this in the string
    while ( (inputStr  = fgets(str,  MAX_INPUT_LENGTH + 2, stdin)) != NULL) {
 
        //printf("fgets returned %s\n", inputStr);
	
        // check input line length
	if(!inputLengthOK(inputStr)) { 
	   action = INPUT_TOO_LONG; 	// too big!
	}
        else {
            //printf("got request |%s|\n", inputStr);
            action = parseInput(inputStr, cmdStr, arg1, arg2);
            //printf("got action = %d\n", action);
	}

	switch(action) {
        
            case CMD_NONE:
		break;
	    case INPUT_TOO_LONG:
		printf(ERR_TOO_LONG, MAX_INPUT_LENGTH);
		break;
	    case INPUT_EXTRA_ARGUMENT:
		printf("Unexpected text after \"%s\" argument.\n", arg1);
		break;
            case EXTRA_ARG:
		printf(ERR_EXTRA_ARG, arg1);
		break;
  	    case NEED_MORE_ARG:
		printf(ERR_NEED_ARG);
		break;
  	    case NO_ARGS_NEEDED:
		printf(ERR_NO_ARGS_NEEDED, cmdStr);
		break;
	    case CMD_HELP:
		showHelp();
		break;
	    case CMD_ERASE:
		doErase(&T);
		break;
	    case CMD_QUIT:
		doQuit();
		break;
	    case CMD_HEIGHT:
		doHeight(T);
		break;
	    case CMD_INSERT:
		doInsert(&T, arg1);
		break;
	    case CMD_PRINT:
		doPrint(T, arg1);
                break;
	    case CMD_PRINT_SINGLE:
		doPrint(T, "InOrder");
                break;
	    case CMD_DELETE:
                doDelete(&T, arg1);
                break;
            case CMD_FIND:
		doFind(T, arg1);
   		break;
            case CMD_UNK:
		printf(ERR_UNK_CMD, cmdStr);
                break;
	    default:
		fprintf(stderr, "at default statement\n");
        }
        *arg1 = '\0';
        *arg2 = '\0';
        *cmdStr = '\0';

        if (input_from_terminal )
           printf(COMMAND_PROMPT);
    }
   
    exit(1);
}


/***************************************************************************************
 *
 * the functions that actually do the command requested by the user
 */

void doQuit() {
    printf("\n");
    exit(0);
}
void showHelp() {
    printf(HELP_MESSAGE);
}

void doErase( BSTObj **ptrT) {
 // your code here
 makeEmpty(ptrT);
 fprintf(stdout, "OK\n");
}

// delete the argument from the tree
void doDelete(BSTObj **ptrT, char *arg) {
        if (deleteItem(arg, ptrT) == 0) fprintf(stdout, "Deleted \"%s\"\n", arg);
        else fprintf(stdout, "Could not find \"%s\" to delete\n", arg);
}

void doHeight( BSTObj *T) {
 // your code here
 int height = treeHeight(T, 0);
 fprintf(stdout, "Height = %d\n", height);
}

// insert the argument into the tree
void doInsert(BSTObj **ptrT, char *arg) {
 // your code here
  int i;
	for(i = 0; i < strlen(arg); i++){
        	if(isgraph((unsigned char) arg[i]) == 0){
                	fprintf(stdout, "Invalid character (decimal value %d) in string\n", (unsigned char)arg[i]);
                	return;
        	}		
	}

 if (insert(arg, ptrT) == 0) fprintf(stdout, "OK\n");
 else fprintf(stdout, "Duplicate string \"%s\"\n", arg);
}

// figure out which print the user wanted and do it
// if there is no ordering then use inorder as the default
void doPrint(BSTObj *T, char *order) {
     // your code here
//     printf("iPrint of type %s\n", order);
     if(strcasecmp(order, "inorder") == 0) {
//	printf("In order print: \n");
	inorderTraverse(stdout, T);
	}else{
		if(strcasecmp(order, "postorder") == 0) {
			//printf("Post order print: \n");
			postorderTraverse(stdout, T);
		}else{
			if(strcasecmp(order, "preorder") == 0) {
				//printf("Pre order print: \n");
				 preorderTraverse(stdout, T);
			}else{
				printf("Unrecognised argument\n Specify one of: inorder, preorder, postorder\n Enter \"help\" for description of each command\n");
			}
		}	
	}
}

void doFind(BSTObj *T, char *term) {
    
 // your code here
 	BSTObj *findObj = find(term, T);
	if(findObj != NULL) printf("Found \"%s\"\n", findObj->term);
	else printf("Could not find \"%s\"\n", term);
}

//check if we have read past the allowed max, not that fgets passes the newline character in a string
// fgets does a read of MAX_INPUT_LENGTH + 1
int inputLengthOK(char *inputStr) {
    
    int  length;

    //printf("input check got |%s|\n", inputStr);
    // confirm that the string is no just a "\n"
    // check that the "\n" 

    length = strlen(inputStr);

   // printf("input check length is %d\n", length);

    // your code here
    if(length == 0) return FALSE;
    if(inputStr[0] == '\n') return FALSE;
    if(length > MAX_INPUT_LENGTH) return FALSE;
    return TRUE;
}
