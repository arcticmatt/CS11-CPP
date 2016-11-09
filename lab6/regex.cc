#include "regex.hh"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


/* Initialize the regex operator to apply exactly once. */
RegexOperator::RegexOperator() {
    minRepeat = 1;
    maxRepeat = 1;
}


/* Returns the "minimum repeat count" value. */
int RegexOperator::getMinRepeat() const {
    return minRepeat;
}


/* Returns the "maximum repeat count" value. */
int RegexOperator::getMaxRepeat() const {
    return maxRepeat;
}


/* Sets the "minimum repeat count" value. */
void RegexOperator::setMinRepeat(int n) {
    assert(n >= 0);
    minRepeat = n;
}


/* Sets the "maximum repeat count" value. */
void RegexOperator::setMaxRepeat(int n) {
    assert(n >= -1);
    maxRepeat = n;
}


/* Clears the list of matches stored in the regex operator.  Typically done
 * in preparation to try to match the regex to a new string.
 */
void RegexOperator::clearMatches() {
    matches.clear();
}


/* Records a new match of the operator in the list of matches. */
void RegexOperator::pushMatch(const Range &r) {
    matches.push_back(r);
}


/* Reports how many times the regex operator has successfully matched in the
 * string.
 */
int RegexOperator::numMatches() const {
    return (int) matches.size();
}


/* Removes the last match the operator successfully matched against.  Used for
 * backtracking by the regex engine.
 */
Range RegexOperator::popMatch() {
    Range r = matches.back();
    matches.pop_back();
    return r;
}


/* ===== Matching Functions ===== */
bool MatchChar::match(const string &s, Range &r) const {
    if (r.start >= s.size()) {
        return false;
    }

    if (s[r.start] == this->matchChar) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}


bool MatchAny::match(const string &s, Range &r) const {
    if (r.start >= s.size()) {
        return false;
    }

    r.end = r.start + 1;
    return true;
}


bool MatchFromSubset::match(const string &s, Range &r) const {
    if (r.start >= s.size()) {
        return false;
    }

    std::string::size_type found = this->subset.find(s[r.start]);
    if (found != std::string::npos) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}


bool ExcludeFromSubset::match(const string &s, Range &r) const {
    if (r.start >= s.size()) {
        return false;
    }

    std::string::size_type found = this->subset.find(s[r.start]);
    if (found == std::string::npos) {
        r.end = r.start + 1;
        return true;
    }

    return false;
}
/* ============================== */


/* Parse string representing a regex into a vector of RegexOperations. 
 * No error checking for now. Do this by iterating forward through the string
 * and checking each case.
 */
vector<RegexOperator *> parseRegex(const string &expr) {
    vector<RegexOperator *> ops;
    for (int i = 0; i < expr.size(); ++i) {
        // Handle all the cases
        if (expr[i] == '.') {
            // '.'
            RegexOperator *op = new MatchAny();
            ops.push_back(op);
        } else if (expr[i] == '[') {
            // '[] and [^]
            string subset = "";
            bool include = (expr[++i] != '^');
            if (!include) {
                i++;
            }
            while (expr[i] != ']') {
                subset += expr[i++];
            }
            if (include) {
                RegexOperator *op = new MatchFromSubset(subset);
                ops.push_back(op);
            } else {
                RegexOperator *op = new ExcludeFromSubset(subset);
                ops.push_back(op);
            }
        } else if (expr[i] == '?') {
            // '?'
            RegexOperator *back_op = ops.back();
            back_op->setMinRepeat(0);
            back_op->setMaxRepeat(1);
        } else if (expr[i] == '*') {
            // '*'
            RegexOperator *back_op = ops.back();
            back_op->setMinRepeat(0);
            back_op->setMaxRepeat(-1);
        } else if (expr[i] == '+') {
            // '+'
            RegexOperator *back_op = ops.back();
            back_op->setMinRepeat(1);
            back_op->setMaxRepeat(-1);
        } else {
            // Regular character
            RegexOperator *op = new MatchChar(expr[i]);
            ops.push_back(op);
        }
    }

    return ops;
}


/* Free memory and clear vector */
void clearRegex(vector<RegexOperator *> regex) {
    while (!regex.empty()) {
        RegexOperator *back_op = regex.back();
        delete back_op;
        regex.pop_back();
    }
}
