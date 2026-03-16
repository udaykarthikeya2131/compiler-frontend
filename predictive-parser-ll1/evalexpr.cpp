#include<iostream>
#include<string>
#include<stack>
#include "lex.yy.c"
using namespace std;
int yywrap(void) {
    return 1;
}
typedef struct _symbol_node {
    string name;
    int value;
    struct _symbol_node *next;
} symbol_node;
typedef symbol_node *symbol_table;

typedef struct _number_node {
    int number;
    struct _number_node *next;
} number_node;
typedef number_node *number_table;



void print_symbol_table(symbol_table table) {
    symbol_node* ptr = table;
    cout << "Symbol Table: ";
    while (ptr != NULL) {
        cout << ptr->name << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

symbol_table add_symbol(symbol_table table, string id) {
    symbol_node *ptr = table;
    while (ptr) {
        if (ptr->name == id) {
            return table;
        }
        ptr = ptr->next;
    }
    ptr = (symbol_node *)malloc(sizeof(symbol_node));
    ptr->name = id;
    ptr->value = 0;
    ptr->next = table;
    return ptr;
}

symbol_node* find_symbol(symbol_table table, string id) {
    symbol_node *ptr = table;
    while (ptr) {
        if (ptr->name == id) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

symbol_node* reverse_list(symbol_node* head) {
    symbol_node *curr = head, *prev = nullptr, *next;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int string_to_number(string s) {
    int sign = 1;
    int i = 0;
    if (s[i] == '-') {
        sign = -1;
        i++;
    }
    else if (s[i] == '+') {
        i++;
    }
    int result = 0;
    while (i < s.length()) {
        int digit = s[i] - '0';
        result = result * 10 + digit;
        i++;
    }
    result *= sign;
    return result;
}

number_table add_number(number_table table, string id) {
    int temp = stoi(id);
    if (table == NULL) {
        table = (number_node*)malloc(sizeof(number_node));
        table->number = temp;
        table->next = NULL;
        return table;
    }
    number_node *ptr = table;
    if (ptr->number == temp) {
        return ptr;
    }
    while (ptr->next != NULL) {
        if (ptr->next->number == temp) {
            return ptr->next;
        }
        ptr = ptr->next;
    }
    number_node* new_number = (number_node *)malloc(sizeof(number_node));
    new_number->number = temp;
    ptr->next = new_number;
    return new_number;
}

typedef struct _cell {
    int index;
    struct _cell *next;
} cell;
typedef cell *cell_list;

cell_list add_cell(cell_list list, int i) {
    cell* new_cell = (cell*)malloc(sizeof(cell));
    new_cell->index = i;
    new_cell->next = list;
    return new_cell;
}

typedef union tree_union {
    char operator_char;
    symbol_node* symbol_ptr;
    number_node* number_ptr;
} tree_union;

typedef struct tree_node {
    int node_type;
    tree_union data;
    struct tree_node* left;
    struct tree_node* right;
    struct tree_node* parent;
    tree_node(int type, tree_union value) {
        node_type = type;
        data = value;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
} tree_node;
typedef tree_node* tree;

tree add_to_tree(tree root, int type, tree_union value) {
    tree new_node = new tree_node(type, value);
    if (root->left == NULL) {
        new_node->parent = root;
        root->left = new_node;
        if (type == 0) {
            root = root->left;
        }
    }
    else if (root->right == NULL) {
        new_node->parent = root;
        root->right = new_node;
        if (type == 0) {
            root = root->right;
        }
    }
    else {
        root = root->parent;
        new_node->parent = root;
        root->right = new_node;
        if (type == 0) {
            root = root->right;
        }
    }
    return root;
}

// Function to print the tree
void print_tree(tree root, int depth) {
    if (root == NULL) {
        return;
    }
    for (int i = 1; i < depth; i++) {
        cout << "     ";
    }
    if (depth >= 1) {
        cout << "--->";
    }
    if (root->node_type == 0) {
        cout << "OP(" << root->data.operator_char << ")" << endl;
        print_tree(root->left, depth + 1);
        print_tree(root->right, depth + 1);
    }
    else if (root->node_type == 1) {
        cout << "ID(" << root->data.symbol_ptr->name << ")" << endl;
    }
    else {
        cout << "NUM(" << root->data.number_ptr->number << ")" << endl;
    }
}

// Function to calculate the result of the expression tree
int calculate_tree(tree root) {
    if (root == NULL) {
        return 0;
    }
    if (root->node_type == 0) {
        int left_value = calculate_tree(root->left);
        int right_value = calculate_tree(root->right);
        switch (root->data.operator_char) {
            case '+': return left_value + right_value;
            case '-': return left_value - right_value;
            case '*': return left_value * right_value;
            case '/': return left_value / right_value;
            case '%': return left_value % right_value;
            default: return 0;
        }
    }
    else if (root->node_type == 1) {
        return root->data.symbol_ptr->value;
    }
    else {
        return root->data.number_ptr->number;
    }
}

// Function to get the operation code
int get_operation_code(string op) {
    if (op == "+") return 2;
    if (op == "-") return 3;
    if (op == "*") return 4;
    if (op == "/") return 5;
    if (op == "%") return 6;
    return -1;
}

// Main function
int main() {
    symbol_table symbolTable = NULL;
    number_table numTable = NULL;
    string allTokens[12] = {"(", ")", "+", "-", "*", "/", "%", "ID", "NUM", "EXPR", "OP"};
    cell_list parsingTable[12][12];
    cell_list temp = NULL;
    
    // Initialize parsing table with cell transitions
    temp = add_cell(temp, 0);
    temp = add_cell(temp, 10);
    temp = add_cell(temp, 11);
    temp = add_cell(temp, 11);
    temp = add_cell(temp, 1);
    parsingTable[9][0] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 9);
    parsingTable[11][0] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 2);
    parsingTable[10][2] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 3);
    parsingTable[10][3] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 4);
    parsingTable[10][4] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 5);
    parsingTable[10][5] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 6);
    parsingTable[10][6] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 7);
    parsingTable[11][7] = temp;
    
    temp = NULL;
    temp = add_cell(temp, 8);
    parsingTable[11][8] = temp;
    
    stack<int> parseStack;
    parseStack.push(9);
    
    int openCount = 0, closeCount = 0;
    tree currentNode = NULL;
    tree root = NULL;
    int token;
    
    while ((token = yylex())) {
        int tokenType;
        tree_union u_temp;
        switch (token) {
            case lb: tokenType = 0; break;
            case Id: symbolTable = add_symbol(symbolTable, (string)yytext); u_temp.symbol_ptr = find_symbol(symbolTable, (string)yytext); tokenType = 7; break;
            case Num: u_temp.number_ptr = add_number(numTable, (string)yytext); tokenType = 8; break;
            case rb: tokenType = 1; break;
            case Op: tokenType = get_operation_code((string)yytext); u_temp.operator_char = *yytext; break;
            default: break;
        }
        
        if (tokenType == 0) {
            openCount++;
            while (parseStack.top() != 0) {
                int topValue = parseStack.top();
                parseStack.pop();
                cell_list currentCell = parsingTable[topValue][0];
                if (currentCell != NULL) {
                    while (currentCell != NULL) {
                        parseStack.push(currentCell->index);
                        currentCell = currentCell->next;
                    }
                }
                else {
                    cout << "Error: Parsing table entry is not available" << endl;
                    exit(0);
                }
            }
            parseStack.pop();
        }
        else if (tokenType == 1) {
            closeCount++;
            int topValue = parseStack.top();
            if (topValue == 1) {
                parseStack.pop();
                if (currentNode->parent != NULL) {
                    currentNode = currentNode->parent;
                }
            }
            else {
                cout << "Error: A closing bracket is expected" << endl;
                exit(0);
            }
        }
        else if (tokenType >= 2 && tokenType <= 6) {
            int topValue = parseStack.top();
            if (topValue == 10) {
                parseStack.pop();
            }
            else {
                cout << "Error: An operator is expected" << endl;
                exit(0);
            }
            if (root == NULL) {
                currentNode = new tree_node(0, u_temp);
                root = currentNode;
            }
            else {
                currentNode = add_to_tree(currentNode, 0, u_temp);
            }
        }
        if (tokenType == 8) {
            int topValue = parseStack.top();
            if (topValue == 11) {
                parseStack.pop();
            }
            else {
                cout << "Error: A  number is expected" << endl;
                exit(0);
            }
            currentNode = add_to_tree(currentNode, 2, u_temp);
        }
        else if (tokenType == 7) {
            int topValue = parseStack.top();
            if (topValue == 11) {
                parseStack.pop();
            }
            else {
                cout << "Error: A  identifier is expected" << endl;
                exit(0);
            }
            currentNode = add_to_tree(currentNode, 1, u_temp);
        }
        if (openCount == closeCount) {
            break;
        }
    }
    
    cout << "Parsing is successful" << endl;
    print_tree(root, 0);
    
    symbolTable = reverse_list(symbolTable);
    symbol_table symbolTablePtr = symbolTable;
    if (symbolTablePtr != NULL) {
        cout << "Reading variable values from the input" << endl;
    }
    while (token == yylex()) {
        int value = stoi(yytext);
        if (symbolTablePtr == NULL) {
            break;
        }
        symbolTablePtr->value = value;
        cout << symbolTablePtr->name << " = " << symbolTablePtr->value << endl;
        symbolTablePtr = symbolTablePtr->next;
    }
    
    cout << "The expression evaluates to " << calculate_tree(root) << endl;
    return 0;
}
