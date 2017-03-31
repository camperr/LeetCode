#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Edge{
    Edge *last;
    int wi;
    int h;
};

int is_conn(string u, string v, int size){
    int i;
    int dis = 0;
    //cout<<"conn "<<u<<" "<<v<<" "<<size<<endl;
    for(i=0; i<size; i++){
        if(u[i]!=v[i]) dis++;
    }
    return dis==1;
}

vector<string> find_path(Edge *e, int path_len, int n, vector<string> &wordList, string &beginWord){
    vector<string> path(path_len);
    Edge *p = e;
    int i=path_len - 1;
    while(p != NULL){
        if(p->wi == -1){
            path[i--] = beginWord;
        }else{
            path[i--] = wordList[p->wi];
        }
        p = p->last;
    }
    return path;
}

class Solution {
public:
    vector<vector<string> > findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int i,j,k;
        int n = beginWord.size();
        int w = wordList.size();
        vector<vector<string> > res;
        int path_cnt;
        int* h = new int[w];
        Edge* qu = new Edge[w*w];
        vector<vector<int> > conn(w);
        int p,q;
        int hend = -1;
        int endi = -1;
        for(i=0;i<w;i++){
            for(j=0;j<i;j++){
                if(is_conn(wordList[i], wordList[j], n)){
                    conn[i].push_back(j);
                    conn[j].push_back(i);
                }
            }
        }
        for(i=0; i<w; i++) h[i] = -1;
        p = 1;
        q = 0;
        Edge head = {NULL, -1, 0};
        qu[0] = head;
        path_cnt = 0;
        for(i=0; i<w; i++){
            if(wordList[i] == endWord) endi = i;
        }
        if(endi == -1) return res;
        
        while(q < p){
            
            Edge* cur= &(qu[q]);
            if(hend != -1 && cur->h == hend) break;
            q++;
            if(cur->h == 0){
                for(i=0; i<w; i++){
                    if(is_conn(beginWord, wordList[i], n)){
                        h[i] = 1;
                        Edge ei = {cur, i, 1};
                        qu[p++] = ei;
                        if(endi == i){
                            hend = h[i];
                            path_cnt ++;
                        }
                    }
                } 
                continue;
            }
            int conn_cnt = conn[cur->wi].size();
            for(j=0; j<conn_cnt; j++){
                i = conn[cur->wi][j];
                if(h[i] == -1) h[i] = cur->h + 1;
                else if(h[i] < cur->h + 1) continue;
                Edge ei = {cur, i, h[i]};
                qu[p++] = ei;
                if(endi == i){
                    hend = h[i];
                    path_cnt ++;
                }
            }
        }
        i=0;
        while(q < p){
            Edge *cur = &(qu[q++]);
            if(cur->wi != endi) continue;
            res.push_back(find_path(cur, hend + 1, n, wordList, beginWord));
        }
        return res;  
    }
};