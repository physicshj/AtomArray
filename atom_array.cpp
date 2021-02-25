#include <cstdio>
#include <string>
#include <cstdlib>
#include <malloc.h>
#include <queue>
#include <iostream>
using namespace std;

const int N = 200;//�������й�ģ
const int M = 1000;//�����������ģ

int N_array,M_array;//��ʾ�������еĴ�С��N*M
int n_array, m_array;//��ʾ������λ��Ҫ���n*m�����У�������ΪĿ������
char Array[N][N];//�ڽӾ���洢ԭ��������Ϣ��*��ʾ��ԭ��
int Arraycopy[N][N];
bool FlagArray[N][N];//���bfs�з��ʹ��ĵ�
bool Flagarea[M];//����Ѿ�ȷ��������С�������ĵ�
int AreaNum;//Ŀ�������з�տ�����ĸ���
int findarea_sequence[M];//����Ŀǰ���Ľ��

queue<int> q_x, q_y;//����bfs�Ķ��д洢�������

struct node1 {
	int edge_pointx[N], edge_pointy[N];//�洢ĳ������߽��ϵĵ������
	int num ;//�߽��ϵ�ĸ���
}area[N];

struct node2 {//�洢��С��������
	int x, y;
	struct node2* pre,* next;
}*head[M],*tail[M];

struct node3 {//�洢Ѱ�ҵ�·��
	int parent_x,parent_y;
}path[N][N];

bool JudgeInside(int x,int y) {//�ж�(x,y)�Ƿ���Ŀ��������
	if (x < (N_array - n_array) / 2 + 1)return false; 
	if (x > (N_array + n_array) / 2)return false;
	if (y < (M_array - m_array) / 2 + 1)return false; 
	if (y > (M_array + m_array) / 2)return false;
	return true;
}

bool JudgeEdge(int x, int y) {//�ж�(x,y)�Ƿ���ĳ������ı߽���
	if (Array[x + 1][y] == '*')return true;
	if (Array[x - 1][y] == '*')return true;
	if (Array[x][y + 1] == '*')return true;
	if (Array[x][y - 1] == '*')return true;
	return false;
}
 
void Number(int x,int y) {//dfs��һ����ͨ������Ϻţ����Ϊ��ǰ��AreaNum
	Arraycopy[x][y] = AreaNum;
	if (JudgeEdge(x, y)) {
		area[AreaNum].num++;
		area[AreaNum].edge_pointx[area[AreaNum].num] = x;
		area[AreaNum].edge_pointy[area[AreaNum].num] = y;
	}
	if (Arraycopy[x + 1][y] == -2 && JudgeInside(x + 1, y))Number(x + 1, y);
	if (Arraycopy[x - 1][y] == -2 && JudgeInside(x - 1, y))Number(x - 1, y);
	if (Arraycopy[x][y + 1] == -2 && JudgeInside(x, y+1))Number(x, y+1);
	if (Arraycopy[x][y -1 ] == -2 && JudgeInside(x, y-1))Number(x, y-1);
}

void bfs(int findarea_num) {
	int x, y;
	struct node2* tmp;
	while (!q_x.empty()) {
		x = q_x.front();
		y = q_y.front();
		q_x.pop();
		q_y.pop();
		if (Arraycopy[x + 1][y] > 0 && !Flagarea[Arraycopy[x + 1][y]]) {
			Flagarea[Arraycopy[x + 1][y]] = true;
			findarea_sequence[findarea_num] = Arraycopy[x + 1][y];
			tail[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->next = NULL;
			tail[findarea_num]->x = x + 1;
			tail[findarea_num]->y = y;
			head[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->pre = head[findarea_num];
			head[findarea_num]->next = tail[findarea_num];
			head[findarea_num]->pre = NULL;
			while (path[x][y].parent_x != 0) {
				tmp = (node2*)malloc(sizeof(node2));
				tmp->x = x;
				tmp->y = y; printf("(%d,%d)\n", x, y);
				tmp->next = head[findarea_num]->next;
				tmp->pre = head[findarea_num];
				head[findarea_num]->next = tmp;
				x = path[x][y].parent_x;
				y = path[x][y].parent_y;
			}
			head[findarea_num]->x = x;
			head[findarea_num]->y = y;
			break;
		}
		if (Arraycopy[x - 1][y] > 0 && !Flagarea[Arraycopy[x - 1][y]]) {
			Flagarea[Arraycopy[x - 1][y]] = true;
			findarea_sequence[findarea_num] = Arraycopy[x - 1][y];
			tail[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->next = NULL;
			tail[findarea_num]->x = x - 1;
			tail[findarea_num]->y = y;
			head[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->pre = head[findarea_num];
			head[findarea_num]->next = tail[findarea_num];
			head[findarea_num]->pre = NULL;
			while (path[x][y].parent_x != 0) {
				tmp = (node2*)malloc(sizeof(node2));
				tmp->x = x;
				tmp->y = y; printf("(%d,%d)\n", x, y);
				tmp->next = head[findarea_num]->next;
				tmp->pre = head[findarea_num];
				head[findarea_num]->next = tmp;
				x = path[x][y].parent_x;
				y = path[x][y].parent_y;
			}
			head[findarea_num]->x = x;
			head[findarea_num]->y = y;
			break;
		}
		if (Arraycopy[x][y + 1] > 0 && !Flagarea[Arraycopy[x][y + 1]]) {
			Flagarea[Arraycopy[x][y + 1]] = true;
			findarea_sequence[findarea_num] = Arraycopy[x][y + 1];
			tail[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->next = NULL;
			tail[findarea_num]->x = x;
			tail[findarea_num]->y = y + 1;
			head[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->pre = head[findarea_num];
			head[findarea_num]->next = tail[findarea_num];
			head[findarea_num]->pre = NULL;
			while (path[x][y].parent_x != 0) {
				tmp = (node2*)malloc(sizeof(node2));
				tmp->x = x;
				tmp->y = y;printf("(%d,%d)\n", x, y);
				tmp->next = head[findarea_num]->next;
				tmp->pre = head[findarea_num];
				head[findarea_num]->next = tmp;
				x = path[x][y].parent_x;
				y = path[x][y].parent_y;
			}
			head[findarea_num]->x = x;
			head[findarea_num]->y = y;
			break;
		}
		if (Arraycopy[x][y - 1] > 0 && !Flagarea[Arraycopy[x][y - 1]]) {
			Flagarea[Arraycopy[x][y - 1]] = true;
			findarea_sequence[findarea_num] = Arraycopy[x][y - 1];
			tail[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->next = NULL;
			tail[findarea_num]->x = x;
			tail[findarea_num]->y = y - 1; 
			head[findarea_num] = (node2*)malloc(sizeof(node2));
			tail[findarea_num]->pre = head[findarea_num];
			head[findarea_num]->next = tail[findarea_num];
			head[findarea_num]->pre = NULL;
			while (path[x][y].parent_x != 0) {
				tmp = (node2*)malloc(sizeof(node2));
				tmp->x = x;
				tmp->y = y;printf("(%d,%d)\n", x, y);
				tmp->next = head[findarea_num]->next;
				tmp->pre = head[findarea_num];
				head[findarea_num]->next = tmp;
				x = path[x][y].parent_x;
				y = path[x][y].parent_y;
			}
			head[findarea_num]->x = x;
			head[findarea_num]->y = y;
			break;
		}
		if (Array[x + 1][y] == '*' && JudgeInside(x + 1, y) && !FlagArray[x + 1][y]) {
			q_x.push(x + 1);
			q_y.push(y);
			path[x + 1][y].parent_x = x;
			path[x + 1][y].parent_y = y;
			FlagArray[x + 1][y] = true;
		}
		if (Array[x - 1][y] == '*' && JudgeInside(x - 1, y) && !FlagArray[x - 1][y]) {
			q_x.push(x - 1);
			q_y.push(y);
			path[x - 1][y].parent_x = x;
			path[x - 1][y].parent_y = y;
			FlagArray[x - 1][y] = true;
		}
		if (Array[x][y + 1] == '*' && JudgeInside(x, y + 1) && !FlagArray[x][y + 1]) {
			q_x.push(x);
			q_y.push(y + 1);
			path[x][y+1].parent_x = x;
			path[x][y+1].parent_y = y;
			FlagArray[x][y + 1] = true;
		}
		if (Array[x][y - 1] == '*' && JudgeInside(x, y - 1) && !FlagArray[x][y - 1]) {
			q_x.push(x);
			q_y.push(y - 1);
			path[x][y-1].parent_x = x;
			path[x][y-1].parent_y = y;
			FlagArray[x][y - 1] = true;
		}
	}
}

void Prim() {//��С������prim�㷨�ҳ���ͨ�����������ٵ�ԭ����
	int i, j, k;
	for (k = 0; k <= AreaNum-1; k++) {
		for (i = (N_array - n_array) / 2 + 1; i <= (N_array + n_array) / 2; i++) {
			q_x.push(i);
			q_y.push((M_array - m_array) / 2);
			q_x.push(i);
			q_y.push((M_array + m_array) / 2 + 1);
			FlagArray[i][(M_array - m_array) / 2] = true;
			FlagArray[i][(M_array + m_array) / 2 + 1] = true;
			path[i][(M_array - m_array) / 2].parent_x = 0;
			path[i][(M_array + m_array) / 2 + 1].parent_x = 0;
			path[i][(M_array - m_array) / 2].parent_y = 0;
			path[i][(M_array + m_array) / 2 + 1].parent_y = 0;
		}
		for (j = (M_array - m_array) / 2 + 1; j <= (M_array + m_array) / 2; j++) {
			q_x.push((N_array - n_array) / 2);
			q_y.push(j);
			q_x.push((N_array + n_array) / 2 + 1);
			q_y.push(j);
			FlagArray[(N_array - n_array) / 2][j] = true;
			FlagArray[(N_array + n_array) / 2 + 1][j] = true;
			path[(N_array - n_array) / 2][j].parent_x = 0;
			path[(N_array + n_array) / 2 + 1][j].parent_x = 0;
			path[(N_array - n_array) / 2][j].parent_y = 0;
			path[(N_array + n_array) / 2 + 1][j].parent_y = 0;
		}//��Ŀ�����б߽���һ�ܵĵ�Ž�����
		for (i = 0; i <= k; i++) {//�������е����н��Ž�����
			for (j = 1; j <= area[findarea_sequence[i]].num; j++) {
			    q_x.push(area[findarea_sequence[i]].edge_pointx[j]);
				q_y.push(area[findarea_sequence[i]].edge_pointy[j]);
				FlagArray[area[findarea_sequence[i]].edge_pointx[j]][area[findarea_sequence[i]].edge_pointy[j]] = true;
				path[area[findarea_sequence[i]].edge_pointx[j]][area[findarea_sequence[i]].edge_pointy[j]].parent_x = 0;
				path[area[findarea_sequence[i]].edge_pointx[j]][area[findarea_sequence[i]].edge_pointy[j]].parent_y = 0;
			}
		}
		for (i = 0; i <= N_array + 1; i++) {
			for (j = 0; j <= M_array + 1; j++) {
				FlagArray[i][j] = false;
			}
		}
		bfs(k+1);
		while (!q_x.empty()) {
			q_x.pop();
			q_y.pop();
		}
	}
}

int main() {
	int i, j;
	bool flag;
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d%d\n", &N_array, &M_array,&n_array, &m_array);
	for (i = 1; i <= N_array; i++) {
		cin.getline(Array[i]+1, sizeof(Array[i]));
	}
	for (i = 0; i <= N_array+1; i++) {
		Arraycopy[i][0] = -2;
		Arraycopy[i][M_array+1] = -2;
	}
	for (j = 0; j <= M_array+1; j++) {
		Arraycopy[0][j] = -2;
		Arraycopy[N_array+1][j] = -2;
	}
	for (i = 1; i <= N_array; i++) {
		for (j = 1; j <= M_array; j++) {
			if (Array[i][j] == '*')Arraycopy[i][j] = -1;
			else Arraycopy[i][j] = -2;
		}
	}
	AreaNum = 0;
	area[0].num = 0;
	flag = false;
	for (j = (M_array - m_array) / 2 + 1; j <= (M_array + m_array) / 2; j++) {
		if (Arraycopy[(N_array - n_array) / 2 + 1][j] == -2) {
			Number((N_array - n_array) / 2 + 1, j);
		}
		if (Arraycopy[(N_array + n_array) / 2][j] == -2) {
			Number((N_array + n_array) / 2, j);
		}
	}//��Ŀ�������������������ͨ�Ĳ��ֱ�Ϊ1
	for (i = (N_array - n_array) / 2 + 1; i <= (N_array + n_array) / 2; i++) {
		if (Arraycopy[i][(M_array - m_array) / 2 + 1] == -2) {
			Number(i, (M_array - m_array) / 2 + 1);
		}
		if (Arraycopy[i][(M_array + m_array) / 2] == -2) {
			Number(i, (M_array + m_array) / 2);
		}
	}//��Ŀ�������������������ͨ�Ĳ��ֱ�Ϊ1
	for (i = (N_array - n_array) / 2 + 1; i <= (N_array + n_array) / 2; i++) {
		for (j = (M_array - m_array) / 2 + 1; j <= (M_array + m_array) / 2; j++) {
			if (Arraycopy[i][j] == -2) {
				AreaNum++;
				area[AreaNum].num = 0;
				Number(i, j);
			}
		}
	}//��Ŀ����������������粻��ͨ�Ĳ������α��
	memset(Flagarea, false, AreaNum+1);
	Flagarea[0] = true;
	findarea_sequence[0] = 0;
	Prim(); 
	/*for (i = 0; i <= N_array+1; i++) {
		for (j = 0; j <= M_array+1; j++) {
			printf("%d ", Arraycopy[i][j]);
		}cout << endl;
	}
	for (i = 0; i <= AreaNum; i++) {
		cout << i << endl;
		for (j = 1; j <= area[i].num; j++) {
			printf("(%d,%d)", area[i].edge_pointx[j], area[i].edge_pointy[j]);
		}cout << endl;
	}*/
	return 0;
}
