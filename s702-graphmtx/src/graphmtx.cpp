#include "graphmtx.hpp"
////////////////////////////////
/// 函数实现
void InitGraph(GraphMtx *g) {
  printf("Function:InitGraph\n");
  g->MaxVerTices = Default_Vertex_Size;
  g->NumVertices = 0;
  g->NumEdges = 0;

  g->VerticesList = (T *)malloc(sizeof(T) * g->MaxVerTices);
  assert(g->VerticesList != NULL);
  // 开辟二维数组空间
  // 开辟行空间
  g->Edge = (int **)malloc(sizeof(int *) * g->MaxVerTices);
  assert(g->Edge != NULL);
  // 开辟列空间
  for (int i = 0; i < g->MaxVerTices; i++)
    g->Edge[i] = (int *)malloc(sizeof(int) * g->MaxVerTices);
  // 二维数组赋0
  for (int i = 0; i < g->MaxVerTices; i++) {
    for (int j = 0; j < g->MaxVerTices; j++)
      g->Edge[i][j] = 0;
  }
}

void ShowGraph(GraphMtx *g) {
  for (int i = 0; i < g->NumVertices; i++)
    printf("%c ", g->VerticesList[i]);
  printf("\n");
  for (int i = 0; i < g->NumVertices; i++) {
    for (int j = 0; j < g->NumVertices; j++)
      printf("%d ", g->Edge[i][j]);
    printf(" %c\n", g->VerticesList[i]);
  }
  printf("\n");
}
void InsertVertex(GraphMtx *g, T data) {
  if (g->NumVertices >= g->MaxVerTices)
    return;
  g->VerticesList[g->NumVertices++] = data;
}

void InsertEdge(GraphMtx *g, T data1, T data2) {
  int p1 = GetVertexPost(g, data1);
  int p2 = GetVertexPost(g, data2);
  if (p1 == -1 || p2 == -1)
    return;
  g->Edge[p1][p2] = 1;
  g->Edge[p2][p1] = 1;
  g->NumEdges++;
}
void RemoveVerTices(GraphMtx *g, T data) {
  int p = GetVertexPost(g, data);
  if (p == -1)
    return;

  int numedges = 0;

  for (int i = p; i < g->NumVertices - 1; i++)
    g->VerticesList[i] = g->VerticesList[i + 1];

  for (int i = 0; i < g->NumVertices; i++) {
    if (g->Edge[p][i] != 0)
      numedges++;
  }

  for (int i = p; i < g->NumVertices - 1; i++) {
    for (int j = 0; j < g->NumVertices; j++) {
      g->Edge[i][j] = g->Edge[i + 1][j];
    }
  }
  for (int i = p; i < g->NumVertices; i++) {
    for (int j = 0; j < g->NumVertices; j++)
      g->Edge[j][i] = g->Edge[j][i + 1];
  }
  g->NumVertices--;
  g->NumEdges -= numedges;
}
void RemoveEdge(GraphMtx *g, T data1, T data2) {

  int p1 = GetVertexPost(g, data1);
  int p2 = GetVertexPost(g, data2);
  if (p1 == -1 || p2 == -1)
    return;
  g->Edge[p1][p2] = 0;
  g->Edge[p2][p1] = 0;
  g->NumEdges--;
}
void DestroyGraph(GraphMtx *g) {
  free(g->VerticesList);
  g->VerticesList = NULL;
  for (int i = 0; i < g->NumVertices; i++) {
    free(g->Edge[i]);
  }
  free(g->Edge);
  g->Edge = NULL;
  g->NumVertices = 0;
  g->NumEdges = 0;
}
int GetFirstNeighbor(GraphMtx *g, T data) {
  int pos = GetVertexPost(g, data);
  if (pos == -1)
    return -1;
  for (int i = 0; i < g->NumVertices; i++) {
    if (g->Edge[pos][i] == 1)
      return i;
  }
  return -1;
}
int GetNextNeighbor(GraphMtx *g, T data1, T data2) {
  int pos_data1 = GetVertexPost(g, data1);
  int pos_data2 = GetVertexPost(g, data2);
  if (pos_data1 == -1 || pos_data2 == -1)
    return -1;
  for (int i = pos_data2 + 1; i < g->NumVertices; i++) {
    if (g->Edge[pos_data1][i] == 1)
      return i;
  }
  return -1;
}
//////////////////////////////////////
/// 辅助函数
int GetVertexPost(GraphMtx *g, T data) {
  for (int k = 0; k < g->NumVertices; k++) {
    printf("k= %d\n", k);
    if (g->VerticesList[k] == data)
      return k;
  }
  return -1;
}
