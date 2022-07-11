#include <iostream>
#include <string>
#include <vector>

#include "stringB.h"

class Logic {
private:
    std::string memInp;
    std::vector<bool> currentBools;
    std::string vars = "";
    std::vector<bool> res;
    int varAmount;

    stringB inp = "";

    enum {
        NOT,
        PAR,
        AND,
        XOR,
        OR,
        IMPLY,
        EQ
    };
    std::string bools = "01";
    std::string symbs = "!(&^|)>= ";
    std::string opera = "!(&^|>=";

    stringB changeInpFormant(std::string inp){
        stringB tempInp = "";
        
        for(int i = 0; i < inp.size(); ++i){
            if(inp[i] != ' '){ 
                tempInp += inp[i];
                tempInp += ' ';
            }
        }
        tempInp.pop_back();

        return tempInp;
    }

    inline bool isBool(char symb) {
        for (int i = 0; i < bools.size(); ++i) {
            if (symb == bools[i]) return true;
        }
        return false;
    }

    inline bool isOperator(char symb) {
        for (int i = 0; i < symbs.size(); ++i) {
            if (symb == symbs[i]) { return true; }
        }
        return false;
    }

    inline bool isIncludedInVars(char symb){
        for(int i = 0; i < vars.size(); ++i){
            if(symb == vars[i]) { return true; }
        }
        return false;
    }

    int checkForVarAmount() {
        int count = 0;

        for (int i = 0; i < inp.size(); ++i) {
            if (!isOperator(inp[i]) && !isIncludedInVars(inp[i])) {
                vars += inp[i];
                ++count;
            }
        }
        return count;
    }

    void initCurrentBools(){
        currentBools.clear();
        for(int i = 0; i < varAmount; ++i) currentBools.push_back(false);
    }

    bool checkIfDone(std::vector<bool>& currentBools) {
        bool res = true;

        for (int i = 0; i < currentBools.size(); ++i) {
            res = res && currentBools[i];
            if (!res) return false;
        }
        return true;
    }

    inline void createCurrentBoolVect(std::vector<bool>& currentBools) {
        for (int i = 0; i < varAmount; ++i) currentBools.push_back(false);
    }

    void nextBoolComb(std::vector<bool>& currentBools, int currentBool) {
        if (currentBool != 0 && currentBools[currentBool]) {
            currentBools[currentBool] = false;
            nextBoolComb(currentBools, currentBool - 1);
        }
        else currentBools[currentBool] = true;
    }

    stringB createSubRes(std::string inp, int j) {
        stringB subProc = "";
        int parCount = 1;

        for (int currentJ = j + 2; ; ++currentJ) {
            if (currentJ == inp.size()) throw;

            if(inp[currentJ] == '(')      ++parCount;
            else if(inp[currentJ] == ')') --parCount;

            if(parCount == 0) break;

            subProc += inp[currentJ];
        }
        subProc.pop_back();

        //std::cout << subProc << "\n";

        return subProc;
    }

    int findIndexOfVar(char ch) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i] == ch) return i;
        }

        return -1;
    }

    bool evaluateLogicalOperation(stringB inp, int i, int j) {
        bool done = false;
        bool evalueted;
        bool varIndex[2];
        bool invIndex[2] {false, false};

        int taskCounter = 0;
        std::string currentTask = "";

        currentTask += inp[j - 2];
        currentTask += inp[j + 2];
        
        for(int i = 0; i < 2; ++i){
            if(isBool(currentTask[i])) varIndex[i] = charToBool(currentTask[i]);
            else varIndex[i] = currentBools[findIndexOfVar(currentTask[i])];

            if(inp.giveFlagAt(j - 2 + 4 * i)) varIndex[i] = !varIndex[i];
        }

        switch (i) {
        case AND:
            evalueted = varIndex[0] && varIndex[1];
            break;
        case XOR:
            evalueted = varIndex[0] ^ varIndex[1];
            break;
        case OR:
            evalueted = varIndex[0] || varIndex[1];
            break;
        case IMPLY:
            if(varIndex[0] && !varIndex[1]) evalueted = false;
            else evalueted = true;
            break;
        case EQ:
            evalueted = varIndex[0] == varIndex[1];
            break;
        default:
            throw;
        }

        return evalueted;
    }

    inline std::string boolToString(bool b) { return b ? "1" : "0"; }
    inline bool charToBool(char c) { return (c == '1' ? true : false); }

    bool mainProc(stringB inp) {
        stringB subRes;
        bool subResBool;
        int unaryOp = 0;
        bool fastDone = false;
        bool memPar = false;

        for (int i = 0; i < opera.size(); ++i) {
            for (int j = 0; j < inp.length(); ++j) {
                if(inp.size() == 1){
                    if(isBool(inp[0])) subResBool = charToBool(inp[0]);
                    else subResBool = currentBools[findIndexOfVar(inp[0])];

                    if(inp.giveFlagAt(0)) subResBool = !subResBool;

                    fastDone = true;

                    break;
                }
                else if (opera[i] == inp[j]) {
                    if (i == NOT){
                        //inp.printIds();
                        if(opera[i] == inp[j + 2]) inp.erase(j, 4);
                        else{
                            inp.erase(j, 2);
                            inp.setFlagAt(j, true);
                        }
                        //inp.printIds();
                    }
                    else if (i == PAR) {
                        if(inp.giveFlagAt(j)) memPar = true;

                        subRes = createSubRes(inp, j);
                        subResBool = mainProc(subRes);
                        inp.replace(j, subRes.size() + 4, boolToString(subResBool));

                        if(memPar) inp.setFlagAt(j);
                    }
                    else {
                        subResBool = evaluateLogicalOperation(inp, i, j);
                        inp.replace(j - 2, 5, boolToString(subResBool));
                    }
                    
                    j = -1;
                }
            }
            if(fastDone) break;
        }

        return subResBool;
    }
    
public:
    Logic(std::string tempInp) {
        inp = changeInpFormant(tempInp);

        //memInp.copy(inp);
        varAmount = checkForVarAmount();
        if(varAmount > 0){
            initCurrentBools();

            while (!checkIfDone(currentBools)) {
                res.push_back(mainProc(inp));
                nextBoolComb(currentBools, currentBools.size() - 1);
            }
            res.push_back(mainProc(inp));
        }
        else std::cerr << "No variables inputed\n";
    }

    void showTable() {
        initCurrentBools();

        for(int i = 0; i < varAmount; ++i){
            std::cout << vars[i] << " ";
        }
        std::cout << "\n";

        for (int i = 0; i < res.size(); ++i) {
            for(int j = 0; j < varAmount; ++j){
                std::cout << currentBools[j] << " ";
            }
            std::cout << "| ";

            std::cout << res[i] << "\n";
            nextBoolComb(currentBools, currentBools.size() - 1);
        }
    }

    bool operator[](int index){ 
        if(index <= res.size() && index >= 0) return res[index];
        else throw; 
    }
};

int main(int argc, char* argv[]) {

    std::string test;
    std::getline(std::cin, test);
    std::cout << "\n";
    //test = "! a & ! b";

    Logic l(test);
    l.showTable();
}