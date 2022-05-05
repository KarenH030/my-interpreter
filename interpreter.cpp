#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>


int line = 1;



struct variable{
    std::string type;
    std::string value;
};
std::map<std::string, variable> var_info;

std::vector<std::string> keywords {"num", "boolean", "whether", "other", "cycle", "print"};


void interpretate(std::ifstream & fin);



bool is_arithmetical_operator(std::string& tmp) {

    const std::string arr[4] = {"+", "-", "*", "/"};

    for(int i = 0; i < 4; i++) {

        if(tmp == arr[i])
            return true;
    }
    return false;
}




bool is_identifier(std::string& token) {

    for(int i = 0; i < keywords.size(); i++) {

        if(token == keywords[i])
            return true;
    }
    return false;
}




void error () {
    std::cout << "You have  ERROR in the line number  " << line << "  !!!" << std::endl;
    exit(1);
}




double calculate (const double& a, const double& b, const char& ch) {

    double calculation = 0;

    switch(ch) {
        case '+':
                calculation = a + b;
                return calculation;
        case '-':
                calculation = a - b;
                return calculation;
        case '*':
                calculation = a * b;
                return calculation;
        case '/':
                calculation = a / b;
                return calculation;
        default :
                error();
                break;
    }
    return 0;
}



int keyword_check(std::string& first_token) {

    for (int i = 0; i < keywords.size(); i++) {
        if(keywords[i] == first_token)
            return i;
    }
    return -1;
}




bool is_arithmetical_symbol(const char& ch) {
    bool check = ((ch == 37) || (ch == 42) || (ch == 47) || (ch == 45) || (ch == 43));
    return check;
}





bool is_symbol(const char& ch){
    bool check = ((ch <= 90 && ch >= 65) || (ch <= 122 && ch >= 97));
    return check;
}






bool is_digit(const char& ch) {
    bool check = (ch <= 57 && ch >= 48);
    return check;
}





bool is_operator(char& ch) {
    bool check = ((ch == '!') || (ch == '=') || (ch == '>') || (ch == '<'));
    return check;
}





bool is_logical (std::string& token) {
    std::string arr[6] = {"==", "!=", ">=", "<=", "<", ">"};
    for(int i = 0; i < 6; i++) {
        if(token == arr[i])
            return true;
    }
    return false;
}




void do_output_print(std::ifstream& fin, int& type_index) {
    std::string token;
    fin >> token;
    int index = keyword_check(token);

    if(token == "#") {
        std::string expression = "";
        while(token != "#") {
            fin >> token;
            expression = expression + token + " ";
        }
        std::cout << expression;
    }
    else if(token == "##") {
        std::string expression = "";
        while(token != "##") {
            fin >> token;
            expression = expression + token + " ";
        }
        std::cout << expression << std::endl;
    }
    else if(index < 6) {
        error();
    }
    else if(index > 5) {
        std::cout << keywords[index] << std::endl;
    }
    else
        error();
}





bool check_boolean(const std::string& str1, const std::string& str2, const std::string& oper) {
    const std::string arr[7] = {"==", "!=", ">=", "<=", ">", "<"};
    bool check = false;
    double a = 0, b = 0;
    for(int i = 0; i < keywords.size(); i++) {
        if(str1 == keywords[i])
            a = std::stod(var_info[str1].value);
        if(str2 == keywords[i])
            b = std::stod(var_info[str2].value);
    }

    for(int i = 0; i < 6; i++) {
        if(oper == arr[i]) {
           switch(i) {
                case 0:
                return check = (a == b);
                break;
                case 1:
                return check = (a != b);
                break;
                case 2:
                return check = (a >= b);
                break;
                case 3:
                return check = (a <= b);
                break;
                case 4:
                return check = (a > b);
                break;
                case 5:
                return check = (a < b);
                break;
           }
        }
    }
    return check;
}





bool check_condition(std::string& expression) {
    int size = 0;
    for( ; expression[size] != '\0'; size++){}
    std::string name1 = "";
    std::string name2 = "";

    for(int i = 0; i < size; i++) {
        if(is_operator(expression[i])) {
            if(is_operator(expression[i + 1])) {
                std::string tmp = "";
                tmp = expression[i] + expression[i + 1];
                int a = i - 1;
                int b = i + 2;
                while(is_symbol(expression[a]) || is_symbol(expression[b])) {
                    if(is_symbol(expression[a])){
                        name1 = expression[a] + name1;
                        --a;
                    }
                    if(is_symbol(expression[b])){
                        name2 = name2 + expression[b];
                        ++b;
                    }
                }
                return check_boolean(name1, name2, tmp);
            }

            else {
                std::string tmp = "";
                tmp = expression[i];
                int a = i - 1;
                int b = i + 1;
                while(is_symbol(expression[a]) || is_symbol(expression[b])) {
                    if(is_symbol(expression[a])) {
                        name1 = expression[a] + name1;
                        --a;
                    }
                    if(is_symbol(expression[b])){
                        name2 = name2 + expression[b];
                        ++b;
                    }
                }
                return check_boolean(name1, name2, tmp);
            }
        }
    }

    return false;
}





int functioning (std::string& expression) {

    int size = 0;
    for( ; expression[size] != '\0'; size++) {}
    std::string tmp1 = "";
    std::string tmp2 = "";
    double num1 = 0;
    double num2 = 0;
    double sum = 0;
    int a = 0;
    while(is_digit(expression[a])) {

      if(is_digit(expression[a]))
           tmp1 = tmp1 + expression[a];

         ++a;
    }



    for(int i = 0; i < size; i++) {

        if(is_arithmetical_symbol(expression[i])) {
            int k = i + 1;
            char ch = expression[i];

            if(is_symbol(expression[k]))
                error();

            while(is_digit(expression[k])) {

                if(is_digit(expression[k]))
                    tmp2 = tmp2 + expression[k];

                ++k;
            }

            num1 = std::stod(tmp1); 
            num2 = std::stod(tmp2);
            sum = calculate(num1, num2, ch);
            tmp1 = std::to_string(sum);
            expression.erase(0,k); 
            tmp2.clear();
        }
    }
    return sum;
}




void do_boolean(std::ifstream& fin, int& type_index) {

        std::string token;
    do{
        std::string name;
        fin >> token;
        if (is_identifier(token)) 
            error();

        var_info[token].type = keywords[type_index];
        keywords.push_back(token);
        name = token;
        fin >> token;
        if(token == "=") {
           fin >> token;

           std::string tmp;
           fin >> tmp;
           if(tmp == "," || tmp == ";") {
                int index = keyword_check(token);

                if (index > 6) {
                    if(var_info[keywords[index]].value != "0")
                        var_info[name].value  = "1";
                    else
                        var_info[name].value  = "0";
                }
                else if(index == -1) {
                    if(is_digit(token[0])) {
                        if(token == "0")
                            var_info[name].value  = "0";
                        else
                            var_info[name].value  = "1";
                    }
                    else
                        var_info[name].value = token;
                }
                else
                    error();

                if(token == "true")                                    
                    var_info[name].value  = "1";
                else if(token == "false") {
                    var_info[name].value  = "0";
                }
                token = tmp;
           }
	   else if (is_arithmetical_operator(tmp)) {

               std::string expression = "";
               expression += token + tmp;
               while (token != "," && token != ";"){
                                fin >> token;
                   expression += token;
               }
               var_info[name].value = functioning(expression);
           }
           else if(is_logical(tmp) || tmp == "(") {

               std::string expression = "";
               expression += token + tmp;
               while (token != "," && token != ";" && token != ")") {

                   fin >> token;
                   expression += token;
               }
               var_info[name].value = check_condition(expression);
           }
           else
               error();

        }
    }while(token != ";" && !(keyword_check(token) + 1));
}





void for_other_operations(std::ifstream& fin, std::string& token) {

    std::string that_line;
 do{
        std::string str = token;
        int index = keyword_check(str);
        if(index < 6)
            error();
        else {
            fin >> that_line;
            if(that_line == "=") {

                std::string expression;
                while(that_line != ";" || that_line != ",") {
                    fin >> that_line;
                    expression = expression + that_line;
                }
                var_info[str].value = functioning(expression);
                if(that_line == ",") {
                    fin >> that_line;
                    str = that_line;
                }
            }
            else
                error();
        }

    }while(that_line != ";" && !(keyword_check(that_line) + 1));
}




void declerate (std::ifstream& fin, const int type_index){
    std::string token;
    do{
        std::string name;
        fin >> token;
        if (is_identifier(token)) 
            error();

        var_info[token].type = keywords[type_index];
        keywords.push_back(token);
        name = token;
        fin >> token;
        if(token == "=") {
           fin >> token;

           std::string tmp;
           fin >> tmp;
           if(tmp == "," || tmp == ";") {

                int index = keyword_check(token);

                if (index > 6)
                    var_info[name].value  = var_info[keywords[index]].value;
                else if(index == -1){
                       var_info[name].value = token;
                }
                else
                    error();

                token = tmp;
           }
           else if (is_arithmetical_operator(tmp)) {

               std::string expression = "";
               expression += token + tmp;
               while (token != "," && token != ";") {
                   fin >> token;
                   expression += token;
               }
               var_info[name].value = functioning(expression);
           }
           else
               error();
        }
    }while(token != ";" && !(keyword_check(token) + 1));
}



void checking_condition_code(std::ifstream& fin) {

    std::string token;
    fin >> token;

    if(token == "{") {
        while(token != "}") {
            fin >> token;
            interpretate(fin);
        }
    }
    else
        error();
}




void do_condition_else(std::ifstream& fin, int& type_index) {
    checking_condition_code(fin);
}




// whether 
void do_condition (std::ifstream& fin, const int& type_index){ 
    std::string token;
    std::string name;
    fin >> token;
    if(token == "("){
        fin >> token;
        std::string tmp;
        fin >> tmp;
        if(keyword_check(token) == -1)
            error();
        if(!is_logical(tmp))
            error();
        std::string expression;
        expression += token + tmp;
        while(token != ")") {
            fin >> token;
            expression += token;
        }
        if (check_condition(expression))
            checking_condition_code(fin);
        else
            return;
    }
    else
        error();

}





void do_cycle (std::ifstream& fin, int& type_index) {
    std::string token;
    fin >> token;
    if(token == "(") {
        std::string expression = "";
        while(token != ")") {
            fin >> token;
            expression = expression + token;
        }
        if(check_condition(expression)) {
            std::string tmp;
            fin >> tmp;
            if(tmp == "{") {
                while(tmp != "}")
                    interpretate(fin);
            }
        }
        else
            return;
    }
    else
        error();
}





int main()
{
    std::ifstream file;
    std::string path ;
    do{
        std::cout << "Enter file name: ";
        std::cin >> path;
        file.open(path);
    }while(!file.is_open());


    if(file.is_open())
        interpretate(file);
    else
        std::cout << "Something was gone wrong !" << std::endl;

    file.close();
}




void interpretate(std::ifstream& fin) {

    std::string token = "";

    while (!fin.eof()) {
        static bool check_for_condition_else = false;
        fin >> token;
        int which_keyword = keyword_check(token);

        switch (which_keyword) {
            case 0: // num
                declerate(fin, which_keyword); 
                break;
            case 1:  //boolean
                do_boolean(fin, which_keyword); 
                break;
            case 2: // whether
                do_condition(fin, which_keyword); 
                break;
            case 3: // other
                if(check_for_condition_else)  
                    do_condition_else(fin, which_keyword);
                else
                    error();
                break;
            case 4: // whilst
                do_cycle(fin, which_keyword);  
                break;
            case 5: // print
                do_output_print(fin,which_keyword); 
                break;
            case -1:
                error();
                break;
            default: 
                for_other_operations(fin, token); 
                break;

        }
        if(which_keyword != 2)
            check_for_condition_else = false;
        else
            check_for_condition_else = true;

        line++;
    }
}

