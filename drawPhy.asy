import graph;
usepackage ("lmodern");
size (400, 400); //, IgnoreAspect);
defaultpen (font ("ptmr8t", 7pt) + 0.1);

pen apen= font ("ptmr8t", 10pt) + 1;
pen bpen= font ("ptmr8t", 9pt) + 1.2;
pen cpen= font ("ptmr8t", 7pt) + 0.5;
pen dpen= font ("ptmr8t", 12pt) + 2;
pen epen= font ("ptmr8t", 9pt) + 1.5;
pen fpen= Helvetica (series="b", shape="n");
pen graypen1= font ("ptmr8t", 14pt) + gray(0.7);
pen graypen2= font ("ptmr8t", 14pt) + gray(0.5);
pen redpen= font ("ptmr8t", 14pt) + rgb(1,0,0) + 1.5;
pen bluepen= font ("ptmr8t", 14pt) + rgb(0,0,1) + 1.5;
pen greenpen= font ("ptmr8t", 14pt) + rgb(0,1,0) + 1;
string[] cn={ "1", "2", "3", "4", "5"};

string fname = stdin;
//file finPath = input ("pathCoordSeveral.txt");
//file finPath = input (fname);
//file finPath = input ("pathCoord.txt");
//file finPath = input ("cutCoord.txt");
//file finSquares = input("valvesCoord.txt");



file finEdges = input("edgesPhyDesign.txt");
file finNodes = input("nodePhyDesign.txt");

//real[] row = finSquares; //means row unlimited, column 1
//real[] pathCoord = finPath; 

real[] edges = finEdges;
real[] nodes = finNodes;



/*for (int i = 0; i < labels.length;i+=1)
{
	  label(labels[i],(labelPos[2 *i],labelPos[2*i+1]));
}*/

for (int i = 0; i < edges.length ; i+=4)
{		

	draw((edges[i],edges[i+1])--(edges[i+2],edges[i+3]),bluepen);
	
	
}

for(int i = 0; i < nodes.length ; i+=2)
{	
		
	filldraw(circle((nodes[i],nodes[i+1]), 0.2), redpen);

}






