int baseballScore(string ops) {
    stack<int> scores;
    int sum = 0;
    for (char op : ops) {
        if (op == 'C') {
            sum -= scores.top();
            scores.pop();
        } else if (op == 'D') {
            int prevScore = scores.top();
            int newScore = prevScore * 2;
            scores.push(newScore);
            sum += newScore;
        } else if (op == '+') {
            int prevScore1 = scores.top();
            scores.pop();
            int prevScore2 = scores.top();
            int newScore = prevScore1 + prevScore2;
            scores.push(prevScore1);
            scores.push(newScore);
            sum += newScore;
        } else {
            int newScore = op - '0';
            scores.push(newScore);
            sum += newScore;
        }
    }
    return sum;
}