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
#include "TKey.h"
#include "TProfile.h"
#include "TGaxis.h"
#include "TList.h"

#include "DrawHistFile.h"
#include "HistDrawOpt.h"
//Int_t padw = 800, padh = 600;

#include "style.C"

using namespace std;




/////////////////////////////////////////////////////////////
Int_t drawHist() {

	style();
	//gStyle->SetOptStat(0);
	gROOT->ForceStyle();
	//gStyle->SetLineColor(kBlue);
	//gStyle->SetHistLineColor(kBlue);
	gStyle->SetHistLineColor(kBlack);
	gStyle->SetHistLineWidth(2);
	//gStyle->SetPaintTextFormat(".2e");
	gStyle->SetOptTitle(1);
	gStyle->SetOptStat(1);

	TGaxis::SetExponentOffset(0.02, -0.07, "x");


	vector<TString> *list_Events = new vector<TString>;
	vector<TString> *list_Events_special = new vector<TString>;
	vector<TString> *list_Particle = new vector<TString>;
	vector<TString> *list_Jets = new vector<TString>;
	vector<TString> *list_Jets_meas = new vector<TString>;


	// Event
	list_Events->push_back("h_Events");
	list_Events->push_back("h_Events_Diffractive");

	list_Events->push_back("h_Event_nPart_final");
	list_Events->push_back("h_Event_nJets");
	list_Events->push_back("h_Event_nJets_meas");

	list_Events->push_back("h_Event_xQ2");
	list_Events->push_back("h_Event_yQ2");
	list_Events->push_back("h_Event_xy");

	list_Events->push_back("h_Event_nHCal_xQ2");
	list_Events->push_back("h_Event_nHCal_yQ2");
	list_Events->push_back("h_Event_nHCal_xy");

	list_Events->push_back("h_Event_nPion_p");
	list_Events->push_back("h_Event_nPion_n");
	list_Events->push_back("h_Event_nKaon_p");
	list_Events->push_back("h_Event_nKaon_n");
	list_Events->push_back("h_Event_nProton_p");
	list_Events->push_back("h_Event_nProton_n");
	list_Events->push_back("h_Event_nElectron_p");
	list_Events->push_back("h_Event_nElectron_n");

	list_Events->push_back("h_Event_nNeutron");
	list_Events->push_back("h_Event_nGamma");

	list_Events->push_back("h_Event_HCal_jets");
	list_Events->push_back("h_Event_HCal_jets_meas");

	list_Events->push_back("h_Particle_eta_wE");


	list_Events_special->push_back("h_Event_Q2");
	list_Events_special->push_back("h_Event_x");
	list_Events_special->push_back("h_Event_y");

	list_Events_special->push_back("h_Event_nHCal_0_Q2");
	list_Events_special->push_back("h_Event_nHCal_0_x");
	list_Events_special->push_back("h_Event_nHCal_0_y");

	list_Events_special->push_back("h_Event_nHCal_1_Q2");
	list_Events_special->push_back("h_Event_nHCal_1_x");
	list_Events_special->push_back("h_Event_nHCal_1_y");

	list_Events_special->push_back("h_Event_nHCal_2_Q2");
	list_Events_special->push_back("h_Event_nHCal_2_x");
	list_Events_special->push_back("h_Event_nHCal_2_y");

	list_Events_special->push_back("h_Event_AllHCal_Q2");
	list_Events_special->push_back("h_Event_AllHCal_x");
	list_Events_special->push_back("h_Event_AllHCal_y");


	list_Events_special->push_back("h_Event_JetMeas_nHCal_0_Q2");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_0_x");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_0_y");

	list_Events_special->push_back("h_Event_JetMeas_nHCal_1_Q2");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_1_x");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_1_y");

	list_Events_special->push_back("h_Event_JetMeas_nHCal_2_Q2");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_2_x");
	list_Events_special->push_back("h_Event_JetMeas_nHCal_2_y");

	list_Events_special->push_back("h_Event_JetMeas_AllHCal_Q2");
	list_Events_special->push_back("h_Event_JetMeas_AllHCal_x");
	list_Events_special->push_back("h_Event_JetMeas_AllHCal_y");


/*
	// MC particles
	list_MCpart->push_back("h_MCpart_mass");
	list_MCpart->push_back("h_MCpart_charge");
	list_MCpart->push_back("h_MCpart_E");
	list_MCpart->push_back("h_MCpart_p");
	list_MCpart->push_back("h_MCpart_pT");
*/

	// eta, momentum
	list_Particle->push_back("h_Particle_pion_p_eta_p");
	list_Particle->push_back("h_Particle_pion_n_eta_p");
	list_Particle->push_back("h_Particle_Kaon_p_eta_p");
	list_Particle->push_back("h_Particle_Kaon_n_eta_p");
	list_Particle->push_back("h_Particle_proton_p_eta_p");
	list_Particle->push_back("h_Particle_proton_n_eta_p");
	list_Particle->push_back("h_Particle_Electron_p_eta_p");
	list_Particle->push_back("h_Particle_Electron_n_eta_p");

	list_Particle->push_back("h_Particle_Neutron_eta_p");
	list_Particle->push_back("h_Particle_Gamma_eta_p");

	// eta, transverse momentum pT
	list_Particle->push_back("h_Particle_pion_p_eta_pT");
	list_Particle->push_back("h_Particle_pion_n_eta_pT");
	list_Particle->push_back("h_Particle_Kaon_p_eta_pT");
	list_Particle->push_back("h_Particle_Kaon_n_eta_pT");
	list_Particle->push_back("h_Particle_proton_p_eta_pT");
	list_Particle->push_back("h_Particle_proton_n_eta_pT");
	list_Particle->push_back("h_Particle_Electron_p_eta_pT");
	list_Particle->push_back("h_Particle_Electron_n_eta_pT");

	list_Particle->push_back("h_Particle_Neutron_eta_pT");
	list_Particle->push_back("h_Particle_Gamma_eta_pT");

	// eta, energy
	list_Particle->push_back("h_Particle_Pion_p_eta_E");
	list_Particle->push_back("h_Particle_Pion_n_eta_E");
	list_Particle->push_back("h_Particle_Kaon_p_eta_E");
	list_Particle->push_back("h_Particle_Kaon_n_eta_E");
	list_Particle->push_back("h_Particle_Proton_p_eta_E");
	list_Particle->push_back("h_Particle_Proton_n_eta_E");
	list_Particle->push_back("h_Particle_Electron_p_eta_E");
	list_Particle->push_back("h_Particle_Electron_n_eta_E");

	list_Particle->push_back("h_Particle_Neutron_eta_E");
	list_Particle->push_back("h_Particle_Gamma_eta_E");


	// Jets
	list_Jets->push_back("h_Jet_nPart");
	list_Jets->push_back("h_Jet_mass");
	list_Jets->push_back("h_Jet_charge");
	list_Jets->push_back("h_Jet_E");
	list_Jets->push_back("h_Jet_p");
	list_Jets->push_back("h_Jet_pT");
	list_Jets->push_back("h_Jet_eta");
	list_Jets->push_back("h_Jet_deta");

	list_Jets->push_back("h_Jet_bHCal_part_eta");
	list_Jets->push_back("h_Jet_HCal_part_eta");


	// Jets
	list_Jets_meas->push_back("h_Jet_meas_nPart");
	list_Jets_meas->push_back("h_Jet_meas_mass");
	list_Jets_meas->push_back("h_Jet_meas_charge");
	list_Jets_meas->push_back("h_Jet_meas_E");
	list_Jets_meas->push_back("h_Jet_meas_p");
	list_Jets_meas->push_back("h_Jet_meas_pT");
	list_Jets_meas->push_back("h_Jet_meas_eta");
	list_Jets_meas->push_back("h_Jet_meas_deta");

	list_Jets_meas->push_back("h_Jet_meas_bHCal_part_eta");
	list_Jets_meas->push_back("h_Jet_meas_HCal_part_eta");

	//TCanvas *cnv = new TCanvas();
	//cnv->cd();

	TString outputdir = "output";

	gSystem->mkdir(outputdir);
	//gSystem->cd(outputdir);
	//cnv->cd()->SaveAs("hEventStat0.png");
	//gSystem->cd("../");

	gSystem->mkdir("output/Events/");
	gSystem->mkdir("output/Particles/");
	gSystem->mkdir("output/Jets/");
	gSystem->mkdir("output/Jets_meas/");

	//delete cnv;
	//file->Close();

	TString file = "data/diffractiveDiJets_ep_18x275GeV_full.root";
	//file = "data/diffractiveDiJets_ep_18x275GeV_pT0GeV_full.root";
	//file = "data/diffractiveDiJets_ep_18x275GeV_ee_kT_full.root";
	//file = "data/diffractiveDiJets_ep_18x275GeV_anti_kT_full.root";
	file = "data/diffractiveDiJets_ep_18x275GeV_ee_genkT_full.root";

	drawAny("output/Events/", file, list_Events);
	gSystem->cd("../");
	drawAny("output/Events/", file, list_Events_special);
	gSystem->cd("../");
	drawAny("output/Particles/", file, list_Particle);
	gSystem->cd("../");
	drawAny("output/Jets/", file, list_Jets);
	gSystem->cd("../");
	drawAny("output/Jets_meas/", file, list_Jets_meas);
	gSystem->cd("../");


	return 1.0;

}
