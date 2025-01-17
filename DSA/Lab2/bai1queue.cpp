void interleaveQueue(queue<int>& q) {
    if (q.size() % 2 != 0) {
        return;
    }
    stack<int> s;
    int halfSize = q.size() / 2;
    for (int i = 0; i < halfSize; i++) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    for (int i = 0; i < halfSize; i++) {
        q.push(q.front());
        q.pop();
    }
    for (int i = 0; i < halfSize; i++) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
        q.push(q.front());
        q.pop();
    }
}