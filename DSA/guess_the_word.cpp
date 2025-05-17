https://leetcode.com/problems/guess-the-word/


here idea is to reduce the possible candidates

class Solution {

    int dist(const string& a, const string &b) 
    {
        // Maybe this can be memoized if too slow.
        int dist = 0;
        for (int idx = 0; idx < a.size(); ++idx) {
            dist += a[idx] == b[idx];
        }
        return dist;
    }
    
    int maxEquidistantSetSize(const string& word, const unordered_set<string>& guessSet) 
    {
        vector<int> hist(word.size() + 1, 0);    
        for (auto& guess : guessSet) {
            ++hist[dist(word, guess)];
        }
        return *max_element(hist.cbegin(), hist.cend());
    }
    
    string maxPartitioningGuess(const vector<string>& wordlist, const unordered_set<string>& guessSet)
    {
        // to isme basically ek esa word joh equally similar ho sab candidates se so that skew na ho
        //and probability of removing maximum number of candidates is high
        auto maxGuessIt = wordlist.cend();
        int minMax = wordlist.size();
        for (auto it = wordlist.cbegin(); it != wordlist.cend(); ++it) {
            int curMax = maxEquidistantSetSize(*it, guessSet);
            if (curMax < minMax) {
                minMax = curMax;
                maxGuessIt = it;
            }
        }
        return *maxGuessIt;
    }
    
public:
    void findSecretWord(vector<string>& wordlist, Master& master) 
    {
        // Start guessing
        unordered_set<string> guessSet(wordlist.cbegin(), wordlist.cend());
        while (guessSet.size() > 1) {
            // Calculate max partitioning elem taken from full word list
            string guessWord = maxPartitioningGuess(wordlist, guessSet);

            // we can also randomly pick a word from candidate list and remove other based on that
            // it will also pass all the test cases
        
            // Try the guess
            int d = master.guess(guessWord);
            if (d == guessWord.size()) return; // Got lucky!

            // Eliminate words whose distance != d
            for (auto it = guessSet.begin(); it != guessSet.end();) {
                if (dist(guessWord, *it) != d) {
                    it = guessSet.erase(it);
                } else {
                    ++it;
                }
            }
        }
        if (!guessSet.empty()) {
            master.guess(*guessSet.cbegin());
        }
    }
};