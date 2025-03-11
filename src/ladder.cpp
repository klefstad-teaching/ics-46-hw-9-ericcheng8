#include "ladder.h"
#include <unordered_set>

void error(string word1, string word2, string msg) {
    cout << word1 << word2 << msg;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1 == str2) return true;

    int len1 = str1.size();
    int len2 = str2.size();
    if(abs(len1 - len2) > d) return false;

    if (len1 == len2) {
        int differences = 0;
        for (int i = 0; i < len1; ++i) {
            if (str1[i] != str2[i]) {
                ++differences;
                if (differences > d) return false;
            }
        }
        return (differences <= d);
    } else {
        const string& shorter = (len1 > len2) ? str2 : str1;
        const string& longer = (len1 > len2) ? str1 : str2;
        int differences = 0;
        size_t i = 0, j = 0;
        while (j < shorter.size()) {
            if (longer[i] != shorter[j]) {
                if (++differences > d) return false;
                i++;
            } else {
                i++;
                j++;
            }
        }
        return ((differences + static_cast<int>(longer.size() - i)) <= d);
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> dummy;
    if (begin_word == end_word) return dummy;

    queue<vector<string>> Q;

    // label root as explored
    unordered_set<string> explored;
    explored.insert(begin_word);

    // Q.enqueue(root)
    vector<string> start = {begin_word};
    Q.push(start);

    // while Q is not empty do
    while (!Q.empty()) {
        // v := Q.dequeue()
        vector<string> v = Q.front();
        Q.pop();

        string last = v.back();

        // for all edges from v to w in G.adjacentEdges(v) do
        for (auto &w : word_list) {
            // if w is not labeled as explored then
            if (explored.find(w) == explored.end() && is_adjacent(last, w)) {
                // label w as explored
                explored.insert(w);

                vector<string> v_new = v;
                v_new.push_back(w);
                if (w == end_word) return v_new;
                
                // Q.enqueue(w)
                Q.push(v_new);
            }
        }
    }

    return dummy;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word) word_list.insert(word);
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << " ";
        }
        cout << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    vector<string> tmp;
    
    tmp = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(tmp);
    my_assert(tmp.size() == 4);

    tmp = generate_word_ladder("marty", "curls", word_list);
    print_word_ladder(tmp);
    my_assert(tmp.size() == 6);

    tmp = generate_word_ladder("code", "data", word_list);
    print_word_ladder(tmp);
    my_assert(tmp.size() == 6);

    tmp = generate_word_ladder("work", "play", word_list);
    print_word_ladder(tmp);
    my_assert(tmp.size() == 6);

    tmp = generate_word_ladder("sleep", "awake", word_list);
    print_word_ladder(tmp);
    my_assert(tmp.size() == 8);

    tmp = generate_word_ladder("car", "cheat", word_list);
    print_word_ladder(tmp);
    my_assert(tmp.size() == 4);

}
