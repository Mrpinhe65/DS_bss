#include "graphlink.hpp"

void InitGraph(GraphLink *g) {
  g->MaxVertices = DEFAULT_VERTEX_SIZE;
  g->NumVertices = 0;
  g->NumEdges = 0;

  g->NodeTable = (Vertex *)malloc(sizeof(Vertex) * g->MaxVertices);
  assert(g->NodeTable != NULL);

  for (int i = 0; i < g->MaxVertices; i++)
    g->NodeTable[i].adj = NULL;
}

void InsertVertex(GraphLink *g, T vertex) {
  if (g->NumVertices >= g->MaxVertices)
    return;
  g->NodeTable[g->NumVertices++].data = vertex;
}

void ShowGraphLink(GraphLink *g) {
  Edge *p;
  for (int i = 0; i < g->NumVertices; i++) {
    printf("[%d] %c:> ", i, g->NodeTable[i].data);
    p = g->NodeTable[i].adj;
    while (p != NULL) {
      printf("%d-->", p->dest);
      p = p->link;
    }
    printf("nil\n");
  }
}

int GetVertexPost(GraphLink *g, T vertex) {
  for (int i = 0; i < g->NumVertices; i++) {

    if (g->NodeTable[i].data == vertex)
      return i;
  }
  return -1;
}
// TODO
void InsertEdge(GraphLink *g, T vertex_1, T vertex_2) {
  int post_1 = GetVertexPost(g, vertex_1);
  int post_2 = GetVertexPost(g, vertex_2);
  if (post_1 == -1 || post_2 == -1)
    return;

  Edge *s;
  // A->B
  s = (Edge *)malloc(sizeof(Edge));
  assert(s != NULL);
  s->dest = post_2;
  s->link = g->NodeTable[post_1].adj;
  g->NodeTable[post_1].adj = s;

  // B->A
  s = (Edge *)malloc(sizeof(Edge));
  assert(s != NULL);
  s->dest = post_1;
  s->link = g->NodeTable[post_2].adj;
  g->NodeTable[post_2].adj = s;
  g->NumEdges++;
}

void RemoveEdge(GraphLink *g, T vertex_1, T vertex_2) {
  int post_1 = GetVertexPost(g, vertex_1);
  int post_2 = GetVertexPost(g, vertex_2);
  if (post_1 == -1 || post_2 == -1)
    return;

  Edge *q = NULL;
  Edge *p;
  // post_1->post_2
  p = g->NodeTable[post_1].adj;
  while (p != NULL && p->dest != post_2) {
    q = p;
    p = p->link;
  }
  if (p == NULL)
    return;

  if (q == NULL) {
    g->NodeTable[post_1].adj = p->link;
  } else {
    q->link = p->link;
  }
  free(p);

  // v2->v1
  q = NULL;
  p = g->NodeTable[post_2].adj;
  while (p->dest != post_1) {
    q = p;
    p = p->link;
  }
  if (q == NULL) {
    g->NodeTable[post_2].adj = p->link;
  } else {
    q->link = p->link;
  }
  free(p);
  g->NumEdges--;
}

void RemoveVertex(GraphLink *g, T vertex) {
  int post = GetVertexPost(g, vertex);
  if (post == -1)
    return;
  Edge *p = g->NodeTable[post].adj;
  Edge *t = NULL;
  Edge *s;
  while (p != NULL) {
    s = g->NodeTable[p->dest].adj;
    while (s != NULL && s->dest != post) {
      t = s;
      s = s->link;
    }
    if (s != NULL) {
      if (t == NULL)
        g->NodeTable[p->dest].adj = s->link;
      else
        t->link = s->link;
      free(s);
    }
    g->NodeTable[post].adj = p->link;
    free(p);
    p = g->NodeTable[post].adj;
  }
  g->NumVertices--;
  g->NodeTable[post].data = g->NodeTable[g->NumVertices].data;
  g->NodeTable[post].adj = g->NodeTable[g->NumVertices].adj;
  s = g->NodeTable[post].adj;
  while (s != NULL) {
    p = g->NodeTable[s->dest].adj;
    while (p != NULL) {
      if (p->dest == g->NumVertices) {
        p->dest = post;
        break;
      }
      p = p->link;
    }
    s = s->link;
  }
}

void Destroy(GraphLink *g) {
  Edge *p;
  for (int i = 0; i < g->NumVertices; i++) {
    p = g->NodeTable[i].adj;
    while (p != NULL) {
      g->NodeTable[i].adj = p->link;
      free(p);
      p = g->NodeTable[i].adj;
    }
  }
  free(g->NodeTable);
  g->NumVertices = 0;
  g->NumEdges = 0;
}
int GetFirstNeighbor(GraphLink *g, T vertex) {
  int post = GetVertexPost(g, vertex);
  if (post == -1)
    return -1;
  Edge *p = g->NodeTable[post].adj;
  if (p != NULL)
    return p->dest;
  return -1;
}

int GetNextNeighbor(GraphLink *g, T vertex_1, T vertex_2) {
  int post_1 = GetVertexPost(g, vertex_1);
  int post_2 = GetVertexPost(g, vertex_2);
  if (post_1 == -1 || post_2 == -1)
    return -1;

  Edge *p = g->NodeTable[post_1].adj;
  while (p != NULL && p->dest != post_2)
    p = p->link;
  if (p != NULL && p->link != NULL)
    return p->link->dest;
  return -1;
}
