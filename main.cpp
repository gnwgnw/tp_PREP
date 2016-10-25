#include "tree.h"

static void launch(ifstream &f_source,ofstream &f_target);

int main(int argc, char** argv){
    ifstream f_source;
    ofstream f_target;
    int code = ALL_OK;

    switch (argc) {
    case 1:
        f_source.open("source.txt");
        f_target.open("target.txt");
        break;
    case 2:
        f_source.open(argv[1]);
        f_target.open("target.txt");
        break;
    case 3:
        f_source.open(argv[1]);
        f_target.open(argv[2]);
        break;
    default:
        code = ALL_BAD;
        cout << "example.exe <source.txt> <target.txt>" << endl;
        break;
    }

    if (code != ALL_BAD){
        if ((!f_source.is_open())||(!f_target.is_open())){
            code = ALL_BAD;
            cout << "can not open file" << endl;
        } else {
            launch(f_source, f_target);
            f_source.close();
            f_target.close();
        }
    }
   // system ("pause");
    return code;
}

static void launch(ifstream &f_source,ofstream &f_target)
{
    char c;
    int digit;
    Tree* tree = new Tree();

    while(!f_source.eof()){
        f_source >> c;
        if (c == '+'){
            f_source >> digit;
            tree->insert(digit);
        }else if (c == '-'){
            f_source >> digit;
            tree->del(digit);
        }else if (c == '?'){
            f_source >> digit;
            tree->find(digit);
        }
    }

    tree->print_tree(f_target, tree->root);

}














