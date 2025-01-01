vector<int> stock_span(const vector<int>& ns) {
    int n = ns.size();
    if (n == 0) {
        return vector<int>();
    }
    vector<int> span(n, 1);
    stack<int> s;
    s.push(0);
    for (int i = 1; i < n; i++) {
        while (!s.empty() && ns[s.top()] <= ns[i]) {
            s.pop();
        }
        if (s.empty()) {
            span[i] = i + 1;
        }
        else {
            span[i] = i - s.top();
        }
        s.push(i);
    }
    return span;
}