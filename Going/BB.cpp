#include <iostream>  
#include <queue>  
#include <algorithm>  
#include <cstring>  
#include <cmath>  
#include <iomanip>  
using namespace std;  
  
/* 
S棵卫星，P个村庄。有卫星的村庄间可以任意通信，否则村庄只能和距离小于D的村庄通信； 
求出D的最小值； 
显然D越小，就需要更大的卫星数量S； 
S棵卫星的存在允许存在S个连通分量； 
把最大的那S-1个连线砍掉，就形成S个联通分量，其中具有最小的D； 
转为求第S长的连线； 
可以用数组从小到大存储最小生成树的连线长度，共P-1条； 
第S长的连线即数组的第P-S-1号元素； 
*/  
  
//可以使用更经常使用的向量形式加以实现；  
  
int Pi[510]; //储存每个村庄的根；  
double d[510]; //从大到小存储边的长度；  
int m, k;  
struct CoorStruct  
{  
    double x, y;  
}Coor[510];  
  
struct EdgeStruct{  
    int u, v;  
    double w;  
}Edge[500000];  e
  
bool CMP(EdgeStruct e1, EdgeStruct e2)  
{  
    return e1.w < e2.w;  
}  
  
double GET_DIS(double x1, double y1, double x2, double y2)  
{  
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));  
}  
  
void INIT(int n)  
{ //认己作父；  
    for (int i = 1; i <= n; i++)  
        Pi[i] = i;  
}  
  
int FIND(int x)  
{ //返回根节点；  
    if (x != Pi[x])  
        Pi[x] = FIND(Pi[x]);  
    return Pi[x];  
}  
  
void MERGE(int a, int b)  
{ //合并两个集合；  
    int p = FIND(a);  
    int q = FIND(b);  
    if (p == q)  
        return;
	else
	{	
		Pi[p] = q;
		return;
	}	
}  
  
void KRUSKAL(int n)  
{ //将满足条件的边的长度放入数组d中；  
    k = 0;  
    for (int i = 0; i < m; i++)  
    {  
        if (FIND(Edge[i].u) != FIND(Edge[i].v))  
        {  
            MERGE(Edge[i].u, Edge[i].v);  
            d[k++] = Edge[i].w;  
            n--;  
            if (n == 1)  
                return;  
        }  
    }  
}  
  
int main()  
{  
    int casenum, snum, pnum;  
    double x, y;  
    cin >> casenum;  
    while (casenum--)  
    {  
        m = 0;  
        cin >> snum >> pnum;  
        INIT(pnum);  
        for (int i = 1; i <= pnum; i++)  
            cin >> Coor[i].x >> Coor[i].y;

        for (int i = 1; i <= pnum; i++)  
        {  
            for (int j = i + 1; j <= pnum; j++)  
            {
                Edge[m].u = i;  
                Edge[m].v = j;  
                Edge[m++].w = GET_DIS(Coor[i].x, Coor[i].y, Coor[j].x, Coor[j].y);  
                Edge[m].u = j;  
                Edge[m].v = i;  
                Edge[m++].w = Edge[m - 1].w; 
			}
        }  
        sort(Edge, Edge+m, CMP);  
        KRUSKAL(pnum);
        cout << fixed << setprecision(2) << d[pnum - snum - 1] << endl;  
    }  
    return 0;  
}  