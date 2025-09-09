#pragma once

#include <assert.h>
#include <ctime>
#include <malloc.h>
#include <stdio.h>
// 定义顶点最大数
#define Default_Vertex_Size 10

typedef char T;

// 定义图的结构体
typedef struct GraphMtx {
  int MaxVerTices; // 最大顶点数
  int NumVertices; // 实际顶点数
  int NumEdges;    // 边数
  T *VerticesList;
  int **Edge;
} GraphMtx;

////////////////////////////
/// 函数声明
/// 主函数
void InitGraph(GraphMtx *g);
void ShowGraph(GraphMtx *g);
void InsertVertex(GraphMtx *g, T data);
void InsertEdge(GraphMtx *g, T data1, T data2);
void RemoveVerTices(GraphMtx *g, T data);
void RemoveEdge(GraphMtx *g, T data1, T data2);
void DestroyGraph(GraphMtx *g);
int GetFirstNeighbor(GraphMtx *g, T data);
int GetNextNeighbor(GraphMtx *g, T data1, T data2);

///////////////////////////////////
/// 辅助函数
int GetVertexPost(GraphMtx *g, T data);
