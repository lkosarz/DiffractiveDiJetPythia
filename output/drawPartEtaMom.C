#include <exception>
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

#include "TString.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TFile.h"
#include "TArrayI.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TProfile.h"
#include "TLatex.h"

#include "style.C"

using namespace std;

void drawPartEtaMombin(TString infile = "data/diffractiveDiJets_ep_18x275GeV_full.root", double etalo = -4.14, double etahi = -1.18, int charge = -1.0, TString mkdir = "outputSpectra/eta", TString outfile = "outputMomNeg.root", TString pngfile = "h_MCpart_neg_p_eta");

void drawPartEtaMom()
{

	TString file = "data/diffractiveDiJets_ep_18x275GeV_full.root";
	TString dir = "outputSpectra/eta";

	//file = "data/diffractiveDiJets_ep_18x275GeV_full.root";
	//dir = "outputSpectra/eta";

	drawPartEtaMombin(file, -4.14, -1.18, -1.0, dir, "outputMomNeg_eta_-4.14_-1.18.root", "h_Particle_neg_p_eta");
	drawPartEtaMombin(file, -4.14, -1.18, 1.0, dir, "outputMomPos_eta_-4.14_-1.18.root", "h_Particle_pos_p_eta");

	drawPartEtaMombin(file, -2.0, -1.0, -1.0, dir, "outputMomNeg_eta_-2.0_-1.0.root", "h_Particle_neg_p_eta");
	drawPartEtaMombin(file, -2.0, -1.0, 1.0, dir, "outputMomPos_eta_-2.0_-1.0.root", "h_Particle_pos_p_eta");

	drawPartEtaMombin(file, -3.0, -2.0, -1.0, dir, "outputMomNeg_eta_-3.0_-2.0.root", "h_Particle_neg_p_eta");
	drawPartEtaMombin(file, -3.0, -2.0, 1.0, dir, "outputMomPos_eta_-3.0_-2.0.root", "h_Particle_pos_p_eta");

	drawPartEtaMombin(file, -4.0, -3.0, -1.0, dir, "outputMomNeg_eta_-4.0_-3.0.root", "h_Particle_neg_p_eta");
	drawPartEtaMombin(file, -4.0, -3.0, 1.0, dir, "outputMomPos_eta_-4.0_-3.0.root", "h_Particle_pos_p_eta");

}

/////////////////////////////////////////////////////////////
void drawPartEtaMombin(TString infile, double etalo, double etahi, int charge, TString mkdir, TString outfile, TString pngfile) {

	style();
	//gStyle->SetOptStat(0);
	gROOT->ForceStyle();

	Int_t padw = 800, padh = 530;

	const Int_t nPadX = 1;
	const Int_t nPadY = 1;

	const Int_t nFiles = 6;

	vector<TFile*> *files = new vector<TFile*>;

	files->push_back(TFile::Open(infile));
	files->push_back(TFile::Open(infile));
	files->push_back(TFile::Open(infile));
	files->push_back(TFile::Open(infile));
	files->push_back(TFile::Open(infile));
	files->push_back(TFile::Open(infile));

	gSystem->MakeDirectory(mkdir.Data());
	gSystem->cd(mkdir);
	TFile *fileOut = new TFile(outfile, "recreate");
	fileOut->cd();
	gSystem->cd("../");
	gSystem->cd("../");


	vector<TH1D*> *hists = new vector<TH1D*>;
	vector<TCanvas*> *vec_cnv = new vector<TCanvas*>;
	vector<TLegend*> *legends = new vector<TLegend*>;
	vector<TLegend*> *legends_mean = new vector<TLegend*>;
	vector<TString> *names = new vector<TString>;
	vector<int> *colors = new vector<int>;
	vector<TString> *drawOpt = new vector<TString>;
	vector<TString> *labels = new vector<TString>;
	vector<bool> *log = new vector<bool>;
	vector<int> *rebin = new vector<int>;
	vector<double> *range_hi = new vector<double>;
	vector<double> *range_lo = new vector<double>;

	if(charge>0)
	{
		names->push_back("h_Particle_Pion_p_eta_p");
		names->push_back("h_Particle_Kaon_p_eta_p");
		names->push_back("h_Particle_Proton_p_eta_p");
		names->push_back("h_Particle_Electron_p_eta_p");
		//names->push_back("h_Particle_eta_Electron_p_eta_p");
	}
	if(charge<0)
	{
		names->push_back("h_Particle_Pion_n_eta_p");
		names->push_back("h_Particle_Kaon_n_eta_p");
		names->push_back("h_Particle_Proton_n_eta_p");
		names->push_back("h_Particle_Electron_n_eta_p");
		//names->push_back("h_Particle_eta_Electron_n_eta_p");
	}

	names->push_back("h_Particle_Neutron_eta_p");
	names->push_back("h_Particle_Gamma_eta_p");

	log->push_back(true);

	colors->push_back(kBlue);
	colors->push_back(kMagenta);
	colors->push_back(kGreen);
	colors->push_back(kRed);
	colors->push_back(kBlack);
	colors->push_back(kTeal);

	drawOpt->push_back("e");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");

	legends->push_back(new TLegend(0.7, 0.6, 1.0, 1.0));
	//legends->push_back(new TLegend(0.7, 0.6, 0.75, 1.0));
	//legends_mean->push_back(new TLegend(0.75, 0.6, 1.0, 1.0));

	if(charge>0)
	{
		labels->push_back("#pi^{+}");
		labels->push_back("K^{+}");
		labels->push_back("p^{+}");
		labels->push_back("e^{+}");
		labels->push_back("n");
		labels->push_back("#gamma");
	}
	if(charge<0)
	{
		labels->push_back("#pi^{-}");
		labels->push_back("K^{-}");
		labels->push_back("p^{-}");
		labels->push_back("e^{-}");
		labels->push_back("n");
		labels->push_back("#gamma");
	}

	rebin->push_back(4);
	rebin->push_back(4);
	rebin->push_back(4);
	rebin->push_back(4);
	rebin->push_back(4);
	rebin->push_back(4);

	range_hi->push_back(24.0);
	range_lo->push_back(0.0);

	vec_cnv->push_back(new TCanvas("cnv_p", "MCparticle momentum", nPadX*padw, nPadY*padh));

	for (int i = 0; i < names->size(); ++i) {

		TH2D *hist2d = (TH2D *)files->at(i%nFiles)->Get(names->at(i));

		int biny_hi = hist2d->GetXaxis()->FindBin(etahi);
		int biny_lo = hist2d->GetXaxis()->FindBin(etalo);

		TH1D *hist = (TH1D *)hist2d->ProjectionY(Form("%s_px", hist2d->GetName()), biny_lo, biny_hi);

		//hist->SetName(Form("data_%s", hist->GetName()));

		//cout<<hist->GetName()<<endl;

		hist->Rebin(rebin->at(i));

		hist->GetXaxis()->SetRangeUser(range_lo->at(i/nFiles),range_hi->at(i/nFiles));

		hists->push_back(hist);

		cout<<i<<endl;
	}


	gSystem->cd(mkdir.Data());

	for (int i = 0; i < hists->size(); ++i) {

		cout<<i<<endl;

		vec_cnv->at(i/nFiles)->Divide(nPadX,nPadY);

		//hists->at(i)->Scale(1.0/hists->at(i)->Integral());

		hists->at(i)->SetLineColor(colors->at(i%nFiles));
		
		//legends->at(i/nFiles)->AddEntry(hists->at(i), labels->at(i));
		legends->at(i/nFiles)->AddEntry(hists->at(i), Form("%s <p> = %.2f [GeV]", labels->at(i).Data(), hists->at(i)->GetMean()));
		//legends_mean->at(i/nFiles)->AddEntry((TObject*)0, Form("<E> = %.2f [GeV]", hists->at(i)->GetMean()), "");

		if(log->at(i/nFiles)) vec_cnv->at(i/nFiles)->cd(1)->SetLogy();
		if(!log->at(i/nFiles)) vec_cnv->at(i/nFiles)->cd(1);
		hists->at(i)->Draw(drawOpt->at(i%nFiles));
		//legends_mean->at(i/nFiles)->Draw("same");
		legends->at(i/nFiles)->Draw("same");


		cout<<hists->at(i)->GetName()<<"\t mean p = "<<hists->at(i)->GetMean()<<endl;

		//vec_cnv->at(i/nFiles)->cd(1)->SaveAs(Form("%s.png", hists->at(i)->GetName()));
		hists->at(i)->Write();
	}


	TLatex *latex = new TLatex();
	latex->SetNDC();
	latex->DrawLatex(0.5, 0.75, Form("%.2f<#eta<%.2f", etalo, etahi));

	vec_cnv->at(0)->cd(1)->SaveAs(Form("%s_%.f_%.f.png", pngfile.Data(), etalo, etahi));

	//--------------------------------------------

	gSystem->cd("../");
	gSystem->cd("../");

	//fileOut->cd();
	fileOut->Write();

}
