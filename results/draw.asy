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

file finLabelPos = input("labepos.txt");
file finDevices = input("devices.txt");
file finEdgeInfo = input("edgesInfo.txt");
file finEdges = input("edges.txt");
file finDeviceName = input("deviceName.txt");
//real[] row = finSquares; //means row unlimited, column 1
//real[] pathCoord = finPath; 

real[] devices = finDevices;
real[] edges = finEdges;
string[] edgeInfo = finEdgeInfo;
string[] deviceName = finDeviceName;
real[] labelPos = finLabelPos;

/*for (int i = 0; i < labels.length;i+=1)
{
	  label(labels[i],(labelPos[2 *i],labelPos[2*i+1]));
}*/

int cCount = 0;
real e = 0.2;
for (int i = 0; i < edges.length ; i+=5)
{		
	//e = e + 1;
	Label L = Label("e",position = MidPoint, align = (0,e));
	if(edges[4] == 0)	//blue store
		draw((edges[i],edges[i+1])--(edges[i+2],edges[i+3]),L=L,bluepen);
	else if(edges[4] == 1) //green first
		draw((edges[i],edges[i+1])--(edges[i+2],edges[i+3]),L=L,greenpen);
	else if(edges[4] == 2) //red last
		draw((edges[i],edges[i+1])--(edges[i+2],edges[i+3]),L=L,redpen);
	else if(edges[4] == 3) //gray normal
		draw((edges[i],edges[i+1])--(edges[i+2],edges[i+3]),L=L,graypen1);
	cCount = cCount + 1;
}

int deviceCount = 0;
for(int i = 0; i < devices.length ; i+=3)
{	
	real e = devices[i+2] * 25;
	Label L = Label(deviceName[deviceCount],position = MidPoint, align = (e,0),bluepen);	
	filldraw(circle((devices[i],devices[i+1]), devices[i+2]), redpen);
	draw(circle((devices[i],devices[i+1]), devices[i+2]),L = L,redpen);
	deviceCount = deviceCount + 1;
}




