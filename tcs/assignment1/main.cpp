// Mukhammadrizo Maribjonov DS-AI-4


#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// 0 - states
// 1 - alphabet
// 2 - init states
// 3 - fin states
// 4 - transitions
vector<vector<string>> transitions = vector<vector<string>>();
vector<vector<string>> inputs = vector<vector<string>>();
/* true if vector contains given str */
bool contains(vector<string> alphabet, string word) {
    if (std::find(alphabet.begin(), alphabet.end(), word) == alphabet.end())
    {
        return false;
    }

    return true;
}

/* true if FSA is connected, false if there are any disjoints */
bool isConnected() {
    bool changed = true;
    vector<string> connected_nodes = vector<string>();
    connected_nodes.push_back(inputs[2][0]);
    while (changed) {
        changed = false;
        for (auto tr : transitions) {
            bool c_0 = contains(connected_nodes, tr[0]);
            bool c_1 = contains(connected_nodes, tr[2]);

            // if only one of them in connected nodes
            if ( c_0 && !c_1 ) {
                changed = true;
                connected_nodes.push_back(tr[2]);
            } else if (!c_0 && c_1) {
                changed = true;
                connected_nodes.push_back(tr[0]);
            }
        }
    }

    return connected_nodes.size() == inputs[0].size();
}

/* splits input from console into lists */
vector<string> splitter(unordered_map<string, vector<string>>& graph, string line, string delimiter = ",", bool special = false) {
    size_t indexer = 0;
    int c = 1;
    if (special) {
        c = 0;
    } else if (line[0] == 's') {
        indexer = 8;
    } else if (line[0] == 'a') {
        indexer = 7;
    } else if (line[0] == 'i') {
        indexer = 9;
    } else if (line[0] == 'f') {
        indexer = 8;
    } else if (line[0] == 't') {
        indexer = 7;
        line = line.substr(indexer, line.size()-indexer-1);
        vector<string>commaSep = splitter(graph, line, delimiter = ",", special = true);
        for (auto substr : commaSep) {
            vector<string> trans = splitter(graph,substr, delimiter = ">", special = true);
            transitions.push_back(trans);
            if (trans[0] != trans[2]) {
                if (!contains(graph[trans[2]], trans[0])) {
                    graph[trans[2]].push_back(trans[0]);
                }
                if (!contains(graph[trans[0]], trans[2])) {
                    graph[trans[0]].push_back(trans[2]);
                }
            } else {
                graph[trans[0]].push_back(trans[2]);
            }
        }

        return vector<string>();
    }

    string substring = line.substr(indexer, line.size() - indexer - c);
    if (substring == "") {
        return vector<string>();
    }

    vector<string> output = vector<string>();

    size_t pos = 0;
    string token;
    while ((pos = substring.find(delimiter)) != std::string::npos) {
        token = substring.substr(0, pos);
        output.push_back(token);
        substring.erase(0, pos + delimiter.length());
    }
    output.push_back(substring);

    return output;
}

/* true if E1 is identified */
bool E1(string& undef_str) {
    map<string, bool> approved_states = map<string, bool>();

    // validating states in initial states
    for(auto init_st : inputs[2]) {
        if (approved_states[init_st]) {
            continue;
        }
        if (!contains(inputs[0], init_st)) {
            undef_str = init_st;
            return true;
        }
        approved_states[init_st] = true;
    }

    // validating states in final states
    for(auto fin_st : inputs[3]) {
        if (approved_states[fin_st]) {
            continue;
        }
        if (!contains(inputs[0], fin_st)) {
            undef_str = fin_st;
            return true;
        }
        approved_states[fin_st] = true;
    }

    // validating states in transitions
    for(auto tr_st : transitions) {
        if (approved_states[tr_st[0]] && approved_states[tr_st[2]]) {
            continue;
        }

        // if first node is not valid
        if (!contains(inputs[0], tr_st[0]))
        {
            undef_str = tr_st[0];
            return true;
        }

        // if second node is not valid
        if (!contains(inputs[0], tr_st[2])) {
            undef_str = tr_st[2];
            return true;
        }

        approved_states[tr_st[0]] = true;
        approved_states[tr_st[2]] = true;
    }

    return false;
}

/* true if E2 is identified */
bool E2(unordered_map<string, vector<string>> graph) {

    if (!isConnected()) {
        return true;
    }
    return false;
}

/* true if E3 is identified */
bool E3(string& undefined_transition) {
    map<string, bool> valid_trans = map<string, bool>();
    for (auto tr : transitions) {
        if (!valid_trans[tr[1]]) {
            if (!contains(inputs[1], tr[1])) {
                undefined_transition = tr[1];
                return true;
            }

            valid_trans[tr[1]] = true;
        }
    }
    return false;
}

/* true if E4 is identified */
bool E4() {
    return inputs[2].empty();
}

/* false if str is not valid */
bool str_validator(string str) {
    if ((str.substr(0, 8) == "states=[" && str[str.size()-1] == ']') ||
        (str.substr(0, 7) == "alpha=[" && str[str.size()-1] == ']') ||
        (str.substr(0, 9) == "init.st=[" && str[str.size()-1] == ']') ||
        (str.substr(0, 8) == "fin.st=[" && str[str.size()-1] == ']') ||
        (str.substr(0, 7) == "trans=[" && str[str.size()-1] == ']')) {
        return true;
    }

    return false;
}

/* return true if FSA is complete, false otherwise */
bool isCompleteFSA() {

    // each key of a map is a node
    // each element of a set is a transition of from current node to some other node
    // to be complete fsa, each node should have same amount of trans as alphabet
    map<string, set<string>> node_transitions = map<string, set<string>>();
    for (auto tr : transitions) {
        node_transitions[tr[0]].insert(tr[1]);
    }

    for (auto node : node_transitions) {
        if (node.second.size() != inputs[1].size()) {
            return false;
        }
    }

    return true;
}
/* true when non deterministic */
bool isNonDeterministic() {

    // map of node, where each node has map of transition, and each node transition has a list of nodes where transition leads. If that list
    // is bigger than 1, it means that from one node more that 1 identical transitions are available to 2 different nodes => Non-deterministic
    map<string, map<string, vector<string>>> determ = map<string, map<string, vector<string>>>();
    for (auto tr : transitions) {
        determ[tr[0]][tr[1]].push_back(tr[2]);
        if (determ[tr[0]][tr[1]].size() > 1) {
            // false when non-determ
            return true;
        }
    }

    return false;
}

/* true if all states are reachable, false otherwise */
bool allStatesReachable(const vector<string>& states,
                        const vector<string>& alphabet,
                        const vector<string>& initialStates,
                        const vector<vector<string>>& transitions) {

    // set of all states
    unordered_set<string> States(states.begin(), states.end());

    // set of all alphabet symbols
    unordered_set<string> Symbols(alphabet.begin(), alphabet.end());

    // map of all transitions
    unordered_map<string, unordered_map<string, unordered_set<string>>> transition_map;
    for (const auto& t : transitions) {
        if (t.size() != 3) {
            return false;
        }
        const auto& begin_node = t[0];
        const auto& transition_Str = t[1];
        const auto& end_node = t[2];
        if (States.find(begin_node) == States.end() ||
            States.find(end_node) == States.end() ||
            Symbols.find(transition_Str) == Symbols.end()) {
            return false;
        }
        transition_map[begin_node][transition_Str].insert(end_node);
    }

    // BFS to find all reachable states
    unordered_set<string> visited;
    queue<string> queue1;
    for (const auto& s : initialStates) {
        queue1.push(s);
    }
    while (!queue1.empty()) {
        const auto& currState = queue1.front();
        queue1.pop();
        if (visited.find(currState) != visited.end()) {
            continue;
        }
        visited.insert(currState);
        for (const auto& sym : Symbols) {
            if (transition_map[currState].find(sym) != transition_map[currState].end()) {
                for (const auto& nextState : transition_map[currState][sym]) {
                    queue1.push(nextState);
                }
            }
        }
    }

    // check if all states are reachable
    for (const auto& s : States) {
        if (visited.find(s) == visited.end()) {
            return false;
        }
    }

    return true;
}
int main() {

    ifstream inputFile ("fsa.txt");
    ofstream outputFile;
    outputFile.open("result.txt");

    map<string, bool> states = map<string, bool>();
    vector<string> alphabet = vector<string>();
    vector<string> initial_states = vector<string>();
    vector<string> final_states = vector<string>();
    unordered_map<string, vector<string>> graph;

    string inputLine;
    vector<string> split_strings;
    bool isValidStr;
    while (getline(inputFile, inputLine)) {
        isValidStr = str_validator(inputLine);
        if (!isValidStr) {
            outputFile << "Error:" << endl;
            outputFile << "E5: Input file is malformed" << endl;
            outputFile.close();
        }
        inputs.push_back(splitter(graph, inputLine));
    }

    if (E4()) {
        outputFile << "Error:" << endl;
        outputFile << "E4: Initial state is not defined" << endl;
        outputFile.close();
        return 0;
    }

    string undefined_state;
    if(E1(undefined_state)) {
        outputFile << "Error:" << endl;
        outputFile << "E1: A state '" << undefined_state << "' is not in the set of states"<< endl;
        outputFile.close();
        return 0;
    }

    string undefined_trans;
    if (E3(undefined_trans)) {
        outputFile << "Error:" << endl;
        outputFile << "E3: A transition '" << undefined_trans << "' is not represented in the alphabet" << endl;
        outputFile.close();
        return 0;
    }

    // build graph
    for (auto st : inputs[0]) {
        if (graph[st].empty()) {
            graph[st] = vector<string>();
        }
    }
    if (E2(graph)) {
        outputFile << "Error:" << endl;
        outputFile << "E2: Some states are disjoint" << endl;
        outputFile.close();
        return 0;
    }

    bool isComplete = isCompleteFSA();
    if (isComplete) {
        outputFile << "FSA is complete" << endl;
    } else {
        outputFile << "FSA is incomplete" << endl;
    }

    bool w1, w2, w3;
    w1 = inputs[3].empty();
    w2 = !allStatesReachable(
            inputs[0],
            inputs[1],
            inputs[2],
            transitions
    );
    w3 = isNonDeterministic();

    if (w1 || w2 || w3) {
        outputFile << "Warning: " << endl;
    }

    if (w1) {
        outputFile << "W1: Accepting state is not defined" << endl;
    }
    if (w2) {
        outputFile << "W2: Some states are not reachable from the initial state" << endl;
    }

    if (w3) {
        outputFile << "W3: FSA is nondeterministic" << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
