#include <iostream>
#include <vector>
#include <string>
#include <TH1F.h>
using namespace std;

void merge_histos()
{
    vector<std::string> names_files {"signal1.root", "signal2.root", "bkg1.root", "bkg2.root", "bkg3.root"};

    vector<std::string> names {"t#bar{t}Z', m(Z')= 350 GeV", "t#bar{t}Z', m(Z')= 1000 GeV", "tth", "t#bar{t}t#bar{t}", "t#bar{t}b#bar{b}/h"};

    vector<std::string> plots {"deltaR_b1b2", "PT_leptons", "ETA_leptons", "PT_b1", "MET", "sdETA_b1b2", "N_Merged", "N_notMerged", "N_partiallyMerged", "N_fullyMerged", "PT_dijet_partially", "ETA_dijet_partially", "M_dijet_partially", "PT_b_dijet_partially", "ETA_b_dijet_partially", "M_b_dijet_partially", "PT_b_dijet_fully", "ETA_b_dijet_fully", "M_b_dijet_fully", "PT_b_not_used", "ETA_b_not_used", "sdPHI_lMET"};

    vector<std::string> plots_names {"#DeltaR(b_{1},b_{2})", "P_{T}(leptons)", "#eta(leptons)", "P_{T}(b_{1})", "MET", "#Delta#eta(b_{1},b_{2})", "Merge Categories", "Not Merged", "Partially Merged", "Fully Merged", "P_{T}(j_{1}j_{2}) Partially Merged", "#eta(j_{1}j_{2}) Partially Merged", "M(j_{1}j_{2}) Partially Merged", "P_{T}(bj_{1}j_{2}) Partially Merged", "#eta(bj_{1}j_{2}) Partially Merged", "M(bj_{1}j_{2}) Partially Merged", "P_{T}(bj_{1}j_{2}) Fully Merged", "#eta(bj_{1}j_{2}) Fully Merged", "M(bj_{1}j_{2}) Fully Merged", "P_{T}(b)- b-quark Not Used in Top Reconstruction", "#eta(b)- b-quark Not Used in Top Reconstruction", "#Delta#phi(lepton,MET)"};

    vector<std::string> x_labels {"#DeltaR(b_{1},b_{2}) [a.u.]", "P_{T}(leptons) [GeV]", "#eta(leptons) [a.u.]", "P_{T}(b_{1}) [GeV]", "MET [GeV]", "#Delta#eta(b_{1},b_{2}) [a.u.]", "Merge Categories", "Not Merged", "Partially Merged", "Fully Merged", "P_{T}(j_{1}j_{2}) [GeV]", "#eta(j_{1}j_{2}) [a.u.]", "M(j_{1}j_{2}) [GeV]", "P_{T}(bj_{1}j_{2}) [GeV]", "#eta(bj_{1}j_{2}) [a.u.]", "M(bj_{1}j_{2}) [GeV]", "P_{T}(bj_{1}j_{2}) [GeV]", "#eta(bj_{1}j_{2}) [a.u.]", "M(bj_{1}j_{2}) [GeV]", "P_{T}(b) [GeV]", "#eta(b) [a.u.]", "#Delta#phi(lepton,MET) [a.u.]"};

    //vector<std::string> plots {"deltaR_b1b2"};

    vector<int> colors {2, 4, 3, 7, 6};

    vector<int> linestyles {10, 9, 1, 1, 1};
    
      
     
    TList *l = new TList();
    for(int i=0; i<plots.size(); i++)
    {
        THStack *hs = new THStack("hs", plots_names[i].c_str());
        TCanvas *c2 = new TCanvas(plots[i].c_str(),"Histos",1280,1024);  
        Double_t x_1,x_2;
        if (plots[i]=="M_dijet_partially" || plots[i]=="M_b_dijet_partially" || plots[i]=="M_b_dijet_fully"){
            x_1 = 0.15;
            x_2 = 0.35;
        }
        else{
            x_1 = 0.65;
            x_2 = 0.85;
        }

        auto legend = new TLegend(x_1,0.65,x_2,0.85);
    for (int j=0; j<names.size(); j++)
    {    
        TFile f(names_files[j].c_str());
        TH1F *h = (TH1F*)f.Get(plots[i].c_str());
        h->SetDirectory(0);
        h->SetLineColor(colors[j]);
        h->SetLineStyle(linestyles[j]);
        h->SetLineWidth(2);
        h->Scale(1.0/h->Integral());
   	legend->AddEntry(h,names[j].c_str(),"l");
        legend->SetBorderSize(0);
        hs->Add(h); 
    }   
        hs->Draw("NOSTACK HIST");
        hs->GetXaxis()->SetTitle(x_labels[i].c_str());
        hs->GetYaxis()->SetTitle("a.u.");
        legend->Draw();
        l->Add(c2);
        std::string filename = plots[i] + ".png";
        c2->SaveAs(filename.c_str());
    }
    TFile* Output = new TFile("joined.root", "RECREATE"); 
    l->Write();
    Output->Close();
       

    
}
