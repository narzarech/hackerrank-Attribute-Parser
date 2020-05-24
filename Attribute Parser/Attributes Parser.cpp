#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
void cleanTag(vector<string>& tag) {
    tag[0].erase(0, 1);
    /*if (tag[0][0] == '/') {
        tag[0].erase(0, 1);
    }*/

    if (tag.size() > 1) {
        for (unsigned i = 3; i < tag.size(); i = i + 3) {
            tag[i].erase(0, 1);
            tag[i].erase(tag[i].size() - 1, 1);
        }
    }
    tag[tag.size() - 1].erase(tag[tag.size() - 1].size() - 1, 1);
}
void stdQuery(string& str, vector<string>& query) {
    for (auto& c : str) {
        if (c == '.' || c == '~') {
            c = ' ';
        }
    }
    stringstream ss(str);
    string word;
    while (ss >> word) {
        query.push_back(word);
    }
}
string scan(const vector<string>& query, const vector<vector<string>>& tags) {
    unsigned i = 0;
    for (; i < tags.size(); ++i) {
        if (tags[i][0] == query[query.size() - 2]) {
            break;
        }
    }
    if (i == tags.size()) {
        return "Not Found!"; //tag not exist
    }
    //data is a string array containing the appropriate address of a tag
    vector<string> data;
    for (unsigned j = 0; j <= i; ++j) {
        data.push_back(tags[j][0]);
    }
    //keep incomplete tags
    vector<string>cmp, incmp, rec;
    vector<unsigned>pos;
    for (unsigned n = 0; n != data.size(); ++n) {
        if (data[n][0] == '/') {
            string temp = data[n];
            temp.erase(0, 1);
            cmp.push_back(temp);
        }
        else {
            incmp.push_back(data[n]);
        }
    }
    for (unsigned a = 0; a != cmp.size(); ++a) {
        for (unsigned b = 0; b != incmp.size(); ++b) {
            if (cmp[a] == incmp[b]) {
                pos.push_back(b);
                break;
            }
        }
    }
    for (unsigned c = 0; c != incmp.size(); ++c) {
        unsigned d = 0;
        for (; d != pos.size(); ++d) {
            if (c == pos[d]) {
                break;
            }
        }
        if (d == pos.size()) {
            rec.push_back(incmp[c]);
        }
    }

    /*auto it = std::unique(data.begin(),data.end());
    data.resize(std::distance(data.begin(), it));
    for (int j = i; j >= 0; --j) {
        if (tags[j][0][0] != '/') {
            temp.push_back(tags[j][0]);
        }
        else {
            break;
        }
    }*/

    //compare query to the appropriate address of a tag
    if (rec.size() == query.size() - 1) {
        for (unsigned k = 0; k < rec.size(); ++k) {
            if (rec[k] != query[k]) {
                return "Not Found!"; //different
            }
        }
    }
    else {
        return "Not Found!"; //different
    }
    //Reference the attribute
    unsigned m = 1;
    for (; m < tags[i].size(); m = m + 3) {
        if (tags[i][m] == query[query.size() - 1]) {
            break;
        }
    }
    if (m <= tags[i].size() - 1) {
        return tags[i][m + 2];
    }
    else {
        return "Not Found!";
    }
}
int main() {
    int nTags, nQueries; cin >> nTags >> nQueries;
    cin.ignore(32767, '\n');
    vector<vector<string>> tags;
    //Process each tag
    for (int i = 0; i < nTags; ++i) {
        string line, word;
        getline(cin, line);
        stringstream ss(line);

        //Process each word in a tag
        vector<string> oneTag;
        while (ss >> word) {
            oneTag.push_back(word);
        }
        cleanTag(oneTag);
        tags.push_back(oneTag);
    }
    vector<vector<string>> queries;
    //Process each query
    for (int i = 0; i < nQueries; ++i) {
        string line;
        getline(cin, line);

        vector<string>oneQuery;
        stdQuery(line, oneQuery);
        queries.push_back(oneQuery);
    }
    for (int i = 0; i < nQueries; ++i) {
        cout << scan(queries[i], tags) << endl;
    }
    return 0;
}
