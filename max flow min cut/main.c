//
//  main.c
//  max flow
//
//  Created by 김환석 on 2020/07/11.
//  Copyright © 2020 김환석. All rights reserved.
//

#include <stdio.h>

#define MAX 100
#define INF 100000000

int n = 6, result;
int c[MAX][MAX], f[MAX][MAX], d[MAX];

int front = -1;
int rear = -1;
int queue[MAX];

int graph[MAX][MAX];
int graph_size[MAX];

void maxFlow(int strat, int end);


int main(int argc, const char * argv[]) {
    graph[1][graph_size[1]++] = 2;
    graph[2][graph_size[2]++] = 1;
    c[1][2] = 12;
    
    graph[1][graph_size[1]++] = 4;
    graph[4][graph_size[4]++] = 1;
    c[1][4] = 11;
    
    graph[2][graph_size[2]++] = 3;
    graph[3][graph_size[3]++] = 2;
    c[2][3] = 6;
    
    graph[2][graph_size[2]++] = 4;
    graph[4][graph_size[4]++] = 2;
    c[2][4] = 3;
    
    graph[2][graph_size[2]++] = 5;
    graph[5][graph_size[5]++] = 2;
    c[2][5] = 5;
    
    graph[2][graph_size[2]++] = 6;
    graph[6][graph_size[6]++] = 2;
    c[2][6] = 9;
    
    graph[3][graph_size[3]++] = 6;
    graph[6][graph_size[6]++] = 3;
    c[3][6] = 8;
    
    graph[4][graph_size[4]++] = 5;
    graph[5][graph_size[5]++] = 4;
    c[4][5] = 9;
    
    graph[5][graph_size[5]++] = 3;
    graph[3][graph_size[3]++] = 5;
    c[5][3] = 3;
    
    graph[5][graph_size[5]++] = 6;
    graph[6][graph_size[6]++] = 5;
    c[5][6] = 4;
    
    maxFlow(1,6);
    printf("%d ", result);
    
    
}

void init_queue()
{
    front = -1;
    rear = -1;
}
int IsEmpty()
{
    if(front == rear)
        return 1;
    else
        return 0;
}
void push(int n)
{
    queue[++rear] = n;
}
int pop()
{
    return queue[++front];
}
int queue_front()
{
    int temp = front + 1;
    return queue[temp];
}

int min(int n1, int n2)
{
    if(n1 < n2)
        return n1;
    else
        return n2;
}

void maxFlow(int start, int end)
{
    while(1)
    {
        //모든 정점을 -1로 초기화
        for(int i = 0; i < MAX; i++)
            d[i] = -1;
        init_queue();
        push(start);
        while(IsEmpty() == 0)
        {
            int x = pop();
            for(int i = 0; i< graph_size[x]; i++)
            {
                int y = graph[x][i];
                
                if(c[x][y] - f[x][y] > 0 && d[y] == -1)
                {
                    push(y);
                    d[y] = x;
                    
                    if(y == end)
                        break;
                }
            }
            
        }
        if(d[end] == -1)
            break;
        int flow = INF;
        for(int i = end; i != start; i = d[i])
        {
            flow = min(flow, c[d[i]][i] - f[d[i]][i]);
        }
        
        for(int i = end; i != start; i = d[i])
        {
            f[d[i]][i] += flow;
            f[i][d[i]] -= flow;
        }
        result += flow;
    }
}




