#include "TH1.h"
#include "TH1F.h"
#include<iostream>
#include<TFile.h>
#include<TH1F.h>
#include<TH2F.h>
#include<TCanvas.h>
#include<TStyle.h>
#include<TF1.h>
#include<TF2.h>
#include<TGaxis.h>
#include<TTree.h>
#include<TMath.h>
#include<fstream>
#include<TChain.h>
{


//Choose your signal region binning
Double_t bins[13] = {100,150,200,250,300,350,400,450,500,550,650,850, 1500};

TH1 *h1[3], *h2[3], *hnew ;
//array size should be equal to number of input bkg root files

std::vector<std::string>sample;
std::string str;
std::ifstream in("bkg_list.txt"); //list of bkg root files
while (std::getline(in, str))
{
if(str.size() > 0)
        sample.push_back(str);
}
TFile *file[3];  ////array size should be equal to number of input bkg root files
for(int i=0; i < 3; i++){ ////array size should be equal to number of input bkg root files
char nl[256];
sprintf(nl,"%s",sample.at(i).c_str());
file[i] = new TFile(nl);

file[i]->GetObject("NDiJetCombinations/Muon1Tau1ReconstructableMass",h2[i]);
//h2[i]->Scale(3.3); //Scaling 2017 to full RunII
TH1F *hnew = (TH1F*)h2[i]->Rebin(12,"hnew",bins);
for(int j = 1; j < 13 ;j++){ 
double yield = hnew->GetBinContent(j);

char name1[256];
std::string n[3] = {"dy", "vv","ST"};
//std::cout<<n[i]<<std::endl;
sprintf(name1,"%s",n[i].c_str());
std::ofstream log1(TString(name1)+"_binyield.txt",std::ios_base::app|std::ios_base::out); //output yield txt files ready to be used in datacards
log1<<j<<" "<<yield<<std::endl;
log1.close();
}
}

}






