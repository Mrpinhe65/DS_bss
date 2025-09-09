#pragma once

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

#define DEFAULT_VERTEX_SIZE 10

typedef char T;

// 定义边的结构体
typedef struct Edge {
  int dest;
  struct Edge *link;
} Edge;

// 定义顶点的结构体
typedef struct Vertex {
  T data; // 数据，此处为字符
  Edge *adj;
} Vertex;

// 定义图的结构体
typedef struct GraphLink {
  int MaxVertices;
  int NumVertices;
  int NumEdges;
  Vertex *NodeTable;
} GraphLink;

void InitGraph(GraphLink *g);
void InsertVertex(GraphLink *g, T vertex);
int GetVertexPost(GraphLink *g, T vertex);
void ShowGraphLink(GraphLink *g);
void InsertEdge(GraphLink *g, T vertex_1, T vertex_2);

void RemoveEdge(GraphLink *g, T vertexi_1, T vertex_2);
void RemoveVertex(GraphLink *g, T vertex);
void Destroy(GraphLink *g);
int GetFirstNeighbor(GraphLink *g, T vertex);
int GetNextNeighbor(GraphLink *g, T vertex_1, T vertex_2);
