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

file finOperations = input("operations.txt");
file finArrows = input("arrows.txt");
//real[] row = finSquares; //means row unlimited, column 1
//real[] pathCoord = finPath; 

real[] operations = finOperations;
real[] arrows = finArrows;



for(int i = 0; i < operations.length ; i+=4)
{	
	

	if(operations[i] == 0){
		draw(circle((operations[i+1],operations[i+2]), operations[i+3]), redpen);
	}
	else if(operations[i] == 1){
		draw(circle((operations[i+1],operations[i+2]), operations[i+3]), bluepen);
	}
	else if(operations[i] == 2){
		draw(circle((operations[i+1],operations[i+2]), operations[i+3]), greenpen);
	}
	else if(operations[i] == 3){
		draw(circle((operations[i+1],operations[i+2]), operations[i+3]), graypen1);
	}
	else if(operations[i] == 4){
		draw(circle((operations[i+1],operations[i+2]), operations[i+3]), graypen2);
	}

	
	
	
}


for (int i = 0; i < arrows.length ; i+=4)
{	
	
	
	draw((arrows[i],arrows[i+1])--(arrows[i+2],arrows[i+3]),arrow=Arrow());

}


