#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.hpp"
#include "classes.hpp"
using namespace std;

void printEdges(FILE *f, face *faceHead, int edges)
{
    for (int i = 0; i < edges; i++)
        fprintf(f, "%d\n", i);
}

void printHalfEdges(FILE *f, face *faceHead)
{
    halfEdge *Head = faceHead->edgeHead;
    do
    {
        fprintf(f, "startVertexIndex=%d ", Head->prevVertex->vertexIndex);
        fprintf(f, "endVertexIndex=%d ", Head->nextVertex->vertexIndex);
        fprintf(f, "nextEdge=%d ", Head->nextEdge->edgeIndex);
        fprintf(f, "previousEdge%d ", Head->prevEdge->edgeIndex);
        fprintf(f, "faceIndex=%d ", Head->faceIndex);
        fprintf(f, "edgeIndex=%d\n", Head->edgeIndex);
        Head = Head->nextEdge;
    } while (Head != faceHead->edgeHead);
}

void printFace(FILE *f, face *faceHead)
{
    fprintf(f, "FaceIndex:%d Edges ", faceHead->faceIndex);
    halfEdge *Head = faceHead->edgeHead;
    do
    {
        fprintf(f, "%d->", Head->edgeIndex);
        Head = Head->nextEdge;
    } while (Head->nextEdge != faceHead->edgeHead);
    fprintf(f, "%d \n", Head->edgeIndex);
}

void twinedge(halfEdge *edge, int edges, face *newFace)
{
    halfEdge *twinEdge = new halfEdge();
    twinEdge->edgeIndex = edge->edgeIndex;
    twinEdge->nextVertex = edge->prevVertex;
    twinEdge->prevVertex = edge->nextVertex;
    newFace->edgeHead = twinEdge;
    twinEdge->faceIndex = newFace->faceIndex;
    edge->twinEdge = twinEdge;
    twinEdge->twinEdge = edge;
}

void updateTwinEdge1(halfEdge *edge, halfEdge *splittedEdge)
{
    halfEdge *twinEdge = new halfEdge();
    splittedEdge->twinEdge = twinEdge;
    twinEdge->twinEdge = splittedEdge;
    twinEdge->edgeIndex = splittedEdge->edgeIndex;
    twinEdge->nextEdge = edge;
    twinEdge->faceIndex = edge->faceIndex;
    twinEdge->nextVertex = splittedEdge->prevVertex;
    twinEdge->prevEdge = edge->prevEdge;
    twinEdge->prevVertex = edge->prevVertex;
    edge->prevEdge = twinEdge;
    edge->prevVertex = twinEdge->nextVertex;
    twinEdge->prevEdge->nextEdge = twinEdge;
}

void updateTwinEdge2(halfEdge *edge, halfEdge *splittedEdge)
{
    halfEdge *twinEdge = new halfEdge();
    splittedEdge->twinEdge = twinEdge;
    twinEdge->twinEdge = splittedEdge;
    twinEdge->edgeIndex = splittedEdge->edgeIndex;
    twinEdge->nextEdge = edge->nextEdge;
    twinEdge->faceIndex = edge->faceIndex;
    twinEdge->nextVertex = edge->nextVertex;
    twinEdge->prevEdge = edge;
    twinEdge->prevVertex = splittedEdge->nextVertex;
    edge->nextEdge = twinEdge;
    edge->nextVertex = twinEdge->nextVertex;
    twinEdge->nextEdge->prevEdge = twinEdge;
}

bool parity(vertex *prevVertex, vertex *nextVertex, int x0, int y0, int x, int y)
{
    int y1 = prevVertex->y, x1 = prevVertex->x, x2 = nextVertex->x, y2 = nextVertex->y;
    int z = ((y0 - y1) * (x2 - x1) - (y2 - y1) * (x0 - x1)) * ((y - y1) * (x2 - x1) - (y2 - y1) * (x - x1));
    if (z > 0)
        return true;
    return false;
}

face *pointLocation(face *faceHead, int x, int y)
{
    face *currentface = faceHead;
    do
    {
        halfEdge *currentEdge = currentface->edgeHead;
        float x0 = 0, y0 = 0, count = 0;
        do
        {
            x0 += currentEdge->prevVertex->x;
            y0 += currentEdge->prevVertex->y;
            count++;
            currentEdge = currentEdge->nextEdge;
        } while (currentEdge != currentface->edgeHead);
        x0 = x0 / count;
        y0 = y0 / count;
        // loop to iterate over all edges of currentface
        do
        {
            bool p = parity(currentEdge->prevVertex, currentEdge->nextVertex, x0, y0, x, y);
            if (!p)
                break;
            currentEdge = currentEdge->nextEdge;
            if (currentEdge == currentface->edgeHead)
                return currentface;
        } while (currentEdge != currentface->edgeHead);
        currentface = currentface->nextFace;
    } while (currentface != NULL);
    return NULL;
}
