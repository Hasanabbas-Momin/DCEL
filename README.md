# DCEL
Used Object-Oriented Programming and concept of Pointers to build dynamic DCEL to split a planar angular shape into parts as per given input points to represent a 3-D shape.<br>

It uses classes 'Vertex', 'Halfedge' and 'Faces' to represent the graph.
## Input
An input co-ordinates of virtices of initial shape is given in input file.<br>
An input to split the edges will be given in input split file. This will create another edge which will bisect the mentioned edge. At the end another input of co-ordinates is given for which for which the face in which it lies is determined.<br>
## Output 
Edges: ..<br>
Halfedges: {startVertexIndex=.., endVertexIndex=.., nextEdge=.., previousEdge=.., faceIndex=.., edgeIndex=..}<br>
Faces: {FaceIndex:.., Edges:..}<br>
This will be printed after every split.<br>

Face to which input points belongs to:<br>
{Id FaceIndex}
