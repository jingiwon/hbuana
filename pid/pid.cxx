#include "PIDTool.h"

using namespace std;

int main(int argc,char* argv[])
{
	string file="",tree="";
	string fntuple="",tntuple="";
	int train=0,bdtntuple=0;
	for(int i=1;i<argc;i++)
	{
		if(string(argv[i])==string("-f"))
		{
			file = string(argv[i+1]);
		}
		else if(string(argv[i])==string("-t"))
		{
			tree = string(argv[i+1]);
		}
		else if(string(argv[i])==string("-train"))
		{
			train=1;
		}
		else if(string(argv[i])==string("-tag"))
		{
			bdtntuple=1;
			fntuple = string(argv[i+1]);
			tntuple = string(argv[i+2]);
		}
	}
	cout<<file<<" "<<tree<<endl;
	PIDTool *pt = new PIDTool();
	if(file!="" && tree!="")
	{
		pt->GenNtuple(file,tree);
	}
	if(train==1)
	{
		pt->AddVar("xwidth",'D');
		pt->AddVar("ywidth",'D');
		pt->AddVar("zwidth",'D');
		pt->AddVar("Edep",'D');
		pt->AddVar("shower_start",'I');
		pt->AddVar("shower_layer_ratio",'D');
		pt->AddVar("shower_density",'D');
		pt->AddVar("shower_length",'D');
		pt->AddVar("ntrack",'D');

		pt->AddSignal("pid_pion.root","T","pion");
		pt->AddSignal("pid_e.root","T","electron");
		pt->AddSignal("pid_muon.root","T","muon");
		pt->AddSignal("pid_proton.root","T","proton");
		
		pt->TrainBDT();
	}
	if(bdtntuple==1)
	{
		pt->BDTNtuple(fntuple,tntuple);
	}
	delete pt;
	return 0;
}
