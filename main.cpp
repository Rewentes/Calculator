#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

const double Pi = acos(-1);
struct typeVal {
    char type;
    double val;
};

double factorial(double x)
{
    if (x == 0) return 1;
    else return x * factorial(x-1);
}
double Sin(double x) {
    return (round(sin(x) * 10000000) / 10000000);
}
double Cos(double x) {
    return (round(cos(x) * 10000000) / 10000000);
}
double Tan(double x) {
    return (round(tan(x) * 10000000) / 10000000);
}
double ctg(double x) {
    double a = Cos(x);
    double b = Sin(x);
    return (a / b);
}
int bin(int x) {
    double b = 0, k = 1;
    while (x != 0) {
        b += x % 2 * k;
        x /= 2;
        k *= 10;
    }
    return b;
}

int switchCase(stack <typeVal> &Number, stack <typeVal> &Operations, typeVal &tmp) {

    double c, b, a;
    a = Number.top().val;
    Number.pop();
    switch (Operations.top().type) {

        case '+':
            b = Number.top().val;
            Number.pop();
            c = a + b;
            tmp.type = '0';
            tmp.val = c;
            Number.push(tmp);
            Operations.pop();
            break;

        case '-':
            b = Number.top().val;
            Number.pop();
            c = b - a;
            tmp.type = '0';
            tmp.val = c;
            Number.push(tmp);
            Operations.pop();
            break;

        case '*':
            b = Number.top().val;
            Number.pop();
            c = a * b;
            tmp.type = '0';
            tmp.val = c;
            Number.push(tmp);
            Operations.pop();
            break;

        case '/':
            b = Number.top().val;
            Number.pop();
            if (a == 0) {
                cerr << "Error! Division at 0.";
                return 1;
            } else {
                c = b / a;
                tmp.type = '0';
                tmp.val = c;
                Number.push(tmp);
                Operations.pop();
                break;
            }

        /*case '!':
            tmp.type = '0';
            tmp.val = factorial(a);
            Number.push(tmp);
            Operations.pop();
            break;*/

        case '^':
            b = Number.top().val;
            Number.pop();
            c = pow(b, a);
            tmp.type = '0';
            tmp.val = c;
            Number.push(tmp);
            Operations.pop();
            break;

        case 's': // Синус
            tmp.type = '0';
            tmp.val = Sin(a);
            Number.push(tmp);
            Operations.pop();
            break;

        case 'c': // Косинус
            tmp.type = '0';
            tmp.val = Cos(a);
            Number.push(tmp);
            Operations.pop();
            break;

        case 't': // Тангенс
            if (Cos(a) == 0) {
                cerr << "Error! (tan) does not exist";
                return false;
            }
            else {
                tmp.type = '0';
                tmp.val = Tan(a);
                Number.push(tmp);
                Operations.pop();
                break;
            }

        case 'g': // Котангенс
            if (Sin(a) == 0) {
                cerr << "Error! (ctg) does not exist";
                return false;
            }
            else {
                tmp.type = '0';
                tmp.val = ctg(a);
                Number.push(tmp);
                Operations.pop();
                break;
            }
        case 'e':
            tmp.type = '0';
            tmp.val = exp(a);
            Number.push(tmp);
            Operations.pop();
            break;

        case 'b': // Перевод в 2-ю СС
            tmp.type = '0';
            tmp.val = bin(a);
            Number.push(tmp);
            Operations.pop();
            break;

        default:
            cerr << "Error";
            return 1;
            break;
    }

    return true;
}

int rangOperations(char Ch) {
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/' ) return 2;
    if (Ch == '!') return 3;
    if (Ch == '^') return 4;
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e' || Ch == 'b') return 5;
    return 0;
}

int logics(bool minus, stack <typeVal> &Number, stack <typeVal> &Operations, typeVal &tmp) {

    char Ch;
    double value;
    while (true) {

        Ch = cin.peek();
        if (Ch == '\n') {
            return 0;
        }

        if (Ch == ' ') {
            cin.ignore();
            continue;
        }

        // ------------------------------------ТРИГОНОМЕТРИЧЕСКИЕ ФУНКЦИИ------------------------------------ //
        if (Ch == 'p' ) { // Пи
            tmp.type = '0';
            tmp.val = Pi;
            Number.push(tmp);
            minus = false;
            cin.ignore();
            continue;
        }

        if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'e' || Ch == 'b') {
            char arrCh[3];
            for (int i = 0; i < 3; i++) {
                arrCh[i] = cin.peek();
                cin.ignore();
            }
            if (arrCh[0] == 's' && arrCh[1] == 'i' && arrCh[2] == 'n') {
                tmp.type = 's';
                tmp.val = 0;
                Operations.push(tmp);
                continue;
            }
            if (arrCh[0] == 'c' && arrCh[1] == 'o' && arrCh[2] == 's') {
                tmp.type = 'c';
                tmp.val = 0;
                Operations.push(tmp);
                continue;
            }
            if (arrCh[0] == 't' && arrCh[1] == 'a' && arrCh[2] == 'n') {
                tmp.type = 't';
                tmp.val = 0;
                Operations.push(tmp);
                continue;
            }
            if (arrCh[0] == 'c' && arrCh[1] == 't' && arrCh[2] == 'g') {
                tmp.type = 'g';
                tmp.val = 0;
                Operations.push(tmp);
                continue;
            }
            if (arrCh[0] == 'e' && arrCh[1] == 'x' && arrCh[2] == 'p') {
                tmp.type = 'e';
                tmp.val = 0;
                Operations.push(tmp);
                continue;
            }
            if (arrCh[0] == 'b' && arrCh[1] == 'i' && arrCh[2] == 'n') {
                tmp.type = 'b';
                tmp.val = 0;
                Operations.push(tmp);
                continue;
            }

        }

        // ----------------------------------------------ЧИСЛА---------------------------------------------- //
        if (Ch <= '9' && '0' <= Ch || Ch == '-' && minus == true) {
            cin >> value;
            tmp.type = '0';
            tmp.val = value;
            Number.push(tmp);
            minus = false;
            continue;
        }

        // --------------------------------------------ОПЕРАЦИИ-------------------------------------------- //
        if (Ch == '+' || Ch == '-' && minus == 0 || Ch == '*' || Ch == '/' || Ch == '^') {
            if (Operations.size() == 0) {
                tmp.type = Ch;
                tmp.val = 0;
                Operations.push(tmp);
                cin.ignore();
                continue;
            }
            if (Operations.size() != 0 && rangOperations(Ch) > rangOperations(Operations.top().type)) {
                tmp.type = Ch;
                tmp.val = 0;
                Operations.push(tmp);
                cin.ignore();
                continue;
            }
            if (Operations.size() != 0 && rangOperations(Ch) <= rangOperations(Operations.top().type)) {
                if (switchCase(Number, Operations, tmp) == false) return 1;
                continue;
            }
        }
        if (Ch == '!') {
            double a = Number.top().val;
            Number.pop();
            tmp.type = '0';
            tmp.val = factorial(a);
            Number.push(tmp);
            cin.ignore();
            continue;
        }

        // ---------------------------------------------СКОБКИ--------------------------------------------- //
        if (Ch == '(') {
            tmp.type = Ch;
            tmp.val = 0;
            Operations.push(tmp);
            cin.ignore();
            continue;
        }
        if (Ch == ')') {
            while (Operations.top().type != '(') {
                if (switchCase(Number, Operations, tmp) == false) {
                    return 1;
                } else continue;
            }
            Operations.pop();
            cin.ignore();
            continue;
        }

        else {
            cout << "Invalid expression" << endl;
            return -1;
        }
    }
}

int main() {
    typeVal tmp;
    stack <typeVal> Operations;
    stack <typeVal> Number;
    bool minus = true;
    cout << "Enter the expression: ";
    while (logics(minus, Number, Operations, tmp) != -1) {


        while (Operations.size() != 0) {
            if (switchCase(Number, Operations, tmp) == false) {
                return 1;
            } else continue;
        }
        cout << "Ans: " << Number.top().val << endl;
        cout << "Enter the expression: ";
        cin.clear();
        cin.get();

    }
}
