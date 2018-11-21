#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <sstream>
#include <TF1.h>
#include <TTree.h>
#include <TStyle.h>
#include <TText.h>
#include <vector>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TMath.h>
#include <TBranch.h>



Int_t color[12] = {kBlack,kCyan,kRed,kGreen,kBlue,kOrange,kMagenta,kSpring,kTeal,kAzure,kViolet,kPink};

void draw_plot(string filename,string graph,Double_t *nbin,string title_axis,string title_png){
	TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],nbin[3]);
	frame1->SetTitle(title_axis.c_str());
	TFile *tf1 = new TFile(filename.c_str());
	TGraphErrors *tg = dynamic_cast<TGraphErrors*>(tf1->Get(graph.c_str()));
	tg->SetLineColor(color[2]);
	tg->SetMarkerColor(color[2]);
	tg->SetMarkerStyle(20);
	tg->SetMarkerSize(0.3);
	tg->Draw("P");
	c1->SaveAs(title_png.c_str());
	delete c1;
	delete tg;
}

void draw_allplot(string filename,Int_t num,string *graph,Double_t *nbin,string title_axis,string title_png){
	TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],nbin[3]);
	frame1->SetTitle(title_axis.c_str());
	TFile *tf1 = new TFile(filename.c_str());
	vector<TGraphErrors*> tg;
	for(Int_t number = 0;number < num;number++){
		tg.push_back((TGraphErrors*)(tf1->Get(graph[number].c_str())));
		tg.at(number)->SetLineColor(color[number]);
		tg.at(number)->SetMarkerColor(color[number]);
		tg.at(number)->SetMarkerStyle(20);
		tg.at(number)->SetMarkerSize(0.3);
		tg.at(number)->Draw("P");
	}
	TLegend *legend1 = new TLegend(0.7,0.1,0.9,0.4,"");
	for(Int_t number = 0;number < num;number++){
		legend1->AddEntry(tg.at(number),graph[number].c_str(),"lep");
	}
	legend1->Draw();
	c1->SaveAs(title_png.c_str());

	delete c1;
	delete legend1;
	tg.clear();
}

void draw_hist(string filename,string graph,Double_t *nbin,string title_axis,string title_png){
	TCanvas *c1 = new TCanvas("c1","c1",1600,900);
	TFile *tf1 = new TFile(filename.c_str());
	TH1D* hist = dynamic_cast<TH1D*>(tf1->Get(graph.c_str()));
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],hist->GetMaximum());
	frame1->SetTitle(title_axis.c_str());
	hist->SetLineColor(color[2]);
	hist->SetFillColor(color[2]);
	hist->SetStats(0);
	hist->SetTitle(title_axis.c_str());
	hist->Draw();
	c1->SaveAs(title_png.c_str());

	delete c1;
	delete hist;
}

void draw_hist2d(string filename,string graph,Double_t *nbin,string title_axis,string title_png){
	gStyle->SetPalette(1);
	TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],nbin[3]);
	frame1->SetTitle(title_axis.c_str());
	TFile *tf1 = new TFile(filename.c_str());
	TH2F* hist = dynamic_cast<TH2F*>(tf1->Get(graph.c_str()));
	hist->SetStats(0);
	hist->SetTitle(title_axis.c_str());
	hist->Draw("colz");
	c1->SaveAs(title_png.c_str());

	delete c1;
	delete hist;
}

void draw_samehist2d(string filename,Int_t num,string *graph,Double_t *nbin,string title_axis,string title_png){
	TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
	gStyle->SetLabelSize(0.02,"XY");
	gStyle->SetTitleYOffset(1.2);
	gStyle->SetPadLeftMargin(0.01);
	gStyle->SetPadRightMargin(0.19);
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],nbin[3]);
	frame1->SetTitle(title_axis.c_str());
	TFile *tf1 = new TFile(filename.c_str());
	vector<TH2F*> hist;
	for(Int_t number = 0;number < num;number++){
		hist.push_back(dynamic_cast<TH2F*>(tf1->Get(graph[number].c_str())));
		hist.at(number)->SetLineColor(color[number]);
		hist.at(number)->SetFillColor(color[number]);
		hist.at(number)->SetStats(0);
		hist.at(number)->SetTitle(title_axis.c_str());
		hist.at(number)->Draw("colz same");
	}
	c1->RedrawAxis();
	c1->SaveAs(title_png.c_str());
	delete c1;
	hist.clear();
	gStyle->Reset();
}

void draw_allhist(string filename,Int_t num,string *graph,Double_t *nbin,string title_axis,string title_png){
	TCanvas *c1 = new TCanvas("c1","c1",1600,900);
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],nbin[3]);
	frame1->SetTitle(title_axis.c_str());
	TFile *tf1 = new TFile(filename.c_str());
	vector<TH1D*> hist;
	for(Int_t number = 0;number < num;number++){
		hist.push_back(dynamic_cast<TH1D*>(tf1->Get(graph[number].c_str())));
		hist.at(number)->SetLineColor(color[number]);
		hist.at(number)->SetFillColor(color[number]);
		hist.at(number)->SetStats(0);
		hist.at(number)->SetTitle(title_axis.c_str());
		hist.at(number)->Draw("same");
	}
	c1->RedrawAxis();
	TLegend *legend1 = new TLegend(0.7,0.7,0.9,0.9,"");
	for(Int_t number = 0;number < num;number++){
		legend1->AddEntry(hist.at(number),graph[number].c_str(),"lep");
	}
	legend1->Draw();
	c1->SaveAs(title_png.c_str());

	delete c1;
	delete legend1;
	hist.clear();
}

void draw_triggerhist(string filename,Int_t num,string *graph,Double_t *nbin,string title_axis,string title_png){
	TCanvas *c1 = new TCanvas("c1","c1",1600,900);
	TH1F *frame1 = gPad->DrawFrame(nbin[0],nbin[1],nbin[2],nbin[3]);
	frame1->SetTitle(title_axis.c_str());
	TFile *tf1 = new TFile(filename.c_str());
	vector<TH1D*> hist;
	for(Int_t number = 0;number < num;number++){
		hist.push_back(dynamic_cast<TH1D*>(tf1->Get(graph[number].c_str())));
		hist.at(number)->SetLineColor(color[number]);
		hist.at(number)->SetFillColor(color[number]);
		hist.at(number)->SetStats(0);
		hist.at(number)->SetTitle(title_axis.c_str());
		hist.at(number)->Draw("same");
	}
	c1->RedrawAxis();
	TLegend *legend1 = new TLegend(0.7,0.7,0.9,0.9,"");
	for(Int_t number = 0;number < 4;number++){
		legend1->AddEntry(hist.at(number),graph[number].c_str(),"lep");
	}
	legend1->Draw();
	c1->SaveAs(title_png.c_str());
	delete c1;
	delete legend1;
	hist.clear();
}

void makeplot(){
	//TFile *tf1 = new TFile("~/dataset/plot2.root");
	//TFile *tf1 = new TFile("~/kayamash/data18_physics_Main_Ztap_hadd.root");
	//string fname = "/gpfs/fs6001/kayamash/Mywork/efficiencyloopoutput/plotadd2.root";
	//string fname = "/gpfs/fs6001/kayamash/Mywork/efficiencyloopoutput/L1MU20plot.root";
	string fname = "/gpfs/fs6001/kayamash/Mywork/efficiencyloopoutput/newdata18_physics_Main_Ztap.root";
	//string fname = "/gpfs/fs6001/kayamash/Mywork/efficiencyloopoutput/newmc16345099.root";
	//string dir = "~/plot/mc16345099/";
	string dir = "~/plot/data18physics_main/";

	Int_t number = 1;
	string graph[8];
	Double_t nbin[4];
	string title_axis;
	string title_png;

	//offline plot
	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 2.5;
	nbin[3] = 300;
	title_axis = "offline phi LargeSpecial;offline phi LargeSpecial;Entries";
	title_png = dir + "offlinephi_LargeSpecial.png";
	draw_hist(fname,"h_offphi_LargeSpecial_0GeV",nbin,title_axis,title_png);

	//L1 plot
	nbin[0] = -2.5;
	nbin[1] = -3.0;
	nbin[2] = 2.5;
	nbin[3] = 3.0;
	title_axis = "L1trigger distribution;offline eta;offline phi";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("L1distribution_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_eff_pSA_etaphi_%dGeV",num*4),nbin,title_axis,title_png);	
	}

	nbin[0] = -2.5;
	nbin[1] = -3.0;
	nbin[2] = 2.5;
	nbin[3] = 3.0;	
	title_axis = "L1 Efficiency;offline eta;offline phi";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("L1Efficiency_%dGeV.png",num*4);
		draw_hist2d(fname,Form("L12DEfficiency_%dGeV",num*4),nbin,title_axis,title_png);	
	}

	//SA plot
/*
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_ALL.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiency_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency Large;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_Large.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLarge_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecial_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial11.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecial11_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial11+.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecialplus11_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial11-.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecialminus11_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial15.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecial15_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial15+.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecialplus15_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency LargeSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_LargeSpecial15-.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencyLargeSpecialminus15_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency Small;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_Small.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencySmall_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency SmallSpecial;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_SmallSpecial.png";
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiencySmallSpecial_%dGeV",num*4);
	}
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiency_barrel_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency@Barrel;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_Barrel.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiency_end_%dGeV",num*4);
	}
	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency@Endcap;offline pt[GeV];efficiency";
	title_png = dir + "SAEfficiency_Endcap.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("SAEfficiency_eta_%dGeV",num*4);
	}
	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 2.5;
	nbin[3] = 1.1;
	title_axis = "SAEfficiency;offline eta;efficiency";
	title_png = dir + "SAEfficiency_eta.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("h_eSA_eta_%dGeV",num*4);
	}
	nbin[0] = -3.0;
	nbin[1] = 0;
	nbin[2] = 3.0;
	nbin[3] = 1000;
	title_png = dir + "SAtrigger_eta.png";
	title_axis = "SAtrigger;offline eta;count";
	draw_allhist(fname,number,graph,nbin,title_axis,title_png);

	nbin[0] = -2.5;
	nbin[1] = -3.0;
	nbin[2] = 2.5;
	nbin[3] = 3.0;
	title_axis = "SA Efficiency;offline eta;offline phi";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAEfficiency_%dGeV.png",num*4);
		draw_hist2d(fname,Form("SA2DEfficiency_%dGeV",num*4),nbin,title_axis,title_png);	
	}
*/

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "Large Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeplus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}
/*
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus11_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialplus11_%dGeV",num*4),nbin,title_axis,title_png);
	}
*/
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus11in_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptplusLargeSpecialplus11in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus11out_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpcialplus11out_%dGeV",num*4),nbin,title_axis,title_png);
	}
/*
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus15_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialplus15_%dGeV",num*4),nbin,title_axis,title_png);
	}
*/
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus15out_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialplus15out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialplus15in_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptplusLargeSpecialplus15in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "Small Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresSmallplus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptSmallplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "SmallSpecial Qeta/|eta|=+1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresSmallSpecialplus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptSmallSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "Large Qeta/|eta|=+-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeminus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeminus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialminus_%dGeV",num*4),nbin,title_axis,title_png);
	}
/*
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus11_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialminus11_%dGeV",num*4),nbin,title_axis,title_png);
	}
*/
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus11in_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptplusLargeSpecialminus11in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus11out_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpcialminus11out_%dGeV",num*4),nbin,title_axis,title_png);
	}
/*
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus15_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialminus15_%dGeV",num*4),nbin,title_axis,title_png);
	}
*/
	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus15out_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptLargeSpecialminus15out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresLargeSpecialminus15in_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptplusLargeSpecialminus15in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "Small Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresSmallminus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptSmallminus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = 0;
	nbin[1] = -2.0;
	nbin[2] = 70;
	nbin[3] = 2.0;
	title_axis = "SmallSpecial Qeta/|eta|=-1;offline pt[GeV];SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAptresSmallSpecialminus_%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_off_ptvsSA_resptSmallSpecialminus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -3.5;
	nbin[1] = 0;
	nbin[2] = 3.5;
	nbin[3] = 4;
	title_axis = "offline phi vs sAddress;offline phi;sAddress";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("sAddress%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offphivsSA_sAddress_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -3.5;
	nbin[1] = -2.0;
	nbin[2] = 3.5;
	nbin[3] = 2.0;
	title_axis = "Large;offline phi;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("Largeres%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offphivsSA_resptLargeplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -3.5;
	nbin[1] = -2.0;
	nbin[2] = 3.5;
	nbin[3] = 2.0;
	title_axis = "LargeSpecial;offline phi;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecialres%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offphivsSA_resptLargeSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -3.5;
	nbin[1] = -2.0;
	nbin[2] = 3.5;
	nbin[3] = 2.0;
	title_axis = "Small;offline phi;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("Smallres%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offphivsSA_resptSmallplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -3.5;
	nbin[1] = -2.0;
	nbin[2] = 3.5;
	nbin[3] = 2.0;
	title_axis = "SmallSpecial;offline phi;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SmallSpecialres%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offphivsSA_resptSmallSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -1.0;
	nbin[1] = 0;
	nbin[2] = 1.0;
	nbin[3] = 300;
	title_axis = "SAresidual Large;L2MuonSA residual pt;Entries";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAresidualLarge%dGeV.png",num*4);
		draw_hist(fname,Form("h_SA_resptLargeplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -1.0;
	nbin[1] = 0;
	nbin[2] = 1.0;
	nbin[3] = 300;
	title_axis = "SAresidual LargeSpecial;L2MuonSA residual pt;Entries";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAresidualLargeSpecial%dGeV.png",num*4);
		draw_hist(fname,Form("h_SA_resptLargeSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -5.0;
	nbin[1] = 0;
	nbin[2] = 5.0;
	nbin[3] = 300;
	title_axis = "SAresidual LargeSpecial;L2MuonSA residual pt;Entries";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAresidualLargeSpecialunzoom%dGeV.png",num*4);
		draw_hist(fname,Form("h_SA_resptLargeSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -1.0;
	nbin[1] = 0;
	nbin[2] = 1.0;
	nbin[3] = 300;
	title_axis = "SAresidual Small;L2MuonSA residual pt;Entries";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAresidualSmall%dGeV.png",num*4);
		draw_hist(fname,Form("h_SA_resptSmallplus_0GeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -1.0;
	nbin[1] = 0;
	nbin[2] = 1.0;
	nbin[3] = 300;
	title_axis = "SAresidual SmallSpecial;L2MuonSA residual pt;Entries";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SAresidualSmallSpecial%dGeV.png",num*4);
		draw_hist(fname,Form("h_SA_resptSmallSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 2.5;
	nbin[3] = 300;
	title_axis = "SAphims LargeSpecial;SAphims;Entries";
	title_png = dir + "SAphims_LargeSpecial.png";
	draw_hist(fname,"h_saphims_LargeSpecial_0GeV",nbin,title_axis,title_png);

	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 2.5;
	nbin[3] = 300;
	title_axis = "SARoIphi LargeSpecial;SARoIphi;Entries";
	title_png = dir + "SARoIphi_LargeSpecial.png";
	draw_hist(fname,"h_saroiphi_LargeSpecial_0GeV",nbin,title_axis,title_png);

	nbin[0] = -10000;
	nbin[1] = -10000;
	nbin[2] = 10000;
	nbin[3] = 10000;
	title_axis = "RPC hit XY;RPC hit X[mm];RPC hit Y[mm]";
	title_png = dir + "RPChitXY.png";
	draw_hist2d(fname,"h_rpchitXvsrpchitY_0GeV",nbin,title_axis,title_png);

	nbin[0] = -25000;
	nbin[1] = -25000;
	nbin[2] = 25000;
	nbin[3] = 25000;
	title_axis = "MDT hit XY;MDT hit X[mm];MDT hit Y[mm]";
	title_png = dir + "MDThitXY.png";
	draw_hist2d(fname,"h_mdthitXvsmdthitY_0GeV",nbin,title_axis,title_png);

	nbin[0] = -10000;
	nbin[1] = -10000;
	nbin[2] = 10000;
	nbin[3] = 10000;
	title_axis = "hit XY;hit X[mm];hit Y[mm]";
	title_png = dir + "hitXY.png";
	string gr[2] = {"h_rpchitXvsrpchitY_0GeV","h_mdthitXvsmdthitY_0GeV"};
	draw_samehist2d(fname,2,gr,nbin,title_axis,title_png);

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "Large;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("Largereseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offetavsSA_resptLargeplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "LargeSpecial;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecialreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offetavsSA_resptLargeSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "Small;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("Smallreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offetavsSA_resptSmallplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "SmallSpecial;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("SmallSpecialreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_offetavsSA_resptSmallSpecialplus_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("highLargeSpecial11outreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_highoffetavsSA_resptLargeSpecialplus11out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("highLargeSpecial11inreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_highoffetavsSA_resptLargeSpecialplus11in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("highLargeSpecial15outreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_highoffetavsSA_resptLargeSpecialplus15out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;offline eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("highLargeSpecial15inreseta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_highoffetavsSA_resptLargeSpecialplus15in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;MDT eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecial11outresmdteta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_mdtetavsSA_resptLargeSpecialplus11out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;MDT eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecial11inresmdteta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_mdtetavsSA_resptLargeSpecialplus11in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;MDT eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecial15outresmdteta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_mdtetavsSA_resptLargeSpecialplus15out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -2.5;
	nbin[1] = -2.0;
	nbin[2] = 2.5;
	nbin[3] = 1.0;
	title_axis = "eta vs residual;MDT eta;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("highLargeSpecial15inresmdteta%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_mdtetavsSA_resptLargeSpecialplus15in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -8.5;
	nbin[1] = -2.0;
	nbin[2] = 8.5;
	nbin[3] = 1.0;
	title_axis = "etaIndex vs residual;etaIndex;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecial11outresetaIndex%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_etaIndexvsSA_resptLargeSpecialplus11out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -8.5;
	nbin[1] = -2.0;
	nbin[2] = 8.5;
	nbin[3] = 1.0;
	title_axis = "etaIndex vs residual;etaIndex;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecial11inresetaIndex%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_etaIndexvsSA_resptLargeSpecialplus11in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -8.5;
	nbin[1] = -2.0;
	nbin[2] = 8.5;
	nbin[3] = 1.0;
	title_axis = "etaIndex vs residual;etaIndex;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("LargeSpecial15outresetaIndex%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_etaIndexvsSA_resptLargeSpecialplus15out_%dGeV",num*4),nbin,title_axis,title_png);
	}

	nbin[0] = -8.5;
	nbin[1] = -2.0;
	nbin[2] = 8.5;
	nbin[3] = 1.0;
	title_axis = "etaIndex vs residual;etaIndex;SApt residual";
	for(Int_t num = 0;num < number;num++){
		title_png = dir + Form("highLargeSpecial15inresetaIndex%dGeV.png",num*4);
		draw_hist2d(fname,Form("h_etaIndexvsSA_resptLargeSpecialplus15in_%dGeV",num*4),nbin,title_axis,title_png);
	}

	//CB plot
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("CBEfficiency_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "CBEfficiency;offline pt[GeV];efficiency";
	title_png = dir + "CBEfficiency_ALL.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("CBEfficiency_barrel_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "CBEfficiency@Barrel;offline pt[GeV];efficiency";
	title_png = dir + "CBEfficiency_Barrel.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("CBEfficiency_end_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_png = dir + "CBEfficiency_Endcap.png";
	title_axis = "CBEfficiency@Endcap;offline pt[GeV];efficiency";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("CBEfficiency_eta_%dGeV",num*4);
	}
	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 2.5;
	nbin[3] = 1.1;
	title_axis = "CBEfficiency;offline eta;efficiency";
	title_png = dir + "CBEfficiency_eta.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("h_eCB_eta_%dGeV",num*4);
	}
	nbin[0] = -3.0;
	nbin[1] = 0;
	nbin[2] = 3.0;
	nbin[3] = 1000;
	title_png = dir + "CBtrigger_eta.png";
	title_axis = "CBtrigger;offline eta;count";
	draw_allhist(fname,number,graph,nbin,title_axis,title_png);

	//EF plot
	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("EFEfficiency_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "EFEfficiency;offline pt[GeV];efficiency";
	title_png = dir + "EFEfficiency_ALL.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("EFEfficiency_barrel_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "EFEfficiency@Barrel;offline pt[GeV];efficiency";
	title_png = dir + "EFEfficiency_Barrel.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("EFEfficiency_end_%dGeV",num*4);
	}
	nbin[0] = -2.0;
	nbin[1] = 0;
	nbin[2] = 81;
	nbin[3] = 1.1;
	title_axis = "EFEfficiency@Endcap;offline pt[GeV];efficiency";
	title_png = dir + "EFEfficiency_Endcap.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("EFEfficiency_eta_%dGeV",num*4);
	}
	nbin[0] = -2.5;
	nbin[1] = 0;
	nbin[2] = 2.5;
	nbin[3] = 1.1;
	title_axis = "EFEfficiency;offline eta;efficiency";
	title_png = dir + "EFEfficiency_eta.png";
	draw_allplot(fname,number,graph,nbin,title_axis,title_png);

	for(Int_t num = 0;num < number;num++){
		graph[num] = Form("h_eEF_eta_%dGeV",num*4);
	}
	nbin[0] = -3.0;
	nbin[1] = 0;
	nbin[2] = 3.0;
	nbin[3] = 1000;
	title_axis = "EFtrigger;offline eta;count";
	title_png = dir + "EFtrigger_eta.png";
	draw_allhist(fname,number,graph,nbin,title_axis,title_png);


}
