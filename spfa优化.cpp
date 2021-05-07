
//  spfa�Ż� 
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
        //   LLL�Ż����Ѷ�ͷ��dis>ƽ��ֵ�ĵ���ڶ�β
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

                //  SLF�Ż������ý���dis���ڶ�ͷԪ�ؾͷŶ�β��������ڶ�ͷ
                if (!que.empty() && dis[v] <= dis[que.front()])
                    que.push_front(v);
                else
                    que.push_back(v);

                //  swap�Ż�������ͷԪ�ش��ڶ�βԪ�أ��򽻻���ͷ��
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
