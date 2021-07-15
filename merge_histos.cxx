#include <iostream>
#include <vector>
#include <string>
#include <TH1F.h>
#include <fstream>
using namespace std;

void merge_histos()
{
    //vector<std::string> names_files {"bkg1.root", "bkg2.root", "bkg3.root", "bkg4.root", "signal1.root", "signal2.root", "signal3.root", "signal4.root", "signal5.root", "signal6.root", "signal7.root", "signal8.root"};
    vector<std::string> names_files {"ttbarh.root", "ttbarbbar_noh.root"};

    //vector<std::string> names_files_wo_ext {"$t\\bar{t}h$", "$t\\bar{t}t\\bar{t}$", "$t\\bar{t}b\\bar{b}/h$", "$WWZ$", "$m(Z')=350\\,GeV$", "$m(Z')=500\\,GeV$", "$m(Z')=750\\,GeV$", "$m(Z')=1000\\,GeV$", "$m(Z')=1500\\,GeV$", "$m(Z')=2000\\,GeV$", "$m(Z')=3000\\,GeV$", "$m(Z')=4000\\,GeV$"};
    vector<std::string> names_files_wo_ext {"$t\\bar{t}h$", "$t\\bar{t}b\\bar{b}/h$"};

    //vector<std::string> names {"t#bar{t}h", "t#bar{t}t#bar{t}", "t#bar{t}b#bar{b}/h", "WWZ", "t#bar{t}Z', m(Z')= 350 GeV", "t#bar{t}Z', m(Z')= 500 GeV", "t#bar{t}Z', m(Z')= 750 GeV", "t#bar{t}Z', m(Z')= 1000 GeV", "t#bar{t}Z', m(Z')= 1500 GeV", "t#bar{t}Z', m(Z')= 2000 GeV", "t#bar{t}Z', m(Z')= 3000 GeV", "t#bar{t}Z', m(Z')= 4000 GeV"};
    vector<std::string> names {"t#bar{t}h", "t#bar{t}b#bar{b}/h"};

    vector<std::string> plots {"deltaR_b1b2", "PT_leptons", "ETA_leptons", "PT_b1", "MET", "sdETA_b1b2", "PT_dijet", "N_Merged", "N_notMerged", "N_partiallyMerged", "N_fullyMerged", "PT_dijet_no", "ETA_dijet_no", "M_dijet_no" ,"PT_dijet_partially", "ETA_dijet_partially", "M_dijet_partially", "PT_b_dijet_partially", "ETA_b_dijet_partially", "M_b_dijet_partially", "PT_b_dijet_fully", "ETA_b_dijet_fully", "M_b_dijet_fully", "PT_b_not_used", "ETA_b_not_used", "PT_b_not_used_diff", "ETA_b_not_used_diff", "M_b_not_used_diff", "PT_b_not_used_indiv", "ETA_b_not_used_indiv", "PT_b1b2", "ETA_b1b2", "M_b1b2", "sdPHI_lMET", "Eff_mu", "Eff_e", "Delta_PT_b_alpha_b_beta"};

    vector<std::string> plots_names {"#DeltaR(b_{1},b_{2})", "p_{T}(leptons)", "#eta(leptons)", "p_{T}(b_{1})", "MET", "#Delta#eta(b_{1},b_{2})", "p_{T}(j_{1}j_{2})", "Merge Categories", "Not Merged", "Partially Merged", "Fully Merged", "p_{T}(j_{1}j_{2}) No Merged", "#eta(j_{1}j_{2}) No Merged", "M(j_{1}j_{2}) No Merged" ,"p_{T}(j_{1}j_{2}) Partially Merged", "#eta(j_{1}j_{2}) Partially Merged", "M(j_{1}j_{2}) Partially Merged", "p_{T}(bj_{1}j_{2}) Partially Merged", "#eta(bj_{1}j_{2}) Partially Merged", "M(bj_{1}j_{2}) Partially Merged", "p_{T}(bj_{1}j_{2}) Fully Merged", "#eta(bj_{1}j_{2}) Fully Merged", "M(bj_{1}j_{2}) Fully Merged", "p_{T}(b)- b-quarks Not Used as one TLorentzVector", "#eta(b)- b-quarks Not Used as one TLorentzVector", "p_{T}(b_{#alpha}b_{#beta})", "#eta(b_{#alpha}b_{#beta})", "M(b_{#alpha}b_{#beta})","p_{T}(b)- b-quarks Not Used as individual entities", "#eta(b)- b-quarks Not Used as individual entities", "p_{T}(b_{1}b_{2})", "#eta(b_{1}b_{2})", "M(b_{1}b_{2})", "#Delta#phi(lepton,MET)", "Normalized Number of Events. Final State with l=#mu", "Normalized Number of Events. Final State with l=e", "#Deltap_{T}(b_{#alpha}b_{#beta})"};

    vector<std::string> x_labels {"#DeltaR(b_{1},b_{2}) [a.u.]", "p_{T}(leptons) [GeV]", "#eta(leptons) [a.u.]", "p_{T}(b_{1}) [GeV]", "MET [GeV]", "#Delta#eta(b_{1},b_{2}) [a.u.]", "p_{T}(j_{1}j_{2}) [GeV]", "Merge Categories", "Not Merged", "Partially Merged", "Fully Merged", "p_{T}(j_{1}j_{2}) [GeV]", "#eta(j_{1}j_{2}) [a.u.]", "M(j_{1}j_{2}) [GeV]","p_{T}(j_{1}j_{2}) [GeV]", "#eta(j_{1}j_{2}) [a.u.]", "M(j_{1}j_{2}) [GeV]", "p_{T}(bj_{1}j_{2}) [GeV]", "#eta(bj_{1}j_{2}) [a.u.]", "M(bj_{1}j_{2}) [GeV]", "p_{T}(bj_{1}j_{2}) [GeV]", "#eta(bj_{1}j_{2}) [a.u.]", "M(bj_{1}j_{2}) [GeV]", "p_{T}(b) [GeV]", "#eta(b) [a.u.]", "p_{T}(b_{#alpha}b_{#beta}) [GeV]", "#eta(b_{#alpha}b_{#beta}) [a.u.]","M(b_{#alpha}b_{#beta}) [GeV]","p_{T}(b) [GeV]", "#eta(b) [a.u.]", "p_{T}(b_{1}b_{2}) [GeV]", "#eta(b_{1}b_{2}) [a.u.]","M(b_{1}b_{2}) [GeV]","#Delta#phi(lepton,MET) [a.u.]","Cuts", "Cuts","#Deltap_{T}(b_{#alpha}b_{#beta}) [GeV]"};


    //vector<int> colors {3, 7, 6, 5, 2, 4, 8, 9, 1, 43, 97, 38};
    vector<int> colors {3, 6};

    //vector<int> linestyles {1, 1, 1, 1, 10, 9, 8, 7, 6, 5, 4, 3};
    vector<int> linestyles {1, 1};

    TList *l = new TList();

    for(int i=0; i<plots.size(); i++)
    {
        THStack *hs = new THStack("hs", plots_names[i].c_str());
        TCanvas *c2 = new TCanvas(plots[i].c_str(),"Histos",1280,1024);  
        Double_t x_1,x_2;
        if (plots[i]=="M_dijet_partially" || plots[i]=="M_b_dijet_partially" || plots[i]=="M_b_dijet_fully" || plots[i]=="M_dijet_no" || plots[i]=="M_b_not_used_diff" || plots[i]=="M_b1b2"){
            x_1 = 0.15;
            x_2 = 0.35;
        }

        else if (plots[i]=="M_b_not_used_diff_before" || plots[i]=="M_b1b2_before"){
            x_1 = 0.45;
            x_2 = 0.65;
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

        if( (plots[i]=="N_Merged") || (plots[i]=="Eff_mu") || (plots[i]=="Eff_e") )
        {
          h->SetLineColor(colors[j]);
          h->SetLineStyle(linestyles[j]);
          h->SetLineWidth(2);   
        }

        else
        {
          if( (names_files[j] == "signal1.root") || (names_files[j] == "signal2.root") || (names_files[j] == "signal3.root") || (names_files[j] == "signal4.root") || (names_files[j] == "signal5.root") || (names_files[j] == "signal6.root") || (names_files[j] == "signal7.root") || (names_files[j] == "signal8.root") )
            {  
              h->SetLineColor(colors[j]);
              h->SetLineStyle(linestyles[j]);
              h->SetLineWidth(2);
            }

            else
            {
              h->SetFillColor(colors[j]);
              h->SetFillStyle(1001);
              h->SetLineColor(0);
            }
        }

        h->Scale(1.0/h->Integral());
    
        if( (plots[i]=="N_Merged") || (plots[i]=="Eff_mu") || (plots[i]=="Eff_e") )
        {
          legend->AddEntry(h,names[j].c_str(),"l");   
        }

        else
        {
          if( (names_files[j] == "signal1.root") || (names_files[j] == "signal2.root") || (names_files[j] == "signal3.root") || (names_files[j] == "signal4.root") || (names_files[j] == "signal5.root") || (names_files[j] == "signal6.root") || (names_files[j] == "signal7.root") || (names_files[j] == "signal8.root") )
            {
              legend->AddEntry(h,names[j].c_str(),"l");
            }

            else
            {
              legend->AddEntry(h,names[j].c_str(),"f");
            }
        }
     
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


    ofstream myfile_mu;
    ofstream myfile_e;

    myfile_mu.open ("Eff_mu.txt");
    myfile_e.open ("Eff_e.txt");

    for (int j=0; j<names.size(); j++)
    {    
        TFile f(names_files[j].c_str());
        TH1F *h_mu = (TH1F*)f.Get("Eff_mu");
        TH1F *h_e = (TH1F*)f.Get("Eff_e");
        myfile_mu << names_files_wo_ext[j] << " " << h_mu->GetBinContent(1) << " " << h_mu->GetBinContent(2) << " " << h_mu->GetBinContent(3) << " " << h_mu->GetBinContent(4) << " " << h_mu->GetBinContent(5) << " " << h_mu->GetBinContent(6) << "\n";
        myfile_e << names_files_wo_ext[j] << " " <<  h_e->GetBinContent(1) << " " << h_e->GetBinContent(2) << " " << h_e->GetBinContent(3) << " " << h_e->GetBinContent(4) << " " << h_e->GetBinContent(5) << " " << h_e->GetBinContent(6) << "\n";
    } 
    
    myfile_mu.close();
    myfile_e.close();


       

    
}
