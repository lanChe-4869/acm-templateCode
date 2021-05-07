
//  spfa优化 
void spfa(int st) {
    for (int i = 1; i <= n; ++i) {
        in[i] = done[i] = false;
        dis[i] = INF;
    }
    deque<int> que;
    que.push_back(st);
    in[st] = 1;
    dis[st] = 0;
    ll sum = 0;
    while (!que.empty()) {
        int x = que.front();
        //   LLL优化：把队头的dis>平均值的点放在队尾
        int sz = que.size();
        while (dis[x] * sz > sum) {
            que.push_back(x);
            que.pop_front();
            x = que.front();
        }
        que.pop_front();
        sum -= dis[x];
        in[x] = false;
        done[x] = true;
        for (int i = head[x]; ~i; i = edge[i].next) {
            int v = edge[i].to;
            if (dis[v] <= dis[x] + edge[i].dis) continue;
            dis[v] = dis[x] + edge[i].dis;
            if (!in[v]) {
                in[v] = true;

                //  SLF优化，当该结点的dis大于队头元素就放队尾，否则放在队头
                if (!que.empty() && dis[v] <= dis[que.front()])
                    que.push_front(v);
                else
                    que.push_back(v);

                //  swap优化，若队头元素大于队尾元素，则交换两头。
                if (que.front() > que.back()) swap(que.front(), que.back());
                sum += dis[v];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (done[i])
            printf("%lld\n", dis[i]);
        else
            puts("NO PATH");
    }
}
